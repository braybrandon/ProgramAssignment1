#include <iostream>
#include <cstdlib>
#include<ctime>

typedef int element;

const int MLS = 50;
const int SENTINEL = -1;

using namespace std;

class AList {

public:

	void read();
	void GenerateRandomList();
	void Print();
	void swap(int pos1, int pos2);
	void BubbleSort();
	void InsertionSort();
	void SelectionSort();
	void LinearSearch(element target, bool & found, int & position);
	void BinarySearch(element target, bool & found, int & position);

	element read_element();
	element CheckRange(element low, element high);

private:

	element size;
	element items[MLS];
	//bool ordered;
};

int main() {
	//seeds the random number generator
	srand(int(time(0)));
	int nowhere;
	AList A;
	A.GenerateRandomList();
	A.Print();
	cin >> nowhere;
	return 0;
}



void AList::read() {

	// PRE: none

	//POST: the Native Object (N.O.) AList is now valid, holding elements provided by the user

	//create a temperary element to hold user input
	element userval;
	
	//sets the size of the list to 0
	size = 0; 
	
	//Ask the user to input the elements the want to be in the list
	cout << "Enter elements, " << SENTINEL << " to stop: ";

	//calls the read_element function to initialize userval
	userval = read_element();
	//loops until user wants to stop or the list is full
	while (userval != SENTINEL && size < MLS) {
		
		//initializes the list at size position to the userval
		items[size] = userval;
		//increases the size of the list by 1
		size++;
		//if the size of list is less than the Maximum list size then read another element
		if (size < MLS)
			userval = read_element();
		//Let the user know the list is full
		else
			cout << "List is now full, ending input" << endl;
	}
}

void AList::GenerateRandomList() {

	element high;
	element low;
	cout << "Ressetting the current list using randomly generated elements" << endl;

	cout << "Enter the desired number of elements (0 ti 50): ";
	size = CheckRange(0, MLS);

	cout << "Enter the lower limit of the range: ";
	low = read_element();

	cout << "Enter the upper limit of the range: ";
	high = read_element();

	for (int i = 0; i < size; i++) {
		items[i] = rand() % (high - low + 1) + low;
	}
}

void AList::Print() {
	for (int i = 0; i < size; i++)
		cout << items[i] << ", ";
}

void AList::swap(int pos1, int pos2) {

	//PRE:	the N.O. AList is valid
	//		0 <= pos1 < size
	//		0 <= pos2 < size

	//POST:	the N.O. AList is unchanged, except that
	//		the two elements previously in positions
	//		pos1 and pos2 have been swapped

	element temp;
	temp = items[pos1];
	items[pos1] = items[pos2];
	items[pos2] = temp;

}

void AList::BubbleSort() {

	//PRE:	the N.O. AList is valid

	//POST:	the N.O. AList is unchanged, except that
	//		its elements are now in ascending order

	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - 1 - i; j++)
			if (items[j] > items[j + 1])
				swap(j, j + 1);
			else
				;
	
}

void AList::InsertionSort() {
	//Pre:	the N.O. AList is valid

	//Post:	the N.O. is unchanged, except that 
	//		its elements are now in ascending order

	int j;
	bool done;

	for (int i = 1; i < size; i++) {

		j = i;
		done = false;

		while (j >= 1 && !done) {
			if (items[j] < items[j - 1]) {
				swap(j, j - 1);
				j--;
			}
			else
				done = true;
		}
	}
}

void AList::SelectionSort() {

	//Pre:	the N.O. AList is valid

	//Post:	the N.O. is unchanged, except that 
	//		its elements are now in ascending order

	int maxpos;

	for (int i = size - 1; i > 0; i--) {
		maxpos = 0;
		for (int j = 1; j <= i; j++) {
			if (items[j] > items[maxpos])
				maxpos = j;
			else
				;
			swap(maxpos, i);
		}
	}
}

void AList::LinearSearch(element target, bool & found, int & position) {

	//Pre:	the N.O is  valid

	//Post:	the N.O. AList is unchanged, and 
	//		if target exists on the N.O. AList:
	//			found will be true, and position will be
	//			a location of the target on the N.O AList
	//		otherwise
	//			found will be false and position will be undefined

	found = false;
	position = 0;
	while (!found && position < size) {
		if (target == items[position])
			found = true;
		else
			position++;
	}

}

void AList::BinarySearch(element target, bool & found, int & position) {
	//Pre:	the N.O is  valid

	//Post:	the N.O. AList is unchanged, and 
	//		if target exists on the N.O. AList:
	//			found will be true, and position will be
	//			a location of the target on the N.O AList
	//		otherwise
	//			found will be false and position will be undefined

	int low;
	int high;
	int mid;

	low = 0;
	high = size - 1;
	found = false;

	while (!found && low <= high) {
		mid = (low + high) / 2;
		if (target == items[mid]) {
			found = true;
			position = mid;
		}
		else if (target < items[mid])
			high = mid - 1;
		else low = mid + 1;
	}
}

element AList::read_element() {

	//PRE:	the user must enter a series of zero
	//		or more non-valid element values,
	//		fallowed by a valid element value

	//POST: all entered non-valid element values
	//		will be successfully discarded, and 
	//		the first valid element value entered
	//		will be returned

	element userval;

	cin >> userval;
	while (cin.fail()) {

		cin.clear();
		cin.ignore(80, '\n');
		cout << "Invalid data type, should be an element, "
			<< "try again: ";
		cin >> userval;
	}
	return userval;
}

element AList::CheckRange(element low, element high) {
	
	element userval;
	userval = read_element();
	while (userval < low || userval > high) {

		cout << "Response must be between " << low << " and " << high << ", try again: ";
		
		userval = read_element();
	}
	return userval;
}