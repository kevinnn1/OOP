#ifndef NOBLE_H
#define NOBLE_H

#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
	class Protector;
	class Noble {
	public:
		Noble(const std::string& nobleName);
		void battle(Noble& opponent);
		bool isAlive() const;
		std::string getName() const;
		void dies();
		virtual int getStrength() const = 0;
		virtual void setStrength(int damage) = 0;
		virtual void cry() = 0;
	private:
		std::string name;
		bool alive;
	};
	class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(const std::string& personName, int personStrength);
		int getStrength() const;
		void setStrength(int damage);
		void cry();
	private:
		int strength;
	};

	class Lord : public Noble {
	public:
		Lord(const std::string& lordName);
		bool hires(Protector& protector);
		void removeFromArmy(Protector& protector);
		bool fires(Protector& protector);
		int getStrength() const;
		void setStrength(int damage);
		void cry();
	private:
		std::vector<Protector*> army;
		int armyStrength;
	};
}
#endif