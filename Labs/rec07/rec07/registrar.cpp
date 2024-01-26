#include "registrar.h"
#include "course.h"
#include "student.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly {
	Registrar::Registrar() {}

	ostream& operator<<(ostream& os, const Registrar& rhs) {
		cout << "Registrar's Report\n";
		cout << "Courses: \n";
		for (size_t i = 0; i < rhs.courses.size(); ++i) {
			cout << *(rhs.courses[i]) << endl;
		}
		cout << "Students: \n";
		for (size_t i = 0; i < rhs.students.size(); ++i) {
			cout << *(rhs.students[i]);
		}
		return os;
	}

	size_t Registrar::findStudent(const string& studentName) const {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName() == studentName) {
				return i;
			}
		}
		return -1;
	};
	size_t Registrar::findCourse(const string& courseName) const {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i]->getName() == courseName) {
				return i;
			}
		}
		return -1;
	};
	bool Registrar::addCourse(const string& courseName) {
		if (findCourse(courseName) == -1) {
			courses.push_back(new Course(courseName));
			return true;
		}
		cout << "Course already added" << endl;
		return false;
	}
	bool Registrar::addStudent(const string& studentName) {
		if (findStudent(studentName) == -1) {
			students.push_back(new Student(studentName));
			return true;
		}
		else {
			cout << "Student already added" << endl;
			return false;
		}
	}
	bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
		size_t studentInd = findStudent(studentName);
		size_t courseInd = findCourse(courseName);
		if (studentInd != -1 && courseInd != -1) {
			courses[courseInd]->addStudent(students[studentInd]);
			students[studentInd]->addCourse(courses[courseInd]);
			return true;
		}
		else {
			cout << "Student or course not found" << endl;
			return false;
		}
	}
	bool Registrar::cancelCourse(const string& courseName) {
		size_t courseInd = findCourse(courseName);
		if (courseInd != -1) {
			for (size_t i = 0; i < students.size(); ++i) {
				students[i]->removedFromCourse(courses[courseInd]);
			}
			for (size_t i = 0; i < courses.size(); ++i) {
				if (courseInd = i) {
					courses[i]->removeStudentsFromCourse();
					for (size_t j = i; j < courses.size() - 1; ++i) {
						courses[j] = courses[j + 1];
					}
					courses.pop_back();
				}
			}
			return true;
		}
		return false;
	}

	void Registrar::purge() {
		for (size_t i = 0; i < students.size(); ++i) {
			delete students[i];
		}
		students.clear();
		for (size_t i = 0; i < courses.size(); ++i) {
			delete courses[i];
		}
		courses.clear();
	}
}