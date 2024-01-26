/*
Kevin Grajeda
hw05
Continuation of warrior game; dynamic memory
*/

#include <vector>
#include <iostream>
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
	Noble* getNoble() const {
		return noble;
	}
	void newNoble(Noble* noblePtr) {
		noble = noblePtr;
	}
	int getStrength() const {
		return strength;
	}
	string getName() const {
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
			// prints the dereferenced warrior object
			cout << "\t" << *(noble.army)[i] << endl; 
		}
		return stream;
	}
public:
	Noble(const string& nobleName)
		: name(nobleName), armyStrength(0), isAlive(true) {} 
	string getName() const {
		return name;
	}
	void dies() {
		isAlive = false;
	}
	bool hire(Warrior& warrior) {
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
	bool fire(Warrior& warrior) {
		bool fired = false;
		if (isAlive) {
			// warrior is free to be hired again
			warrior.newNoble(nullptr);
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i] == &warrior) {
					// shift each warrior down 1 position starting from the position of 
					// the warrior being fired, removing the fired warrior
					for (size_t j = i; j < army.size() - 1; ++j) {
						army[j] = army[j + 1];
					}
					fired = true;
					cout << "You don't have to work for me anymore " << warrior.getName() << "! -- " << name << "." << endl;
				}
			}
		}
		if (fired) {
			// removes warrior from army, which is a copy of the last warrior hired
			// updates army strength
			army.pop_back(); 
			armyStrength = armyStrength - warrior.getStrength(); 
		}
		else {
			cout << "Failed to fire " << warrior.getName() << "!" << endl;
		}
		return fired;
	}
	void battle(Noble& opponent) {
		cout << name << " battles " << opponent.name << endl;
		// equal strength armies
		if (armyStrength == opponent.armyStrength && armyStrength > 0 && opponent.armyStrength > 0) { 
			cout << "Mutual Annihalation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
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
		 else if (armyStrength > opponent.armyStrength && opponent.armyStrength > 0) { 
			// challenging army is stronger and opponent army/noble is alive
			cout << name << " defeats " << opponent.name << endl;
			opponent.dies();
			double damageRatio = double(opponent.armyStrength) / double(armyStrength);
			for (size_t i = 0; i < army.size(); ++i) {
				// adjusts warriors' health based on opponent's strength
				army[i]->setStrength(army[i]->getStrength() - damageRatio * army[i]->getStrength()); 
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
				opponent.army[i]->setStrength(opponent.army[i]->getStrength() - damageRatio * opponent.army[i]->getStrength()); 
			}
			opponent.armyStrength = opponent.armyStrength - armyStrength;
			armyStrength = 0; // challenger noble and army are dead
			for (size_t i = 0; i < army.size(); ++i) {
				army[i]->setStrength(0);
			}
		}
		else if (armyStrength > opponent.armyStrength && opponent.armyStrength == 0) { 
			// opponent army and noble are already dead
			cout << "He's dead, " << name << endl;
		}
		else { 
			// both nobles/armies are dead already
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
	}
private:
	int armyStrength;
	string name;
	vector<Warrior*> army;
	bool isAlive;
};
int find(const string& name, const vector<Noble*> list) { 
	//finds noble in a vector by name
	for (size_t i = 0; i < list.size(); ++i) {
		if (name == list[i]->getName())
			return i;
	}
	return -1;
}
int find(const string& name, const vector<Warrior*> list) {
	//finds warrior in a vector by name
	for (size_t i = 0; i < list.size(); ++i) {
		if (name == list[i]->getName())
			return i;
	}
	return -1;
}
void openStream(ifstream& stream) { 
	string filename;
	cout << "Enter file name:";
	cin >> filename;
	stream.open(filename);
}
void readStream(ifstream& stream, vector<Noble*>& nobles,  vector<Warrior*>& warriors) {
	string command;
	while (stream >> command) {
		if (command == "Noble") {
			string name;
			stream >> name;
			if (find(name, nobles) == -1) {
				// searches for noble with name from input, creates new noble if there is none
				nobles.push_back(new Noble(name));
			}
			else {
				cout << name << " already exists, no noble added :(" << endl;
			}
		}
		else if (command == "Warrior") {
			string name;
			int strength;
			stream >> name;
			stream >> strength;
			if (find(name, warriors) == -1) {
				// searches for warrior with name from input, creates new warrior if there is none
				warriors.push_back(new Warrior(name, strength));
			}
			else {
				cout << name << " already exists, no warrior added :(" << endl;
			}
		}
		else if (command == "Hire" || command == "Fire") {
			string noble;
			string warrior;
			stream >> noble;
			stream >> warrior;
			int nobleInd = find(noble, nobles);
			int warriorInd = find(warrior, warriors);
			if (command == "Hire") {
				// checks if noble/warrior exists for hiring
				if (nobleInd == -1 || warriorInd == -1) {
					cout << "Noble and/or warrior does not exist, " << warrior <<  " not hired :(" << endl;
				}
				else {
					nobles[nobleInd]->hire(*(warriors[warriorInd]));
				}
			}
			else { // Fire
				// checks if noble/warrior exists for firing
				if (nobleInd == -1 || warriorInd == -1) {
					cout << "Noble or warrior does not exit, " << warrior << " not fired :)" << endl;
				}
				else {
					// checks to see if warrior is in noble's army
					Noble* warriorsNoble = warriors[warriorInd]->getNoble();
					if (!warriorsNoble || warriorsNoble->getName() != nobles[nobleInd]->getName()) {
						cout << "Warrior is not in " << noble << "'s army, " << warrior << " not fired :)" << endl;
					}
					else {
						nobles[nobleInd]->fire(*(warriors[warriorInd]));
					}
				}
			}
		}
		else if (command == "Battle") {
			string challenger;
			string opponent;
			stream >> challenger;
			stream >> opponent;
			int challengerInd = find(challenger, nobles);
			int opponentInd = find(opponent, nobles);
			// checks to find if both nobles exist
			if (challengerInd == -1 || opponentInd == -1) {
				cout << "One or both of the nobles do not exist, no battle :/" << endl;
			}
			else {
				nobles[challengerInd]->battle(*(nobles[opponentInd]));
			}
		}
		else if (command == "Status") {
			cout << "Status\n======\nNobles:\n";
			if (nobles.size() == 0) {
				cout << "NONE" << endl;
			}
			else {
				// prints nobles
				for (size_t i = 0; i < nobles.size(); ++i) {
					cout << *(nobles[i]);
				}
			}
			cout << "Unemployed Warriors: " << endl;
			int unemployed = 0;
			for (size_t i = 0; i < warriors.size(); ++i) {
				if (warriors[i]->getNoble() == nullptr) {
					// prints unemplyed warriors, counts how many unemployed
					cout << *(warriors[i]) << endl;
					++unemployed;
				}
			}
			if(unemployed == 0){
				cout << "NONE" << endl;
			}
		}
		else if (command == "Clear") {
		// warriors and nobles removed from heap and vectors cleared
			for (size_t i = 0; i < warriors.size(); ++i) {
				delete warriors[i];
			}
			warriors.clear();
			for (size_t i = 0; i < nobles.size(); ++i) {
				delete nobles[i];
			}
			nobles.clear();
		}
		else {
			cout << "Invalid command";
		}
	}
}
int main() {
	vector<Noble*> listOfNobles;
	vector<Warrior*> listOfWarriors;
	ifstream filename;
	openStream(filename);
	readStream(filename, listOfNobles, listOfWarriors);
	filename.close();
}