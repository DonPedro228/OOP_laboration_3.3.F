#include "BitString.h"
#include "Closed_Set.h"
#include <string>
#include <bitset>
#include <intrin.h>
using namespace std;


void Closed_Set::Init(unsigned long value1, unsigned long value2)
{

    setField_1(value1);
    setField_2(value2);
}

Closed_Set& Closed_Set::operator=(const Closed_Set& other) {
    if (this != &other) {
        BitString::operator=(other);
    }
    return *this;
}

Closed_Set operator+(const Closed_Set& set, int element) {
    Closed_Set result(set);
    if (element >= 0 && element < 32)
        result.setField_1(result.getField_1() | (1UL << element));
    else if (element >= 32 && element < 64)
        result.setField_2(result.getField_2() | (1UL << (element - 32)));
    else
        throw out_of_range("Element out of range");

    return result;
}


Closed_Set operator-(const Closed_Set& set, int element) {
    Closed_Set result(set);
    if (element >= 0 && element < 32) {
        result.setField_1(result.getField_1() & ~(1UL << element));
    }
    else if (element >= 32 && element < 64) {
        result.setField_2(result.getField_2() & ~(1UL << (element - 32)));
    }
    else {
        cout << "Element out of range" << endl;
    }

    return result;
}

Closed_Set& Closed_Set::operator+=(const Closed_Set& other) {
    setField_1(getField_1() | other.getField_1());
    setField_2(getField_2() | other.getField_2());
    return *this;
}

Closed_Set operator/(const Closed_Set& set1, const Closed_Set& set2) {
    Closed_Set result;
    result.setField_1(set1.getField_1() & set2.getField_1());
    result.setField_2(set1.getField_2() & set2.getField_2());
    return result;
}

Closed_Set Closed_Set::operator()(const Closed_Set& other) const {
    Closed_Set result;

    result.setField_1(getField_1() & (getField_1() != other.getField_1()));
    result.setField_2(getField_2() & (getField_2() != other.getField_2()));

    return result;
}

Closed_Set::operator string() const {
    stringstream ss;
    ss << "Field_1: " << getField_1() << endl;
    ss << "Field_2: " << getField_2() << endl;
    return ss.str();
}


ostream& operator<<(ostream& out, const Closed_Set& bitString)
{
    out << "Field_1: " << bitset<64>(bitString.getField_1()) << endl;
    out << "Field_2: " << bitset<64>(bitString.getField_2()) << endl;
    return out;
}

istream& operator>>(istream& in, Closed_Set& bitString) {
    unsigned long number1, number2;

    cout << "Enter first number: ";
    in >> number1;

    cout << "Enter second number: ";
    in >> number2;

    if (number1 > 31) {
        bitString.setField_2(1UL << (number1 - 32));
        bitString.setField_1(0);
    }
    else {
        bitString.setField_1(1UL << number1);
        bitString.setField_2(0);
    }

    if (number2 > 31) {
        bitString.setField_2(bitString.getField_2() | 1UL << (number2 - 32));
    }
    else {
        bitString.setField_1(bitString.getField_1() | 1UL << number2);
    }

    return in;
}

int Closed_Set::operator[](int index) const {
    if (index == 0)
        return __popcnt(getField_1());
    else if (index == 1)
        return __popcnt(getField_2());
    else
        return -1;
}

Closed_Set operator<(const Closed_Set& other, int bits) {
    unsigned long new_field_1, new_field_2;

    if (bits >= 64) {
        return Closed_Set();
    }
    else if (bits >= 32) {
        new_field_1 = other.getField_2() << (bits - 32);
        new_field_2 = 0;
    }
    else {
        new_field_1 = (other.getField_1() << bits) | (other.getField_2() >> (32 - bits));
        new_field_2 = other.getField_2() << bits;
    }

    return Closed_Set(new_field_1, new_field_2);
}

Closed_Set operator>(const Closed_Set& other, int bits) {
    unsigned long new_field_1, new_field_2;

    if (bits >= 64) {
        return Closed_Set();
    }
    else if (bits >= 32) {
        new_field_1 = 0;
        new_field_2 = other.getField_1() >> (bits - 32);
    }
    else {
        new_field_2 = (other.getField_2() >> bits) | (other.getField_1() << (32 - bits));
        new_field_1 = other.getField_1() >> bits;
    }

    return Closed_Set(new_field_1, new_field_2);
}

