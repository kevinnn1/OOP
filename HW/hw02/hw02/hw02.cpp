/*
Kevin Grajeda
hw02.cpp
Medieval times game using warriors; Functions, structs, vectors and file I/O
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Warrior;
void openStream(ifstream& stream);
void createWarrior(string warriorName, int warriorStrength, vector<Warrior>& warriorList);
void battle(Warrior& warrior1, Warrior& warrior2);
void status(const vector<Warrior>& warriorList);
void readStream(ifstream& stream, vector<Warrior> warriorList);

int main() {
	vector<Warrior>listOfWarriors;
	ifstream filename; 
	string line;
	openStream(filename);
	readStream(filename, listOfWarriors);
}
struct Warrior {
	string name;
	int strength;
};
void openStream(ifstream& stream) { // Checks if correct filename is given and opens it
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
void createWarrior(string warriorName, int warriorStrength, vector<Warrior>& warriorList) { // Creates warrior with given name and strength
	Warrior warrior;
	warrior.name = warriorName;
	warrior.strength = warriorStrength;
	warriorList.push_back(warrior); // Adds warrior to the warrior vector
}
void battle(Warrior& warrior1, Warrior& warrior2) { // Battle command
	cout << warrior1.name << " battles " << warrior2.name << endl;
	if (warrior1.strength == warrior2.strength && warrior1.strength != 0 && warrior2.strength != 0) { //Warriors have equal strengths
		warrior1.strength = 0;
		warrior2.strength = 0;
		cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
	}
	else if (warrior1.strength > warrior2.strength && warrior2.strength != 0) { // First warrior is stronger
		cout << warrior1.name << " defeats " << warrior2.name << endl;
		warrior1.strength = warrior1.strength - warrior2.strength;
		warrior2.strength = 0;
	}
	else if (warrior1.strength < warrior2.strength) { // Second warrior is stronger
		cout << warrior2.name << " defeats " << warrior1.name << endl;
		warrior2.strength = warrior2.strength - warrior1.strength;
		warrior1.strength = 0;
	}
	else if (warrior1.strength > 0 && warrior2.strength == 0) { // First warrior challenges a dead warrior
		cout << "He's dead, " << warrior1.name << endl;
	}
	else { // Both warriors are dead
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
}
void status(const vector<Warrior>& warriorList) { // Status command
	cout << "There are: " << warriorList.size() << " warriors" << endl;
	for (size_t i = 0; i < warriorList.size(); ++i) { // Prints warrior name and status
		cout << "Warrior: " << warriorList[i].name << ", Strength: " << warriorList[i].strength << endl;
	}
}

void readStream(ifstream& stream, vector<Warrior> warriorList) { // Reads the file and executes commands
	int num;
	string word;
	while (stream >> word) {
		if (word == "Warrior") { // If streams reads a warrior command, it creates a warrior
			string name;
			int strength;
			stream >> name;
			stream >> strength;
			createWarrior(name, strength, warriorList);
		}
		else if (word == "Battle") { // If streams reads a battle command, it initiates a battle
			vector<Warrior> warriorInBattle;
			string firstWarrior;
			string secondWarrior;
			stream >> firstWarrior;
			stream >> secondWarrior;
			int firstWarriorPosition = 0;
			int secondWarriorPosition = 0;
			for (size_t i = 0; i < warriorList.size(); ++i) { // Finds the first warrior being put in battle
				if (firstWarrior == warriorList[i].name) {
					firstWarriorPosition = i;
				}
			}
			for (size_t j = 0; j < warriorList.size(); ++j) { // Finds the second warrior being put in battle
				if (secondWarrior == warriorList[j].name) {
					secondWarriorPosition = j;
				}
			}
			battle(warriorList[firstWarriorPosition], warriorList[secondWarriorPosition]);
		}
		else { // Takes last possible command, status
			status(warriorList);
		}
	}
}