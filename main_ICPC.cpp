#include <iostream>
#include <string>

#include "Polynomial.h"

using namespace std;


// x^n + 1
Polynomial makeXnPlus1(int n) {

    Polynomial p(n);

    p[0] = Bit(1);
    p[n] = Bit(1);

    return p;
}


// Check parity-check polynomial
bool checkPolynomial(
    int n,
    int k,
    const Polynomial& poly
) {

    // Must not be zero polynomial
    if (poly.isZero())
        return false;

    // Must be monic
    if (!poly[poly.degree()].getValue())
        return false;

    // degree must equal k
    if (poly.degree() != k)
        return false;

    // Must divide x^n + 1
    Polynomial xn1 = makeXnPlus1(n);

    Polynomial quotient;
    Polynomial remainder;

    xn1.divmod(
        poly,
        quotient,
        remainder
    );

    return remainder.isZero();
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;

    cin >> t;

    while (t--) {

        int n, k;

        cin >> n >> k;

        string s;

        cin >> s;

        Polynomial poly =
            Polynomial::fromBinaryString(s);

        if (checkPolynomial(n, k, poly))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
