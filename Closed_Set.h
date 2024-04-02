#pragma once
#include "BitString.h"
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
using namespace std;

class Closed_Set : private BitString
{
public:
	using BitString::getField_1;
	using BitString::getField_2;

	Closed_Set() : BitString() {};
	Closed_Set(unsigned long f1, unsigned long f2) : BitString(f1, f2) {};
	Closed_Set(const Closed_Set& other) : BitString(other.getField_1(), other.getField_2()) {};


	void Init(unsigned long value1, unsigned long value2);

	Closed_Set& operator = (const Closed_Set& other);
	friend Closed_Set operator+(const Closed_Set& set, int element);
	friend Closed_Set operator-(const Closed_Set& set, int element);
	Closed_Set& operator+=(const Closed_Set& other);
	friend Closed_Set operator/(const Closed_Set& set1, const Closed_Set& set2);
	Closed_Set operator()(const Closed_Set& other) const;

	int operator[](int index) const;

	friend Closed_Set operator <(const Closed_Set& other, int bits);
	friend Closed_Set operator >(const Closed_Set& other, int bits);
	
	operator string() const;

	friend ostream& operator <<(ostream&, const Closed_Set&);
	friend istream& operator >>(istream&, Closed_Set&);
};