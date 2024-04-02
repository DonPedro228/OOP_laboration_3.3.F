#include "BitString.h"
#include "Set.h"
#include <string>
#include <bitset>
#include <intrin.h>
using namespace std;


void Set::Init(unsigned long value1, unsigned long value2)
{

    setField_1(value1);
    setField_2(value2);
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        BitString::operator=(other);
    }
    return *this;
}

Set operator+(const Set& set, int element) {
    Set result(set);
    if (element >= 0 && element < 32)
        result.setField_1(result.getField_1() | (1UL << element));
    else if (element >= 32 && element < 64)
        result.setField_2(result.getField_2() | (1UL << (element - 32)));
    else
        throw out_of_range("Element out of range");

    return result;
}


Set operator-(const Set& set, int element) {
    Set result(set);
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

Set& Set::operator+=(const Set& other) {
    setField_1(getField_1() | other.getField_1());
    setField_2(getField_2() | other.getField_2());
    return *this;
}

Set operator/(const Set& set1, const Set& set2) {
    Set result;
    result.setField_1(set1.getField_1() & set2.getField_1());
    result.setField_2(set1.getField_2() & set2.getField_2());
    return result;
}

Set Set::operator()(const Set& other) const {
    Set result;

    result.setField_1(getField_1() & (getField_1() != other.getField_1()));
    result.setField_2(getField_2() & (getField_2() != other.getField_2()));

    return result;
}

Set::operator string() const {
    stringstream ss;
    ss << "Field_1: " << getField_1() << endl;
    ss << "Field_2: " << getField_2() << endl;
    return ss.str();
}


ostream& operator<<(ostream& out, const Set& set)
{
    out << "Field_1: " << bitset<64>(set.getField_1()) << endl;
    out << "Field_2: " << bitset<64>(set.getField_2()) << endl;
    return out;
}

istream& operator>>(istream& in, Set& set) {
    unsigned long number1, number2;

    cout << "Enter first number: ";
    in >> number1;

    cout << "Enter second number: ";
    in >> number2;

    if (number1 > 31) {
        set.setField_2(1UL << (number1 - 32));
        set.setField_1(0);
    }
    else {
        set.setField_1(1UL << number1);
        set.setField_2(0);
    }

    if (number2 > 31) {
        set.setField_2(set.getField_2() | 1UL << (number2 - 32));
    }
    else {
        set.setField_1(set.getField_1() | 1UL << number2);
    }

    return in;
}

int Set::operator[](int index) const {
    if (index == 0)
        return __popcnt(getField_1());
    else if (index == 1)
        return __popcnt(getField_2());
    else
        return -1;
}

Set operator<(const Set& other, int bits) {
    unsigned long new_field_1, new_field_2;

    if (bits >= 64) {
        return Set();
    }
    else if (bits >= 32) {
        new_field_1 = other.getField_2() << (bits - 32);
        new_field_2 = 0;
    }
    else {
        new_field_1 = (other.getField_1() << bits) | (other.getField_2() >> (32 - bits));
        new_field_2 = other.getField_2() << bits;
    }

    return Set(new_field_1, new_field_2);
}

Set operator>(const Set& other, int bits) {
    unsigned long new_field_1, new_field_2;

    if (bits >= 64) {
        return Set();
    }
    else if (bits >= 32) {
        new_field_1 = 0;
        new_field_2 = other.getField_1() >> (bits - 32);
    }
    else {
        new_field_2 = (other.getField_2() >> bits) | (other.getField_1() << (32 - bits));
        new_field_1 = other.getField_1() >> bits;
    }

    return Set(new_field_1, new_field_2);
}
