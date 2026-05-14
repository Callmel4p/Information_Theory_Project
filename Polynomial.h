#pragma once
#include "BinaryVector.h"
#include <string>
#include <vector>
#include <sstream>

// Đa thức trên GF(2): p(x) = a0 + a1*x + a2*x^2 + ... + an*x^n
// coeffs[i] = hệ số của x^i
class Polynomial {
private:
    BinaryVector coeffs; // coeffs[i] = hệ số của x^i

public:
    // Constructors
    Polynomial();
    Polynomial(int degree);         // tạo đa thức bậc degree (n+1 hệ số)
    Polynomial(const BinaryVector& v);

    // Bậc của đa thức (-1 nếu đa thức 0)
    int degree() const;

    // Số hệ số (degree + 1)
    int size() const;

    // Truy cập hệ số x^i
    Bit& operator[](int i);
    const Bit& operator[](int i) const;

    // Phép cộng trên GF(2) (XOR)
    Polynomial operator+(const Polynomial& other) const;

    // Phép nhân trên GF(2)
    Polynomial operator*(const Polynomial& other) const;

    // Phép chia lấy thương và dư: *this = quotient * other + remainder
    void divmod(const Polynomial& divisor,
                Polynomial& quotient,
                Polynomial& remainder) const;

    // So sánh
    bool operator==(const Polynomial& other) const;
    bool operator!=(const Polynomial& other) const;

    // Loại bỏ các hệ số 0 ở đầu (bậc cao)
    void trim();

    // Kiểm tra đa thức 0
    bool isZero() const;

    // Lấy BinaryVector hệ số
    BinaryVector getCoeffs() const;

    // Parse chuỗi dạng "x^3 + x + 1" hoặc "x^3+x^2+1"
    static Polynomial fromString(const std::string& s);

    // Parse binary string like "10111"
    static Polynomial fromBinaryString(const std::string& s);

    // In ra dạng "x^3 + x + 1"
    std::string toString() const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);
    friend std::istream& operator>>(std::istream& is, Polynomial& p);
};
