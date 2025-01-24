#include <iostream>
#include <sstream>
#include "fraction.h"

using namespace std;

int main() {
    Fraction
            f1(42,-301),
            f2(5),
            f3;
    stringstream
            sstr;
    bool
            okay=true;

    // test 1: constructor
    if (f1.getNum() != -6 || f1.getDen() != 43) {
        cout << "Constructor failed, 2 operands" << endl;
        okay = false;
    }
    if (f2.getNum() != 5 || f2.getDen() != 1) {
        cout << "Constructor failed, 1 operand" << endl;
        okay = false;
    }
    if (f3.getNum() != 0 || f3.getDen() != 1) {
        cout << "Constructor failed, 0 operands" << endl;
        okay = false;
    }
    cout << "Constructor: " << (okay ? "pass" : "fail") << endl;

    // output
    okay = true;
    sstr << f1;
    if (sstr.str() != "-6 / 43")
        okay = false;
    sstr.str("");
    sstr << f2;
    if (sstr.str() != "5 / 1")
        okay = false;
    sstr.str("");
    sstr << f3;
    if (sstr.str() != "0 / 1")
        okay = false;
    cout << "     Output: " << (okay ? "pass" : "fail") << endl;

    // input
    sstr.str("2/-4");
    sstr >> f1;
    okay = f1.getNum() == -1 && f1.getDen() == 2;
    cout << "      Input: " << (okay ? "pass" : "fail") << endl;

    // arithmetic
    f1 = Fraction(7,6);
    f2 = Fraction(12,8);

    // +
    f3 = f1 + f2;
    okay = f3.getNum() == 8 && f3.getDen() == 3;
    f3 = f1 + 2;
    okay = okay && f3.getNum() == 19 && f3.getDen() == 6;
    cout << "          +: " << (okay ? "pass" : "fail") << endl;

    // -
    f3 = f1 - f2;
    okay = f3.getNum() == -1 && f3.getDen() == 3;
    f3 = f1 - 2;
    okay = okay && f3.getNum() == -5 && f3.getDen() == 6;
    cout << "          -: " << (okay ? "pass" : "fail") << endl;

    // +
    f3 = f1 * f2;
    okay = f3.getNum() == 7 && f3.getDen() == 4;
    f3 = f1 * 2;
    okay = okay && f3.getNum() == 7 && f3.getDen() == 3;
    cout << "          *: " << (okay ? "pass" : "fail") << endl;

    // +
    f3 = f1 / f2;
    okay = f3.getNum() == 7 && f3.getDen() == 9;
    f3 = f1 / 2;
    okay = okay && f3.getNum() == 7 && f3.getDen() == 12;
    cout << "          /: " << (okay ? "pass" : "fail") << endl;

    // =
    f3 = f1;
    okay = f1.getNum() == f3.getNum() && f1.getDen() == f3.getDen();
    cout << "          =: " << (okay ? "pass" : "fail") << endl;

    // ==
    okay = !(f1 == f2) && (f1 == f1) && !(f1 == 2);
    cout << "         ==: " << (okay ? "pass" : "fail") << endl;

    // !=
    okay = (f1 != f2) && !(f1 != f1) && (f1 != 2);
    cout << "         !=: " << (okay ? "pass" : "fail") << endl;

    // <
    okay = (f1 < f2) && !(f2 < f1) && !(f1 < f1) && (f1 < 2);
    cout << "          <: " << (okay ? "pass" : "fail") << endl;

    // >
    okay = !(f1 > f2) && (f2 > f1) && !(f1 > f1) && !(f1 > 2);
    cout << "          >: " << (okay ? "pass" : "fail") << endl;

    // <=
    okay = (f1 <= f2) && !(f2 <= f1) && (f1 <= f1) && (f1 <= 2);
    cout << "         <=: " << (okay ? "pass" : "fail") << endl;

    // >=
    okay = !(f1 >= f2) && (f2 >= f1) && (f1 >= f1) && !(f1 >= 2);
    cout << "         >=: " << (okay ? "pass" : "fail") << endl;

    return 0;
}
