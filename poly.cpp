///////////////////////////////// poly.cpp /////////////////////////////////
#include "poly.h"

//------------------------------------------------------------------------------
// Default Constructor
Poly::Poly()
{
	highestDegree = 0;
	coefficients = new double[highestDegree+1]();
	
}

//------------------------------------------------------------------------------
// Constructor
Poly::Poly(const double& coeff, const int& degree)
{
	if (degree >= 0)
	{
		highestDegree = degree;
		coefficients = new double[highestDegree + 1]();
		coefficients[degree] = coeff;
	}
	else
	{
		highestDegree = 0;
		coefficients = new double[highestDegree + 1]();
		
	}
	
	
}

//------------------------------------------------------------------------------
// Copy Constructor
Poly::Poly(const Poly& copy)
{
	highestDegree = copy.highestDegree;
	coefficients = new double[highestDegree + 1]();

	for (int i = 0; i < copy.highestDegree + 1; i++)
	{
		coefficients[i] = copy.coefficients[i];
	}
}

//------------------------------------------------------------------------------
// Destructor
Poly::~Poly()
{
	delete[] coefficients;
	coefficients = nullptr;
}

//------------------------------------------------------------------------------
// getCoeff
// --Returns the coefficient if array holds the degree
//   else it returns 0
int Poly::getCoeff(const int& degree) const
{
	int coefficaint = 0;
	if (degree <= highestDegree && degree >= 0)
	{
		coefficaint = coefficients[degree];
	}

	return coefficaint;
}

//------------------------------------------------------------------------------
// setCoeff
// --If degree is larger than array, array grows
//   then stores coeff at array[degree]
// --Else if degree is valid, then stores coeff
//   at array[degree]
// --Else if degree is not valid, it does nothing
void Poly::setCoeff(const double& coeff, const int& degree)
{
	if (degree > this->highestDegree)
	{
		Poly temp = *this;
		delete[] this->coefficients;
		this->highestDegree = degree;
		this->coefficients = new double[highestDegree + 1]();

		for (int i = 0; i < temp.highestDegree + 1; i++)
		{
			this->coefficients[i] = temp.coefficients[i];
		}

		this->coefficients[degree] = coeff;
		
	}
	else if (degree >= 0)
	{
		this->coefficients[degree] = coeff;
	}

}

//------------------------------------------------------------------------------
// clearCoeff
// --Clears the whole array by having all coeffs = 0
void Poly::clearCoeff()
{
	for (int i = 0; i < this->highestDegree + 1; i++)
	{
		this->coefficients[i] = 0;
	}
}

//------------------------------------------------------------------------------
// isEmpty
// --Checks if all coeffs are 0
//   if so then returns true
bool Poly::isEmpty() const
{
	bool check = true;

	for (int i = 0; i < highestDegree + 1 && check; i++)
	{
		if (coefficients[i] != 0)
		{
			check = false;
		}
	}

	return check;
}

//------------------------------------------------------------------------------
// operator +
// --Adds 2 polynomials together
//	 and returns the summation

Poly Poly::operator+(const Poly& other) const
{
	int size = maxDegree(*this, other);
	Poly combination(0, size);

	for (int i = 0; i < this->highestDegree + 1; i++)
	{
		combination.coefficients[i] = this->coefficients[i];
	}

	for (int i = 0; i < other.highestDegree + 1; i++)
	{
		combination.coefficients[i] += other.coefficients[i];
	}

	return combination;
}

//------------------------------------------------------------------------------
// operator +=
// --Adds 2 polynomials
//   and assigns the summation to caller of function
Poly& Poly::operator+=(const Poly& other)
{
	*this = *this + other;
	return *this;
}

//------------------------------------------------------------------------------
// operator -
// --Subtracts 2 polynomials
//   and returns the deduction
Poly Poly::operator-(const Poly& other) const
{
	int size = maxDegree(*this, other);
	Poly combination(0, size);

	for (int i = 0; i < this->highestDegree + 1; i++)
	{
		combination.coefficients[i] = this->coefficients[i];
	}

	for (int i = 0; i < other.highestDegree + 1; i++)
	{
		combination.coefficients[i] -= other.coefficients[i];
	}

	return combination;
}

//------------------------------------------------------------------------------
// operator -=
// --Subtracts 2 polynomials
//   and assigns the deduction to caller of the function
Poly& Poly::operator-=(const Poly& other)
{
	*this = *this - other;
	return *this;
}

//------------------------------------------------------------------------------
// operator *
// --Multiplies 2 polynomials
//   and returns the product
Poly Poly::operator*(const Poly& other)
{
	int size = this->highestDegree + other.highestDegree;
	Poly combination(0, size);

	for (int i = 0; i < this->highestDegree + 1; i++)
	{
		for (int j = 0; j < other.highestDegree + 1; j++)
		{
			combination.coefficients[i + j] += 
				this->coefficients[i] * other.coefficients[j];
		}
	}

	return combination;

}

//------------------------------------------------------------------------------
// operator *=
// --Multiplies 2 polynomials
//   and assigns the product to caller of function
Poly& Poly::operator*=(const Poly& other)
{
	*this = *this * other;
	return *this;
}

//------------------------------------------------------------------------------
// operator ==
// --Checks if 2 poloynomials are
//   the same, if so returns true
bool Poly::operator==(const Poly& other) const
{
	bool comparison = true;
	if (this->highestDegree != other.highestDegree) //if one array is larger than the other
	{												//the other then will 
													//pick smaller array to check first
		if (this->highestDegree < other.highestDegree)
		{
			for (int i = 0; i < this->highestDegree + 1 && comparison; i++)
			{
				if (this->coefficients[i] != other.coefficients[i])
				{
					comparison = false;
				}
			}

			for (int i = this->highestDegree + 1; i < other.highestDegree + 1 && comparison; i++)
			{                                                                                     
				if (other.coefficients[i] != 0)
				{
					comparison = false;
				}
			}
		}
		else
		{
			for (int i = 0; i < other.highestDegree + 1 && comparison; i++)
			{
				if (this->coefficients[i] != other.coefficients[i])
				{
					comparison = false;
				}
			}

			for (int i = other.highestDegree + 1; i < this->highestDegree + 1 && comparison; i++)
			{
				if (this->coefficients[i] != 0)
				{
					comparison = false;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < this->highestDegree + 1 && comparison; i++)
		{
			if (this->coefficients[i] != other.coefficients[i])
			{
				comparison = false;
			}
		}
	}
	

	return comparison;
}

//------------------------------------------------------------------------------
// operator !=
// --Checks if 2 polynomials are 
//	 not the same, if so then returns true
bool Poly::operator!=(const Poly& other) const
{
	return !(*this == other);
}

//------------------------------------------------------------------------------
// operator =
// --If right value(pNomial) is not *this, then it 
//   first determines if it needs to grow.
// --If it does not need to grow, *this will clear 
//   its coeffs and then copy pNomials coeffs
// --If it does need to grow, then it grows, and the copies
//   pNomials values
Poly& Poly::operator=(const Poly& pNomial)
{
	if (this != &pNomial)
	{
		if (pNomial.highestDegree <= this->highestDegree)
		{
			this->clearCoeff();

			for (int i = 0; i < pNomial.highestDegree + 1; i++)
			{
				this->coefficients[i] = pNomial.coefficients[i];
			}
		}
		else
		{
			delete[] this->coefficients;
			this->highestDegree = pNomial.highestDegree;
			this->coefficients = new double[this->highestDegree + 1]();

			for (int i = 0; i < pNomial.highestDegree + 1; i++)
			{
				this->coefficients[i] = pNomial.coefficients[i];
			}
		}
		
	}

	return *this;
}

//------------------------------------------------------------------------------
// maxDegree
// --Returns largest degree between 
//   2 polynomials
int Poly::maxDegree(const Poly& a, const Poly& b) const
{
	int max = a.highestDegree;

	if (b.highestDegree > a.highestDegree)
	{
		max = b.highestDegree;
	}

	return max;
	
}

//------------------------------------------------------------------------------
// operator >>
// --Will take in as many paired inputs until
//   user inputs -1 -1 to stop
std::istream & operator>>(std::istream& input, Poly& pNomial)
{
	bool keepGoing = true;
	int tempCoeff = 0;
	int tempPower = 0;


	do
	{
		input >> tempCoeff;
		input >> tempPower;

		if (tempCoeff == -1 && tempPower == -1)
		{
			keepGoing = false;
		}
		else
		{
			pNomial.setCoeff(tempCoeff, tempPower);
		}
	} while (keepGoing);

	return input;
}

//------------------------------------------------------------------------------
// operator << 
// --Will output polynomial from largest degree to
//   smallest.
std::ostream& operator<<(std::ostream& output, const Poly& pNomial)
{
	if (!pNomial.isEmpty())
	{
		for (int i = pNomial.highestDegree; i >= 0; i--)
		{
			if (pNomial.coefficients[i] != 0)
			{
				if (i == 1)
				{
					if (pNomial.coefficients[i] >= 1)// checking if positive
					{
						output << " +" << pNomial.coefficients[i] << "x";
					}
					else
					{
						output << " " << pNomial.coefficients[i] << "x";
					}
				}
				else if (i == 0)
				{
					if (pNomial.coefficients[i] >= 1)
					{
						output << " +" << pNomial.coefficients[i];
					}
					else
					{
						output << " " << pNomial.coefficients[i];
					}
				}
				else
				{
					if (pNomial.coefficients[i] >= 1)
					{
						output << " +" << pNomial.coefficients[i] << "x^" << i;
					}
					else
					{
						output << " " << pNomial.coefficients[i] << "x^" << i;
					}

				}
			}	
			
		}
	}
	else
	{
		output << " 0";
	}

	

	return output;
	
}
