#include <iostream>
#include <cstdlib>
#include<ctime>

typedef int element;

const int MLS = 50;
const int SENTINEL = -1;

using namespace std;

class AList {

public:
	AList();
	void GetMenu();
	void executeMenu(int userval);
	void read();
	void GenerateRandomList();
	void Print();
	void swap(int pos1, int pos2);
	void BubbleSort();
	void InsertionSort();
	void SelectionSort();
	void LinearSearch();
	void BinarySearch();


	element read_element();
	element CheckRange(element low, element high);

	bool GetQuit();

private:
	element size;
	element items[MLS];

	bool ordered;
	bool quit;
};


int main() {

	//seeds the random number generator
	srand(int(time(0)));

	int userval;
	AList A;

	while (!A.GetQuit()) {
		A.Print();
		A.GetMenu();
		userval = A.CheckRange(1, 8);
		A.executeMenu(userval);

	}
	return 0;
}


AList::AList() {
	ordered = true;
	quit = false;
	size = 0;
}

void AList::GetMenu() {

	cout << endl << "Actions:" << endl;
	cout << "\t" << "1." << "\t" << "Reset the current list from the keyboard" << endl;
	cout << "\t" << "2." << "\t" << "Reset the current list using randomly generated elements" << endl;
	cout << "\t" << "3." << "\t" << "Perform Bubble Sort on the current list" << endl;
	cout << "\t" << "4." << "\t" << "Perform Insertion Sort on the current list" << endl;
	cout << "\t" << "5." << "\t" << "Perform Selection Sort on the current list" << endl;
	cout << "\t" << "6." << "\t" << "Perform Linear Search on the current list" << endl;
	cout << "\t" << "7." << "\t" << "Perform Binary Search on the current list" << endl;
	cout << "\t" << "8." << "\t" << "Quit the program" << endl;
	cout << endl << "Choose an action: ";
}

void AList::executeMenu(int userval) {

	switch (userval) {
	case 1:
		read();
		break;
	case 2:
		GenerateRandomList();
		break;
	case 3:
		BubbleSort();
		break;
	case 4:
		InsertionSort();
		break;
	case 5:
		SelectionSort();
		break;
	case 6:
		LinearSearch();
		break;
	case 7:
		if (ordered)
			BinarySearch();
		else
			cout << endl << "Sorry, since the current list is not know to be ordered, the Binary Search" << endl
			<< "cannot be performed at this time. Please sort the current list first." << endl;
		break;
	default:
		quit = true;
		break;
	}
}

void AList::read() {

	// PRE: none

	//POST: the Native Object (N.O.) AList is now valid, holding elements provided by the user
	//create a temperary element to hold user input

	element userval;

	ordered = false;

	//sets the size of the list to 0
	size = 0;

	cout << endl << "Resetting the current list from the keyboard." << endl;

	//Ask the user to input the elements the want to be in the list
	cout << endl << "Enter a series of elements, " << SENTINEL << " to stop: ";

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

	ordered = false;

	element high;
	element low;

	cout << endl << "Ressetting the current list using randomly generated elements" << endl;

	cout << endl << "Enter the desired number of elements (0 t0 50): ";
	size = CheckRange(0, MLS);

	cout << endl << "Enter the lower limit of the range: ";
	low = read_element();

	cout << "Enter the upper limit of the range: ";
	high = read_element();

	for (int i = 0; i < size; i++)
		items[i] = rand() % (high - low + 1) + low;

}

void AList::Print() {

	cout << endl << "Current list: ";

	if (size == 0)
		cout << "\t(empty)";
	else
		for (int i = 0; i < size; i++)
			cout << items[i] << ", ";
	if (ordered)
		cout << "\t" << "(KNOWN to be ordered)" << endl;
	else
		cout << "\t" << "(Not KNOWN to be ordered)" << endl;

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

	cout << endl << "Performing Bubble Sort on the current list." << endl;

	ordered = true;
	int emoved;
	int moved;
	int ecompared;
	int compared;

	ecompared = (size *size - size) / 2;
	moved = 0;
	emoved = 3 * ecompared;
	compared = 0;

	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - 1 - i; j++) {
			if (items[j] > items[j + 1]) {
				swap(j, j + 1);
				moved += 3;
			}
			else
				;
			compared++;
		}
	cout << endl << "Theoretical sort statistics:\t" << ecompared << " element comparisons, " << emoved << " element movements" << endl;
	cout << "Actual sort statistics:\t\t" << compared << " element comparisons, " << moved << " element movements" << endl;
	cout << endl << "Finishing Bubble Sort." << endl;
}

void AList::InsertionSort() {

	//Pre:	the N.O. AList is valid

	//Post:	the N.O. is unchanged, except that 
	//		its elements are now in ascending order

	cout << endl << "Performing Insertion Sort on the current list." << endl;

	ordered = true;

	int j;
	int emoved;
	int ecompared;
	int moved;
	int compared;
	bool done;

	moved = 0;
	compared = 0;

	ecompared = (size *size - size) / 2;
	emoved = 3 * ecompared;

	for (int i = 1; i < size; i++) {
		j = i;
		done = false;
		while (j >= 1 && !done) {
			if (items[j] < items[j - 1]) {
				swap(j, j - 1);
				j--;
				moved += 3;
			}
			else
				done = true;
			compared++;
		}
	}
	cout << endl << "Theoretical sort statistics:\t" << ecompared << " element comparisons, " << emoved << " element movements" << endl;
	cout << "Actual sort statistics:\t\t" << compared << " element comparisons, " << moved << " element movements" << endl;
	cout << endl << "Finishing Insertion Sort." << endl;
}

void AList::SelectionSort() {

	//Pre:	the N.O. AList is valid

	//Post:	the N.O. is unchanged, except that 
	//		its elements are now in ascending order

	cout << endl << "Performing Selection Sort on the current list." << endl;

	ordered = true;
	int compared;
	int ecompared;
	int moved;
	int emoved;
	int maxpos;

	compared = 0;
	moved = 0;

	ecompared = (size *size - size) / 2;
	emoved = (size - 1) * 3;

	for (int i = size - 1; i > 0; i--) {

		maxpos = 0;
		for (int j = 1; j <= i; j++) {
			if (items[j] > items[maxpos])
				maxpos = j;
			else
				;
			compared++;
		}
		swap(maxpos, i);
		moved += 3;
	}
	cout << endl << "Theoretical sort statistics:\t" << ecompared << " element comparisons, " << emoved << " element movements" << endl;
	cout << "Actual sort statistics:\t\t" << compared << " element comparisons, " << moved << " element movements" << endl;
	cout << endl << "Finishing Selection Sort." << endl;
}

void AList::LinearSearch() {

	//Pre:	the N.O is  valid

	//Post:	the N.O. AList is unchanged, and 
	//		if target exists on the N.O. AList:
	//			found will be true, and position will be
	//			a location of the target on the N.O AList
	//		otherwise
	//			found will be false and position will be undefined

	cout << endl << "Performing Linear Search on the current list." << endl;

	element target;
	cout << endl << "Enter a target element to search for: ";
	target = read_element();

	bool found;
	int position;
	int ecompared;
	int compared;

	ecompared = size;
	compared = 0;

	found = false;
	position = 0;
	while (!found && position < size) {
		if (target == items[position])
			found = true;
		else
			position++;
		compared++;
	}

	if (found)
		cout << endl << "The target was FOUND on the current list in position " << position << "." << endl;
	else
		cout << endl << "The target was NOT FOUND" << endl;

	cout << endl << "Theoretical search statistics:\t" << ecompared << " element comparisons" << endl;
	cout << "Actual search statistics:\t" << compared << " element comparisons." << endl;
	cout << endl << "Finishing Linear Search." << endl;
}
void AList::BinarySearch() {

	//Pre:	the N.O is  valid

	//Post:	the N.O. AList is unchanged, and 
	//		if target exists on the N.O. AList:
	//			found will be true, and position will be
	//			a location of the target on the N.O AList
	//		otherwise
	//			found will be false and position will be undefined

	cout << endl << "Performing Binary Search on the current list." << endl;

	element target;
	cout << endl << "Enter a target element to search for: ";
	target = read_element();

	bool found;

	int compared;
	int ecompared;
	int position;
	int low;
	int high;
	int mid;

	ecompared = 2 * log2(size);
	compared = 0;
	low = 0;
	high = size - 1;
	found = false;

	while (!found && low <= high) {
		mid = (low + high) / 2;
		if (target == items[mid]) {
			found = true;
			position = mid;
		}
		else if (target < items[mid]) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
		compared++;
	}
	if (found)
		cout << endl << "The target was FOUND on the current list in position " << position << "." << endl;
	else
		cout << endl << "The target was NOT FOUND" << endl;

	cout << endl << "Theoretical search statistics:\t" << ecompared << " element comparisons" << endl;
	cout << "Actual search statistics:\t" << compared << " element comparisons." << endl;
	cout << endl << "Finishing Binary Search." << endl;
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

bool AList::GetQuit() {
	return quit;
}