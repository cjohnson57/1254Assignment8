#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "Fraction.h"

using namespace std;

/***************************************************/

void showDecimal(Fraction r)
{
	printf("%lf\n", (double)r.getNum() / (double)r.getDenom());
}

/***************************************************/

string Fraction::toString(void) const
{
	char r[100];

	if(getIsNeg())
		sprintf_s(r, "[-%llu / %llu]", getNum(), getDenom());
	else
		sprintf_s(r, "[%llu / %llu]", getNum(), getDenom());

	return string(r);
}

/***************************************************/

//bool Fraction::operator> (const Fraction& lhs, const Fraction& rhs)
bool Fraction::operator> (const Fraction& rhs) const
{	
	/* check signs */
	if(rhs.getIsNeg() && !this->getIsNeg())
		return true;
		
	if(!rhs.getIsNeg() && this->getIsNeg())
		return false;
	
	unsigned long long int rsNum = rhs.getNum();
	unsigned long long int rsDen = rhs.getDenom();
	unsigned long long int lsNum = this->getNum();
	unsigned long long int lsDen = this->getDenom();
	
	if(rhs.getIsNeg())
		return lsNum * rsDen < rsNum * lsDen;
	else
		return lsNum * rsDen > rsNum * lsDen;
} /* greater than */

/***************************************************/

bool Fraction::operator< (const Fraction& rhs) const
{	
	/* check signs */
	if(rhs.getIsNeg() && !this->getIsNeg())
		return false;
		
	if(!rhs.getIsNeg() && this->getIsNeg())
		return true;
		
	unsigned long long int rsNum = rhs.getNum();
	unsigned long long int rsDen = rhs.getDenom();
	unsigned long long int lsNum = this->getNum();
	unsigned long long int lsDen = this->getDenom();
		
	if(rhs.getIsNeg())
		return lsNum * rsDen > rsNum * lsDen;
	else
		return lsNum * rsDen < rsNum * lsDen;

} /* less than */

/***************************************************/

bool Fraction::operator== (const Fraction& rhs) const
{	
	/* check signs */
	if(rhs.getIsNeg() != this->getIsNeg())
		return false;

	unsigned long long int rsNum = rhs.getNum();
	unsigned long long int rsDen = rhs.getDenom();
	unsigned long long int lsNum = this->getNum();
	unsigned long long int lsDen = this->getDenom();
	
	return lsNum * rsDen == rsNum * lsDen;
} /* equal to */

/***************************************************/

bool Fraction::operator!= (const Fraction& rhs) const
{	
	return !(*this == rhs);
} /* not equal */

/***************************************************/

Fraction Fraction::operator+ (const Fraction& rhs) const
{
	unsigned long long int rsNum = rhs.getNum();
	unsigned long long int rsDen = rhs.getDenom();
	unsigned long long int lsNum = this->getNum();
	unsigned long long int lsDen = this->getDenom();
	bool rsIsNeg = rhs.getIsNeg();
	bool lsIsNeg = this->getIsNeg();
	
	/* get lcm and gcd */
	unsigned long long int a = lsDen;
	unsigned long long int b = rsDen;
	unsigned long long int c = a % b;
	while(c > 1)
	{
		a = b;
		b = c;
		c = a % b;
	}

	unsigned long long int gcd = (c == 0) ? b : 1;
	unsigned long long int lcm = lsDen * rsDen / gcd;
	
	/* make denoms lcm */
	rsNum *= lcm / rsDen;
	rsDen *= lcm / rsDen;
	lsNum *= lcm / lsDen;
	lsDen *= lcm / lsDen;
	
	int retNum, retDenom;
	bool retIsNeg;
	
	if(rsIsNeg != lsIsNeg)
	{ /* if signs are the opposite */
		
		/* subtract */
		retNum = (lsNum > rsNum) ? lsNum - rsNum : rsNum - lsNum;
		retDenom = lsDen;
		
		/* calculate return sign */
		retIsNeg = (lsNum > rsNum) ? lsIsNeg : rsIsNeg;
		
	} /* if signs are the opposite */
	else
	{ /* else if signs are the same */
		
		/* add */
		retNum = lsNum + rsNum;
		retDenom = lsDen;
		
		/* make return sign */
		retIsNeg = lsIsNeg;
		
	} /* else if signs are the same */
		
	/* reduce and return */
	Fraction *ret = new Fraction(retNum, retDenom);
	ret->setIsNeg(retIsNeg);
	
	return *ret;
		
} /* plus */

/***************************************************/

Fraction Fraction::operator- (const Fraction& rhs) const
{
	Fraction *newRhs = new Fraction(rhs.getNum(), rhs.getDenom());
	newRhs->setIsNeg(!rhs.getIsNeg());
	return *this + *newRhs;
	
} /* minus */

/***************************************************/

void Fraction::reciprocal(void)
{
	unsigned long long int temp = num;
	num = denom;
	denom = temp;
	
} /* reciprocal */

/***************************************************/

Fraction Fraction::operator* (const Fraction& rhs) const
{
	Fraction *ret = new Fraction(rhs.getNum() * this->getNum(), rhs.getDenom() * this->getDenom());	
	ret->setIsNeg(rhs.getIsNeg() != this->getIsNeg());
	
	/* get gcd */
	unsigned long long int a = ret->getNum();
	unsigned long long int b = ret->getDenom();
	unsigned long long int c = a % b;
	while(c > 1)
	{
		a = b;
		b = c;
		c = a % b;
	}

	if(c == 0)
	{
		ret->setNum(ret->getNum() / b);
		ret->setDenom(ret->getDenom() / b);
		ret->num /= b;
		ret->denom /= b;
	}
		
	return *ret;
		
} /* multiply */

/***************************************************/

Fraction Fraction::operator/ (const Fraction& rhs) const
{
	Fraction *ret = new Fraction(rhs.getDenom() * this->getNum(), rhs.getNum() * this->getDenom());	
	ret->setIsNeg(rhs.getIsNeg() != this->getIsNeg());
	
	/* get gcd */
	unsigned long long int a = ret->getNum();
	unsigned long long int b = ret->getDenom();
	unsigned long long int c = a % b;
	while(c > 1)
	{
		a = b;
		b = c;
		c = a % b;
	}

	if(c == 0)
	{
		ret->setNum(ret->getNum() / b);
		ret->setDenom(ret->getDenom() / b);
		ret->num /= b;
		ret->denom /= b;
	}
	
	return *ret;
		
} /* divide */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
