/*
Kevin Grajeda
rec05.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Section {
public:
	friend ostream& operator<<(ostream& stream, Section& section) {
		cout << "Section: " << section.sectionName << ", Time Slot: " << section.sectionTimeSlot << ", Students: " << section.sectionStudents << endl;
		return stream;
	}
	Section(const string& name, const string& day, const unsigned hour)
		: sectionName(name), sectionTimeSlot(day, hour) {}
	Section(const Section& anotherSection)
		: sectionName(anotherSection.sectionName), sectionTimeSlot(anotherSection.sectionTimeSlot) {
		for (size_t i = 0; i < sectionStudents.size(); ++i) {
			Student* newStudent = new Student(*sectionStudents[i]);
			sectionStudents.push_back(newStudent);
		}
	}
	void addStudent(const string& name) {
		Student* student = new Student(name);
		sectionStudents.push_back(student);
	}
	void newGrade(const string& name, const int grade, const int week) {
		for (size_t i = 0; i < sectionStudents.size(); ++i) {
			if (sectionStudents[i]->getName() == name) {
				sectionStudents[i]->getGrades()[week - 1] = grade;
			}
		}
	}
	~Section() {
		cout << "Section " << this << " is being deleted" << endl;
		for (size_t i = 0; i < sectionStudents.size(); i++) {
			cout << "Deleting " << sectionStudents[i]->getName() << endl;
			delete sectionStudents[i];
		}
	}
private:
	class TimeSlot {
	public:
		friend ostream& operator<<(ostream& stream, TimeSlot timeslot) {
			int convertedTime = timeslot.timeSlotHour;
			string timeOfDay = "am";
			if (timeslot.timeSlotHour > 12) {
				convertedTime = timeslot.timeSlotHour - 12;
				timeOfDay = "pm";
			}
			cout << "[Day: " << timeslot.timeSlotDay << ", Start time: " << convertedTime << timeOfDay << "]";
			return stream;
		}
		TimeSlot(const string& day, const unsigned hour)
			: timeSlotDay(day), timeSlotHour(hour) {}
	private:
		string timeSlotDay;
		unsigned timeSlotHour;
	};
	class Student {
	public:
		friend ostream& operator<<(ostream& stream, vector<Student*> students) {
			if (students.size() == 0) {
				cout << "None";
			}
			cout << endl;
			for (size_t i = 0; i < students.size(); i++) {
				cout << "Name: " << students[i]->studentName << ", Grades: ";
				for (size_t j = 0; j < students[i]->studentGrades.size(); ++j) {
					cout << students[i]->studentGrades[j];
				}
				cout << endl;
			}
			return stream;
		}
		Student(const string& name)
			: studentName(name), studentGrades(14, -1) {}
		string getName() {
			return  studentName;
		}
		vector<int> getGrades() {
			return studentGrades;
		}
	private:
		string studentName;
		vector<int> studentGrades;
	};
	string sectionName;
	TimeSlot sectionTimeSlot;
	vector<Student*> sectionStudents;
};
class LabWorker {
public:
	friend ostream& operator<<(ostream& stream, LabWorker& worker) {

		if (worker.workerSection == nullptr) {
			cout << worker.workerName << " does not have a section" << endl;
		}
		else {
			cout << worker.workerName << " has: " << *(worker.workerSection) << endl;
		}
		return stream;
	}
	LabWorker(const string& name)
		: workerName(name), workerSection(nullptr) {}
	void addSection(Section addedSection) {
		workerSection = &addedSection;
	}
	void addGrade(const string& name, const int grade, const int week) {
		workerSection->newGrade(name, grade, week);
	}
private:
	string workerName;
	Section* workerSection;
};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	cout << secA2 << endl;
	
	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe( "Moe" );
	cout << moe << endl;

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection( secA2 );
	cout << moe << endl;

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane( "Jane" );
	Section secB3( "B3", "Thursday", 11 );
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection( secB3 );
	cout << jane << endl;
	
	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);  
	moe.addGrade("Paul", 19, 1);  
	moe.addGrade("George", 16, 1);  
	moe.addGrade("Ringo", 7, 1);  
	cout << moe << endl;
	;
	
	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);  
	moe.addGrade("Paul", 20, 3);  
	moe.addGrade("Ringo", 0, 3);  
	moe.addGrade("George", 16, 3);  
	cout << moe << endl;

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
		<< "those students (or rather their records?)\n";

	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works:\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";

} // main
