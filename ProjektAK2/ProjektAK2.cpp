#include "BCDNumber.h"
#include <iostream>
#include <conio.h>
using namespace std;
int main(int argc, char ** argv)
{//                22              15              
    string a, b,c,d; // digits[0] to koniec liczby 
    char opt = 1;
    BCDNumber num1;
    BCDNumber num2;
    BCDNumber sum;
    BCDNumber substraction;
    BCDNumber multiplication;
    BCDNumber division;

    while (opt != '0') {
        cout << "\nProsze podac pierwsza liczbe: ";
        cin >> a;
        cout << "\nProsze podac druga liczbe: ";
        cin >> b;
        num1 = BCDNumber(a);
        num2 = BCDNumber(b);
        sum = num1 + num2;
        substraction = num1 - num2;
        multiplication = num1 * num2;
        division = num1 / num2;
        cout << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << endl;
        cout << num1.toString() << " - " << num2.toString() << " = " << substraction.toString() << endl;
        cout << num1.toString() << " * " << num2.toString() << " = " << multiplication.toString() << endl;
        cout << num1.toString() << " / " << num2.toString() << " = " << division.toString() << endl;
        cout << "Jesli chcesz zakonczyc obliczenia kliknij 0 w przeciwnym razie kliknij 1: ";
        opt = _getche();
    }
    return 0;
}