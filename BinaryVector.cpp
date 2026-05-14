#include "BinaryVector.h"

BinaryVector::BinaryVector() {
}

BinaryVector::BinaryVector(int n) {
    bits.resize(n);
}

int BinaryVector::size() const {
    return bits.size();
}

bool BinaryVector::empty() const {
    return bits.empty();
}

void BinaryVector::resize(int n) {
    bits.resize(n);
}

Bit& BinaryVector::operator[](int index) {
    return bits[index];
}

const Bit& BinaryVector::operator[](int index) const {
    return bits[index];
}

BinaryVector BinaryVector::operator+(
    const BinaryVector& other
) const {

    int n = bits.size();

    BinaryVector result(n);

    for (int i = 0; i < n; i++) {
        result[i] = bits[i] + other[i];
    }

    return result;
}

BinaryVector& BinaryVector::operator=(
    const BinaryVector& other
) {
    bits = other.bits;
    return *this;
}

bool BinaryVector::operator==(
    const BinaryVector& other
) const {
    return bits == other.bits;
}

bool BinaryVector::operator!=(
    const BinaryVector& other
) const {
    return bits != other.bits;
}

void BinaryVector::push_back(const Bit& b) {
    bits.push_back(b);
}

int BinaryVector::hammingWeight() const {

    int cnt = 0;

    for (const Bit& b : bits) {
        if (b.getValue())
            cnt++;
    }

    return cnt;
}

void BinaryVector::leftShift() {

    if (bits.empty())
        return;

    Bit first = bits[0];

    for (int i = 0; i < size() - 1; i++) {
        bits[i] = bits[i + 1];
    }

    bits[size() - 1] = first;
}

void BinaryVector::rightShift() {

    if (bits.empty())
        return;

    Bit last = bits[size() - 1];

    for (int i = size() - 1; i >= 1; i--) {
        bits[i] = bits[i - 1];
    }

    bits[0] = last;
}

void BinaryVector::clear() {
    bits.clear();
}

ostream& operator<<(ostream& os,
                    const BinaryVector& v) {

    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }

    return os;
}

istream& operator>>(istream& is,
                    BinaryVector& v) {

    int n;
    is >> n;

    v.resize(n);

    for (int i = 0; i < n; i++) {
        is >> v[i];
    }

    return is;
}
