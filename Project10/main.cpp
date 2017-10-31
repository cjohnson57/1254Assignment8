/*
        Author: W. Douglas Lafield
		Author2: Caleb Johnson
        main.cpp
*/
#include <iostream>
#include <fstream>
#include "Stack.h"
#include <string>
#include "Fraction.h"
#include "RatDec.h"

using namespace std;

/***************************************************/

/* prototypes */
RatDec calculate(RatDec lettervalues[], string function);
string shuntingyard(string function);
RatDec postfixinterpreter(RatDec lettervalues[], string function);
bool isOperator(char s);
bool isLetter(char s);
int letterToNum(char letter);
char numToLetter(int num);
int precedence(char oper);

/***************************************************/

int main(int argc, char** argv)
{
	//argc = 2; //for testing
	if(argc < 2)
	{
		cout << "You must enter a filename by command line." << endl;
		cout << "The command should be as follows:" << endl;
		cout << argv[0] << " [file containing roster]." << endl;
		return 0;
	}
	
	ifstream f;
	f.open(argv[1]); //should be argv[1], for testing "C:\\Users\\Caleb\\Desktop\\1254 Projects\\prog5\\limerick.txt"
	if (!f)
	{
		cout << argv[1] << " does not exist." << endl;
		return 0;
	}
	int lines;
	f >> lines;

	RatDec lettervalues[26];

	for (int i = 0; i < 26; i++)
	{
		lettervalues[i] = new RatDec();
	}

	//lettervalues[0].fracToDec(new Fraction(1, 24)); //For testing fractodec

	//lettervalues[0] = new RatDec("-5.08.3");
	//lettervalues[0].decToFrac(); //For testing dectofrac

	for (int i = 0; i <= lines; i++) //The first getline tries to read the line with the number of lines which has already been retrieved, so there is one extra loop
	{
		string command;
		getline(f, command);
		if (command.substr(0, 3) == "let")
		{
			char letter = command[4];
			string number = command.substr(8);
			RatDec temp = new RatDec(number);
			lettervalues[letterToNum(letter)] = temp;
		}
		else if (command.substr(0, 4) == "calc")
		{
			char letter = command[5];
			string function = command.substr(9);
			lettervalues[letterToNum(letter)] = calculate(lettervalues, function);
		}
		else if (command.substr(0, 5) == "print")
		{
			char letter = command[6];
			cout << letter << " = " << lettervalues[letterToNum(letter)].toString() << endl;
		}
		else if (command.substr(0, 7) == "compare")
		{
			char letter1 = command[8];
			char oper = command[10];
			char letter2 = command[12];
			switch (oper)
			{
			case '=':
				cout << ((lettervalues[letterToNum(letter1)] == lettervalues[letterToNum(letter2)]) ? "Yes" : "No") << endl;
				break;
			case '<':
				cout << ((lettervalues[letterToNum(letter1)] < lettervalues[letterToNum(letter2)]) ? "Yes" : "No") << endl;
				break;
			case '>':
				cout << ((lettervalues[letterToNum(letter1)] > lettervalues[letterToNum(letter2)]) ? "Yes" : "No") << endl;
				break;
			default:
				cout << "Error reading compare statement on line" << i << endl;
			}
		}
		else if (i != 0) //Since the first getline doesn't read anything, the error is ignored for the first loop
		{
			cout << "Error reading line " << i << endl;
		}

	}

	f.close();

	cout << "Done." << endl;
	
	return 0;
} /* main */

RatDec calculate(RatDec lettervalues[], string function)
{
	string function_postfix = shuntingyard(function);
	return postfixinterpreter(lettervalues, function_postfix);
}

string shuntingyard(string function)
{
	string function_postfix = "";
	int length = function.length();
	Stack<char> st;
	for (int i = 0; i < length; i++)
	{
		char token = function[i];
		if (token == '(')
		{
			st.push(token);
		}
		else if (token == ')')
		{
			while (st.top() != '(')
			{
				function_postfix += st.top();
				st.pop();
			}
			st.pop();
		}
		else if (isOperator(token))
		{
			while (st.getLength() != 0 && precedence(st.top()) >= precedence(token))
			{
				function_postfix += st.top();
				st.pop();
			}
			st.push(token);
		}
		else if (isLetter(token))
		{
			function_postfix += token;
		}
	}

	while (st.getLength() != 0)
	{
		function_postfix += st.top();
		st.pop();
	}

	return function_postfix;
}

RatDec postfixinterpreter(RatDec lettervalues[], string function)
{
	int length = function.length();
	Stack<RatDec> st;
	for (int i = 0; i < length; i++)
	{
		char token = function[i];
		if (isOperator(token))
		{
			RatDec operand2 = st.top();
			st.pop();
			RatDec operand1 = st.top();
			st.pop();
			switch (token)
			{
				case '+':
					st.push(operand1 + operand2);
					break;
				case '-':
					st.push(operand1 - operand2);
					break;
				case '*':
					st.push(operand1 * operand2);
					break;
				case '/':
					st.push(operand1 / operand2);
					break;
			}
		}
		else
		{
			st.push(lettervalues[letterToNum(token)]);
		}
	}
	return st.top();
}

/***************************************************/

char numToLetter(int num)
{
	return 'A' + num;
} /* num to letter */

/***************************************************/

int letterToNum(char letter)
{
	return letter - 'A';
} /* letter to num */

/***************************************************/

int precedence(char oper)
{
	if(oper == '+' || oper == '-')
		return 2;
	if(oper == '*' || oper == '/')
		return 3;
	if (oper != '(')
	{
		cout << "ERROR" << endl;
	}
	return -1;
	
} /* precedence */

/***************************************************/

bool isOperator(char s)
{
	return (s == '+' || s == '-' || s == '*' || s == '/');
} /* is operator */

bool isLetter(char s)
{
	return (s >= 65 && s <= 90);
} /* is operator */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
