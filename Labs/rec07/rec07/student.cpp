#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
	Student::Student(const string& studentName) : name(studentName) {}

	const string& Student::getName() const {
		return name;
	};

	ostream& operator<<(ostream& os, const Student& rhs) {
		cout << rhs.name << ": ";
		if (rhs.courses.size() == 0) {
			cout << "No courses";
		}
		else {
			for (size_t i = 0; i < rhs.courses.size(); ++i) {
				cout << rhs.courses[i]->getName() << " ";
			}
		}
		cout << endl;
		return os;
	}

	bool Student::addCourse(Course* courseName) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courseName->getName() == courses[i]->getName()) {
				cout << "Student already in course" << endl;
				return false;
			}
		}
		courses.push_back(courseName);
		return true;
	}

	void Student::removedFromCourse(Course* course) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (course->getName() == courses[i]->getName()) {
				for (size_t j = i; j < courses.size() - 1; ++j) {
					courses[j] = courses[j + 1];
				}
				courses.pop_back();
			}
		}
	}
}