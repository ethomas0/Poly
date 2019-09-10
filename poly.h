//////////////////////////////////////// poly.h file ///////////////////////////
#ifndef POLY_H
#define POLY_H
#include <iostream>

// --------------------------class Poly------------------------------------
// ADT Polynomial: finite, ordered collection of zero or more coefficiants
//                 the coefficiants are stored using their degree as the index
//
//
// Implementation and assumptions:
//	-- Implemented using a dynamic array
//	-- At miniumum when an instance is created, array size is 1
//	   array will never be smaller than size 1
//	-- Array will always grow, but will never shrink
//	-- Assumes user will enter correct data type
//     and will always enter paired inputs (except for constructor)
//	-- Class function explanations are documented in cpp
// ------------------------------------------------------------------------
class Poly
{
	friend std::istream& operator>>(std::istream& input, Poly& pNomial);
	friend std::ostream& operator<<(std::ostream& output, const Poly& pNomial);

	public:
		Poly();	
		Poly(const double& coeff, const int& degree = 0);	
		Poly(const Poly& copy);	
		~Poly();	

		int getCoeff(const int& degree)const;	
		void setCoeff(const double& coeff, const int& degree);	
			

		Poly operator+(const Poly& other) const;
		Poly& operator+=(const Poly& other);

		Poly operator-(const Poly& other) const;
		Poly& operator-=(const Poly& other);

		Poly operator*(const Poly& other);
		Poly& operator*=(const Poly& other);

		bool operator==(const Poly& other) const; 
		bool operator !=(const Poly& other) const;

		Poly& operator=(const Poly& pNomial);
	
	private:
		int maxDegree(const Poly& a, const Poly& b) const;
		void clearCoeff();
		bool isEmpty()const;

		double* coefficients;
		int highestDegree;


};
#endif // !POLY_H
