/*
Kevin Grajeda
rec03.cpp
Bank account and transactions tutorial
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std; 

/*
//Task 1
struct bankAccount{
	string accountName;
	int accountNumber;
};
void openStream(ifstream& stream) {
	string filename;
	cout << "Enter file name:";
	cin >> filename;
	stream.open(filename);
	while (!stream) {
		stream.clear();
		cout << "Invalid filename, re-enter file name: ";
		cin >> filename;
		stream.open(filename);
	}
}
void fillVector1a(ifstream& stream, vector<bankAccount>& baVector) {
	string name;
	int accNumber;
	while (stream >> name >> accNumber) {
		bankAccount account;
		account.accountName = name;
		account.accountNumber = accNumber;
		baVector.push_back(account);
	}
}
void fillVector1b(ifstream& stream, vector<bankAccount>& baVector) {
	string name;
	int accNumber;
	while (stream >> name >> accNumber) {
		bankAccount account{ name, accNumber };
		baVector.push_back(account);
	}
}
void displayVector(const vector<bankAccount>& baVector) {
	for (size_t i = 0; i < baVector.size(); ++i) {
		cout << "Name: " << baVector[i].accountName << ", " << "Account Number: "  << baVector[i].accountNumber << endl;
	}
}
int main() {
	ifstream accounts;
	vector<bankAccount> listOfAccounts;
	openStream(accounts);
	fillVector1a(accounts, listOfAccounts);
	displayVector(listOfAccounts);
	accounts.close();
	listOfAccounts.clear();
	openStream(accounts);
	fillVector1b(accounts, listOfAccounts);
	displayVector(listOfAccounts);
	accounts.close();
}
*/
//Task 3
class transactions {
public:
	transactions(int amount, string type)
		: amountDepOrWith(amount), depOrWith(type) {}
	string getTransactionType() {
		return depOrWith;
	}
	int getAmount() {
		return amountDepOrWith;
	}
private:
	int amountDepOrWith;
	string depOrWith;
};


//Task 2
class BankAccount {
	//Task 2
	friend ostream& operator<<(ostream& stream, vector<BankAccount>& baVector) {
		for (size_t i = 0; i < baVector.size(); ++i) {
			cout << "Account: Name: " << baVector[i].accountName << ", " << "Account Number: " << baVector[i].accountNumber << endl;
			//Task 3
			for (size_t j = 0; j < baVector[i].transactionHistory.size(); ++j) {
				cout << baVector[i].transactionHistory[j].getTransactionType() << ": " << baVector[i].transactionHistory[j].getAmount() << " "  << baVector[i].balance << endl;
			}
		}
		return stream;
	}
public:
	//Task 2
	BankAccount(const string& name, int accNumber)
		: accountName(name), accountNumber(accNumber) {}
	/*
	string getName() const {
		return accountName;
	}
	*/
	int getAccNumber() const {
		return accountNumber;
	}
	
	//Task 3
	void deposit(int amount) {
		balance = balance + amount;
		transactions Transaction(amount, "Deposit");
		transactionHistory.push_back(Transaction);
	}
	void withdraw(int amount) {
		balance = balance - amount;
		transactions Transaction(-amount, "Withdraw");
		if (amount < balance) {
			transactionHistory.push_back(Transaction);
		}
		else {
			cout << "Insufficient funds";
		}
	}

private:
	//Task 2
	string accountName;
	int accountNumber;
	//Task 3
	int balance;
	vector<transactions> transactionHistory;
};


void openStream(ifstream& stream) {
	string filename;
	cout << "Enter file name:";
	cin >> filename;
	stream.open(filename);
	while (!stream) {
		stream.clear();
		cout << "Invalid filename, re-enter file name: ";
		cin >> filename;
		stream.open(filename);
	}
}
//Task 2
void fillVectorPushBack(ifstream& stream, vector<BankAccount>& baVector) {
	string name;
	int accNumber;
	while (stream >> name >> accNumber) {
		baVector.push_back(BankAccount(name, accNumber));
	}
}
void fillVectorEmplaceBack(ifstream& stream, vector<BankAccount>& baVector) {
	string name;
	int accNumber;
	while (stream >> name >> accNumber) {
		baVector.emplace_back(name, accNumber);
	}
}
void readFile(ifstream& stream, vector<BankAccount>& accountList) {
	string word;
	while (stream >> word) {
		int accNum;
		int transactionAmount;
		stream >> accNum;
		stream >> transactionAmount;
		for (size_t i = 0; i < accountList.size(); ++i) {
			if (accountList[i].getAccNumber() == accNum) {
				if (word == "Deposit") {
					accountList[i].deposit(transactionAmount);
				}
				else {
					accountList[i].withdraw(transactionAmount);
				}
			}
		}
	}
}

/*
ostream& operator<<(ostream& stream, const vector<bankAccount>& baVector) {
	for (size_t i = 0; i < baVector.size(); ++i) {
		cout << "Name: " << baVector[i].getName() << ", " << "Account Number: " << baVector[i].getAccNumber() << endl;
	}
	return stream;
}
*/

int main() {
	ifstream accounts;
	vector<BankAccount> listOfAccounts;
	openStream(accounts);
	fillVectorEmplaceBack(accounts, listOfAccounts);
	cout << listOfAccounts;
	ifstream transactions;
	openStream(transactions);
	readFile(transactions, listOfAccounts);
	cout << listOfAccounts;
}


//Task 4