#include "BCDLibrary.h"
#include <iostream>
using namespace std;
BCDNumber repair("0110");
int main()
{//                22              15              
    string a = "10001001", b = "10000111"; // + 00110111
                                           // - 00000111
    BCDNumber num1(a);
    BCDNumber num2(b);
    BCDNumber sum = num1 + num2;
    BCDNumber substraction = num1 - num2;
    cout << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << std::endl;
    cout << num1.toString() << " - " << num2.toString() << " = " << substraction.toString() << std::endl;

    return 0;
}

BCDNumber BCDNumber::operator+(BCDNumber& other) {
     if (digits[digits.size()-1] == 0)
            digits.erase(digits.end()-1);
     if (other.digits[other.digits.size()-1] == 0)
         other.digits.erase(other.digits.end()-1);
    BCDNumber result;
    int newSize = max(digits.size(), other.digits.size());
    unsigned char carry = '0';
    unsigned char sum;
    for (int i = 0; i < newSize; i++) {
        sum = carry;
    
        if (i < digits.size()) 
            sum += digits[digits.size() - 1 - i];
        if (i < other.digits.size()) 
            sum += other.digits[other.digits.size() - 1 - i];
        result.digits.insert(result.digits.begin(), sum % 2 + 48);
        if (int(sum) - 145 > 0)
            carry = '1';
        else
            carry = '0';
        if (i % 4 == 3 && carry == '1') {
           /* if (result.digits[result.digits.size() - 1] == 0)
                result.digits.erase(result.digits.end()-1);*/
            int x = 0;
            string str;
            /*for (int j = i - 3; j <= i; j++)
                str.push_back(result.digits[j]);
            BCDNumber temp(str);
            BCDNumber corrected = temp + repair;
            for (int j = i - 3; j <= i; j++) {
                result.digits[j] = corrected.digits[x];
                x++;
                10001001 + 10000111
            }*/
            BCDNumber temp(result.toString());
            for (int j = i - 3; j > 0; j--)
                repair.digits.insert(repair.digits.end(), 48);
            result = temp + repair;
            result.digits.erase(result.digits.end() - 1);
            if (newSize < result.digits.size()) 
                newSize = result.digits.size();
            if (i == newSize -1)
            for (int k = 0; k <= 3; k++) {
                if (k == 0)
                    result.digits.insert(result.digits.begin(), 49);
                else
                    result.digits.insert(result.digits.begin(), 48);
            }
        }
    }
   /* for (int i = 0; i < newSize; i++) {
        if (i % 4 == 3) {
            if (result.digits[i] == '1' && (result.digits[i - 1] == '1' || result.digits[i - 2] == '1')) {
                int x = 0;
                string str;
                for (int j = i - 3; j <= i; j++)
                    str.push_back(result.digits[j]);
                BCDNumber temp(str);
                BCDNumber corrected = temp + repair;
                for (int j = i - 3; j <= i; j++) {
                    result.digits[j] = corrected.digits[x];
                    x++;
                }
            }
        }
    }*/
    return result;
}
// Konstruktor, tworzący BCDNumber o wartości 0
BCDNumber::BCDNumber() {
    digits.push_back(0);
}
BCDNumber BCDNumber::operator-(BCDNumber& other) {

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
