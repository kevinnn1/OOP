//Kevin Grajeda
//rec02.cpp
//Takes a list of hydrocarbon formulas and names from a text file and puts them in a vector, sorts them by formula, and prints them
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Hydrocarbons;
Hydrocarbons addInformation(ifstream& stream);
void fillHCVector(ifstream& stream, vector<Hydrocarbons>& hcvector);
void sortHCVector(vector<Hydrocarbons>& hcvector);	
void printHCVector(vector<Hydrocarbons> hcvector);
void openStream(ifstream& stream);

int main() {
	vector<Hydrocarbons> ListOfHydrocarbons;
	ifstream formulaList;
	openStream(formulaList);
	fillHCVector(formulaList, ListOfHydrocarbons);
	sortHCVector(ListOfHydrocarbons);
	printHCVector(ListOfHydrocarbons);
}

struct Hydrocarbons {
	vector<string> names;
	int numberOfCarbon;
	int numberOfHydrogen;
};
void openStream(ifstream& stream) {
	string filename;
	cout << "Enter file name:";
	cin >> filename;
	stream.open(filename);
	while (!stream) {
		stream.clear();
		cout << "Invalid filename, re-enter file name: ";
		cin >> filename;
		stream.open(filename);
	}
}
Hydrocarbons addInformation(ifstream& stream) {
	Hydrocarbons hydrocarbon;
	string name;
	int carbonCount, hydrogenCount;
	char carbon, hydrogen;
	stream >> name;
	stream >> carbon;
	stream >> carbonCount;
	stream >> hydrogen;
	stream >> hydrogenCount;
	hydrocarbon.numberOfCarbon = carbonCount;
	hydrocarbon.numberOfHydrogen = hydrogenCount;
	hydrocarbon.names.push_back(name);
	return hydrocarbon;
}
void fillHCVector(ifstream& stream, vector<Hydrocarbons>& hcvector) {
	string line;
	Hydrocarbons hydrocarbon = addInformation(stream);
	hcvector.push_back(hydrocarbon);
	do {
		bool sameFormula = false;
		Hydrocarbons hydrocarbon = addInformation(stream);
		for (size_t i = 0; i < hcvector.size(); ++i) {
			if ((hcvector[i].numberOfCarbon == hydrocarbon.numberOfCarbon) && (hydrocarbon.numberOfHydrogen == hcvector[i].numberOfHydrogen)) {
				hcvector[i].names.push_back(hydrocarbon.names[0]);
				sameFormula = true;
			}
		}
		if (!sameFormula) {
			hcvector.push_back(hydrocarbon);
		}
	} while (getline(stream, line));
}
void sortHCVector(vector<Hydrocarbons>& hcvector) {
	for (size_t i = 0; i < hcvector.size(); i++) {
		int smallest = i;
		for (size_t j = i + 1; j < hcvector.size(); j++) {
			if (hcvector[j].numberOfCarbon < hcvector[smallest].numberOfCarbon) {
				smallest = j;
			}
			else {
				if (hcvector[j].numberOfCarbon == hcvector[smallest].numberOfCarbon) {
					if (hcvector[j].numberOfHydrogen < hcvector[smallest].numberOfHydrogen) {
						smallest = j;
					}
				}
			}
		}
		if (smallest != i) {
			Hydrocarbons placeholder = hcvector[i];
			hcvector[i] = hcvector[smallest];
			hcvector[smallest] = placeholder;
		}
	}
}
void printHCVector(vector<Hydrocarbons> hcvector) {
	;
	for (size_t i = 0; i < hcvector.size(); ++i) {
		cout << "C" << hcvector[i].numberOfCarbon << "H" << hcvector[i].numberOfHydrogen << " ";
		for (size_t j = 0; j < hcvector[i].names.size(); ++j) {
			cout << hcvector[i].names[j] << " ";
		}
		cout << endl;
	}
}