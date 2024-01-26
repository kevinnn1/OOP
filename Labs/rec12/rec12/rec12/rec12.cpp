//Kevin Grajeda
//rec12.cpp
//Linked Lists

// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
	friend ostream& operator<<(ostream& os, List list) {
		Node* cursor = list.header;
		cursor = cursor->next;
		for (size_t i = 0; i < list.size(); ++i) {
			cout << cursor->data << " ";
			cursor = cursor->next;
		}
		return os;
	}
public:
	struct Node;
	class Iterator {
		friend class List;
		friend bool operator==(Iterator lhs, Iterator rhs)  {
			return lhs.node == rhs.node;
		}
		friend bool operator!=(Iterator lhs, Iterator rhs)  {
			return !(lhs == rhs);
		}
	public:
		Iterator(Node* ptr) : node(ptr) {}
		Iterator& operator++() {
			node = node->next;
			return *this;
		}
		Iterator& operator--() {
			node = node->prior;
			return *this;
		}
		int& operator*() { return node->data; }
		Node* getNode() const { return node; }
	private:
		Node* node;
	};
	List() : listSize(0) {
		header = new Node(0, trailer, nullptr);
		trailer = new Node(0, nullptr, header);
	}
	Iterator insert(const Iterator& iter, int data)  {
		Node* nodeAfter = iter.getNode();
		Node* nodeToInsert = new Node(data, nodeAfter, nodeAfter->prior);
		nodeToInsert->prior->next = nodeToInsert;
		nodeToInsert->next->prior = nodeToInsert;
		++listSize;
		return Iterator(nodeToInsert);
	}
	Iterator erase(const Iterator& iter) {
		Iterator returned = iter.getNode()->next;
		Node* victim = iter.getNode();
		victim->next->prior = victim->prior;
		victim->prior->next = victim->next;
		delete victim;
		--listSize;
		return returned;
	}
	void push_back(int data) {
		Node* next = new Node(data, trailer, trailer->prior);
		trailer->prior->next = next;
		trailer->prior = next;
		++listSize;
	}
	void pop_back() {
		Node* victim = trailer->prior;
		trailer->prior = trailer->prior->prior;
		trailer->prior->next = trailer;
		delete victim;
		--listSize;
	}
	void push_front(int data) {
		Node* next = new Node(data, header->next, header);
		header->next->prior = next;
		header->next = next;
		++listSize;
	}
	void pop_front() {
		Node* victim = header->next;
		header->next = header->next->next;
		header->next->prior = header;
		delete victim;
		--listSize;
	}

	int operator[](const size_t index) const {
		if (index <= listSize) {
			int count = 0;
			for (List::Iterator iter = begin(); iter != end(); ++iter) {
				if (count == index) {
					return *iter;
				}
				count++;
			}
		}
		else {
			cout << "Index out of range" << endl;
			exit(0);
		}
	}
	int& operator[](const size_t index) {
		if (index <= listSize) {
			int count = 0;
			for (List::Iterator iter = begin(); iter != end(); ++iter) {
				if (count == index) {
					return *iter;
				}
				count++;
			}
		}
		else {
			cout << "Index out of range" << endl;
			exit(0);
		}
	}
	// [] operator without iterators
	/*
	int operator[](const size_t index) const {
		if (index <= listSize) {
			Node* current = header;
			for (size_t i = 0; i <= index; ++i) {
				current = current->next;
			}
			int data = current->data;
			return current->data;
		}
		else {
			cout << "Index out of range" << endl;
			exit(0);
		}
	}
	int& operator[](const size_t index) {
		if (index <= listSize) {
			Node* current = header;
			for (size_t i = 0; i <= index; ++i) {
				current = current->next;
			}
			return current->data;
		}
		else {
			cout << "Index out of range" << endl;
			exit(0);
		}
	}
	*/

	int size() const { return listSize; }
	const int& front() const { return header->next->data; }
	int& front() { return header->next->data; }
	const int& back() const { return trailer->prior->data; }
	int& back() { return trailer->prior->data; }
	Iterator begin() const { return Iterator(header->next); }
	Iterator end() const { return Iterator(trailer); }

	void clear() {
		Node* current = header->next;
		header->next = trailer;
		trailer->prior = header;
		int size = listSize;
		for (size_t i = 0; i < size; ++i) {
			Node* victim = current->next;
			delete current;
			current = victim;
			--listSize;
		}		
	}
private:
	struct Node {
		Node(int data = 0, Node * next = nullptr, Node * prior = nullptr)
			: data(data), next(next), prior(prior) {}
		int data;
		Node* next;
		Node* prior;
	};
	size_t listSize;
	Node* header;
	Node* trailer;
	
};

// Task 1
void printListInfo(const List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList) {
	theList.front() = 17;
	theList.back() = 42;
}


// Task 4
void printListSlow(const List& myList) {
	for (size_t i = 0; i < myList.size(); ++i) {
		cout << myList[i] << ' ';
	}
	cout << endl;
}
/*
// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}
*/
int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";

	cout << "Modify the first and last items, and display the results\n";
	changeFrontAndBack(myList);
	printListInfo(myList);
	cout << "===================\n";

	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	// Task 2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i * i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";
	
	// Task 3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i * i);
	}
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";

	// Task 4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Now calling a function, printListSlow, to do the same thing\n";
	printListSlow(myList);
	cout << "Finally, for this task, using the index operator to modify\n"
		<< "the data in the third item in the list\n"
		<< "and then using printListSlow to display it again\n";
	myList[2] = 42;
	printListSlow(myList);
	
	
	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i * i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	// Note you can choose to nest the iterator class or not, your choice.
	//for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
	for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";
	
	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);

	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
	printListInfo(myList);

	// ***Need test for insert other than begin/end***
	cout << "===================\n";
	
	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";
	/*
	// Task 8
	cout << "\n------Task Eight------\n";
	cout << "Copy control\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
	printListInfo(myList);
	cout << "Calling doNothing(myList)\n";
	doNothing(myList);
	cout << "Back from doNothing(myList)\n";
	printListInfo(myList);

	cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	List listTwo;
	for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i * i);
	printListInfo(listTwo);
	cout << "listTwo = myList\n";
	listTwo = myList;
	cout << "myList: ";
	printListInfo(myList);
	cout << "listTwo: ";
	printListInfo(listTwo);
	cout << "===================\n";
	*/
}
