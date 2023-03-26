#include "BCDLibrary.h"
#include <iostream>
using namespace std;

int main()
{
    string a = "10000001", b = "10100101"; //00100110
    BCDNumber num1(a);
    BCDNumber num2(b);
    BCDNumber sum = num1 + num2;
    cout << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << std::endl;

    return 0;
}

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber odwrotnie;
    BCDNumber result;
    int newSize = max(digits.size(), other.digits.size());
    unsigned char carry = '0';
    for (int i = 0; i < newSize; i++) {
        cout << "i: " << i << ", carry: " << int(carry) << "      ";
        unsigned char sum = carry;
        //      0010
        // 0101 0001
        if (i < digits.size()) {
            sum += digits[digits.size() - 1 - i];
            cout << "suma: " << int(sum) << " digit: " << digits[digits.size() - 1 - i] << "   ";
        }
        if (i < other.digits.size()) {
            sum += other.digits[other.digits.size() - 1 - i];
            cout << "suma: " << int(sum) << " digit: " << other.digits[other.digits.size() - 1 - i] << "   ";
        }
        cout << "co wpisuje " << int(sum % 2 + 48);
        result.digits.insert(result.digits.begin(), sum % 2 + 48);
        if (int(sum) - 145 > 0)
            carry = '1';
        else
            carry = '0';
        cout << "i: " << i << ", carry: " << carry << ", sum: " << sum << endl;
    }
    if (carry == '1') {
        for (int i = 0; i <= 3; i++) {
            if (i == 0)
                result.digits.insert(result.digits.begin(), 49);
            else 
                result.digits.insert(result.digits.begin(), 48);
        }
    }
    return result;
}
// Konstruktor, tworzący BCDNumber o wartości 0
BCDNumber::BCDNumber() {
    digits.push_back(0);
}

BCDNumber::BCDNumber(string str) {
    for (int i = 0; i < str.size(); i++) {
        digits.push_back(str[i]);
    }
}


// Konwersja na string
string BCDNumber::toString() {
    string str;
    str.reserve(digits.size());

    for (unsigned char digit : digits) {
        str.push_back(digit);
    }

    return str;
}
