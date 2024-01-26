/*
Kevin Grajeda
rec04.cpp
Warriors game; classes and association
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class Warrior;
class Noble;

class Warrior {
	friend ostream& operator<<(ostream& stream, Warrior warrior) {
		cout << warrior.name << ": " << warrior.strength;
		return stream;
	}
public:
	Warrior(const string warriorName, int warriorStrength)
		: name(warriorName), strength(warriorStrength), noble(nullptr) {}
	Noble* getNoble() {
		return noble;
	}
	void newNoble(Noble* noblePtr) {
		noble = noblePtr;
	}
	int getStrength() {
		return strength;
	}
	string getName() {
		return name;
	}
	void setStrength(const int remainingHealth) {
		strength = remainingHealth;
	}
private:
	string name;
	int strength;
	Noble* noble;
};
class Noble {
	friend ostream& operator<<(ostream& stream, Noble& noble) {
		cout << noble.name << " has an army of " << noble.army.size() << endl;
		for (size_t i = 0; i < noble.army.size(); ++i) {
			cout << "\t" << *(noble.army)[i] << endl; // prints the dereferenced warrior object
		}
		return stream;
	}
public:
	Noble(const string& nobleName)
		: name(nobleName), armyStrength(0) {} // armyStrength being 0 denotes noble has no strength, but does not mean noble is dead
	bool hire(Warrior &warrior) {
		if (warrior.getNoble() == nullptr && armyStrength != -1) { // warrior being hired is not already hired and the noble is not dead (-1 denotes dead)
			Warrior* warriorPtr = &warrior; 
			army.push_back(warriorPtr); // adds warrior to army (pointer to warrior to the vector)
			warrior.newNoble(this); // sets the warrior's noble (pointer for the noble the warrior works with to the noble hiring)
			armyStrength = armyStrength + warrior.getStrength(); // updates army strength
			return true;
		}
		return false;
	}
	bool fire(Warrior &warrior) {
		bool fired = false;
		if(armyStrength != -1)
			warrior.newNoble(nullptr); // warrior is free to be hired again
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i] == &warrior) {
					// shift each warrior down 1 position starting from the position of the warrior being fired, removing the fired warrior
					for (size_t j = i; j < army.size()-1; ++j) {
						army[j] = army[j+1];
					}
					fired = true;
					cout << "You don't have to work for me anymore " << warrior.getName() << "! --" << name << "." << endl;
				}
			}
		if(fired){
			army.pop_back(); // removes warrior from army, which is a copy of the last warrior hired
			armyStrength = armyStrength - warrior.getStrength(); //updates army strength
		}
		return fired;
	}
	void battle(Noble &opponent) {
		cout << name << " battles " << opponent.name << endl;
		if (armyStrength == opponent.armyStrength && armyStrength >= 0 && opponent.armyStrength >= 0) { // equal strength armies
			cout << "Mutual Annihalation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
			armyStrength = -1; // challenger noble and army are dead
			opponent.armyStrength = -1; // opponent noble and army are dead
			for (size_t i = 0; i < army.size(); ++i) { // sets the strengths of the warriors of the deafeated army to 0
				army[i]->setStrength(0);  // sets the strengths of the warriors of the deafeated army to 0
			}
			for (size_t i = 0; i < opponent.army.size(); ++i) {
				opponent.army[i]->setStrength(0);
			}
		}
		else if (armyStrength > opponent.armyStrength && opponent.armyStrength >= 0) { // challenging army is stronger and opponent army/noble is alive
			cout << name << " defeats " << opponent.name << endl;
			double damageRatio = double(opponent.armyStrength) / double(armyStrength); // sets the ratio that will determine damage
			for (size_t i = 0; i < army.size(); ++i) {
				armyStrength = armyStrength - opponent.armyStrength; // adjusts army health for challenger (winner)
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->setStrength(army[i]->getStrength() - damageRatio * army[i]->getStrength()); // adjusts warriors' health for challenger (winner)
				}
			}
			opponent.armyStrength = -1; // opponent noble and army are dead
			for (size_t i = 0; i < opponent.army.size(); ++i) {
				opponent.army[i]->setStrength(0);
			}
		}
		else if (armyStrength < opponent.armyStrength) {  // opponent army is stronger
			cout << opponent.name << " defeats " << name << endl;
			double damageRatio = double(armyStrength) / double(opponent.armyStrength); 
			for (size_t i = 0; i < opponent.army.size(); ++i) {
				opponent.armyStrength = opponent.armyStrength - armyStrength; // adjusts army health for opponent (winner)
				for (size_t i = 0; i < opponent.army.size(); ++i) {
					opponent.army[i]->setStrength(opponent.army[i]->getStrength() - damageRatio * opponent.army[i]->getStrength()); // adjusts warriors' health for opponent (winner)
				}
			}
			armyStrength = -1; // challenger noble and army are dead
			for (size_t i = 0; i < army.size(); ++i) {
				army[i]->setStrength(0);
			}
		}
		else if (armyStrength > opponent.armyStrength && opponent.armyStrength < 0) { // opponent army and noble are already dead
			cout << "He's dead, " << name << endl;
		}
		else { // both nobles/armies are dead already
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}	
	}
private:
	int armyStrength;
	string name;
	vector<Warrior*> army;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);	

	cout << "==========\n"
		<< "Status before all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

	art.fire(cheetah);
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "==========\n"
		<< "Status after all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

}
