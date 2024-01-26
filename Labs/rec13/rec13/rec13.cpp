// Kevin Grajeda
// rec13.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void printList(const list<int>& intList) {
	for (list<int>::const_iterator i = intList.begin(); i != intList.end(); ++i) {
		cout << *i << " ";
	}
}
void printListRanged(const list<int>& intList) {
	for (int x : intList) {
		cout << x << " ";
	}
}
list<int>::const_iterator findInt(const list<int>& intList, int search) {
	for (list<int>::const_iterator i = intList.begin(); i != intList.end(); ++i) {
		if (*i == search) {
			return i;
		}
	}
	return intList.end();
}
auto findIntAuto(const list<int>& intList, int search) {
	for (auto i = intList.begin(); i != intList.end(); ++i) {
		if (*i == search) {
			return i;
		}
	}
	return intList.end();
}
bool isEven(int integer) {
	return integer % 2 == 0;
}
list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator stop, int search) {
	for (list<int>::iterator i = start; i != stop; ++i) {
		if (*i == search) {
			return i;
		}
	}
	return stop;
}
template <typename T, typename U>
T ourFind(T start, T stop, U search) {
	cout << "Template used" << endl;
	for (T i = start; i != stop; ++i) {
		if (*i == search) {
			return i;
		}
	}
	return stop;
}
class Even {
public:
	bool operator() (int integer) {
		return integer % 2 == 0;
	}
};

int main() {
	// 1. Create a vector with some values and display using ranged for
	cout << "Task 1:\n";
	vector<int> vectorInt = { 2, 4, 1, 5, 3, 7, 6, 9, 10, 8 };
	for (int x : vectorInt) {
		cout << x << " ";
	}
	cout << "\n=======\n"; 

	// 2. Initalize a list as a copy of values from the vector
	cout << "Task 2:\n";
	list<int> listInt(vectorInt.begin(), vectorInt.end());
	for (int x : listInt) {
		cout << x << " ";
	}
	cout << "\n=======\n";

	// 3. Sort the original vector.  Display both the vector and the list
	cout << "Task 3:\n";
	sort(vectorInt.begin(), vectorInt.end());
	for (int x : vectorInt) {
		cout << x << " ";
	}
	cout << endl;
	for (int x : listInt) {
		cout << x << " ";
	}
	cout << "\n=======\n";

	// 4. print every other element of the vector.
	cout << "Task 4:\n";
	for (size_t i = 0; i < vectorInt.size(); i = i+2) {
		cout << vectorInt[i] << " ";
	}
	cout << "\n=======\n";

	// 5. Attempt to print every other element of the list using the
	//    same technique.
	cout << "Task 5:\n";
	//for (size_t i = 0; i < listInt.size(); i = i + 2) {
	//	cout << listInt[i] << " ";
	//}
	cout << "\n=======\n";

	//
	// Iterators
	//

	// 6. Repeat task 4 using iterators.  Do not use auto;
	cout << "Task 6:\n";
	for (vector<int>::iterator i = vectorInt.begin(); i != vectorInt.end(); i = i + 2) {
		cout << *i << " ";
	}
	cout << "\n=======\n";

	// 7. Repeat the previous task using the list.  Again, do not use auto.
	//    Note that you cannot use the same simple mechanism to bump
	//    the iterator as in task 6.
	cout << "Task 7:\n";
	for (list<int>::iterator i = listInt.begin(); i != listInt.end(); ++i) {
		cout << *i++ << " ";
	}
	cout << "\n=======\n";

	// 8. Sorting a list
	cout << "Task 8:\n";
	listInt.sort();
	for (list<int>::iterator i = listInt.begin(); i != listInt.end(); ++i) {
		cout << *i << " ";
	}
	cout << "\n=======\n";

	// 9. Calling the function to print the list
	cout << "Task 9:\n";
	printList(listInt);
	cout << "\n=======\n";

	// 10. Calling the function that prints the list, using ranged-for
	cout << "Task 10:\n";
	printListRanged(listInt);
	cout << "\n=======\n";

	//
	// Auto
	//

	// 11. Calling the function that, using auto, prints alterate
	// items in the list
	cout << "Task 11:\n";
	for (auto i = listInt.begin(); i != listInt.end(); ++i) {
		cout << *i++ << " ";
	}
	cout << "\n=======\n";


	// 12.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 12:\n";
	list<int>::const_iterator found = findInt(listInt, 7);
	cout << *found;
	cout << "\n=======\n";

	// 13.  Write a function find that takes a list and value to search for.
	//      What should we return if not found
	cout << "Task 13:\n";
	auto foundAuto = findIntAuto(listInt, 5);
	cout << *foundAuto;
	cout << "\n=======\n";

	//
	// Generic Algorithms
	//

	// 14. Generic algorithms: find
	cout << "Task 14:\n";
	list<int>::iterator foundInt = find(listInt.begin(), listInt.end(), 3);
	cout << *foundInt;
	cout << "\n=======\n";

	// 15. Generic algorithms: find_if
	cout << "Task 15:\n";
	list<int>::iterator foundEvenInt = find_if(listInt.begin(), listInt.end(), isEven);
	cout << *foundEvenInt;
	cout << "\n=======\n";

	// 16. Functor
	cout << "Task 16:\n";
	list<int>::iterator foundEvenIntFunctor = find_if(listInt.begin(), listInt.end(), Even());
	cout << *foundEvenIntFunctor;
	cout << "\n=======\n";

	// 17. Lambda
	cout << "Task 17:\n";
	list<int>::iterator foundEvenIntLambda = find_if(listInt.begin(), listInt.end(), [](int integer) { return integer % 2 == 0;});
	cout << *foundEvenIntLambda;
	cout << "\n=======\n";

	// 18. Generic algorithms: copy to an array
	cout << "Task 18:\n";
	int arr[10];
	copy(listInt.begin(), listInt.end(), arr);
	for (int x : arr) {
		cout << x << " ";
	}
	cout << endl;
	cout << *find(arr, arr + 10, 2) << " ";
	cout << *find_if(arr, arr + 10, isEven) << " ";
	cout << *find_if(arr, arr + 10, Even()) << " ";
	cout << *find_if(arr, arr + 10, [](int integer) { return integer % 2 == 0;});
	cout << "\n=======\n";

	//
	// Templated Functions
	//

	// 19. Implement find as a function for lists
	cout << "Task 19:\n";
	cout << *ourFind(arr, arr + 10, 2);
	cout << "\n=======\n";

	// 20. Implement find as a templated function
	cout << "Task 20:\n";
	cout << *ourFind(vectorInt.begin(), vectorInt.end(), 2);
	cout << endl;
	cout << *ourFind(listInt.begin(), listInt.end(), 2);
	cout << "\n=======\n";

	//
	// Associative collections
	//

	// 21. Using a vector of strings, print a line showing the number
	//     of distinct words and the words themselves.
	cout << "Task 21:\n";
	ifstream file;
	file.open("pooh-nopunc.txt");
	if (!file) {
		exit(0);
	}
	string word;
	vector<string> words;
	while (file >> word) {
		if (find(words.begin(), words.end(), word) == words.end()) {
			words.push_back(word);
		}
	}
	cout << "Word Count: " << words.size() << endl;
	for (size_t i = 0; i < words.size(); ++i) {
		cout << words[i] << " ";
	}
	file.close();
	cout << "\n=======\n";

	// 22. Repeating previous step, but using the set
	cout << "Task 22:\n";
	file.open("pooh-nopunc.txt");
	if (!file) {
		exit(0);
	}
	set<string> wordSet;
	while (file >> word) {
		if (wordSet.find(word) == wordSet.end()) {
			wordSet.insert(word);
		}
	}
	cout << "Word Count: " << wordSet.size() << endl;
	for (string word : wordSet) {
		cout << word << " ";
	}
	cout << "\n=======\n";
	file.close();
	// 23. Word co-occurence using map
	cout << "Task 23:\n";
	file.open("pooh-nopunc.txt");
	if (!file) {
		exit(0);
	}
	map<string, vector<int>> wordMap;
	int count = 0;
	while (file >> word) {
		wordMap[word].push_back(count);
		count++;
	}
	cout << "Word size: " << wordMap.size();
	for (const auto& word : wordMap) {
		cout << word.first << ", ";
		for (int x : word.second) {
			cout << x << " " ;
		}
		cout << endl;
	}
	file.close();
	cout << "\n=======\n";
}
