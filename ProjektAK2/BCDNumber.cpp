#include "BCDNumber.h"
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include <vector>
#include <algorithm>

using namespace std;
//                  licznik (liczba dzielona)   mianownik (to przez co dzielimy)
bool isGreater(vector<unsigned char> vector1, vector<unsigned char> vector2) {
    if (vector2.size() > vector1.size())
        return true;
    for (int i = vector1.size()-1; i >=0; i--) {
        if (vector1[i] < vector2[i])
            return true;    //zwraca prawde kiedy mianownik jest wiekszy od licznika tez do przerobienia
        else if (vector1[i] > vector2[i])
            return false;
    }
    return false; 
}

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
        // Wywo�anie instrukcji AAA, aby skorygowa� sum�
        __asm {
            mov al, digit1
            add al, digit2
            aaa; korygujemy cyfry jednosci(-6 jesli wi�ksze od 9 i przeniesienie = 1)
            mov digit_sum, al
            mov carry, ah
        }
        digit1 = 0;
        digit2 = 0;
        // Zapisywanie sumy cyfr do wynikowego wektora  
        result[i] |= digit_sum;

        // Wyci�ganie cyfr dziesi�tek z wektor�w i dodawanie ich
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
        // Wywo�anie instrukcji AAA, aby skorygowa� sum�
        __asm {
            mov al, digit1
            add al, digit2
            aaa; ewentualne dodanie przeniesienia z jednosci i korekta wartosci w rejestrze al w przypadku przekroczenia wartosci 9
            mov digit_sum, al
            mov carry, ah
        }
        digit1 = 0;
        digit2 = 0;
        // Zapisywanie sumy dziesi�tek do wynikowego wektora
        result[i] |= (digit_sum << 4);
        if (i == maxSize - 1 && carry) {
            result.push_back(1);
        }
    }
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
        if (digit1 <= digit2 && carry) {
            digit1 += 9;
            if (digit1 > 15) {
                digit1 -= 4;
                digit2 -= 4;
            }
        }
        else if (digit1 > digit2 && carry) {
            carry--;
            digit1--;
        }
        bonuscarry = carry;
        __asm {
            mov al, digit1
            sub al, digit2
            aas; korygujemy cyfry jednosci(-6 jesli wi�ksze od 9 i przeniesienie = 1)
            mov digit_sub, al
            mov carry, ah
        }
        if (carry != 0 || bonuscarry)
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
            if (digit1 > 15) {
                digit1 -= 4;
                digit2 -= 4;
            }
            bonuscarry = carry;
            carry = 0;
        }
        if (digit1 > digit2 && carry) {
            digit1--;
            bonuscarry = 0;
            carry--;
        }
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
        for (int j = 0; j < vector1.size(); j++) {
            // Wyci�ganie cyfr z wektor�w i dodawanie ich
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
        for (int k = x; k > 0; k--)
            result1.push_back(0);
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

vector<unsigned char> bcd_division(vector<unsigned char>& vector1, vector<unsigned char> vector2, unsigned long long &comma, unsigned long long comma1) {
    BCDNumber a;
    BCDNumber b;
    unsigned char digit1;
    unsigned char digit2;
    unsigned char divider;
    vector<unsigned char> result(vector1.size(),0);
    vector<unsigned char> temp;
    vector<unsigned char> temp1;
    int x = 0;
    int precision = comma1/2;
    for (int i = vector1.size()-1; i >= 0; i--) {
        temp.insert(temp.begin(), vector1[i] & 0xF0); //do przerobienia
        while (1) {
            while (temp.size() != vector2.size() && vector2.size() < temp.size()) {
                vector2.push_back(0);
            }
            temp1 = temp;
            for (int j = 0; j < temp.size(); j++) {
                if (j + 1 < temp.size()) {
                    temp[j] = temp[j] >> 4;
                    temp[j] |= (temp[j + 1] & 0x0F )<< 4;
                }
                else 
                    temp[j] = temp[j] >> 4;
            }
            if (isGreater(temp, vector2)) {
                for (int j = temp.size()-1; j >= 0; j--) {
                    temp[j] = temp[j] << 4;
                    if (j != 0) {
                        temp[j] |= (temp[j - 1] & 0xF0) >> 4;
                    }
                }
                temp[0] |= vector1[i] & 0x0F;
                break;
            }
            else {
                result[x] += 16;
                a.digits = temp;
                b.digits = vector2;
                a.digits = (a - b).digits;
                temp = a.digits;
            }
            for (int j = temp.size() - 1; j >= 0; j--) {
                temp[j] = temp[j] << 4;
                if (j != 0) {
                    temp[j] |= (temp[j - 1] & 0xF0) >> 4;
                }
            }
        }
        while (1) {
            if (isGreater(temp, vector2)) {
                x++;
                break;
            }
            else {
                result[x] += 1;
                a.digits = temp;
                b.digits = vector2;
                a.digits = (a - b).digits;
                temp = a.digits;
            }
        }
    }

    while (precision > 0) {
        temp.insert(temp.begin(), 0); //do przerobienia
        result.push_back(0);
        while (1) {
            while (temp.size() != vector2.size() && vector2.size() < temp.size()) {
                vector2.push_back(0);
            }
            temp1 = temp;
            for (int j = 0; j < temp.size(); j++) {
                if (j + 1 < temp.size()) {
                    temp[j] = temp[j] >> 4;
                    temp[j] |= (temp[j + 1] & 0x0F) << 4;
                }
                else
                    temp[j] = temp[j] >> 4;
            }
            if (isGreater(temp, vector2)) {
                for (int j = temp.size() - 1; j >= 0; j--) {
                    temp[j] = temp[j] << 4;
                    if (j != 0) {
                        temp[j] |= (temp[j - 1] & 0xF0) >> 4;
                    }
                }
                break;
            }
            else {
                result[x] += 16;
                a.digits = temp;
                b.digits = vector2;
                a.digits = (a - b).digits;
                temp = a.digits;
            }
            for (int j = temp.size() - 1; j >= 0; j--) {
                temp[j] = temp[j] << 4;
                if (j != 0) {
                    temp[j] |= (temp[j - 1] & 0xF0) >> 4;
                }
            }
        }
        while (1) {
            if (isGreater(temp, vector2)) {
                x++;
                break;
            }
            else {
                result[x] += 1;
                a.digits = temp;
                b.digits = vector2;
                a.digits = (a - b).digits;
                temp = a.digits;
            }
        }
        comma += 2;
        precision--;
    }
  
    return result;
}

BCDNumber BCDNumber::operator+(BCDNumber& other) {
    BCDNumber result; // tworzymy result do kt�rego b�dziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_addiction
    int i = 0;
    result.comma = max(comma, other.comma);
    if (comma > other.comma) {
        while (comma != other.comma) {
            other.digits.insert(other.digits.begin(), 0);
            other.comma += 2;
        }
    }
    else if (comma < other.comma) {
        while (comma != other.comma) {
            digits.insert(digits.begin(), 0);
            comma += 2;
        }
    }
    if (sign == other.sign)
    {
        result.digits = bcd_addition(digits, other.digits);
        result.sign = sign;
    }
    else if (sign) {
        if (digits.size() - comma > other.digits.size() - other.comma) {
            result.digits = bcd_substraction(digits, other.digits); //sprawdzic ktora liczba jest wieksza i ustawic odpowiedni znak ewentualnie odpowiednia kolejnosc odejmowania
            result.sign = sign;
        }
        else if (digits.size() - comma == other.digits.size() - other.comma) {
            i = digits.size() -1;
            while (digits[i] == other.digits[i]) {
                if (i == 0)
                    break;
                i--;
            }
            if (i == 0 && other.digits[i] == digits[i]) {
                result.digits = bcd_substraction(digits, other.digits);
                result.sign = false;
            }
            else if (digits[i] > other.digits[i]) {
                result.digits = bcd_substraction(digits, other.digits);
                result.sign = true;
            }
            else {
                result.digits = bcd_substraction(other.digits, digits);
                result.sign = false;
            }
        }
        else {
            result.digits = bcd_substraction(other.digits, digits);
            result.sign = false;
        }
    }
    else {
        if (digits.size() - comma > other.digits.size() - other.comma) {
            result.digits = bcd_substraction(digits, other.digits); //sprawdzic ktora liczba jest wieksza i ustawic odpowiedni znak ewentualnie odpowiednia kolejnosc odejmowania
            result.sign = false;
        }
        else if (digits.size() - comma == other.digits.size() - other.comma) {
            i = digits.size() - 1;
            while (digits[i] == other.digits[i]) {
                if (i == 0)
                    break;
                i--;
            }
            if (i == 0 && other.digits[i] == digits[i]) {
                result.digits = bcd_substraction(digits, other.digits);
                result.sign = false;
            }
            else if (digits[i] > other.digits[i]) {
                result.digits = bcd_substraction(digits, other.digits);
                result.sign = false;
            }
            else {
                result.digits = bcd_substraction(other.digits, digits);
                result.sign = true;
            }
        }
        else {
            result.digits = bcd_substraction(other.digits, digits);
            result.sign = true;
        }
    }
    return result;
}

BCDNumber BCDNumber::operator-(BCDNumber& other) {
    BCDNumber result; // tworzymy result do kt�rego b�dziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_substraction
    int i = 0;
    result.comma = max(comma, other.comma);
    if (comma > other.comma) {
        while (comma != other.comma) {
            other.digits.insert(other.digits.begin(), 0);
            other.comma += 2;
        }
    }
    else if (comma < other.comma) {
        while (comma != other.comma) {
            digits.insert(digits.begin(), 0);
            comma += 2;
        }
    }
    if (sign) {
        if (other.sign) {
            if (digits.size() - comma == other.digits.size() - other.comma) {
                i = digits.size() - 1;
                while (digits[i] == other.digits[i]) {
                    if (i == 0)
                        break;
                    i--;
                }
                if (digits[i] == other.digits[i]) {
                    result.digits = bcd_substraction(digits, other.digits);
                    result.sign = false;
                }
                else if (digits[i] > other.digits[i]) {
                    result.digits = bcd_substraction(digits, other.digits);
                    result.sign = true;
                }
                else {
                    result.digits = bcd_substraction(other.digits, digits);
                    result.sign = false;
                }
            }
            else if (digits.size() - comma > other.digits.size() - other.comma) {
                result.digits = bcd_substraction(digits, other.digits);
                result.sign = true;
            }
            else {
                result.digits = bcd_substraction(other.digits, digits);
                result.sign = false;
            }
        }
        else {
            result.digits = bcd_addition(digits, other.digits);
            result.sign = true;
        }
    }
    else {
        if (other.sign) {
            result.digits = bcd_addition(digits, other.digits);
            result.sign = false;
        }
        else {
            if (digits.size() - comma == other.digits.size() - other.comma) {
                i = digits.size() - 1;
                while (digits[i] == other.digits[i]) {
                    if (i == 0)
                        break;
                    i--;
                }
                if (digits[i] == other.digits[i]) {
                    result.digits = bcd_substraction(digits, other.digits);
                    result.sign = false;
                }
                else if (digits[i] > other.digits[i]) {
                    result.digits = bcd_substraction(digits, other.digits);
                    result.sign = false;
                }
                else {
                    result.digits = bcd_substraction(other.digits, digits);
                    result.sign = true;
                }
            }
            else if (digits.size() - comma > other.digits.size() - other.comma) {
                result.digits = bcd_substraction(digits, other.digits);
                result.sign = false;
            }
            else {
                result.digits = bcd_substraction(other.digits,digits);
                result.sign = true;
            }
        }
    }
    
    return result;
}

BCDNumber BCDNumber::operator*(BCDNumber& other) {
    BCDNumber result; // tworzymy result do kt�rego b�dziemy "doklejac" kolejne cyfry wyniku w petli for w bcd_substraction
    while (digits[0] == 0 && comma >= 2) {
        digits.erase(digits.begin());
        comma -= 2;
    }
    
    while (other.digits[0] == 0 && other.comma >= 2) {
        other.digits.erase(other.digits.begin());
        other.comma -= 2;
    }
    if ((digits[0] == 0 && digits.size() == 1) || (other.digits[0] == 0 && other.digits.size() == 1)) {
        result.digits.push_back(0);
        result.sign = false;
        result.comma = 0;
    }
    else {
        result.digits = bcd_multiplication(digits, other.digits);
            if (sign == other.sign)
                result.sign = false;
            else
                result.sign = true;
            result.comma = comma + other.comma;
    }
    return result;
    
}

BCDNumber BCDNumber::operator/(BCDNumber& other) {
    BCDNumber result; // dorobic dopasowanie liczb przed dzieleniem (zrobic przesuniecia comma i dopisywanie 0 ewentualne)
    result.comma = 0;
    unsigned long long j = 0;
    unsigned long long k = 0;
    if (other.digits[0] == 0 && other.digits.size() == 1)
        result.digits.push_back(15);
    else {
        while (digits[0] == 0 && comma >= 2) {
            digits.erase(digits.begin());
            comma -= 2;
        }
        while (other.digits[0] == 0 && other.comma >= 2) {
            other.digits.erase(other.digits.begin());
            other.comma -= 2;
        }
        if (comma > other.comma) {
            k = other.comma;
            while (comma != k) {
                other.digits.insert(other.digits.begin(), 0);
                k += 2;
            }
        }
        else if (comma < other.comma) {
            j = comma;
            while (j != other.comma) {
                digits.insert(digits.begin(), 0);
                j += 2;
            }
        }


        result.digits = bcd_division(digits, other.digits, result.comma, comma);
        while (j > comma) {
            digits.erase(digits.begin());
            j -= 2;
        }
        while (k > other.comma) {
            other.digits.erase(other.digits.begin());
            k -= 2;
        }
        reverse(result.digits.begin(), result.digits.end());
        if (sign == other.sign)
            result.sign = false;
        else
            result.sign = true;
    }
    return result;
}

BCDNumber::BCDNumber() {
}

BCDNumber::BCDNumber(string str) {
    int x;
    int y;
    int z;
    unsigned char move;
    comma = 0;
    if (str.substr(0, 1) == "-") {
        sign = true;
        str.erase(0, 1);
    }
    else
        sign = false;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str.substr(i, 1) == ",") {
            str.erase(i, 1);
            comma = str.size() - i;
            break;
        }
    }
    if (comma % 2 == 1) {
        str.insert(str.end(), '0');
        comma++;
    }
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
    comma = 0;
    sign = false;
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
        if (str.length() - comma > 1)
            str.erase(0, 1);
        else
            break;
    }
    if (comma != 0)
        str.insert(str.size() - comma, ",");
    if (sign)
        str.insert(str.begin(), '-');
    for(int i = comma; i>0;i--){
        if (str[str.size() - 1] != '0')
            break;
        str.erase(str.size()-1, 1);
        if (i == 1)
            str.erase(str.size() - 1, 1);
    }
    return str;
}