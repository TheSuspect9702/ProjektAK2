﻿#include "BCDNumber.h"
#include <iostream>
using namespace std;
int main(int argc, char ** argv)
{//                22              15              
    string a = "121399218", b = "32192193712"; // digits[0] to koniec liczby 
    BCDNumber num1(a);
    BCDNumber num2(b);
    BCDNumber sum = num1 + num2;
    BCDNumber substraction = num1 - num2;
    BCDNumber multiplication = num1 * num2;
    cout << num1.toString() << " + " << num2.toString() << " = " << sum.toString() << std::endl;
    cout << num1.toString() << " - " << num2.toString() << " = " << substraction.toString() << std::endl;
    cout << num1.toString() << " * " << num2.toString() << " = " << multiplication.toString() << std::endl;

    return 0;
}