#include "BCDNumber.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi

using namespace std;

vector<unsigned char> bcd_addition(vector<unsigned char>& vector1, vector<unsigned char>& vector2) {
    unsigned char carry = 0;
    unsigned char digit1;
    unsigned char digit2;
    unsigned char digit_sum;
   

    int maxSize = max(vector1.size(), vector2.size());
    vector<unsigned char> result(maxSize, 0);
    for (int i = 0; i < maxSize; i++) {
        if (i < vector1.size() && i < vector2.size()) {
            // Wyci¹ganie cyfr z wektorów i dodawanie ich
            digit1 = vector1[i] & 0x0F; //wyciagniecie cyfry za pomoca operacji AND 0x0F to 00001111 czyli dla vectora[i] = przykladowo 0x32
            digit2 = vector2[i] & 0x0F; //operacja spowoduje ze wszystkie bity w vector[i] oprocz 4 najmlodszych zostana ustawione na 0 czyli otrzymujemy jednosci 
            digit2 += carry;
        }
        else if (i < vector1.size()) {
            digit1 = vector1[i] & 0x0F;
            digit1 += carry;
        }
        else {
            digit1 = vector2[i] & 0x0F;
            digit1 += carry;
        }
        // Wywo³anie instrukcji AAA, aby skorygowaæ sumê
        __asm {
            mov al, digit1
            add al, digit2
            aaa; korygujemy cyfry jednosci(-6 jesli wiêksze od 9 i przeniesienie = 1)
            mov digit_sum, al
            mov carry, ah
        }
        digit1 = 0;
        digit2 = 0;
        // Zapisywanie sumy cyfr do wynikowego wektora  
        result[i] |= digit_sum;

        // Wyci¹ganie cyfr dziesi¹tek z wektorów i dodawanie ich
        if (i < vector1.size() && i < vector2.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit2 = (vector2[i] >> 4) & 0x0F;
            digit2 += carry;
        }
        else if (i < vector1.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit1 += carry;
        }
        else {
            digit1 = (vector2[i] >> 4) & 0x0F;
            digit1 += carry;
        }
        // Wywo³anie instrukcji AAA, aby skorygowaæ sumê
        __asm {
            mov al, digit1
            add al, digit2
            aaa; ewentualne dodanie przeniesienia z jednosci i korekta wartosci w rejestrze al w przypadku przekroczenia wartosci 9
            mov digit_sum, al
            mov carry, ah
        }
        digit1 = 0;
        digit2 = 0;
        // Zapisywanie sumy dziesi¹tek do wynikowego wektora
        result[i] |= (digit_sum << 4);
        if (i == maxSize - 1 && carry) {
            result.push_back(1);
        }
    }
    return result;
}

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber result; // tworzymy result do którego bêdziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_addiction
    result.digits = bcd_addition(digits, other.digits);

    return result;
}

vector<unsigned char> bcd_substraction(vector<unsigned char>& vector1, vector<unsigned char>& vector2) {
    unsigned char carry = 0;
    unsigned char bonuscarry = 0;
    unsigned char digit1;
    unsigned char digit2;
    unsigned char digit_sub;
    int maxSize = max(vector1.size(), vector2.size());
    vector<unsigned char> result(maxSize, 0);
    for (int i = 0; i < maxSize; i++) {
        digit2 = 0;
        if (i < vector1.size() && i < vector2.size()) {
            // Wyci¹ganie cyfr z wektorów i odejmowanie ich
            digit1 = vector1[i] & 0x0F; //wyciagniecie cyfry za pomoca operacji AND 0x0F to 00001111 czyli dla vectora[i] = przykladowo 0x32
            digit2 = vector2[i] & 0x0F; //operacja spowoduje ze wszystkie bity w vector[i] oprocz 4 najmlodszych zostana ustawione na 0 czyli otrzymujemy jednosci 
        }
        else if (i < vector1.size()) {
            digit1 = vector1[i] & 0x0F;
        }
        if (digit1 <= digit2 && carry)
            digit1 += 9;
        else if (digit1 > digit2 && carry)
            digit1--;
        bonuscarry = carry;
        __asm {
            mov al, digit1
            sub al, digit2
            aas; korygujemy cyfry jednosci(-6 jesli wiêksze od 9 i przeniesienie = 1)
            mov digit_sub, al
            mov carry, ah
        }
        if (carry != 0 || bonuscarry)
            carry = 1;
        // Zapisywanie ró¿nicy cyfr do wynikowego wektora  
        result[i] |= digit_sub;

        // Wyci¹ganie cyfr dziesi¹tek z wektorów i odejmowanie ich
        if (i < vector1.size() && i < vector2.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit2 = (vector2[i] >> 4) & 0x0F;
        }
        else if (i < vector1.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
        }
        // Wywo³anie instrukcji AAS, aby skorygowaæ ró¿nicê
        if (digit1 <= digit2 && carry) {
            digit1 += 9;
            bonuscarry = carry;
            carry=0;
        }
        if (digit1 > digit2 && carry)
            digit1--;
        __asm {
            mov al, digit1
            sub al, digit2
            aas; ewentualne dodanie przeniesienia z jednosci i korekta wartosci w rejestrze al w przypadku przekroczenia wartosci 9
            mov digit_sub, al
            mov carry, ah
        }
        if (carry != 0 || bonuscarry) {
            carry = 1;
            bonuscarry = 0;
        }
        

        // Zapisywanie ró¿nicy dziesi¹tek do wynikowego wektora
        result[i] |= (digit_sub << 4);
    }
    return result;
}

BCDNumber BCDNumber::operator-(BCDNumber& other) {
    BCDNumber result; // tworzymy result do którego bêdziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_substraction
    result.digits = bcd_substraction(digits, other.digits);

    return result;
}

vector<unsigned char> bcd_multiplication(vector<unsigned char>& vector1, vector<unsigned char>& vector2) {
    unsigned char carry = 0;
    unsigned char carry1 = 0;
    unsigned char digit1;
    unsigned char digit2;
    unsigned char digitMultiplicant;
    unsigned char digit_mul;
    unsigned char temp1;
    BCDNumber finalResult(0);
    int x = 0;
    int maxSize = max(vector1.size(), vector2.size());
    vector<unsigned char> result(maxSize, 0);
    vector<unsigned char> result1(maxSize, 0);
    for (int i = 0; i < vector2.size(); i++) {
        x = i;
        result1.clear();
        result.clear();
        for (int k = x; k > 0; k--)
            result1.push_back(0);
        for (int j = 0; j < vector1.size(); j++) {
            // Wyci¹ganie cyfr z wektorów i dodawanie ich
            digit1 = vector1[j] & 0x0F; //wyciagniecie cyfry za pomoca operacji AND 0x0F to 00001111 czyli dla vectora[i] = przykladowo 0x32
            digit2 = (vector1[j] >> 4) & 0x0F;; //operacja spowoduje ze wszystkie bity w vector[i] oprocz 4 najmlodszych zostana ustawione na 0 czyli otrzymujemy jednosci 
            digitMultiplicant = vector2[i] & 0x0F;
            if (result.size() <= j) {
                result.push_back(0);
            }
            if (vector1[j] == 0 || vector2[i] == 0) {
                result.push_back(0);
                result1.push_back(0);
                continue;
            }
            if (result[j] == 0) {
                __asm {
                    mov al, digit1
                    mul digitMultiplicant; mnozymy 0x razy 0x
                    aam
                    mov digit_mul, al
                    mov carry, ah
                }
                result[j] |= digit_mul;
                temp1 = carry;
                __asm {
                    mov al, digit2
                    mul digitMultiplicant
                    aam
                    mov digit_mul, al
                    mov carry, ah
                    mov ah, 0
                    add al, temp1
                    aaa
                    mov digit_mul, al
                    mov carry1, ah; przeniesienie z mnozenia x0* 0x wpisujemy carry1
                    mov al, carry
                    add al, carry1
                    mov carry, al
                }
                // Zapisywanie sumy cyfr do wynikowego wektora  

                result[j] |= (digit_mul << 4);
                if (carry != 0)
                    result.push_back(carry);
            }
            else
            {
                temp1 = result[j] & 0x0F;
                __asm {
                    mov al, digit1
                    mul digitMultiplicant; mnozymy 0x razy 0x
                    aam
                    mov digit_mul, al
                    mov carry, ah
                    mov ah, 0
                    add al, temp1
                    aaa
                    mov digit_mul, al
                    mov temp1, ah
                }
                temp1 += carry;
                result[j] = digit_mul;
                __asm {
                    mov al, digit2
                    mul digitMultiplicant
                    aam
                    mov digit_mul, al
                    mov carry, ah
                    add al, temp1
                    mov ah, 0
                    aaa
                    mov digit_mul, al
                    mov carry1, ah; przeniesienie z mnozenia x0* 0x wpisujemy carry1
                    mov al, carry
                    add al, carry1
                    mov carry, al
                }
                result[j] |= (digit_mul << 4);
                if (carry != 0)
                    result.push_back(carry);
            }
            digitMultiplicant = (vector2[i] >> 4) & 0x0F;
            if (result1.size() <= j) {
                result1.push_back(0);
            }
            if (result1[j] == 0)
            {
                __asm {
                    mov al, digit1
                    mul digitMultiplicant; mnozymy 0x razy 0x
                    aam
                    mov digit_mul, al
                    mov carry, ah
                }
                result1[j] |= (digit_mul << 4) ;
                temp1 = carry;
                __asm {
                    mov al, digit2
                    mul digitMultiplicant
                    aam
                    mov digit_mul, al
                    mov carry, ah
                    mov ah, 0
                    add al, temp1
                    aaa
                    mov digit_mul, al
                    mov carry1, ah; przeniesienie z mnozenia x0* 0x wpisujemy carry1
                    mov al, carry
                    add al, carry1
                    mov carry, al
                }
                // Zapisywanie sumy cyfr do wynikowego wektora  

                result1.push_back(digit_mul);
                if (carry != 0)
                    result1[1+j] |= carry << 4;
            }
            else {
                temp1 = (result1[j] >> 4) & 0x0F;
                __asm {
                    mov al, digit1
                    mul digitMultiplicant; mnozymy 0x razy 0x
                    aam
                    mov digit_mul, al
                    mov carry, ah
                    mov ah, 0
                    add al, temp1
                    aaa
                    mov digit_mul, al
                    mov temp1, ah
                }
                temp1 += carry;
                carry1 = result1[j] & 0x0F;
                result1[j] = (digit_mul << 4) + carry1;
                __asm {
                    mov al, digit2
                    mul digitMultiplicant
                    aam
                    mov digit_mul, al
                    mov carry, ah
                    mov ah, 0
                    add al, temp1
                    aaa
                    mov digit_mul, al
                    mov carry1, ah; przeniesienie z mnozenia x0* 0x wpisujemy carry1
                    mov al, carry
                    add al, carry1
                    mov carry, al
                }
                result1.push_back(digit_mul);
                if (carry != 0)
                    result1[1+j] |= carry << 4;
            }
            x++;
        }
        x = i;
        string str;
        str.reserve(result.size());
        int z;
        int y;
        for (char digit : result) { //poprawione wypisywanie liczb 
            z = (digit >> 4) & 0x0F;
            y = digit & 0x0F;
            str.insert(str.begin(), y + '0');
            str.insert(str.begin(), z + '0');
        }
        for(int u = 0 ; u < (x*2);u++)
        str.push_back('0');
        BCDNumber temporary(str);
        str.clear();
        str.reserve(result1.size());
        for (char digit : result1) { //poprawione wypisywanie liczb 
            z = (digit >> 4) & 0x0F;
            y = digit & 0x0F;
            str.insert(str.begin(), y + '0');
            str.insert(str.begin(), z + '0');
        }
        for (int u = 0; u < x * 2; u++)
            str.push_back('0');
        BCDNumber temporaryResult(str);
        finalResult = temporary + temporaryResult + finalResult;
    }
    if (carry1 != 0)
        result.push_back(carry1);

    return finalResult.digits;
}

BCDNumber BCDNumber::operator*(BCDNumber& other) {
    BCDNumber result; // tworzymy result do którego bêdziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_substraction
    result.digits = bcd_multiplication(digits, other.digits);

    return result;
    
}
// Konstruktor, tworz¹cy BCDNumber o wartoœci 0
BCDNumber::BCDNumber() {
}

BCDNumber::BCDNumber(string str) {
    int x;
    int y;
    int z;
    unsigned char move;
    if (str.size() % 2)
        str.insert(0, "0");
    for (int i = 0; i < str.size(); i += 2) {
        x = stoi(str.substr(i, 2));
        y = x / 10;
        z = x % 10;
        move = (y << 4) | z;
        digits.insert(digits.begin(), move);
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
    for (char digit : digits) { //poprawione wypisywanie liczb 
        x = (digit >> 4) & 0x0F;
        y = digit & 0x0F;
        str.insert(str.begin(), y + '0');
        str.insert(str.begin(), x + '0');
    }
    while (str.substr(0, 1) == "0") {
        if (str.length() > 1)
            str.erase(0, 1);
        else
            break;
    }
    return str;
}