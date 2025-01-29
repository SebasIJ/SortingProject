#include "ofApp.h"
#include "vector"

//Sources used:		https://www.w3schools.com/dsa/dsa_data_arrays.php
//					https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/

std::vector<int> Numbers(5); //array containing the radius oof every circle
int numSize; //size of the array

void ArrayRandomizer() {

	//goes through the array and assigns a random number from 10 to 100
	for (int i = 0; i < Numbers.size(); i++) {

		Numbers[i] = rand() % (90 +1);
		Numbers[i] += 10;
	}
	
}

void BubbleSort() {

	//external loop to go through the sorting for the lenght of the array
	for (int i = 0; i < numSize - 1; i++) {

		//internal loop compares current value with the next value
		for (int j = 0; j < numSize - i - 1; j++) {

			//if the current value is larger than the next value they swap position
			if (Numbers[j] > Numbers[j + 1]) {

				int hold = Numbers[j];
				Numbers[j] = Numbers[j + 1];
				Numbers[j + 1] = hold;

			}

		}

	}

}

void InsertionSort() {

	//goes through the array value by value
	for (int i = 0; i < numSize; i++) {

		//gets the current value, its index and the previous index
		int index = i;
		int currentNum = Numbers[i];
		int checkIndex = i - 1;

		//compares current number to all previous indexes
		//does not run for first value (when previous index is out of range)
		while (checkIndex >= 0 && Numbers[checkIndex] > currentNum)
		{
			//while loop finds proper index for value
			Numbers[checkIndex + 1] = Numbers[checkIndex];
			index = checkIndex;
			checkIndex--;
		}

		//places value in proper index
		Numbers[index] = currentNum;
	}

}

void Merge(int start, int middle, int end) {

	int i, j, k; //index values to be used, i for first half, j for second half and k for main array
	int n1 = middle - start + 1; //size of the first half
	int n2 = end - middle; //size of the second half 

	std::vector<int> left(n1), right(n2);

	//assigns the corresponding values to the subarrays
	for (i = 0;i < n1; i++) {
		left[i] = Numbers[start + i];
	}
	for (j = 0;j < n2; j++) {
		right[j] = Numbers[middle + 1 + j];
	}

	//resets index variables
	i = 0;
	j = 0;
	k = start;

	//compares values in both subarrays and assigns them to main array until one subarray runs out of values
	//index only advances when a value is assigned to the main array
	while (i < n1 && j < n2) {

		if (left[i] <= right[j]) {
			Numbers[k] = left[i];
			i++;
		}
		else {
			Numbers[k] = right[j];
			j++;
		}
		k++;

	}

	//remaining values from subarray that did not go fully through are assigned to next spots on main array
	while (i < n1)
	{
		Numbers[k] = left[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		Numbers[k] = right[j];
		j++;
		k++;
	}

}

void MergeSort(int start, int end) {

	//if start is less than end the array can be further divided
	if (start < end) {

		//finds the middle point of the array
		int middle = (start + end) / 2;

		//verifies if both halves can be further divided by calling the same method
		MergeSort(start, middle);
		MergeSort(middle + 1, end);

		//sorts the array based on both halves
		Merge(start, middle, end);

	}

}

int QuickPivot(int lower, int higher) {

	//the last value is the starting pivot
	int pivot = Numbers[higher];
	int i = lower - 1;

	//goes through the array in the current subdivision
	for (int j = lower; j < higher; j++) {

		//compares the current value with the value of the pivot
		if (Numbers[j] <= pivot) {

			//swaps values of position i and j and increases i index if value is smaller or equal than pivot
			i++;
			int hold = Numbers[i];
			Numbers[i] = Numbers[j];
			Numbers[j] = hold;

		}

	}

	//places value of the pivot at the end of the newly arranged array section
	int hold = Numbers[i + 1];
	Numbers[i + 1] = Numbers[higher];
	Numbers[higher] = hold;
	return i + 1; //returns the new pivot index to proceed with next subdivision

}

void QuickSort(int lower, int higher) {

	//subdivides the array based on a pivot starting with the last value
	if (lower < higher) {

		//gets last sorting pivot
		int pivotIndex = QuickPivot(lower, higher);

		//calls same function around the pivot index
		QuickSort(lower, pivotIndex - 1);
		QuickSort(pivotIndex + 1, higher);

	}

}

void ShuffleArray() {

	//goes through the array in reverse
	for (int i = numSize - 1; i > 0; i--) {

		//picks a random number within the array boundaries
		int j = rand() % (i + 1);

		//swaps the current value with the valuee in the random position
		int hold = Numbers[i];
		Numbers[i] = Numbers[j];
		Numbers[j] = hold;

	}

}


//--------------------------------------------------------------
void ofApp::setup(){
	//randomizes values and gets array size when the program starts
	ArrayRandomizer();
	numSize = Numbers.size();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	int x = 100; //x position of the circles starting at 100
	int radiusTotal=0; //cummulative radius of all the circles

	//goes through the array
	for (int i = 0; i < Numbers.size(); i++) {
		
		//draws a circle with radius of the current array value
		//cummulative radius is added to x position to ensure circles are spread from each other
		ofDrawCircle(x + radiusTotal, 100, Numbers[i]);
		//writes radius size below circle
		ofDrawBitmapString(Numbers[i], x + radiusTotal - 5, 250);

		//adds current radius to total and increases x for next circle
		radiusTotal += Numbers[i];
		x += 100;
	}

	//writes all available options with their respective keyboard key
	ofDrawBitmapString("R: Generate", 100, 350);
	ofDrawBitmapString("B: Bubble Sort", 100, 375);
	ofDrawBitmapString("I: Insertion Sort", 100, 400);
	ofDrawBitmapString("M: Merge Sort", 100, 425);
	ofDrawBitmapString("Q: Quick Sort", 100, 450);
	ofDrawBitmapString("S: Shuffle", 100, 475);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//switch case that checks for the pressed key
	//all cases call their respective function as well as the draw function to refresh the screen
	switch (key)
	{
	case 'R':
	case 'r':
		ArrayRandomizer();
		draw();
		break;

	case 'B':
	case 'b':
		BubbleSort();
		draw();
		break;

	case 'I':
	case 'i':
		InsertionSort();
		draw();
		break;

	case 'M':
	case 'm':
		MergeSort(0, numSize - 1);
		draw();
		break;

	case 'Q':
	case 'q':
		QuickSort(0, numSize - 1);
		draw();
		break;

	case 'S':
	case 's':
		ShuffleArray();
		draw();
		break;

	default:
		break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
