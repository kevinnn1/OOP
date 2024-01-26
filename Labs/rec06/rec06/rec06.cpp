/*
Kevin Grajeda
Recitation 06
CS2124
Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
	friend ostream& operator<<(ostream& os, const Position& rhs) {
		os << '[' << rhs.title << ',' << rhs.salary << ']';
		return os;
	}
public:
	Position(const string& aTitle, double aSalary)
		: title(aTitle), salary(aSalary) {}
	const string& getTitle() const { return title; }
	double getSalary() const { return salary; }
	void changeSalaryTo(double d) { salary = d; }
private:
	string title;
	double salary;
}; // class Position

class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs) {
		os << rhs.name << ' ' << rhs.room
			<< ' ' << rhs.phone << ", " << *rhs.pos;
		return os;
	}
public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
		: name(name), room(room), phone(phone), pos(&position) {
	}
	const string& getName() const { return name; }
	unsigned getPhone() const { return phone; }
private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
}; // class Entry

class Directory {
	friend ostream& operator<<(ostream& stream, const Directory& directory) {
		for (size_t i = 0; i < directory.size; ++i) {
			stream << *(directory.entries[i]) << endl;
		}
		return stream;
	}
public:
	// Of course the first function you need to write for this (or
	// any) class is...
	// ???
	// ...
	Directory()
		: size(0), capacity(1), entries(new Entry*[1]) {}
	// We'll get you started with the add method, but obviously you
	// have a lot of work to do here.
	Directory(const Directory& rhsDirectory) {
		size = rhsDirectory.size;
		capacity = rhsDirectory.capacity;
		entries = new Entry*[capacity];
		for (size_t i = 0; i < rhsDirectory.size; ++i) {
			//entries[i] = rhsDirectory.entries[i];
			Entry* oldEntry = rhsDirectory.entries[i];
			entries[i] = new Entry(*oldEntry);
		}
	}
	~Directory() {
		for (size_t i = 0; i < size; ++i) {
			delete entries[i];
			entries[i] = nullptr;
		}
		delete[] entries;
	}
	Directory& operator=(const Directory& rhsDirectory) {
		if (this != &rhsDirectory) {
			delete[] entries;
			for (size_t i = 0; i < size; ++i) {
				delete entries[i];
				entries[i] = nullptr;
			}
			size = rhsDirectory.size;
			capacity = rhsDirectory.capacity;
			entries = new Entry * [capacity];
			for (size_t i = 0; i < rhsDirectory.size; ++i) {
				//entries[i] = rhsDirectory.entries[i];
				Entry* oldEntry = rhsDirectory.entries[i];
				entries[i] = new Entry(*oldEntry);
			} 
		}
		return *this;
	}
	unsigned operator[](const string& name) const {
		for (size_t i = 0; i < size; ++i) {
			if (entries[i]->getName() == name) {
				return entries[i]->getPhone();
			}
		}
		return 0;
	}
	void add(const string& name, unsigned room, unsigned ph, Position& pos) {
		if (size == capacity) {
			// something is missing!!!  Add it!
			Entry** oldEntries = entries;
			entries = new Entry*[2 * capacity];
			for (size_t i = 0; i < size; ++i) {
				//Entry* oldEntry = oldEntries[i];
				//entries[i] = new Entry(*oldEntry);
				entries[i] = oldEntries[i];
			}
			capacity = capacity * 2;
			delete[] oldEntries;
		} // if
		entries[size] = new Entry(name, room, ph, pos);
		++size;
	} // add

private:
	Entry** entries;
	size_t size;
	size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {

	// Note that the Postion objects are NOT on the heap.
	Position boss("Boss", 3141.59);
	Position pointyHair("Pointy Hair", 271.83);
	Position techie("Techie", 14142.13);
	Position peon("Peonissimo", 34.79);

	// Create a Directory
	Directory d;
	d.add("Marilyn", 123, 4567, boss);
	cout << d << endl;
	
	Directory d2 = d;	// What function is being used??
	d2.add("Gallagher", 111, 2222, techie);
	d2.add("Carmack", 314, 1592, techie);
	cout << d << endl;

	cout << "Calling doNothing\n";
	doNothing(d2);
	cout << "Back from doNothing\n";

	Directory d3;
	d3 = d2;

	// Should display 1592
	cout << d2["Carmack"] << endl;
	
} // main
