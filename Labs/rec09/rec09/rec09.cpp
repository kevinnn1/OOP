#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial(unsigned pages) :
		numberOfPages(pages) {}
	virtual void displayNumPages() const = 0; // { cout << numberOfPages; }
protected:
private:
	unsigned numberOfPages;
};
void PrintedMaterial::displayNumPages() const {
	cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned pages) :
		PrintedMaterial(pages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned pages) :
		PrintedMaterial(pages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned pages, unsigned indexPages) :
		Book(pages), numOfIndexPages(indexPages) {}
	void displayNumPages() const { 
		cout << "Pages: ";
		PrintedMaterial::displayNumPages(); 
		cout << "Index Pages: ";
		cout << numOfIndexPages << endl;
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned pages) :
		Book(pages) {}
	void displayNumPages() const {
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t(400, 25);
	t.displayNumPages();
	Novel n(200);
	n.displayNumPages();
	Magazine m(50);
	m.displayNumPages();

	cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
	cout << "Now with the virtual mechanism involved\n";
	PrintedMaterial* pmPtr;
	pmPtr = &t;
	pmPtr->displayNumPages();
}