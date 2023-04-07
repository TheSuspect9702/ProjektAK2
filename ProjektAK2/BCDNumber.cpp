#include "BCDNumber.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
using namespace std;

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber result;
    int newSize = max(digits.size(), other.digits.size());
    unsigned char carry = 1;
    for (int i = 0; i < newSize; i++) {

    }
    return result;
}
// Konstruktor, tworz¹cy BCDNumber o wartoœci 0
BCDNumber::BCDNumber() {
    digits.push_back(0);
}
BCDNumber BCDNumber::operator-(BCDNumber& other) {
    BCDNumber repair("0110");
    BCDNumber result;
    int newSize = max(digits.size(), other.digits.size());
    unsigned char carry = '0'; //zapozyczenie
    unsigned char sub = '0'; //wynik poszczegolnych odejmowan
    int b = 0, c = 0;
    if (digits.size() >= other.digits.size()) {
        for (int i = 0; i < newSize; i++) {

            // 0010 0010
            // 0001 0101

            if (i < other.digits.size()) {
                sub = digits[digits.size() - 1 - i] - b - other.digits[other.digits.size() - i - 1] + 48;

                /*cout << "c: " << c << ", b: " << b << ", sub: " << sub << endl;*/
            }
            else {
                sub = digits[digits.size() - 1 - i] - b;
            }
            if (sub < 48) {
                sub += 2;
                b = 1;
            }
            else {
                b = 0;
            }


            result.digits.insert(result.digits.begin(), sub);
            //Dodanie korekty przy zapozyczeniu z kolejnej grupy bitow
            if (i % 4 == 3 && b == 1) {
                int x = 0;
                string str;
                for (int j = i - 3; j <= i; j++)
                    str.push_back(result.digits[j]);
                BCDNumber temp(str);
                BCDNumber corrected = temp - repair;
                for (int j = i - 3; j <= i; j++) {
                    result.digits[j] = corrected.digits[x];
                    x++;
                }
            }
        }
    }
    else cout << "No nie da sie" << endl;

    return result;

}
BCDNumber::BCDNumber(string str) {
    int x;
    int y;
    int z;
    unsigned char move;
    for (int i = 0; i < str.size(); i+=2) {
        x = stoi(str.substr(i, 2));
        y = x / 10;
        z = x % 10;
        move = (y << 4) | z;
        digits.push_back(move);
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
