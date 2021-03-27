#include <iostream>

using std::string;
#pragma once
class BigInteger
{
public:
	
	//Constructors
	BigInteger();
	BigInteger(string value);
	BigInteger(const char* value);
	BigInteger(size_t value);
	BigInteger(int value);
	BigInteger(long int value);
	
	//Functions
	int size();
	BigInteger length();
	string toString();

	//Operators friends
	friend std::ostream& operator<<(std::ostream& o, BigInteger bi);
	friend std::istream& operator >>(std::istream& i, BigInteger &bi);

	//Operators
	BigInteger operator+(int value);
	BigInteger operator+(long int value);
	BigInteger operator+(BigInteger bi2);
	BigInteger operator-(BigInteger bi2);
	BigInteger operator*(BigInteger bi2);
	BigInteger operator/(BigInteger bi2);

	void operator+=(BigInteger bi2);
	void operator+=(int value);
	void operator-=(BigInteger bi2);
	void operator*=(BigInteger bi2);

	//Operators Increments & Decrements
	void operator++();
	void operator++(int);
	void operator--();
	void operator--(int);

	//Logics Operators
	bool operator ==(BigInteger bi);
	bool operator ==(const char* value);
	bool operator !=(BigInteger bi);
	bool operator <(BigInteger bi);
	bool operator >(BigInteger bi);
	bool operator <=(BigInteger bi);
	bool operator >=(BigInteger bi);
private:
	//Functions
	bool CheckNumbers(string &word);
	bool IsSmaller(string s1, string s2, bool intensive = false);
	void EraseZero(string& str);

	//variables
	string value;
};