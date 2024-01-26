/*
	Kevin Grajeda
	rec08.cpp
	CS2124
	Operator overloading for the Rational class
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// If time allows use  separate compilation, otherwise just define the class below
// #include "Rational.h"
// If time allows after implementing separate compilation, then wrap the class in a namespace.
// using namespace CS2124;

class Rational {
	friend ostream& operator<<(ostream& os, const Rational& number) {
		int gcd = abs(greatestCommonDivisor(number.numerator, number.denominator));
		if (number.numerator < 0 && number.denominator < 0) {
			cout << -1*(number.numerator / gcd) << "/" << -1*(number.denominator / gcd);
		}
		else {
			cout << number.numerator / gcd << "/" << number.denominator / gcd;
		}
		return os;
	}
	friend istream& operator>>(istream& in, Rational& number) {
		in >> number.numerator;
		in.ignore();
		in >> number.denominator;
		return in;
	}
	friend bool operator==(const Rational& lhs, const Rational& rhs) {
		return (lhs.numerator / lhs.denominator) == (rhs.numerator / rhs.denominator);
	}
	friend bool operator<(const Rational& lhs, const Rational& rhs) {
		return (lhs.numerator / lhs.denominator) < (rhs.numerator / rhs.denominator);
	}

public:
	Rational(int integerNum = 0, int integerDen = 1) 
		: numerator(integerNum), denominator(integerDen){
	}
	Rational& operator+=(const Rational& rhs) {
		int addend = rhs.numerator * denominator;
		numerator *= rhs.denominator;
		denominator *= rhs.denominator;
		numerator += addend;
		return *this;
	}
	Rational& operator++() {
		Rational addend(1, 1);
		*this += addend;
		return *this;
	}
	Rational operator++(int dummy) {
		Rational original(*this);
		Rational addend(1, 1);
		*this += addend;
		return original;
	}
	explicit operator bool() const {
		return numerator != 0;
	}
private:
	int numerator;
	int denominator;
};


int greatestCommonDivisor(int x, int y) {
	while (y != 0) {
		int temp = x % y;
		x = y;
		y = temp;
	}
	return x;
}
Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational result(lhs);
	return result += rhs;
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}
Rational& operator--(Rational& number) {
	Rational operand(-1, 1);
	number += operand;
	return number;
}
Rational operator--(Rational& number, int dummy) {
	Rational operand(-1, 1);
	Rational original(number);
	number += operand;
	return original;
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
	return !(lhs < rhs);
}
bool operator>(const Rational& lhs, const Rational& rhs) {
	return !(lhs <= rhs);
}

int main() {
	Rational twoThirds(2, 3);
	cout << twoThirds << endl;

	Rational a, b;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "a: ";
	cin >> a;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "b: ";
	cin >> b;
	const Rational one = 1;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "b < a " << boolalpha << (b < a) << endl;
	cout << "b <= a " << boolalpha << (b <= a) << endl;
	cout << "b > a " << boolalpha << (b > a) << endl;
	cout << "b >= a " << boolalpha << (b >= a) << endl;
	cout << "one = " << one << endl;
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;
	
	// Implement as non-member, but not a friend
	cout << "a + one: " << (a + one) << endl;
	cout << "a == one: " << boolalpha << (a == one) << endl;
	
	// How does this manage to work?
	// It does NOT require writing another == operator.
	cout << "1 == one: " << boolalpha << (1 == one) << endl;
	
	// Do not implement as friend.
	cout << "a != one: " << boolalpha << (a != one) << endl;

	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;
	
	cout << "++ ++a = " << (++ ++a) << endl;
	cout << "a = " << a << endl;
	cout << "-- --a = " << (-- --a) << endl;
	cout << "a = " << a << endl;
	
	cout << "a++ ++ = " << (a++ ++) << endl;
	cout << "a = " << a << endl;
	
	// Even though the above example, (a++ ++), compiled, the
	// following shouldn't.
	// But some compiler vendors might let it...  Is your compiler
	// doing the right thing?
	//cout << "a-- -- = " << (a-- --) << endl;
	//cout << "a = " << a << endl;
	

	// Should report that 1 is true
	if (Rational(1)) {
		cout << "1 is true" << endl;
	}
	else {
		cout << "1 is false" << endl;
	}
	// Should report that 0 is false
	if (Rational(0)) {
		cout << "0 is true" << endl;
	}
	else {
		cout << "0 is false" << endl;
	}
}