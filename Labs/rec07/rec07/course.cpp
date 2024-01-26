#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
	Course::Course(const string& courseName) : name(courseName) {}

	const string& Course::getName() const {
		return name;
	};
	ostream& operator<<(ostream& os, const Course& rhs) {
		cout << rhs.name << ": ";
		if (rhs.students.size() == 0) {
			cout << "No students";
		}
		else {
			for (size_t i = 0; i < rhs.students.size(); ++i) {
				cout << rhs.students[i]->getName() << " ";
			}
		}
		return os;
	}
	bool Course::addStudent(Student* studentName) {
		for (size_t i = 0; i < students.size(); ++i) {
			if (studentName->getName() == students[i]->getName()) {
				cout << "Student already in course" << endl;
				return false;
			}
		}
		students.push_back(studentName);
		return true;
	}
	void Course::removeStudentsFromCourse() {
		for (size_t i = 0; i < students.size(); ++i) {
			students.pop_back();
		}
	}
}