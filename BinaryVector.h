#ifndef BINARY_VECTOR_H
#define BINARY_VECTOR_H

#include <iostream>
#include <vector>

#include "Bit.h"

using namespace std;

class BinaryVector {
private:
    vector<Bit> bits;

public:

    // Constructors
    BinaryVector();
    BinaryVector(int n);

    // Basic methods
    int size() const;
    bool empty() const;

    void resize(int n);

    // Access operators
    Bit& operator[](int index);
    const Bit& operator[](int index) const;

    // Vector addition (XOR)
    BinaryVector operator+(const BinaryVector& other) const;

    // Assignment
    BinaryVector& operator=(const BinaryVector& other);

    // Comparison
    bool operator==(const BinaryVector& other) const;
    bool operator!=(const BinaryVector& other) const;

    // Push bit
    void push_back(const Bit& b);

    // Hamming weight
    int hammingWeight() const;

    // Cyclic shifts
    void leftShift();
    void rightShift();

    // Clear vector
    void clear();

    // Stream operators
    friend ostream& operator<<(ostream& os,
                               const BinaryVector& v);

    friend istream& operator>>(istream& is,
                               BinaryVector& v);
};

#endif
