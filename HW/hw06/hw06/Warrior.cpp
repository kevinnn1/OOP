#include <vector>
#include <iostream>
#include <string>
#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft {
	class Noble;
	ostream& operator<<(ostream& stream, const Warrior& warrior) {
		cout << warrior.name << ": " << warrior.strength;
		return stream;
	}
	Warrior::Warrior(const string& warriorName, int warriorStrength)
		: name(warriorName), strength(warriorStrength), noble(nullptr) {}
	Noble* Warrior::getNoble() const {
		return noble;
	}
	void Warrior::newNoble(Noble* noblePtr) {
		noble = noblePtr;
	}
	int Warrior::getStrength() const {
		return strength;
	}
	string Warrior::getName() const {
		return name;
	}
	void Warrior::setStrength(const int remainingHealth) {
		strength = remainingHealth;
	}
	bool Warrior::runaway() {
		if (noble != nullptr) {
			cout << name << " flees in terror, abandoning his lord, "
				 << noble->getName() << endl;
			// sets warrior's noble to nullptr
			// removes warrior from noble's army
			noble->removeFromArmy(*this);
			return true;
		}
		else {
			cout << "Failed to run away" << endl;
			return false;
		}
	}
}