#ifndef BCDNUMBER_H
#define BCDNUMBER_H

#include <vector>
#include <iostream>

class BCDNumber {
public:
    // Konstruktory
    BCDNumber();
    BCDNumber(std::string str);

    BCDNumber(char value);

    // Przeci¹¿anie operatorów arytmetycznych
    BCDNumber operator+(BCDNumber& other);
    BCDNumber operator-(BCDNumber& other);
    BCDNumber operator*(BCDNumber& other);
    BCDNumber operator/(BCDNumber& other);

    int comma;
    bool sign; // true - liczba jest ujemna, false liczba jest dodatnia
    std::string toString();
    std::vector<unsigned char> digits;
};

#endif // BCDNUMBER_H