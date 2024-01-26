#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
	class Noble;
	class Protector {
	public:
		Protector(const std::string& protectorName, int protectorStrength);
		Noble* getNoble() const;
		int getStrength() const;
		std::string getName() const;
		void newStrength(int remainingHealth);
		void newNoble(Noble* noblePtr);
		virtual void cry() = 0;
	private:
		std::string name;
		int strength;
		Noble* noble;
	};
	class Wizard : public Protector {
	public:
		Wizard(const std::string& wizardName, int wizardStrength);
		void cry();
	};
	class Warrior : public Protector {
	public:
		Warrior(const std::string& warriorName, int warriorStrength);
	};
	class Archer : public Warrior {
	public:
		Archer(const std::string& archerName, int archerStrength);
		void cry();
	};
	class Swordsman : public Warrior {
	public:
		Swordsman(const std::string& swordsmanName, int swordsmanStrength);
		void cry();
	};
}
#endif
