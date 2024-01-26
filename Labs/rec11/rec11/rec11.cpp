/*
Kevin Grajeda
rec11
Linked Lists
*/

#include <vector>
#include <iostream>
using namespace std;

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node * next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

void listDisplay(Node* headPtr) {
	Node* p = headPtr;
	while (p != nullptr) {
		cout << p->data << ' ';
		p = p->next;  // bump
	}
	cout << endl;
}

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
	while (headPtr) {
		Node* next = headPtr->next;
		delete headPtr;
		headPtr = next;
	}
}
void splice(Node* addedListPtr, Node* targetPtr) {
	if (targetPtr == nullptr) {
		targetPtr = addedListPtr;
		return;
	}
	if (addedListPtr == nullptr) {
		return;
	}
	Node* next = targetPtr->next;
	targetPtr->next = addedListPtr;
	while(addedListPtr->next != nullptr){
		addedListPtr = addedListPtr->next;
	}
	addedListPtr->next = next;
}

Node* isSublist(Node* LookingIn, Node* LookingFor) {
	if (LookingFor == nullptr || LookingIn == nullptr) {
		cout << "List searching/for is empty" << endl;
		return nullptr;
	}
	Node* searchIn = LookingIn;
	Node* firstNode = LookingFor;
	while (searchIn != nullptr) {
		Node* track = searchIn;
		LookingFor = firstNode;
		if (searchIn->data == LookingFor->data) {
			Node* result = searchIn;
			while (searchIn->data == LookingFor->data) {
				searchIn = searchIn->next;
				LookingFor = LookingFor->next;
				if (LookingFor == nullptr) {
					return result;
				}
				if (searchIn == nullptr) {
					cout << "Failed to Match";
					return nullptr;
				}
			}
			searchIn = searchIn->next;
			LookingFor = LookingFor->next;
		}
		searchIn = track->next;
	}
	cout << "Failed to Match";
	return nullptr;
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listAddHead(result, vals[index - 1]);
	}
	return result;
}

int main() {
	Node* list1 = listBuild({ 5,7,9,1 });
	Node* list2 = listBuild({ 6,3,2 });

	cout << "Part One: " << endl;
	cout << "L1: ";
	listDisplay(list1);
	cout << "L2: ";
	listDisplay(list2);

	cout << "Splicing L2 at target in L1: " << endl;
	splice(list2, list1->next);

	listDisplay(list1);
	listDisplay(list2);
	cout << endl;

	cout << "==============================" << endl;
	cout << "Part Two: " << endl;

	Node* list3 = listBuild({ 1, 2, 3, 2, 3, 2, 4, 5, 6 });
	Node* list4 = listBuild({ 1 });
	Node* list5 = listBuild({ 3,9 });
	Node* list6 = listBuild({ 2,3 });
	Node* list7 = listBuild({ 2,4,5,6 });
	Node* list8 = listBuild({ 2,3,2,4 });
	Node* list9 = listBuild({ 5,6,7 });
	Node* list10 = listBuild({ 6 });

	cout << "Target: ";
	listDisplay(list3);
	cout << endl;

	cout << "Attempt Match: ";
	listDisplay(list4);
	listDisplay(isSublist(list3, list4));
	cout  << endl;

	cout << "Attempt Match: ";
	listDisplay(list5);
	listDisplay(isSublist(list3, list5));
	cout << endl;

	cout << "Attempt Match: ";
	listDisplay(list6);
	listDisplay(isSublist(list3, list6));
	cout <<  endl;

	cout << "Attempt Match: ";
	listDisplay(list7);
	listDisplay(isSublist(list3, list7));
	cout <<  endl;

	cout << "Attempt Match: ";
	listDisplay(list8);
	listDisplay(isSublist(list3, list8));
	cout <<  endl;

	cout << "Attempt Match: ";
	listDisplay(list9);
	listDisplay(isSublist(list3, list9));
	cout << endl;

	cout << "Attempt Match: ";
	listDisplay(list10);
	listDisplay(isSublist(list3, list10));
	cout << endl;

	listClear(list1);
	listClear(list3);
	listClear(list4);
	listClear(list5);
	listClear(list6);
	listClear(list7);
	listClear(list8);
	listClear(list9);
	listClear(list10);

}