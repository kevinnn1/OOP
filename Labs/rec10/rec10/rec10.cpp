/*
Kevin Grajeda
rec10
Inheritance
*/

#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
	virtual void makeSound() = 0;
	virtual void playNormal() = 0;
private:
};
void Instrument::makeSound() { cout << "To make a sound..."; }

class Brass : public Instrument {
public:
	Brass(unsigned mouthPieceSize)
		: size(mouthPieceSize) {}
	void makeSound() {
		Instrument::makeSound();
		cout << "blow on a mouthpiece of size " << size << endl;
	}
private:
	unsigned size;
};
class String : public Instrument{
public:
	String(unsigned stringPitch)
		: pitch(stringPitch) {}
	void makeSound() {
		Instrument::makeSound();
		cout << "bow a string with pitch " << pitch << endl;
	}
private:
	unsigned pitch;
};
class Percussion : public Instrument {
public:
	Percussion() {} 
	void makeSound() {
		Instrument::makeSound();
		cout << "hit me" << endl;
	}
private:
};
class Drum : public Percussion {
public:
	using Percussion::Percussion;
	void playNormal() { cout << "Boom"; }
private:
};
class Cymbal : public Percussion {
public:
	using Percussion::Percussion;
	void playNormal() { cout << "Crash"; }
private:
};
class Trombone : public Brass {
public:
	using Brass::Brass;
	void playNormal() { cout << "Blat"; }
private:
};
class Trumpet : public Brass {
public:
	using Brass::Brass;
	void playNormal() { cout << "Toot"; }
private:
};
class Violin : public String {
public:
	using String::String;
	void playNormal() { cout << "Screech"; }
private:
};
class Cello : public String {
public:
	using String::String;
	void playNormal() { cout << "Squawk"; }
private:
};

class MILL {
public:
	void receiveInstr(Instrument& instrument) {
		instrument.makeSound();
		Instrument* instrumentPtr = &instrument;
		for (size_t i = 0; i < instruments.size(); ++i) {
			if (instruments[i] == nullptr) {
				instruments[i] = instrumentPtr;
				return;
			}
		}
		instruments.push_back(instrumentPtr);
	}
	void dailyTestPlay() {
		for (size_t i = 0; i < instruments.size(); ++i) {
			if (instruments[i] != nullptr) {
				instruments[i]->makeSound();
			}
		}
	}
	Instrument* loanOut() {
		for (size_t i = 0; i < instruments.size(); ++i) {
			if (instruments[i] != nullptr) {
				Instrument* instrumentLoaned = instruments[i];
				instruments[i] = nullptr;
				return instrumentLoaned;
			}
		}
		return nullptr;
	}
private:
	vector<Instrument*> instruments;
};

class Musician {
public:
	Musician() : instr(nullptr) {}

	void acceptInstr(Instrument* instPtr) { instr = instPtr; }

	Instrument* giveBackInstr() {
		Instrument* result(instr);
		instr = nullptr;
		return result;
	}

	void testPlay() const {
		if (instr) instr->makeSound();
		else cerr << "have no instr\n";
	}
	Instrument* getInstrument() const { return instr; }
private:
	Instrument* instr;
};

class Orch {
public:
	void addPlayer(Musician& player) {
		Musician* musicianPtr = &player;
		orchestra.push_back(musicianPtr);
	}
	void play() {
		for (size_t i = 0; i < orchestra.size(); ++i) {
			if (orchestra[i]->getInstrument() != nullptr) {
				orchestra[i]->getInstrument()->playNormal();
			}
		}
		cout << endl;
	}
private:
	vector<Musician*> orchestra;
};
// PART ONE
int main() {

	 cout << "Define some instruments ------------------------------------\n";
	 Drum drum;
	 Cello cello(673);
	 Cymbal cymbal;
	 Trombone tbone(4);
	 Trumpet trpt(12) ;
	 Violin violin(567) ;

	 // use the debugger to look at the mill
	 cout << "Define the MILL --------------------------------------------\n";
	 MILL mill;
	 mill.receiveInstr(trpt);
	 mill.receiveInstr(violin);
	 mill.receiveInstr(tbone);
	 mill.receiveInstr(drum);
	 mill.receiveInstr(cello);
	 mill.receiveInstr(cymbal);
	 cout << endl;
	 Musician bob;
	 Musician sue;
	 Musician mary;
	 Musician ralph;
	 Musician jody;
	 Musician morgan;

	 Orch orch;
	 
	 // THE SCENARIO

	 //Bob joins the orchestra without an instrument.
	 orch.addPlayer(bob);

	 //The orchestra performs
	 cout << "orch performs\n";
	 orch.play();

	 //Sue gets an instrument from the MIL2 and joins the orchestra.
	 sue.acceptInstr(mill.loanOut());
	 orch.addPlayer(sue);

	 //Ralph gets an instrument from the MIL2.
	 ralph.acceptInstr(mill.loanOut());

	 //Mary gets an instrument from the MIL2 and joins the orchestra.
	 mary.acceptInstr(mill.loanOut());
	 orch.addPlayer(mary);

	 //Ralph returns his instrument to the MIL2.
	 mill.receiveInstr(*ralph.giveBackInstr());

	 //Jody gets an instrument from the MIL2 and joins the orchestra.
	 jody.acceptInstr(mill.loanOut());
	 orch.addPlayer(jody);

	 // morgan gets an instrument from the MIL2
	 morgan.acceptInstr(mill.loanOut());

	 //The orchestra performs.
	 cout << "orch performs\n";
	 orch.play();

	 //Ralph joins the orchestra.
	 orch.addPlayer(ralph);

	 //The orchestra performs.
	 cout << "orch performs\n";
	 orch.play();

	 // bob gets an instrument from the MIL2
	 bob.acceptInstr(mill.loanOut());

	 // ralph gets an instrument from the MIL2
	 ralph.acceptInstr(mill.loanOut());

	 //The orchestra performs.
	 cout << "orch performs\n";
	 orch.play();

	 //Morgan joins the orchestra.
	 orch.addPlayer(morgan);

	 //The orchestra performs.
	 cout << "orch performs\n";
	 orch.play();

	 /*
	 cout << "Put the instruments into the MILL --------------------------\n";
	 mill.receiveInstr(trpt);
	 mill.receiveInstr(violin);
	 mill.receiveInstr(tbone);
	 mill.receiveInstr(drum);
	 mill.receiveInstr(cello);
	 mill.receiveInstr(cymbal);

	 cout << "Daily test -------------------------------------------------\n";
	 cout << endl;
	 cout << "dailyTestPlay()" << endl;
	 mill.dailyTestPlay();
	 cout << endl;

	 cout << "Define some Musicians---------------------------------------\n";
	 Musician harpo;
	 Musician groucho;

	cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
	groucho.testPlay();	
	cout << endl;
	groucho.acceptInstr(mill.loanOut());
	cout << endl;
	groucho.testPlay();
	cout << endl;
	cout << "dailyTestPlay()" << endl;
	mill.dailyTestPlay();

	cout << endl << endl;

	groucho.testPlay();	
	cout << endl;
	mill.receiveInstr(*groucho.giveBackInstr());
	harpo.acceptInstr(mill.loanOut());
	groucho.acceptInstr(mill.loanOut());
	cout << endl;
	groucho.testPlay();
	cout << endl;
	harpo.testPlay();
	cout << endl;
	cout << "dailyTestPlay()" << endl;
	mill.dailyTestPlay();

	cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

    // fifth
	mill.receiveInstr(*groucho.giveBackInstr());
	cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
	mill.receiveInstr(*harpo.giveBackInstr());


	cout << endl;
	cout << "dailyTestPlay()" << endl;
	mill.dailyTestPlay();
	cout << endl;

	cout << endl;
	*/
}
