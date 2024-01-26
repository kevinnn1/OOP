#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

namespace WarriorCraft {
	class Noble;
	class Warrior {
		friend std::ostream& operator<<(std::ostream& stream, 
		const Warrior& warrior);
	public:
		Warrior(const std::string& warriorName, int warriorStrength);
		Noble* getNoble() const;
		void newNoble(Noble* noblePtr);
		int getStrength() const;
		std::string getName() const;
		void setStrength(const int remainingHealth);
		bool runaway();
	private:
		std::string name;
		int strength;
		Noble* noble;
	};
}
#endif
