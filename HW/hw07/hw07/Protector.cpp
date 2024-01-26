#include "Noble.h"
#include "Protector.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace WarriorCraft {
	class Noble;
	Protector::Protector(const string& protectorName, int protectorStrength)
		: name(protectorName), strength(protectorStrength), noble(nullptr) {}

	Noble* Protector::getNoble() const { return noble; }
	int Protector::getStrength() const { return strength; }
	string Protector::getName() const { return name; }
	void Protector::newStrength(int remainingHealth) { 
		strength = remainingHealth; }
	void Protector::newNoble(Noble* noblePtr) { noble = noblePtr; }

	// abstract method that is initialized outside class
	void Protector::cry() {
		cout << " says: Take that in the name of my lord, " 
			 << getNoble()->getName() << endl;
	}

	Wizard::Wizard(const string& wizardName, int wizardStrength)
		: Protector(wizardName, wizardStrength) {}
	void Wizard::cry() { cout << "POOF" << endl; }

	Warrior::Warrior(const string& warriorName, int warriorStrength)
		: Protector(warriorName, warriorStrength) {}

	Archer::Archer(const string& archerName, int archerStrength)
		: Warrior(archerName, archerStrength) {}
	void Archer::cry() {
		cout << "TWANG! " << getName();
		Protector::cry();
	}
	Swordsman::Swordsman(const string& swordsmanName, int swordsmanStrength)
		: Warrior(swordsmanName, swordsmanStrength) {}
	void Swordsman::cry() {
		cout << "CLANG! " << getName();
		Protector::cry();
	}
}