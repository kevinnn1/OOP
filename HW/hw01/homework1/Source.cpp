//Kevin Grajeda
//hw01.cpp
//Takes an a file encryped by the Caeser cypher and decodes it

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

char decrypt(char encryptedChar, int numberOfSteps);
void decryptString(string& encryptedString, int numberOfSteps);
const int WRAP_AROUND = 26;

int main() {
	ifstream encryption("encryption.txt");
	if (!encryption) { //checks to see if the file can be read
		cerr << "Failed to open file";
		exit(1);
	}
	int step;
	encryption >> step;
	encryption.close();
	encryption.open("encryption.txt");
	string line;
	vector<string> decryptedLines;
	while(getline(encryption, line)){ //decrypts each line individually and adds them to the vector
		decryptString(line, step);
		decryptedLines.push_back(line);
	}
	for(size_t ind = decryptedLines.size()-1; ind > 0; --ind){ //iterates throught the vector in reverse and prints the lines in index
		cout << decryptedLines[ind] << endl;
	}

}
char decrypt(char encryptedChar, int numberOfSteps) {
	char decryptedChar;
	if (encryptedChar < 'a' || encryptedChar > 'z') { //checks if the character is a lower case letter
		decryptedChar = encryptedChar;
	}
	else {
		decryptedChar = encryptedChar - numberOfSteps; //undoes the Caeser cypher
		if (decryptedChar < 'a') { //checks if the character is outside the range of lower case letters
			decryptedChar = decryptedChar + WRAP_AROUND; //fixes the encrypted character to its correct decrypted character
		}
	}
	return decryptedChar;
}
void decryptString(string& encryptedString, int numberOfSteps) {
	for (size_t ind = 0; ind < encryptedString.size(); ++ind) { //decrypts each character in the string using decryptChar
		encryptedString[ind] = decrypt(encryptedString[ind], numberOfSteps);
	}
}