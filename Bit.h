#ifndef BIT_H
#define BIT_H

#include <iostream>

using namespace std;

class Bit {
private:
    bool value;

public:

    // Constructors
    Bit();
    Bit(bool v);
    Bit(int v);

    // Getter / Setter
    bool getValue() const;
    void setValue(bool v);

    // Arithmetic operators in GF(2)
    Bit operator+(const Bit& other) const;
    Bit operator-(const Bit& other) const;
    Bit operator*(const Bit& other) const;

    // Assignment
    Bit& operator=(const Bit& other);

    // Comparison
    bool operator==(const Bit& other) const;
    bool operator!=(const Bit& other) const;

    // Logical NOT
    Bit operator!() const;

    // Stream operators
    friend ostream& operator<<(ostream& os, const Bit& b);
    friend istream& operator>>(istream& is, Bit& b);
};

#endif
