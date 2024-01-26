#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace WarriorCraft {
	class Protector;

	Noble::Noble(const string& nobleName)
		: name(nobleName), alive(true) {}
	void Noble::battle(Noble& opponent) {
		cout << name << " battles " << opponent.name << endl;
		cry();
		opponent.cry();
		int strength = getStrength();
		int opponentStrength = opponent.getStrength();
		// equal strength armies
		if (strength == opponentStrength && strength > 0 && opponentStrength > 0) {
			cout << "Mutual Annihalation: " << name << " and "
				<< opponent.name << " die at each other's hands" << endl;
			setStrength(opponentStrength);
			opponent.setStrength(strength);
			dies();
			opponent.dies();
		}
		else if (strength > opponentStrength && opponent.isAlive()) {
			// challenging army is stronger and opponent army/noble is alive
			cout << name << " defeats " << opponent.name << endl;
			opponent.dies();
			// adjusts warriors' health based on opponent's strength
			setStrength(opponentStrength);
			// opponent noble and army are dead
			opponent.setStrength(strength);
		}
		else if (strength < opponentStrength && isAlive()) {
			// opponent army is stronger
			cout << opponent.name << " defeats " << name << endl;
			dies();
			// adjusts warriors' health based on opponent's strength
			opponent.setStrength(strength);
			// challenger noble and army are dead
			setStrength(opponentStrength);
		}
		else if (strength > opponentStrength && opponentStrength == 0) {
			// opponent army and noble are already dead
			cout << "He's dead, " << name << endl;
		}
		else if (strength < opponentStrength && strength == 0) {
			// challenging army and noble are already dead
			cout << "He's dead, " << opponent.name << endl;
		}
		else {
			// both nobles/armies are dead already
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
	}
	bool Noble::isAlive() const { return alive; }
	string Noble::getName() const { return name; }
	void Noble::dies() { alive = false; }

	PersonWithStrengthToFight::PersonWithStrengthToFight
	(const string& personName, int personStrength)
		: strength(personStrength), Noble(personName) {}

	int PersonWithStrengthToFight::getStrength() const { return strength; }
	void  PersonWithStrengthToFight::setStrength(int damage) {
		strength = strength - damage;
		// prevents strength from going below 0
		if (strength < 0) {
			strength = 0;
		}
	}
	void  PersonWithStrengthToFight::cry() {
		if (isAlive()) {
			cout << "Ugh!" << endl;
		}
	}

	Lord::Lord(const string& lordName)
		: armyStrength(0), Noble(lordName) {}
	bool Lord::hires(Protector& protector) {
		if (isAlive()) {
			if (protector.getNoble() == nullptr && protector.getStrength() > 0) {
				Protector* protectorPtr = &protector;
				// adds protector to army and assigns protectors noble
				army.push_back(protectorPtr);
				protector.newNoble(this);
				// updates army strength
				armyStrength = armyStrength + protector.getStrength();
				return true;
			}
			return false;
		}
		return false;
	}
	void Lord::removeFromArmy(Protector& protector) {
		// warrior is free to be hired again
		protector.newNoble(nullptr);
		for (size_t i = 0; i < army.size(); ++i) {
			if (army[i] == &protector) {
				// shift each warrior down 1 position starting from the position of 
				// the warrior being fired, removing the fired warrior
				for (size_t j = i; j < army.size() - 1; ++j) {
					army[j] = army[j + 1];
				}
			}
		}
		// removes warrior and adjusts army strength
		army.pop_back();
		armyStrength = armyStrength - protector.getStrength();
	}
	bool Lord::fires(Protector& protector) {
		bool fired = false;
		if (isAlive()) {
			removeFromArmy(protector);
			fired = true;
			cout << "You don't have to work for me anymore " << protector.getName()
				<< "! -- " << getName() << "." << endl;
		}
		else {
			cout << "Failed to fire " << protector.getName() << "!" << endl;
		}
		return fired;
	}
	void Lord::setStrength(int damage) {
		double damageRatio = double(damage) / double(armyStrength);
		for (size_t i = 0; i < army.size(); ++i) {
			army[i]->newStrength(army[i]->getStrength()
				- damageRatio * army[i]->getStrength());
		}
		armyStrength = armyStrength - damage;
		// prevents strength from going below 0
		if (armyStrength < 0) {
			armyStrength = 0;
		}
	}
	//Has each protector in the army do their cry
	void Lord::cry()  {
		if (isAlive()) {
			for (size_t i = 0; i < army.size(); ++i) {
				army[i]->cry();
			}
		}
	}
	int Lord::getStrength() const { return armyStrength; }
}