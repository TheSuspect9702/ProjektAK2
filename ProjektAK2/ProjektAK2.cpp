#include "BCDLibrary.h"
#include <iostream>
using namespace std;

int main()
{
    string a = "0001",b = "00100101"; //00100110
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
        unsigned char sum = carry;
        //      0010
        // 0101 0001
       /* if (i < digits.size())
            sum += other.digits[other.digits.size() - 1 - i];
        if (i < other.digits.size())
            sum += other.digits[other.digits.size() - 1 - i];

        result.digits.insert(result.digits.begin(), sum % 2 + 48);
        cout << "i: " << i << ", carry: " << carry << ", sum: " << sum << endl;
        carry = sum/2;*/

        cout << "123123";

        if (i < digits.size() && i < other.digits.size()) {
            if (sum == '1') {
                if (other.digits[other.digits.size() - 1 - i] == '1' && other.digits[other.digits.size() - 1 - i] == '1') {
                    sum = '1';
                    carry = '1';
                }
                else if (other.digits[other.digits.size() - 1 - i] == '1' && other.digits[other.digits.size() - 1 - i] == '1') {
                    sum = '0';
                    carry = '1';
                }
                else {
                    sum = '1';
                    carry = '0';
                }
            }
            else {
                if (other.digits[other.digits.size() - 1 - i] == '1' && other.digits[other.digits.size() - 1 - i] == '1') {
                    sum = '0';
                    carry = '1';
                }
                else if (other.digits[other.digits.size() - 1 - i] == '1' && other.digits[other.digits.size() - 1 - i] == '1') {
                    sum = '1';
                    carry = '0';
                }
                else {
                    sum = '0';
                    carry = '0';
                }
            }
        }
        cout << "i: " << i << ", carry: " << carry << ", sum: " << sum << endl;
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
string BCDNumber::toString(){
    string str;
    str.reserve(digits.size());

    for (unsigned char digit : digits) {
        str.push_back(digit);
    }

    return str;
}
