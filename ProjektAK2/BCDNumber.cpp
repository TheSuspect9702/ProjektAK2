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
            // Wyci�ganie cyfr z wektor�w i dodawanie ich
            digit1 = vector1[i] & 0x0F; //wyciagniecie cyfry za pomoca operacji AND 0x0F to 00001111 czyli dla vectora[i] = przykladowo 0x32
            digit2 = vector2[i] & 0x0F; //operacja spowoduje ze wszystkie bity w vector[i] oprocz 4 najmlodszych zostana ustawione na 0 czyli otrzymujemy jednosci 
            digit_sum = digit1 + digit2 + carry;
        }
        else if (i < vector1.size()) {
            digit1 = vector1[i] & 0x0F;
            digit_sum = digit1 + carry;
        }
        else {
            digit1 = vector2[i] & 0x0F;
            digit_sum = digit1 + carry;
        }
        // Wywo�anie instrukcji AAA, aby skorygowa� sum�
        __asm {
            aaa; korygujemy cyfry jednosci(-6 jesli wi�ksze od 9 i przeniesienie = 1)
            mov digit_sum, al
            mov carry, ah
        }

        // Zapisywanie sumy cyfr do wynikowego wektora  
        result[i] |= digit_sum;

        // Wyci�ganie cyfr dziesi�tek z wektor�w i dodawanie ich
        if (i < vector1.size() && i < vector2.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit2 = (vector2[i] >> 4) & 0x0F;
            digit_sum = digit1 + digit2 + carry;
        }
        else if (i < vector1.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit_sum = digit1 + carry;
        }
        else {
            digit1 = (vector2[i] >> 4) & 0x0F;
            digit_sum = digit1 + carry;
        }
        // Wywo�anie instrukcji AAA, aby skorygowa� sum�
        __asm {
            aaa; ewentualne dodanie przeniesienia z jednosci i korekta wartosci w rejestrze al w przypadku przekroczenia wartosci 9
            mov digit_sum, al
            mov carry, ah
        }
        // Zapisywanie sumy dziesi�tek do wynikowego wektora
        result[i] |= (digit_sum << 4);
        if (i == maxSize - 1 && carry) {
            result.push_back(1);
        }
    }
    return result;
}

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber result; // tworzymy result do kt�rego b�dziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_addiction
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
            // Wyci�ganie cyfr z wektor�w i odejmowanie ich
            digit1 = vector1[i] & 0x0F; //wyciagniecie cyfry za pomoca operacji AND 0x0F to 00001111 czyli dla vectora[i] = przykladowo 0x32
            digit2 = vector2[i] & 0x0F; //operacja spowoduje ze wszystkie bity w vector[i] oprocz 4 najmlodszych zostana ustawione na 0 czyli otrzymujemy jednosci 
        }
        else if (i < vector1.size()) {
            digit1 = vector1[i] & 0x0F;
        }
        if (digit1 <= digit2 && carry)
            digit1++;
        if (digit1 > digit2 && carry)
            digit1--;

        __asm {
            mov al, digit1
            sub al, digit2
            aas; korygujemy cyfry jednosci(-6 jesli wi�ksze od 9 i przeniesienie = 1)
            mov digit_sub, al
            mov carry, ah
        }
        if (carry != 0)
            carry = 1;
        // Zapisywanie r�nicy cyfr do wynikowego wektora  
        result[i] |= digit_sub;

        // Wyci�ganie cyfr dziesi�tek z wektor�w i odejmowanie ich
        if (i < vector1.size() && i < vector2.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit2 = (vector2[i] >> 4) & 0x0F;
        }
        else if (i < vector1.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
        }
        // Wywo�anie instrukcji AAS, aby skorygowa� r�nic�
        if (digit1 <= digit2 && carry) {
            digit1 += 9;
            bonuscarry = carry;
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
        

        // Zapisywanie r�nicy dziesi�tek do wynikowego wektora
        result[i] |= (digit_sub << 4);
    }
    return result;
}

BCDNumber BCDNumber::operator-(BCDNumber& other) {
    BCDNumber result; // tworzymy result do kt�rego b�dziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_substraction
    result.digits = bcd_substraction(digits, other.digits);

    return result;
}

vector<unsigned char> bcd_multiplication(vector<unsigned char>& vector1, vector<unsigned char>& vector2) {
    unsigned char carry = 0;
    unsigned char digit1;
    unsigned char digit2;
    unsigned char digit_mul;
    int maxSize = max(vector1.size(), vector2.size());
    vector<unsigned char> result(maxSize, 0);
    for (int i = 0; i < maxSize; i++) {
        if (i < vector1.size() && i < vector2.size()) {
            // Wyci�ganie cyfr z wektor�w i dodawanie ich
            digit1 = vector1[i] & 0x0F; //wyciagniecie cyfry za pomoca operacji AND 0x0F to 00001111 czyli dla vectora[i] = przykladowo 0x32
            digit2 = vector2[i] & 0x0F; //operacja spowoduje ze wszystkie bity w vector[i] oprocz 4 najmlodszych zostana ustawione na 0 czyli otrzymujemy jednosci 
        }
        else if (i < vector1.size()) {
            digit1 = vector1[i] & 0x0F;
        }
        else {
            digit1 = vector2[i] & 0x0F;
        }
        // Wywo�anie instrukcji AAA, aby skorygowa� sum�
        __asm {
            aam; korygujemy cyfry jednosci(-6 jesli wi�ksze od 9 i przeniesienie = 1)
            mov digit_mul, al
            mov carry, ah
        }

        // Zapisywanie sumy cyfr do wynikowego wektora  
        result[i] |= digit_mul;

        // Wyci�ganie cyfr dziesi�tek z wektor�w i dodawanie ich
        if (i < vector1.size() && i < vector2.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
            digit2 = (vector2[i] >> 4) & 0x0F;
        }
        else if (i < vector1.size()) {
            digit1 = (vector1[i] >> 4) & 0x0F;
        }
        else {
            digit1 = (vector2[i] >> 4) & 0x0F;
        }
        // Wywo�anie instrukcji AAA, aby skorygowa� sum�
        __asm {
            aam; ewentualne dodanie przeniesienia z jednosci i korekta wartosci w rejestrze al w przypadku przekroczenia wartosci 9
            mov digit_mul, al
            mov carry, ah
        }
        // Zapisywanie sumy dziesi�tek do wynikowego wektora
        result[i] |= (digit_mul << 4);
    }
    return result;
}

BCDNumber BCDNumber::operator*(BCDNumber& other) {
    BCDNumber result; // tworzymy result do kt�rego b�dziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_substraction
    result.digits = bcd_multiplication(digits, other.digits);

    return result;
    
}
// Konstruktor, tworz�cy BCDNumber o warto�ci 0
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
    return str;
}