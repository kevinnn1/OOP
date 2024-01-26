#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>

namespace Polynomials {
	class Polynomial {
		friend std::ostream& operator<<(std::ostream& os, const Polynomial& node);
		friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
		friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
	public:
		Polynomial();
		Polynomial(const std::vector<int>& listOfCoeff);
		//Polynomial(const Polynomial& rhs);
		//Polynomial& operator=(const Polynomial& rhs);
		//~Polynomial();
		Polynomial& operator+=(const Polynomial& rhs);
		Polynomial operator+(const Polynomial& rhs);
		int evaluate(int x);
	private:
		struct Node;
		Node* header;
		unsigned degree;
	};
	void doNothing(Polynomial temp);
}

#endif