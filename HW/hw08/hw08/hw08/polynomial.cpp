#include <vector>
#include <iostream>
#include <string>
#include "Polynomial.h"
using namespace std;

namespace Polynomials {
	struct Polynomial::Node {
		friend ostream& operator<<(ostream& os, Polynomial::Node node) {
			if (node.exponent == 0) {
				cout << node.coeff;
			}
			else if (node.coeff == 1 && node.exponent == 1) {
				cout << "x + ";
			}
			else if (node.exponent == 1 && node.coeff != 0) {
				cout << node.coeff << "x + ";
			}
			else if (node.coeff == 1) {
				cout << "x^" << node.exponent << " + ";
			}
			else if (node.coeff != 0) {
				cout << node.coeff << "x^" << node.exponent << " + ";
			}
			return os;
		}
		Polynomial::Node(int num = 0, int exp = 0, Polynomial::Node * nextNum = nullptr)
			: coeff(num), exponent(exp), next(nextNum) {};

		int coeff;
		int exponent;
		Node* next;
	};
	ostream& operator<<(ostream& os, const Polynomial& node) {
		int count = node.degree + 1;
		Polynomial::Node* current = node.header->next;
		Polynomial::Node* reset = current;
		for (size_t i = 0; i < node.degree + 1; ++i) {
			for (size_t j = 0; j < count; j++) {
				if (current->exponent == count) {
					cout << *current;
				}
				current = current->next;
			}
			current = reset;
			current = current->next;
			--count;
		}
		cout << *reset;
		return os;
	}
	bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
		if (lhs.degree != rhs.degree) {
			cout << "False";
			return false;
		}
		Polynomial::Node* lhsStart = lhs.header->next;
		Polynomial::Node* rhsStart = rhs.header->next;
		for (size_t i = 0; i < lhs.degree + 1; ++i) {
			if (lhsStart->coeff != rhsStart->coeff
				&& lhsStart->exponent != rhsStart->exponent) {
				cout << "False";
				return false;
			}
			lhsStart = lhsStart->next;
			rhsStart = rhsStart->next;
		}
		cout << "True";
		return true;
	}
	bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
		return !(lhs == rhs);
	}
	Polynomial::Polynomial()
		: header(new Node), degree(0) {}
	Polynomial::Polynomial(const vector<int>& listOfCoeff)
		: header(new Node()), degree(listOfCoeff.size() - 1) {
		Node* current = header;
		for (size_t i = 0; i < degree + 1; ++i) {
			current->next = new Node(listOfCoeff[degree - i], i, nullptr);
			current = current->next;
		}
	}

	Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
		Polynomial addedRhs = rhs;
		if (rhs.degree > degree) {
			Polynomial temp = *this;
			*this = addedRhs;
			addedRhs = temp;
		}
		Polynomial lhs = *this;
		Node* start = lhs.header->next;
		Node* rhsStart = addedRhs.header->next;
		for (size_t i = 0; i < addedRhs.degree + 1; ++i) {
			start->coeff += rhsStart->coeff;
			start = start->next;
			rhsStart = rhsStart->next;
		}
		return *this;
	}
	Polynomial Polynomial::operator+(const Polynomial& rhs) {
		Polynomial result(*this);
		return result += rhs;
	}
	int Polynomial::evaluate(int x) {
		int sum = 0;
		Node* current = header->next;
		for (size_t i = 0; i < degree + 1; ++i) {
			int product = pow(x, current->exponent) * current->coeff;
			sum += product;
			current = current->next;
		}
		return sum;
	}
	void doNothing(Polynomial temp) {};


}

