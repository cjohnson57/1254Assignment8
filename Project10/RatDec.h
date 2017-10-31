#ifndef _RATDEC
#define _RATDEC 1

using namespace std;

#include <cstdlib>
#include <string>
#include <vector>
#include "Fraction.h"

class RatDec
{

private:
	string wholeNum;
	string afterDec;
	string repeat;
	bool isNeg;

public:
	RatDec(RatDec *r)
	{
		isNeg = r->getIsNeg();
		wholeNum = r->getWholeNum();
		afterDec = r->getAfterDec();
		repeat = r->getRepeat();
	} /* constructor from rat dec */
	
	RatDec(int num)
	{
		isNeg = false;
		if (num < 0)
		{
			isNeg = true;
		}
		wholeNum = to_string(num);
		afterDec = "0";
		repeat = "0";
	} /* constructer from int */
	
	RatDec(long long int num)
	{
		isNeg = false;
		if (num < 0)
		{
			isNeg = true;
		}
		wholeNum = to_string(num);
		afterDec = "0";
		repeat = "0";
	} /* constructer from long long int */
	
	RatDec(unsigned int num)
	{
		isNeg = false;
		wholeNum = to_string(num);
		afterDec = "0";
		repeat = "0";
	} /* constructer from unsigned int */
	
	RatDec(unsigned long long int num)
	{
		isNeg = false;
		wholeNum = to_string(num);
		afterDec = "0";
		repeat = "0";
	} /* constructer from unsigned long long int */
	
	RatDec(string w, string d, string r, bool isNeg)
	{
		wholeNum = w;
		afterDec = d;
		repeat = r;
		this->isNeg = isNeg;
		
	} /* constructor from 3 integers */
	
	RatDec(string s)
	{
		int index = 0;
		isNeg = false;
		if (s[0] == '-')
		{
			index = 1;
			isNeg = true;
		}
		int index2 = s.find('.', index);
		wholeNum = s.substr(index, index2 - index);
		int index3 = s.find('.', index2 + 1);
		afterDec = s.substr(index2 + 1, index3 - index2 - 1);
		int index4 = s.find('/n');
		repeat = s.substr(index3 + 1, index4 - index3 - 1);
	} /* constructor from 3 integers */
	
	RatDec(Fraction *f)
	{
		RatDec temp = fracToDec(f);
		isNeg = temp.getIsNeg();
		wholeNum = temp.getWholeNum();
		afterDec = temp.getAfterDec();
		repeat = temp.getRepeat();
	} /* constructer from Fraction */
	
	RatDec()
	{
		wholeNum = "0";
		afterDec = "";
		repeat = "0";
		this->isNeg = false;
	}
	
	~RatDec(){}
	
	string getAfterDec() const { return afterDec; }
	bool getIsNeg() const { return isNeg; }
	string getRepeat() const { return repeat; }
	string getWholeNum() const { return wholeNum; }
	
	void setIsNeg(bool x) { isNeg = x; }
	void toggleIsNeg() { isNeg = !(isNeg); }
	
	RatDec *fracToDec(Fraction *f) const;
	Fraction *decToFrac(void) const;
	
	bool operator> (const RatDec& rhs) const;
	bool operator< (const RatDec& rhs) const;
	bool operator== (const RatDec& rhs) const;
	bool operator!= (const RatDec& rhs) const;
	bool operator>= (const RatDec& rhs) const;
	bool operator<= (const RatDec& rhs) const;
	
	RatDec* operator+ (const RatDec& rhs);
	RatDec* operator- (const RatDec& rhs);
	RatDec* operator* (const RatDec& rhs);
	RatDec* operator/ (const RatDec& rhs);
	
	string toString(void) const;
	
};

#endif
