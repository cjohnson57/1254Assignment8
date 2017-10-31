#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "Fraction.h"
#include "RatDec.h"

using namespace std;

/***************************************************/
bool VectorContains(vector<unsigned long long int> v, unsigned long long int element)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == element)
		{
			return true;
		}
	}
	return false;
}

/***************************************************/

string findAfterDec(vector<unsigned long long int> v1, vector<unsigned long long int> v2, unsigned long long int element)
{
	int index = 0;
	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[i] == element)
		{
			index = i;
			break;
		}
	}
	string afterdec = "";
	for (int i = 0; i < index; i++)
	{
		afterdec += to_string(v1[i]);
	}
	return afterdec;

} /* to string */

/***************************************************/

string findRepeat(vector<unsigned long long int> v1, vector<unsigned long long int> v2, unsigned long long int element)
{
	int index = 0;
	for (int i = 0; i < v2.size(); i++)
	{
		if (v2[i] == element)
		{
			index = i;
			break;
		}
	}
	string repeat = "";
	for (int i = index; i < v1.size(); i++)
	{
		repeat += to_string(v1[i]);
	}
	return repeat;

} /* to string */

  /***************************************************/

string RatDec::toString(void) const
{
	return (isNeg ? "-" : "") + wholeNum + "." + afterDec + "." + repeat;
} /* to string */

/***************************************************/

RatDec *RatDec::fracToDec(Fraction *f) const
{
	unsigned long long int denom = f->getDenom();
	unsigned long long int num = f->getNum();
	RatDec *temp = new RatDec();
	temp->isNeg = f->getIsNeg();
	temp->wholeNum = to_string(num / denom);
	num %= denom;
	vector<unsigned long long int> remList;
	vector<unsigned long long int> quotientList;

	unsigned long long int rem;
	remList.push_back(num);
	while (true)
	{
		num *= 10;
		unsigned long long int next = num / denom;
		rem = num % denom;
		if (VectorContains(remList, rem))
		{
			
			string ad = "";
			for (int i = 0; i < quotientList.size(); i++)
			{
				ad += to_string(quotientList[i]);
			}
			temp->afterDec = findAfterDec(quotientList, remList, rem);
			temp->repeat = findRepeat(quotientList, remList, rem) + to_string(next);
			break;
		}
		else
		{
			num -= denom * next;
			quotientList.push_back(next);
			remList.push_back(rem);
		}
	}
	return temp;

} /* frac to rat */

/***************************************************/

Fraction *RatDec::decToFrac(void) const
{
	string approximationstring = wholeNum + "." + afterDec + repeat + repeat + repeat + repeat + repeat + repeat + repeat + repeat + repeat + repeat + repeat + repeat + repeat;
	double approximation = stod(approximationstring);
	double decimal = approximation - stoi(wholeNum);
	int denominator;
	int numerator;
	if (decimal == 0)
	{
		denominator = 1;
		numerator = stoi(wholeNum);
	}
	else
	{
		denominator = 1 / decimal;
		numerator = 1 + denominator * stoi(wholeNum);
	}
	Fraction* f = new Fraction(numerator, denominator);
	f->setIsNeg(isNeg);
	return f;
} /* rat to frac */

/***************************************************/

bool RatDec::operator> (const RatDec& rhs) const
{
	Fraction oper1 = decToFrac();
	Fraction oper2 = rhs.decToFrac();
	return oper1 > oper2;
} /* greater than */

/***************************************************/

bool RatDec::operator< (const RatDec& rhs) const
{	
	return rhs > *this;
} /* less than */

/***************************************************/

bool RatDec::operator== (const RatDec& rhs) const
{
	return (*this >= rhs && *this <= rhs);
} /* equal to */

/***************************************************/

bool RatDec::operator!= (const RatDec& rhs) const
{	
	return(!(*this == rhs));
} /* not equal to */

/***************************************************/

bool RatDec::operator>= (const RatDec& rhs) const
{
	return (!(*this < rhs));
}

/***************************************************/

bool RatDec::operator<= (const RatDec& rhs) const
{
	return (!(*this > rhs));
}

/***************************************************/

RatDec* RatDec::operator+ (const RatDec& rhs)
{
	Fraction oper1 = decToFrac();
	Fraction oper2 = rhs.decToFrac();
	Fraction final = oper1 + oper2;
	return fracToDec(&final);
} /* plus */
	
/***************************************************/

RatDec* RatDec::operator- (const RatDec& rhs)
{
	Fraction oper1 = decToFrac();
	Fraction oper2 = rhs.decToFrac();
	Fraction final = oper1 - oper2;
	return fracToDec(&final);
} /* minus */
	
/***************************************************/

RatDec* RatDec::operator* (const RatDec& rhs)
{
	Fraction oper1 = decToFrac();
	Fraction oper2 = rhs.decToFrac();
	Fraction final = oper1 * oper2;
	return fracToDec(&final);
} /* multiply */
	
/***************************************************/

RatDec* RatDec::operator/ (const RatDec& rhs)
{
	Fraction oper1 = decToFrac();
	Fraction oper2 = rhs.decToFrac();
	Fraction final = oper1 / oper2;
	return fracToDec(&final);
} /* divide */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
