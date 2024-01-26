#ifndef NOBLE_H
#define NOBLE_H

#include <ostream>
#include <string>
#include <vector>

namespace WarriorCraft {
	class Warrior;
	class Noble {
		friend std::ostream& operator<<(std::ostream& stream, const Noble& noble);
	public:
		Noble(const std::string& nobleName);
		std::string getName() const;
		void dies();
		bool hire(Warrior& warrior);
		void removeFromArmy(Warrior& warrior);
		bool fire(Warrior& warrior);
		void battle(Noble& opponent);
	private:
		int armyStrength;
		std::string name;
		std::vector<Warrior*> army;
		bool isAlive;
	};
}
#endif

