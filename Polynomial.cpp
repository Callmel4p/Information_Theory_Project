#include "Polynomial.h"
#include <algorithm>
#include <stdexcept>
#include <cctype>

// ─── Constructors ────────────────────────────────────────────────────────────

Polynomial::Polynomial() {}

Polynomial::Polynomial(int n) {
    coeffs.resize(n+1); // coeffs[0..n], tất cả = 0
}

Polynomial::Polynomial(const BinaryVector& v) : coeffs(v) {}

// ─── Degree & Size ───────────────────────────────────────────────────────────

int Polynomial::degree() const {
    for (int i = (int)coeffs.size() - 1; i >= 0; i--)
        if (coeffs[i].getValue()) return i;
    return -1; // đa thức 0
}

int Polynomial::size() const { return coeffs.size(); }

// ─── Operator[] ──────────────────────────────────────────────────────────────

Bit& Polynomial::operator[](int i) { return coeffs[i]; }
const Bit& Polynomial::operator[](int i) const { return coeffs[i]; }

// ─── Trim ────────────────────────────────────────────────────────────────────

void Polynomial::trim() {
    int d = degree();
    BinaryVector v(d + 1 > 0 ? d + 1 : 0);
    for (int i = 0; i <= d && i < coeffs.size(); i++)
        v[i] = coeffs[i];
    coeffs = v;
}

bool Polynomial::isZero() const { return degree() == -1; }

// ─── Cộng (XOR từng hệ số) ──────────────────────────────────────────────────

Polynomial Polynomial::operator+(const Polynomial& other) const {
    int n = std::max(coeffs.size(), other.coeffs.size());
    Polynomial result(n-1);
    for (int i = 0; i < n; i++) {
        Bit a = (i < coeffs.size()) ? coeffs[i] : Bit(0);
        Bit b = (i < other.coeffs.size()) ? other.coeffs[i] : Bit(0);
        result[i] = a + b; // XOR
    }
    result.trim();
    return result;
}

// ─── Nhân ───────────────────────────────────────────────────────────────────

Polynomial Polynomial::operator*(const Polynomial& other) const {
    int da = degree(), db = other.degree();
    if (da < 0 || db < 0) return Polynomial(); // nhân với 0 = 0

    int n = da + db;
    Polynomial result(n);
    for (int i = 0; i <= da; i++) {
        if (!coeffs[i].getValue()) continue;
        for (int j = 0; j <= db; j++) {
            if (!other.coeffs[j].getValue()) continue;
            // result[i+j] ^= 1
            result[i + j] = result[i + j] + Bit(1);
        }
    }
    result.trim();
    return result;
}

// ─── Chia (polynomial long division trên GF(2)) ─────────────────────────────

void Polynomial::divmod(const Polynomial& divisor,
                        Polynomial& quotient,
                        Polynomial& remainder) const {
    int dd = divisor.degree();
    if (dd < 0) throw std::runtime_error("Chia cho đa thức 0!");

    // Bắt đầu với remainder = *this
    remainder = *this;
    remainder.trim();

    int dq = degree() - dd;
    if (dq < 0) {
        // bậc số bị chia < bậc số chia → thương = 0, dư = *this
        quotient = Polynomial();
        return;
    }

    quotient = Polynomial(dq);

    for (int i = dq; i >= 0; i--) {
        // Hệ số bậc cao nhất của remainder hiện tại
        if (remainder.degree() == i + dd) {
            quotient[i] = Bit(1);
            // remainder -= x^i * divisor  (GF(2): -= là +=)
            for (int j = 0; j <= dd; j++) {
                if (divisor.coeffs[j].getValue()) {
                    remainder[i + j] = remainder[i + j] + Bit(1);
                }
            }
            remainder.trim();
        }
    }
    quotient.trim();
}

// ─── So sánh ─────────────────────────────────────────────────────────────────

bool Polynomial::operator==(const Polynomial& other) const {
    // So sánh sau khi normalize degree
    int da = degree(), db = other.degree();
    if (da != db) return false;
    for (int i = 0; i <= da; i++)
        if (coeffs[i] != other.coeffs[i]) return false;
    return true;
}

bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other);
}

// ─── getCoeffs ───────────────────────────────────────────────────────────────

BinaryVector Polynomial::getCoeffs() const { return coeffs; }

// ─── Parse chuỗi "x^3 + x^2 + 1" ────────────────────────────────────────────
// Hỗ trợ: x^n, x, 1 (hệ số luôn là 1 trong GF(2))

Polynomial Polynomial::fromString(const std::string& raw) {
    std::string s = raw;
    // Chuẩn hóa: xóa khoảng trắng, chuyển thành lowercase
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);

    // Thay thế '-' bằng '+' (trong GF(2) trừ = cộng)
    std::replace(s.begin(), s.end(), '-', '+');

    // Tách theo '+'
    std::vector<std::string> terms;
    std::string cur;
    for (char c : s) {
        if (c == '+') {
            if (!cur.empty()) terms.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
    if (!cur.empty()) terms.push_back(cur);

    // Tìm bậc tối đa để cấp phát
    int maxDeg = 0;
    std::vector<int> exponents;
    for (const std::string& t : terms) {
        if (t == "1" || t == "0") {
            exponents.push_back(0);
        } else if (t == "x") {
            exponents.push_back(1);
            maxDeg = std::max(maxDeg, 1);
        } else if (t.rfind("x^", 0) == 0) {
            int exp = std::stoi(t.substr(2));
            exponents.push_back(exp);
            maxDeg = std::max(maxDeg, exp);
        } else {
            throw std::runtime_error("Hạng tử không hợp lệ: " + t);
        }
    }

    Polynomial p(maxDeg + 1);
    for (int i = 0; i < (int)terms.size(); i++) {
        if (terms[i] != "0") {
            int e = exponents[i];
            p[e] = p[e] + Bit(1); // XOR (nếu trùng lặp hạng tử)
        }
    }
    p.trim();
    return p;
}

// ─── toString ────────────────────────────────────────────────────────────────

std::string Polynomial::toString() const {
    int d = degree();
    if (d < 0) return "0";

    std::string result;
    for (int i = d; i >= 0; i--) {
        if (!coeffs[i].getValue()) continue;
        if (!result.empty()) result += " + ";
        if (i == 0)       result += "1";
        else if (i == 1)  result += "x";
        else              result += "x^" + std::to_string(i);
    }
    return result.empty() ? "0" : result;
}
// ─── parse chuỗi input nhị phân ────────────────────────────────────────────────────────────────
Polynomial Polynomial::fromBinaryString(
    const string& s
) {

    if (s.empty())
        throw runtime_error("Empty binary string");

    int deg = s.size() - 1;

    Polynomial p(deg);

    for (int i = 0; i < s.size(); i++) {

        if (s[i] != '0' && s[i] != '1')
            throw runtime_error("Invalid binary string");

        if (s[i] == '1') {

            int power = deg - i;

            p[power] = Bit(1);
        }
    }

    p.trim();

    return p;
}

// ─── Stream operators ────────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    os << p.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Polynomial& p) {
    std::string line;
    std::getline(is, line);
    p = Polynomial::fromString(line);
    return is;
}
