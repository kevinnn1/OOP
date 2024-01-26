//Kevin Grajeda
//rec01.cpp
//Reads file, displays it, and gives world count
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string line;
	string word;
	ifstream jab("jabberwocky.txt");
	if (!jab) {
		cerr << "Failed to open file";
		exit(1);
	}
	while (getline(jab, line)) {
		cout << line << endl;
	}
	jab.close();
	jab.open("jabberwocky.txt");
	int wordCount = 0;
	while (jab >> word) {
		++wordCount;
	}
	cout << "\n Word Count:" << wordCount << endl;
	return 0;
}
