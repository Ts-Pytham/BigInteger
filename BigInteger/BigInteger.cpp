#include "BigInteger.hpp"
#include <string>
#include <algorithm>

BigInteger::BigInteger()
{
	value = "0";
}

BigInteger::BigInteger(string value)
{
	if (!CheckNumbers(value))
		throw "Value is not number!";
	if (value[0] == '\0')
		this->value = "0";
	else
		this->value = value;
}

BigInteger::BigInteger(const char* value)
{
	string aux = value;
	if (!CheckNumbers(aux))
		throw "Value is not number!";
	if (aux[0] == '\0')
		this->value = "0";
	else
		this->value = aux;
}

BigInteger::BigInteger(size_t value)
{
	this->value = std::to_string(value);
}

BigInteger::BigInteger(int value)
{
	this->value = std::to_string(value);
}

BigInteger::BigInteger(long int value)
{
	this->value = std::to_string(value);
}

int BigInteger::size()
{
	return this->value.size();
}

BigInteger BigInteger::length()
{
	return BigInteger(this->value.size());
}

string BigInteger::toString()
{
	return this->value;
}

std::ostream& operator<<(std::ostream& o, BigInteger bi)
{
	o << bi.value;
	return o;
}

std::istream& operator>>(std::istream& i, BigInteger &bi)
{
	
	i >> bi.value;
	if (!bi.CheckNumbers(bi.value))
		throw "Value is not number!";
	i.ignore();
	return i;
}

BigInteger BigInteger::operator+(int value)
{
	return operator+(BigInteger(std::to_string(value)));
}

BigInteger BigInteger::operator+(long int value)
{
	return operator+(BigInteger(std::to_string(value)));
}

BigInteger BigInteger::operator+(BigInteger bi2)
{
	if ((bi2.value[0] == '0' && this->value[0] == '0') && bi2.size() + this->size() == 2)
		return BigInteger(0);
	if (bi2.value[0] == '-' && this->value[0] != '-') { //Comprueba si el segundo valor es negativo +- = -
		bi2.value.erase(0, 1);
		return operator-(bi2);
	}
	else {
		bool isNegative = false;
		
		BigInteger bi = this->value;
		if (bi.value[0] == '-' && bi2.value[0] == '-') {
			bi.value.erase(0, 1);
			bi2.value.erase(0, 1);
			
			isNegative = true;
		}
		else if (bi.value[0] == '-' && bi2.value[0] != '-') {
			bi.value.erase(0, 1);
			std::swap(bi.value, bi2.value);
			return bi.operator-(bi2);
		}
		if (bi.size() < bi2.size())
			std::swap(bi.value, bi2.value);

		int asize = bi.size(), bsize = bi2.size();
		int j = asize - 1;
		for (int i = bsize - 1; i >= 0; --i, --j)
			bi.value[j] += (bi2.value[i] - '0');


		for (int i = asize - 1; i > 0; --i) {

			if (bi.value[i] > '9') {
				int aux = bi.value[i] - '0';
				bi.value[i - 1] = ((bi.value[i - 1] - '0') + aux / 10) + '0';
				bi.value[i] = (aux % 10) + '0';
			}
		}
		if (bi.value[0] > '9') {
			string str;
			str += bi.value[0];
			bi.value[0] = ((bi.value[0] - '0') % 10) + '0';
			str[0] = ((str[0] - '0') / 10) + '0';
			bi.value = str + bi.value;
		}

		if (bi.value[0] == '0') {
			bi.value.erase(0);
		}

		if (isNegative)
			bi.value = '-' + bi.value;

		return bi;
	}
}

BigInteger BigInteger::operator-(BigInteger bi2)
{
	if ((bi2.value[0] == '0' && this->value[0] == '0') && bi2.size() + this->size() == 2)
		return BigInteger(0);
	if (this->value[0] != '-' && bi2.value[0] == '-') { //Comprueba si el segundo es negativo ya que -- = +
		bi2.value.erase(0, 1);
		return operator+(bi2);
	}

	BigInteger aux = this->value;
	
	bool isNegative = false;
	int mayor = 0;
	if (aux.value[0] == '-' && bi2.value[0] == '-') {
		aux.value.erase(0, 1);
		bi2.value.erase(0, 1);
		isNegative = true;
		++mayor;
	}
	else if (aux.value[0] == '-' && bi2.value[0] != '-') {
		bi2.value = '-' + bi2.value;
		return aux.operator+(bi2);
	}
	if (IsSmaller(aux.value, bi2.value)) {
		std::swap(aux.value, bi2.value);
		isNegative = true;
		++mayor;
	}

	string str = "";
	int len1 = aux.size(), len2 = bi2.size(), add = 0, dif = len1-len2;
	
	for (int i = len2 - 1; i >= 0; --i) {
		int sub = ((aux.value[i + dif] - '0') - (bi2.value[i] - '0') - add);
		if (sub < 0) {
			sub += 10;
			add = 1;
		}
		else
			add = 0;

		str.push_back(sub + '0');
	}

	for (int i = len1 - len2 - 1; i >= 0; --i) {
		if (aux.value[i] == '0' && add) {
			str.push_back('9');
			continue;
		}
		int sub = ((aux.value[i] - '0') - add);
		if (i > 0 || sub > 0)
			str.push_back(sub + '0');
		
		add = 0;
	}
	reverse(str.begin(), str.end());

	if (isNegative && mayor != 2)
		str = "-" + str;

	EraseZero(str);

	return BigInteger(str);
}

BigInteger BigInteger::operator*(BigInteger bi2)
{
	if (this->value == "0" || bi2 == "0")
		return BigInteger(0);
	
	BigInteger aux = this->value;
	bool isNegative = false;
	if (aux.value[0] == '-' && bi2.value[0] == '-') { // -*- = +
		aux.value.erase(0, 1);
		bi2.value.erase(0, 1);
		
	}
	else if (aux.value[0] == '-' && bi2.value[0] != '-') {
		isNegative = true;
		aux.value.erase(0, 1);
	}
	else if (aux.value[0] != '-' && bi2.value[0] == '-') {
		isNegative = true;
		bi2.value.erase(0, 1);
	}

	int len2 = bi2.size(), len1 = aux.size();
	string result(len1+len2, '0');

	for (int i = len1 - 1; i >= 0; --i) {
		for (int j = len2 - 1; j >= 0; --j) {
			int p = (aux.value[i] - '0') * (bi2.value[j] - '0') + (result[i + j + 1] - '0');
			result[i + j + 1] = p % 10 + '0';
			result[i + j] += p / 10;
		}
	}
	for (int i = 0; i < len1 + len2; i++) {
		if (result[i] != '0') {
			result = result.substr(i);
			if (isNegative)
				result = '-' + result;

			return BigInteger(result);
		}
	}

	return BigInteger(0);
}

BigInteger BigInteger::operator/(BigInteger bi2)
{
	/*
	if (IsSmaller(this->value, bi2.value))
		return BigInteger(0);
	if (bi2.value == this->value)
		return BigInteger(1);

	BigInteger aux = value;
	int len = aux.size(), len2 = bi2.size();
	string result;
	while (IsSmaller(this->value, bi2.value)) {
		while (true) {
			if()
		}
	}
	*/
	return BigInteger(-1);
}

void BigInteger::operator+=(BigInteger bi2)
{
	*this = operator+(bi2);
}

void BigInteger::operator+=(int value)
{
	*this = operator+(BigInteger(value));
}

void BigInteger::operator-=(BigInteger bi2)
{
	*this = operator-(bi2);
}

void BigInteger::operator*=(BigInteger bi2)
{
	*this = operator*(bi2);
}

void BigInteger::operator++()
{
	*this = operator+(BigInteger(1));
}

void BigInteger::operator++(int)
{
	*this = operator+(BigInteger(1));
}

void BigInteger::operator--()
{
	*this = operator-(BigInteger(1));
}

void BigInteger::operator--(int)
{
	*this = operator-(BigInteger(1));
}

bool BigInteger::operator==(BigInteger bi)
{
	if (this->value == bi.value) {
		return true;
	}
	return false;
}

bool BigInteger::operator==(const char* value)
{
	if (this->value == value) {
		return true;
	}
	return false;
}

bool BigInteger::operator!=(BigInteger bi)
{
	if (this->value != bi.value) {
		return true;
	}
	return false;
}

bool BigInteger::operator<(BigInteger bi)
{
	return IsSmaller(this->value, bi.value);
	
}

bool BigInteger::operator>(BigInteger bi)
{
	return IsSmaller(bi.value, this->value);
}

bool BigInteger::operator<=(BigInteger bi)
{
	return IsSmaller(this->value, bi.value, true);
}

bool BigInteger::operator>=(BigInteger bi)
{
	return IsSmaller(bi.value, this->value, true);
}

bool BigInteger::CheckNumbers(string &value)
{
	int len = value.length();
	if (len == 1) {
		
		if (value[0] <= 47 || value[0] >= 58)
			return false;
		else
			return true;
	}
	if (value[0] == '-' && len >= 2) {
		if (value[1] == '0') {
			
			value.erase(0, 1);
			len--;
		}
	}
	if (value[0] == '0' && len >= 2) {
		value.erase(0, 1);
		len--;
	}
	else {
		for (int i = 0; i != len; ++i) {
			if ((value[i] <= 47 || value[i] >= 58) && value[i] != '-') {
				return false;
			}
			if (value[i] == '-' || i != len - 1) {
	
				if (value[i + 1] <= 47 || value[i + 1] >= 58)
					return false;
			}

		}
	}
	return true;
}

bool BigInteger::IsSmaller(string s1, string s2, bool intensive)
{
	if (s1[0] == '-' && s2[0] != '-')
		return true;
	else if (s1[0] != '-' && s2[0] == '-')
		return false;
	else if (s1[0] == '-' && s2[0] == '-')
		std::swap(s1, s2);

	int len1 = s1.length(), len2 = s2.length();
	if (len1 < len2)
		return true;
	if(len2 < len1)
		return false;

	for (int i = 0; i != len1; ++i) {
		if (s1[i] < s2[i])
			return true;
		else if(s1[i] > s2[i])
			return false;
	}
	if (intensive)
		return true; //ambas son iguales
	else
		return false;
}

void BigInteger::EraseZero(string& str)
{
	if (str.length() > 1 && str[0] == '0') {
		
		int len = str.length(), i;
		for (i = 1; i != len; ++i) {
			if (str[i] != '0' && str[i] != '/0')
				return;

		}
		str.erase(1, i);
	}
}
