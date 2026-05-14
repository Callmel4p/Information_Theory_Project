#include "Bit.h"

Bit::Bit() {
    value = 0;
}

Bit::Bit(bool v) {
    value = v;
}

Bit::Bit(int v) {
    value = (v != 0);
}

bool Bit::getValue() const {
    return value;
}

void Bit::setValue(bool v) {
    value = v;
}

Bit Bit::operator+(const Bit& other) const {
    return Bit(value ^ other.value);
}

Bit Bit::operator-(const Bit& other) const {
    return Bit(value ^ other.value);
}

Bit Bit::operator*(const Bit& other) const {
    return Bit(value & other.value);
}

Bit& Bit::operator=(const Bit& other) {
    value = other.value;
    return *this;
}

bool Bit::operator==(const Bit& other) const {
    return value == other.value;
}

bool Bit::operator!=(const Bit& other) const {
    return value != other.value;
}

Bit Bit::operator!() const {
    return Bit(!value);
}

ostream& operator<<(ostream& os, const Bit& b) {
    os << b.value;
    return os;
}

istream& operator>>(istream& is, Bit& b) {
    int x;
    is >> x;
    b.value = (x != 0);
    return is;
}
