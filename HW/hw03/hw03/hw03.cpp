/*
Kevin Grajeda
hw02.cpp
Medieval times game using warriors; Data hiding, encapsulation, delegation, operator overloading
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior;
void openStream(ifstream& stream);
void readStream(ifstream& stream, vector<Warrior>& warriorList);

int main() {
	vector<Warrior> listOfWarriors;
	ifstream filename;
	openStream(filename);
	readStream(filename, listOfWarriors);
}
class Warrior {
	friend ostream& operator<<(ostream& stream, vector<Warrior>& warriorList) {
		cout << "There are: " << warriorList.size() << " warriors" << endl;
		for (size_t i = 0; i < warriorList.size(); ++i) {
			cout << "Warrior: " << warriorList[i].name << warriorList[i].weapon;
		}
		return stream;
	}
public:
	Warrior(const string warriorName, const string weaponName, int weaponStrength)
		: name(warriorName), weapon(weaponName, weaponStrength) {}

	string getWarriorName() {
		return name;
	}
	void weakenWeapon(const int damage) { // Weakens warrior's weapon after battle
		weapon.setStrength(weapon.getStrength() - damage);
	}
	void battleWith(Warrior &opponent) { // Battle command
		cout << name << " battles " << opponent.name << endl;
		int selfStrength = weapon.getStrength();
		int opponentStrength = opponent.weapon.getStrength();
		if (selfStrength == opponentStrength && selfStrength != 0 && opponentStrength != 0) { // Warriors have equal strengths
			cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
			weakenWeapon(selfStrength);
			opponent.weakenWeapon(opponentStrength);
		}
		else if(selfStrength > opponentStrength && opponentStrength != 0){ // First warrior is stronger
			cout << name << " defeats " << opponent.name << endl;
			weakenWeapon(opponentStrength);
			opponent.weakenWeapon(opponentStrength);
		}
		else if(selfStrength < opponentStrength){ // Second warrior is stronger
			cout << opponent.name << " defeats " << name << endl;
			weakenWeapon(selfStrength);
			opponent.weakenWeapon(selfStrength);
		}
		else if(selfStrength > 0 && opponentStrength == 0){ // First warrior challenges a dead warrior
			cout << "He's dead, " << name << endl;
		}
		else { // Both warriors are dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
	}
private:
	class Weapon {
		friend ostream& operator<<(ostream& stream, Weapon& weapon) {
			cout << ", weapon: " << weapon.name << ", " << weapon.strength << endl;
			return stream;
		}
	public:
		Weapon(const string weaponName, const int weaponStrength)
			: name(weaponName), strength(weaponStrength) {}

		string getName() {
			return name;
		}
		int getStrength() {
			return strength;
		}
		void setStrength(int newStrength) {
			strength = newStrength;
		}
	private:
		string name;
		int strength;
	};
	string name;
	Weapon weapon;
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
void readStream(ifstream& stream, vector<Warrior>& warriorList) {
	string word;
	while (stream >> word) { 
		if (word == "Warrior") { // If streams reads a warrior command, it creates a warrior
			string name;
			string weaponName;
			int weaponStrength;
			stream >> name;
			stream >> weaponName;
			stream >> weaponStrength;
			Warrior warrior = Warrior(name, weaponName, weaponStrength);
			warriorList.push_back(warrior);
		}
		else if (word == "Battle") { // If streams reads a battle command, it initiates a battle
			string challenger;
			string opponent;
			stream >> challenger;
			stream >> opponent;
			int challengerPosition = 0;
			int opponentPosition = 0;
			for (size_t i = 0; i < warriorList.size(); ++i) { // Finds the first warrior being put in battle
				if (challenger == warriorList[i].getWarriorName()) {
					challengerPosition = i;
				}
			}
			for (size_t j = 0; j < warriorList.size(); ++j) { // Finds the second warrior being put in battle
				if (opponent == warriorList[j].getWarriorName()) {
					opponentPosition = j;
				}
			}
			warriorList[challengerPosition].battleWith(warriorList[opponentPosition]);
		}
		else { //Takes last possible command, status
			cout << warriorList;
		}
	}
	stream.close();
}