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

    std::string toString();
private:
    std::vector<unsigned char> digits;
};

#endif // BCDNUMBER_H