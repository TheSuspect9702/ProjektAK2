#include "BCDNumber.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
using namespace std;

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber result;
    unsigned char sum;
    unsigned char temp;
    unsigned char temp1;
    unsigned char holdDigits, holdOtherDigits;
    int newSize = max(digits.size(), other.digits.size());
    unsigned char carry = 0;
    unsigned carryInside = 0;
    int k;
    for (int i = 0; i < newSize; i++) {
        k = 0;
        sum = 0;
        if (digits.size() > i && other.digits.size() > i) {
            holdDigits = digits[i];
            holdOtherDigits = other.digits[i];
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
                k++;
                if (j == 4) 
                    if (sum > 9) {
                        sum += 6;
                        if (sum < 16)
                            carryInside = 1;
                        else
                            carryInside = 0;
                    }
                if (j == 0) {
                    unsigned char tempSum = (sum >> 4);
                    unsigned char tempSum1 = sum - tempSum*(pow(2, 4));
                    if (tempSum > 9) {
                        tempSum += 6;
                        sum = (tempSum << 4) | tempSum1;
                        carryInside = 1;
                    }
                    carry = carryInside;
                }
            }
            result.digits.push_back(sum);
            digits[i] = holdDigits;
            other.digits[i] = holdOtherDigits;
        }
        else if (digits.size() > i) { //dodawanie jesli pierwszy wyraz jest d³u¿szy od drugiego
            holdDigits = digits[i];
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
                    }
                    else
                        sum += temp * pow(2, k);
                }
                else {
                    if (carryInside) {
                        sum += carryInside * pow(2, k);
                        carryInside = 0;
                    }
                    else
                        sum += 0;
                }
                k++;
                if (j == 4)
                    if (sum > 9) {
                        sum += 6;
                        if (sum < 16)
                            carryInside = 1;
                        else
                            carryInside = 0;
                    }
                if (j == 0) {
                    unsigned char tempSum = (sum >> 4);
                    unsigned char tempSum1 = sum - tempSum * (pow(2, 4));
                    if (tempSum > 9) {
                        tempSum += 6;
                        sum = (tempSum << 4) | tempSum1;
                        carryInside = 1;
                    }
                    carry = carryInside;
                }
            }
            result.digits.push_back(sum);
            digits[i] = holdDigits;
        }
        else if (other.digits.size() > i) { // dodawanie kiedy drugi wyraz jest d³u¿szy
            holdOtherDigits = other.digits[i];
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
                    }
                    else
                        sum += temp * pow(2, k);
                }
                else {
                    if (carryInside) {
                        sum += carryInside * pow(2, k);
                        carryInside = 0;
                    }
                    else
                        sum += 0;
                }
                k++;
                if (j == 4)
                    if (sum > 9) {
                        sum += 6;
                        if (sum < 16)
                            carryInside = 1;
                        else
                            carryInside = 0;
                    }
                if (j == 0) {
                    unsigned char tempSum = (sum >> 4);
                    unsigned char tempSum1 = sum - tempSum * (pow(2, 4));
                    if (tempSum > 9) {
                        tempSum += 6;
                        sum = (tempSum << 4) | tempSum1;
                        carryInside = 1;
                    }
                    carry = carryInside;
                }
            }
            result.digits.push_back(sum);
            other.digits[i] = holdOtherDigits;
        }
    }
    if (carry == 1) {
        sum = 1;
        result.digits.push_back(sum);
    }
    return result;
}

BCDNumber BCDNumber::operator-(BCDNumber& other) {
    BCDNumber result;
    unsigned char substition;                               //char to put into result digits
    unsigned char temp;
    unsigned char temp1;
    int newSize = max(digits.size(), other.digits.size());  //taking size of the biggest number
    unsigned char borrow = 0;
    unsigned borrowInside = 0;
    unsigned char holdDigits, holdOtherDigits;
    int k;
    if (digits.size() != newSize) {
        cout << "No co ty co ty nie ma liczb ujemnych";
    }
    else {
        for (int i = 0; i < newSize; i++) {
            k = 0;
            substition = 0;
            if (digits.size() > i && other.digits.size() > i) {
                holdDigits = digits[i];
                holdOtherDigits = other.digits[i];
                for (int j = 7; j >= 0; j--) {
                    if (j == 7) {
                        borrowInside = borrow;    //ustawienie przeniesienia z poprzedniej dwojki cyfr 
                        borrow = 0;
                    }
                    temp = 0;
                    temp1 = 0;
                    temp = ((holdDigits % 2) ? 1 : 0);                       // ustalenie wartosci kolejnych bitow zaczynajac od tych najmniej znaczaych (od konca)
                    holdDigits -= (temp + holdDigits / 2);
                    temp1 = ((holdOtherDigits % 2) ? 1 : 0);
                    holdOtherDigits -= (temp1 + holdOtherDigits / 2);       // kolejne dzielenia liczb 
                    if (temp == temp1 && temp != 0) {                       //pocz¹tek logiki odejmowania
                        if (borrowInside) {
                            substition += pow(2, k);
                        }
                    }
                    else if (temp == temp1) {
                        if (borrowInside) {
                            substition += pow(2, k);
                        }
                    }
                    else {
                        if (temp1 > temp) {
                            if (!borrowInside) {
                                substition += pow(2, k);
                                borrowInside = 1;
                            }
                            else
                                borrowInside = 0;
                        }
                        else {
                            if (borrowInside)
                                borrowInside = 0;
                            else
                                substition += pow(2, k);
                        }
                    }
                    k++;
                    if (j == 4)
                        if (substition > 9) {
                            substition -= 6;
                        }
                    if (j == 0) {                                                  // koniec logiki odejmowania
                        unsigned char tempsubstition = (substition >> 4);
                        unsigned char tempsubstition1 = substition - tempsubstition * (pow(2, 4));
                        if (tempsubstition > 9 || borrowInside) {
                            tempsubstition -= 6;
                            substition = (tempsubstition << 4) | tempsubstition1;
                        }
                        borrow = borrowInside;
                    }
                }
                result.digits.push_back(substition);
            }
            else {                                                                  //odejmowanie kiedy skoncza sie bity drugiej liczby 
                holdDigits = digits[i];
                for (int j = 7; j >= 0; j--) {
                    if (j == 7) {
                        borrowInside = borrow;    //ustawienie przeniesienia z poprzedniej dwojki cyfr 
                        borrow = 0;
                    }
                    temp = 0;
                    temp = ((holdDigits % 2) ? 1 : 0);                       // ustalenie wartosci kolejnych bitow zaczynajac od tych najmniej znaczaych (od konca)
                    holdDigits -= (temp + holdDigits / 2);
                    if (temp) {                       //pocz¹tek logiki odejmowania
                        if (borrowInside)
                            borrowInside = 0;
                        else
                            substition += pow(2, k);
                    }
                    else {
                        if (borrowInside)
                            substition += pow(2, k);
                    }
                    k++;
                    if (j == 4)
                        if (substition > 9) {
                            substition -= 6;
                        }
                    if (j == 0) {                                                  // koniec logiki odejmowania
                        unsigned char tempsubstition = (substition >> 4);
                        unsigned char tempsubstition1 = substition - tempsubstition * (pow(2, 4));
                        if (tempsubstition > 9 || borrowInside) {
                            tempsubstition -= 6;
                            substition = (tempsubstition << 4) | tempsubstition1;
                        }
                        borrow = borrowInside;
                    }
                }
                result.digits.push_back(substition);
            }
        }
    }
    return result;
}

BCDNumber BCDNumber::operator*(BCDNumber& other) {
    BCDNumber result;
    unsigned char sum, sum1;
    int multiply = 0;
    unsigned char temp;
    unsigned char temp1;
    unsigned char holdDigits, holdOtherDigits;
    int k,z;
    for (int i = 0; i < other.digits.size(); i++) {
        BCDNumber mult1, mult2, mult3, mult4;
        multiply = 0;
        k = 0;
        z = 0;
        sum = 0;
        sum1 = 0;
        holdOtherDigits = other.digits[i];
        for (int j = 7; j >= 0; j--) {
            temp1 = ((holdOtherDigits % 2) ? 1 : 0);
            holdOtherDigits -= (temp1 + holdOtherDigits / 2);
            sum += temp1 * pow(2, k);
            k++;
        }
        for (int x = 0; x < digits.size(); x++) {
            holdDigits = digits[x];
            for (int c = 3; c >= 0; c--) {
                temp = ((holdDigits % 2) ? 1 : 0);
                holdDigits -= (temp + holdDigits / 2);
                sum1 += temp * pow(2, z);
                z++;
            }
            multiply += sum1 * sum;
            z = 0;
            sum1 = 0;
            for (int c = 3; c >= 0; c--) {
                temp = ((holdDigits % 2) ? 1 : 0);
                holdDigits -= (temp + holdDigits / 2);
                sum1 += temp * pow(2, z);
                z++;
            }
            multiply += sum1 * sum * 10;
            mult1 = BCDNumber(to_string(multiply)); //dziala ale nie dla wszystich na pewno tylko dla liczby dwucyfrowej * jednocyfrowa
        }
        result = result + mult1;
    }
    return result;
}
// Konstruktor, tworz¹cy BCDNumber o wartoœci 0
BCDNumber::BCDNumber() {
    digits.push_back(0);
}

BCDNumber::BCDNumber(string str) {
    int x;
    int y;
    int z;
    unsigned char move;
    if (str.size() % 2)
        str.insert(0, "0");
    for (int i = 0; i < str.size(); i+=2) {
        x = stoi(str.substr(i, 2));
        y = x / 10;
        z = x % 10;
        move = (y << 4) | z;
        digits.insert(digits.begin(),move);
    }
}
BCDNumber::BCDNumber(char value) {
    int x;
    int y;
    unsigned char move;
    x = value / 10;
    y = value % 10;
    move = (x << 4) | y;
    digits.insert(digits.begin(), move);
}

// Konwersja na string
string BCDNumber::toString() {
    string str;
    str.reserve(digits.size());
    int x;
    int y;
    if (digits[0] == 0)
        digits.erase(digits.begin());
    for (char digit : digits) { //poprawione wypisywanie liczb 
        x = (digit >> 4) & 0x0F;
        y = digit & 0x0F;
        str.insert(str.begin(), y + '0');
        str.insert(str.begin(), x + '0');
    }
    return str;
}
//if (j == 4) {
           //    k = 0;
           //    for (int x = 0; x < digits.size(); x++) {
           //        holdDigits = digits[x];
           //        for (int c = 3; c >= 0; c--) {
           //            temp = ((holdDigits % 2) ? 1 : 0);
           //            holdDigits -= (temp + holdDigits / 2);
           //            sum1 += temp * pow(2, z);
           //            z++;
           //        }
           //        z = 0;
           //        sum1 *= sum;
           //        mult1 = BCDNumber(sum1);
           //        sum1 = 0;
           //        for (int c = 3; c >= 0; c--) {
           //            temp = ((holdDigits % 2) ? 1 : 0);
           //            holdDigits -= (temp + holdDigits / 2);
           //            sum1 += temp * pow(2, z);
           //            z++;
           //        }
           //        sum1 *= sum;
           //        mult2 = BCDNumber();//jak to dalej zrobic
           //        BCDNumber add = mult1 + mult2;
           //    }
           //}