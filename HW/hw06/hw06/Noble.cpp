#include <vector>
#include <iostream>
#include <string>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
	class Warrior;
	ostream& operator<<(ostream& stream, const Noble& noble) {
		cout << noble.name << " has an army of " << noble.army.size() << endl;
		for (size_t i = 0; i < noble.army.size(); ++i) {
			// prints the dereferenced warrior object
			cout << "\t" << *(noble.army)[i] << endl;
		}
		return stream;
	}
	Noble::Noble(const string& nobleName)
		: name(nobleName), armyStrength(0), isAlive(true) {}
	string Noble::getName() const {
		return name;
	}
	void Noble::dies() {
		isAlive = false;
	}
	bool Noble::hire(Warrior & warrior) {
		if (warrior.getNoble() == nullptr && isAlive) {
			Warrior* warriorPtr = &warrior;
			// adds warrior to army and assigns warriors noble
			army.push_back(warriorPtr);
			warrior.newNoble(this);
			// updates army strength
			armyStrength = armyStrength + warrior.getStrength();
			return true;
		}
		cout << warrior.getName() << " is Already Hired!" << endl;
		return false;
	}
	void Noble::removeFromArmy(Warrior& warrior) {
		// warrior is free to be hired again
		warrior.newNoble(nullptr);
		for (size_t i = 0; i < army.size(); ++i) {
			if (army[i] == &warrior) {
				// shift each warrior down 1 position starting from the position of 
				// the warrior being fired, removing the fired warrior
				for (size_t j = i; j < army.size() - 1; ++j) {
					army[j] = army[j + 1];
				}
			}
		}
		// removes warrior and adjusts army strength
		army.pop_back();
		armyStrength = armyStrength - warrior.getStrength();
	}
	bool Noble::fire(Warrior& warrior) {
		bool fired = false;
		if (isAlive) {
			removeFromArmy(warrior);
			fired = true;
			cout << "You don't have to work for me anymore " << warrior.getName() 
				 << "! -- " << name << "." << endl;
		}
		else {
			cout << "Failed to fire " << warrior.getName() << "!" << endl;
		}
		return fired;
	}
	void Noble::battle(Noble& opponent) {
		cout << name << " battles " << opponent.name << endl;
		// equal strength armies
		if (armyStrength == opponent.armyStrength && armyStrength > 0 
		&& opponent.armyStrength > 0) {
			cout << "Mutual Annihalation: " << name << " and "
				<< opponent.name << " die at each other's hands" << endl;
			armyStrength = 0;
			opponent.armyStrength = 0;
			dies();
			opponent.dies();
			for (size_t i = 0; i < army.size(); ++i) {
				// sets the strengths of the warriors of the deafeated army to 0
				army[i]->setStrength(0);
			}
			for (size_t i = 0; i < opponent.army.size(); ++i) {
				opponent.army[i]->setStrength(0);
			}
		}
		else if (armyStrength > opponent.armyStrength
		&& opponent.armyStrength > 0) {
			// challenging army is stronger and opponent army/noble is alive
			cout << name << " defeats " << opponent.name << endl;
			opponent.dies();
			double damageRatio = double(opponent.armyStrength) / double(armyStrength);
			for (size_t i = 0; i < army.size(); ++i) {
				// adjusts warriors' health based on opponent's strength
				army[i]->setStrength(army[i]->getStrength()
					- damageRatio * army[i]->getStrength());
			}
			armyStrength = armyStrength - opponent.armyStrength;
			opponent.armyStrength = 0; // opponent noble and army are dead
			for (size_t i = 0; i < opponent.army.size(); ++i) {
				opponent.army[i]->setStrength(0);
			}
		}
		else if (armyStrength < opponent.armyStrength) {
			// opponent army is stronger
			cout << opponent.name << " defeats " << name << endl;
			dies();
			double damageRatio = double(armyStrength) / double(opponent.armyStrength);
			for (size_t i = 0; i < opponent.army.size(); ++i) {
				// adjusts warriors' health based on opponent's strength
				opponent.army[i]->setStrength(opponent.army[i]->getStrength()
					- damageRatio * opponent.army[i]->getStrength());
			}
			opponent.armyStrength = opponent.armyStrength - armyStrength;
			armyStrength = 0; // challenger noble and army are dead
			for (size_t i = 0; i < army.size(); ++i) {
				army[i]->setStrength(0);
			}
		}
		else if (armyStrength > opponent.armyStrength 
		&& opponent.armyStrength == 0) {
			// opponent army and noble are already dead
			cout << "He's dead, " << name << endl;
		}
		else {
			// both nobles/armies are dead already
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
	}
}
	