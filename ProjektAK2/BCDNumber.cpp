#include "BCDNumber.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
using namespace std;

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber result;
    unsigned char sum;
    unsigned char temp;
    unsigned char temp1;
    int newSize = max(digits.size(), other.digits.size());
    unsigned char carry = 0;
    unsigned carryInside = 0;
    int k;
    for (int i = 0; i <newSize; i++) {
        k = 0;
        sum = 0;
        if (digits.size() > i && other.digits.size() > i) {
            for (int j = 7; j >= 0; j--) {
                if (j == 7) {
                    carryInside = carry;    //ustawienie przeniesienia z poprzedniej dwojki cyfr 
                    carry = 0;
                }
                temp = 0;
                temp1 = 0;
                temp = ((digits[i] % 2) ? 1 : 0);
                digits[i] -= (temp + digits[i] / 2);
                temp1 = ((other.digits[i] % 2) ? 1 : 0);
                other.digits[i] -= (temp1 + other.digits[i] / 2);       // kolejne dzielenia liczb 
                if (temp == temp1 && temp != 0) {
                    if (carryInside)
                        sum += carryInside * pow(2, k);
                    else
                        sum += 0;
                    carryInside = 1;
                }
                else if (temp == temp1) {
                    if (carryInside) {
                        sum += carryInside * pow(2, k);
                        carryInside = 0;
                    }
                    else
                        sum += 0;
                }
                else {
                    if (carryInside)
                        sum += 0;
                    else
                        sum += ((temp > temp1) ? temp : temp1) * pow(2, k);
                }
                if (j == 0)
                    carry = carryInside;
                k++;
                if (j == 4) {
                    if (((sum & 0x30) == (0x20 || 0x40 || 0x60)) || ((sum & 0x03) == (0x02 || 0x04 || 0x06))) {
                        
 
                    }
                }
            }
            result.digits.push_back(sum);
        }
        else if (other.digits.size() <= i) { //dodawanie jesli pierwszy wyraz jest d³u¿szy od drugiego
            for (int j = 7; j >= 0; j--) {
                if (j == 7) {
                    carryInside = carry;    //ustawienie przeniesienia z poprzedniej dwojki cyfr 
                    carry = 0;
                }
                temp = 0;
                temp = ((digits[i] % 2) ? 1 : 0);
                digits[i] -= (temp + digits[i] / 2);
                if (temp) {
                    if (carryInside) {
                        sum += 0;
                        carryInside = 1;
                    }
                    else
                        sum += temp * pow(2, k);
                }
                else {
                    if (carryInside)
                        sum += carryInside * pow(2, k);
                    else
                        sum += 0;
                }
                if (j == 0)
                    carry = carryInside;
                k++;
            }
            result.digits.push_back(sum);
        }
        else if (digits.size() <= i) { // dodawanie kiedy drugi wyraz jest d³u¿szy
            for (int j = 7; j >= 0; j--) {
                if (j == 7) {
                    carryInside = carry;    //ustawienie przeniesienia z poprzedniej dwojki cyfr 
                    carry = 0;
                }
                temp = 0;
                temp = ((other.digits[i] % 2) ? 1 : 0);
                other.digits[i] -= (temp + other.digits[i] / 2);
                if (temp) {
                    if (carryInside) {
                        sum += 0;
                        carryInside = 1;
                    }
                    else
                        sum += temp * pow(2, k);
                }
                else {
                    if (carryInside)
                        sum += carryInside * pow(2, k);
                    else
                        sum += 0;
                }
                if (j == 0)
                    carry = carryInside;
                k++;
            }
            result.digits.push_back(sum);
        }
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
        digits.insert(digits.begin(),move);
    }
}


// Konwersja na string
string BCDNumber::toString() {
    string str;
    str.reserve(digits.size());
    int x;
    int y;
    digits.erase(digits.begin());
    for (char digit : digits) { //poprawione wypisywanie liczb 
        x = (digit >> 4) & 0x0F;
        y = digit & 0x0F;
        str.insert(str.begin(), y + '0');
        str.insert(str.begin(), x + '0');
    }
    return str;
}
