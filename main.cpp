#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <thread>
#include <chrono>

#include "Polynomial.h"

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

using namespace std;

void clearScreen() {

    system(CLEAR_COMMAND);
}

// Tạo đa thức x^n + 1 trên GF(2)
Polynomial makeXnPlus1(int n) {

    Polynomial p(n);

    p[0] = Bit(1);
    p[n] = Bit(1);

    return p;
}


// In đường kẻ
void printLine(char c = '-', int len = 60) {

    for (int i = 0; i < len; i++)
        cout << c;

    cout << "\n";
}


// Sleep ngắn để user đọc thông báo
void shortSleep(int ms = 1500) {

    this_thread::sleep_for(
        chrono::milliseconds(ms)
    );
}


// Kiểm tra p(x) có phải đa thức kiểm tra
// của mã vòng tuyến tính C(n, k) hay không

bool checkPolynomial(
    int n,
    int k,
    const Polynomial& poly,
    bool verbose
) {

    int degPoly = poly.degree();

    // Bước 1: kiểm tra monic
    bool monicOK = false;

    if (!poly.isZero()) {
        monicOK = poly[degPoly].getValue();
    }

    if (verbose) {

        printLine('=');

        cout << "KIỂM TRA ĐA THỨC KIỂM TRA "
             << "CỦA MÃ VÒNG C("
             << n << ", " << k << ")\n";

        printLine('=');

        cout << "\n";

        cout << "Đa thức đầu vào p(x) = "
             << poly << "\n";

        cout << "Bậc của p(x)         = "
             << degPoly << "\n\n";

        cout << "── Bước 1: Kiểm tra tính monic ───────────────────\n";

        cout << "Đa thức monic là đa thức có hệ số bậc cao nhất bằng 1.\n\n";

        cout << "Hệ số của x^"
             << degPoly
             << " = ";

        cout << poly[degPoly] << "\n\n";

        cout << "  → p(x) ";

        if (monicOK)
            cout << "LÀ đa thức monic ✓\n\n";
        else
            cout << "KHÔNG PHẢI đa thức monic ✗\n\n";
    }


    // Bước 2: kiểm tra bậc
    if (verbose) {

        cout << "── Bước 2: Kiểm tra bậc ─────────────────────────\n";

        cout << "Với mã C(" << n << ", " << k << "):\n";

        cout << "  - Đa thức kiểm tra phải có bậc = k = "
             << k << "\n";
    }

    bool degreeOK = (degPoly == k);

    if (verbose) {

        cout << "  → Bậc p(x) = "
             << degPoly << " ";

        if (degreeOK)
            cout << "= k ✓\n\n";
        else
            cout << "≠ k ✗\n\n";
    }

    // Bước 3: kiểm tra chia hết x^n + 1
    Polynomial xn1 = makeXnPlus1(n);

    if (verbose) {

        cout << "── Bước 3: Kiểm tra p(x) chia hết "
             << "(x^" << n << " + 1) ─────\n";
    }

    Polynomial quotient;
    Polynomial remainder;

    xn1.divmod(poly, quotient, remainder);

    if (verbose) {

        cout << "  Thực hiện phép chia:\n";

        cout << "  (x^" << n << " + 1) ÷ p(x)\n\n";

        cout << "  Thương q(x) = "
             << quotient << "\n";

        cout << "  Dư r(x)     = ";

        if (remainder.isZero())
            cout << "0\n\n";
        else
            cout << remainder << "\n\n";
    }

    bool divisible = remainder.isZero();

    if (verbose) {

        cout << "  → p(x) ";

        if (divisible)
            cout << "chia hết ✓ ";
        else
            cout << "KHÔNG chia hết ✗ ";

        cout << "(x^" << n << " + 1)\n\n";
    }

    // Kết luận
    bool result =
        monicOK &&
        degreeOK &&
        divisible;

    if (verbose) {

        printLine('=');

        cout << "KẾT LUẬN\n";

        printLine('-');

        if (result) {

            cout << "✔ p(x) = "
                 << poly
                 << " LÀ đa thức kiểm tra của mã vòng C("
                 << n << ", " << k << ").\n";
        }
        else {

            cout << "✘ p(x) = "
                 << poly
                 << " KHÔNG PHẢI đa thức kiểm tra của mã vòng C("
                 << n << ", " << k << ").\n";

            if (!monicOK) {

                cout << "  Lý do: p(x) không phải đa thức monic.\n";
            }

            if (!degreeOK) {

                cout << "  Lý do: bậc p(x) = "
                     << degPoly
                     << ", cần bậc = k = "
                     << k << ".\n";
            }

            if (!divisible) {

                cout << "  Lý do: p(x) không chia hết "
                     << "(x^" << n << " + 1).\n";
            }
        }

        printLine('=');
    }
    else {

        if (result) {

            cout << "KẾT QUẢ: p(x) = "
                 << poly
                 << " LÀ đa thức kiểm tra của mã vòng C("
                 << n << ", " << k << ").\n";
        }
        else {

            cout << "KẾT QUẢ: p(x) = "
                 << poly
                 << " KHÔNG PHẢI đa thức kiểm tra của mã vòng C("
                 << n << ", " << k << ").\n";
        }
    }

    return result;
}


// Chạy một lần kiểm tra
void runCheck() {

    clearScreen();

    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║   KIỂM TRA ĐA THỨC KIỂM TRA MÃ VÒNG TUYẾN TÍNH       ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n\n";

    int n, k;

    cout << "Nhập thông số mã C(n, k):\n";
    
        cout << "  n = ";
    
    if (!(cin >> n)) {
    
        cerr << "\nLỗi: n phải là số nguyên.\n";
    
        cin.clear();
        cin.ignore(10000, '\n');
    
        shortSleep();
    
        return;
    }
    
    cout << "  k = ";
    
    if (!(cin >> k)) {
    
        cerr << "\nLỗi: k phải là số nguyên.\n";
    
        cin.clear();
        cin.ignore(10000, '\n');
    
        shortSleep();
    
        return;
    }
    
    if (n <= 0 || k <= 0 || k >= n) {
    
        cerr << "\nLỗi: cần 0 < k < n.\n";
    
        cin.ignore(10000, '\n');
    
        shortSleep();
    
        return;
    }

    cin.ignore(1000, '\n');

    cout << "\nNhập đa thức p(x)\n";
    cout << "(ví dụ: x^3 + x + 1)\n";

    cout << "  p(x) = ";

    string line;

    getline(cin, line);

    Polynomial poly;

    try {

        poly = Polynomial::fromString(line);
    }
    catch (const exception& e) {

        cerr << "\nLỗi parse đa thức: "
             << e.what() << "\n";

        shortSleep();

        return;
    }

    cout << "\nChọn chế độ hiển thị:\n";

    cout << "  1. Chỉ hiện kết quả\n";
    cout << "  2. Diễn giải từng bước\n";

    cout << "Lựa chọn: ";

    int mode;

    cin >> mode;

    cout << "\n";

    bool verbose = (mode == 2);

    try {

        checkPolynomial(
            n,
            k,
            poly,
            verbose
        );
    }
    catch (const exception& e) {

        cerr << "\nLỗi: "
             << e.what() << "\n";
    }

    cout << "\nNhấn Enter để quay lại menu...";

    cin.ignore(1000, '\n');
    cin.get();
}


// MAIN

int main() {

    string option;

    while (true) {

        clearScreen();

        cout << "╔══════════════════════════════════════════════════════╗\n";
        cout << "║        CHƯƠNG TRÌNH KIỂM TRA ĐA THỨC                 ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n\n";

        cout << "1. Kiểm tra đa thức\n";
        cout << "2. Thoát\n\n";

        cout << "Lựa chọn: ";

        getline(cin, option);

        if (option == "1") {

            runCheck();
        }
        else if (option == "2") {

            cout << "\nThoát chương trình.\n";

            break;
        }
        else {

            cout << "\nLựa chọn không hợp lệ.\n";

            shortSleep();
        }
    }

    return 0;
}
