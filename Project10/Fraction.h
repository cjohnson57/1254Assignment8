#ifndef _FRACTION
#define _FRACTION 1

using namespace std;

#include <cstdlib>
#include <string>

class Fraction
{

private:
	unsigned long long int num;
	unsigned long long int denom;
	bool isNeg;

public:
	Fraction(int wholeNum)
	{
		this->num = (wholeNum < 0) ? -1 * wholeNum : wholeNum;
		this->denom = 1;
		this->isNeg = (wholeNum < 0);
	}
	
	Fraction(unsigned long long int wholeNum)
	{
		this->num = (wholeNum < 0) ? -1 * wholeNum : wholeNum;
		this->denom = 1;
		this->isNeg = (wholeNum < 0);
	}
	
	Fraction(int numerator, int denominator)
	{
		this->num = (numerator < 0) ? -1 * numerator : numerator;
		this->denom = (denominator < 0) ? -1 * denominator : denominator;
		this->isNeg = (numerator * denominator < 0);

		/* get gcd */
		unsigned long long int a = this->num;
		unsigned long long int b = this->denom;
		unsigned long long int c = a % b;
		while(c > 1)
		{
			a = b;
			b = c;
			c = a % b;
		}

		if(c == 0)
		{
			this->num /= b;
			this->denom /= b;
		}
	}
	
	Fraction(unsigned long long int numerator, unsigned long long int denominator)
	{
		this->num = (numerator < 0) ? -1 * numerator : numerator;
		this->denom = (denominator < 0) ? -1 * denominator : denominator;
		this->isNeg = (numerator * denominator < 0);

		/* get gcd */
		unsigned long long int a = this->num;
		unsigned long long int b = this->denom;
		unsigned long long int c = a % b;
		while(c > 1)
		{
			a = b;
			b = c;
			c = a % b;
		}

		if(c == 0)
		{
			this->num /= b;
			this->denom /= b;
		}
	}
	
	Fraction(Fraction *r)
	{
		this->num = r->getNum();
		this->denom = r->getDenom();
		this->isNeg = r->getIsNeg();
	}
	
	Fraction()
	{
		this->num = 0;
		this->denom = 1;
		this->isNeg = false;
	}
	
	~Fraction(){}
	
	unsigned long long int getDenom() const { return this->denom; }
	unsigned long long int getNum() const { return this->num; }
	bool getIsNeg() const { return this->isNeg; }
	
	void setDenom(unsigned long long int x) { this->denom = x; }
	void setNum(unsigned long long int x) { this->num = x; }
	void setIsNeg(bool x) { this->isNeg = x; }
	void toggleIsNeg() { this->isNeg = !(this->isNeg); }
	
	//bool operator> (const Fraction& lhs, const Fraction& rhs);
	bool operator> (const Fraction& rhs) const;
	bool operator< (const Fraction& rhs) const;
	bool operator== (const Fraction& rhs) const;
	bool operator!= (const Fraction& rhs) const;
	
	Fraction operator+ (const Fraction& rhs) const;
	Fraction operator- (const Fraction& rhs) const;
	Fraction operator* (const Fraction& rhs) const;
	Fraction operator/ (const Fraction& rhs) const;
	
	void reciprocal(void);
	string toString(void) const;
};

#endif
