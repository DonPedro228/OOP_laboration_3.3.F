#pragma once
#include "BitString.h"
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
using namespace std;

class Set : public BitString
{
public:
	Set(): BitString() {};
	Set(unsigned long f1, unsigned long f2) : BitString(f1, f2) {};
	Set(const Set& other) : BitString(other.getField_1(), other.getField_2()) {};


	void Init(unsigned long value1, unsigned long value2);

	Set& operator = (const Set& other);
	friend Set operator+(const Set& set, int element);
	friend Set operator-(const Set& set, int element);
	Set& operator+=(const Set& other);
	friend Set operator/(const Set& set1, const Set& set2);
	Set operator()(const Set& other) const;

	int operator[](int index) const;

	friend Set operator <(const Set& other, int bits);
	friend Set operator >(const Set& other, int bits);

	operator string() const;
};