// poly.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "poly.h"
#include <iostream>
#include <string>

using namespace std;

//----------------------------------------------------------------------------
//Operator << 
//outputs the polynomial as " +5x^3 -2x^2 +4" format with no new line
ostream& operator<<(ostream& output, const Poly& p) {

    bool zeroTerms = true; //used to check if all values are zero

    for (int i = p.size - 1; i >= 0; i--) {
        
        if (p.arrayPtr[i] < 0 && p.arrayPtr[i] != 0) { //add negative sign
            if (i == 1) { //checking for no exponent
                output << " " << p.arrayPtr[i] << "x";
            }
            else if (i == 0) {
                output << " " << p.arrayPtr[i];
            }
            else {
                output << " " << p.arrayPtr[i] << "x^" << i;
            }
            zeroTerms = false;
        }
        else if(p.arrayPtr[i] != 0) { //add positive sign
            if (i == 1) { //checking for no exponent
                output << " +" << p.arrayPtr[i] << "x";
            }
            else if (i == 0) {
                output << " +" << p.arrayPtr[i];
            }
            else {
                output << " +" << p.arrayPtr[i] << "x^" << i;
            }
            zeroTerms = false;
        } 
    }

    if (zeroTerms) {
        output << " 0";
    }
    
    return output;
}


//----------------------------------------------------------------------------
//>>operator
//allows the user to enter the coefficient and exponent to change the
//coefficient of the given exponent. This is done continuesly in a
//loop only refusing to insert into a negative exponent 
//until the user enters "-1 -1" No error checking is done other than 
//negative exponent
istream& operator>>(istream& input, Poly& r) {
    int c;
    int e;
    input >> c;
    input >> e;
    while (c != -1 && e != -1) {
        if (e >= r.size) {
            r.resize(e + 1);
        }
        if (e >= 0) {
            r.arrayPtr[e] = c;
        }
        input >> c;
        input >> e;
    }
    return input;
}

//----------------------------------------------------------------------------
//Poly
//Parameters are coefficient and exponent respectively. 
// Can take all integers for coefficient and only positive for exponent.
// all non-positive exponents will become 0 and non integers
// are not handled. 
Poly::Poly(const int c, int e) {
    if (e < 0) { //check illegal exponent
        e = 0;
    }

    size = e + 1;
  
    
    arrayPtr = new int[size];
   
    for (int i = 0; i < size; i++) { //initialize array
        arrayPtr[i] = 0;
    }
    arrayPtr[e] = c; //set cpefficient

}

//----------------------------------------------------------------------------
//Poly copy constructor
//Uses private copy function to deep copy the poly
Poly::Poly(const Poly& toCopy) {
    copy(toCopy);
}

//----------------------------------------------------------------------------
//~Poly
//Deconstructor
Poly::~Poly() {
    delete[]arrayPtr;
    arrayPtr = nullptr;
    size = 0;
}

//----------------------------------------------------------------------------
//= operator 
Poly& Poly::operator=(const Poly& r) {
    if (&r != this) {
        delete[] arrayPtr;
        copy(r);
    }
    return *this;
}


//----------------------------------------------------------------------------
//== operator
bool Poly::operator==(const Poly& r) const {
    int i = 0;
    while (i < r.size && i < size) { //checking array contents
        if (arrayPtr[i] != r.arrayPtr[i]) {
            return false;
        }
        i++;
    }

    for (i; i < r.size; i++) { //checking if larger contains values
        if (r.arrayPtr[i] != 0) {
            return false;
        }
    }
   
    for (i; i < size; i++) { //checking if larger contains values
        if (arrayPtr[i] != 0) {
            return false;
        }
    }

    return true;
}

//----------------------------------------------------------------------------
//!= operator
bool Poly::operator!=(const Poly& r) const {
    int i = 0;
    while (i < r.size && i < size) { //checking array contents
        if (arrayPtr[i] != r.arrayPtr[i]) {
            return true;
        }
        i++;
    }

    for (i; i < r.size; i++) { //checking if larger contains values
        if (r.arrayPtr[i] != 0) {
            return true;
        }
    }

    for (i; i < size; i++) { //checking if larger contains values
        if (arrayPtr[i] != 0) {
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------------
//operator+
//adds the polynomial and returns it
Poly Poly::operator+(const Poly& r) const {

    int largerSize = (r.size >= size) ? r.size : size;
    Poly temp(0, largerSize);
    
    int i = 0;
    while (i < r.size && i < size) { //adding arrays to shortest length
        temp.arrayPtr[i] = r.arrayPtr[i] + arrayPtr[i];
        i++;
    }

    for (i; i < r.size; i++) { //adding largest length
        temp.arrayPtr[i] += r.arrayPtr[i];
    }

    for (i; i < size; i++) { //adding largest length
        temp.arrayPtr[i] += arrayPtr[i];
    }

    return temp;
    
}

//----------------------------------------------------------------------------
//operator-
//adds the polynomial and returns it
Poly Poly::operator-(const Poly& r) const {

    int largerSize = (r.size >= size) ? r.size : size;
    Poly temp(0, largerSize);

    int i = 0;
    while (i < r.size && i < size) { //adding arrays to shortest length
        temp.arrayPtr[i] = arrayPtr[i] - r.arrayPtr[i];
        i++;
    }

    for (i; i < r.size; i++) { //subtracting largest length right of op
        temp.arrayPtr[i] -= r.arrayPtr[i];
    }

    for (i; i < size; i++) { //adding largest length left of op
        temp.arrayPtr[i] += arrayPtr[i];
    }

    return temp;

}

//----------------------------------------------------------------------------
//operator* 
Poly Poly::operator*(const Poly& r) const{
    int newSize = size + r.size;
    Poly temp(0, newSize);

    for (int i = 0; i < r.size; i++) {
        for (int j = 0; j < size; j++) {
            temp.arrayPtr[i + j] += r.arrayPtr[i] * arrayPtr[j];
        }
    }

    return temp;
}

//----------------------------------------------------------------------------
//operator+=
Poly& Poly::operator+=(const Poly& r) {
    return (*this = *this + r);
}

//----------------------------------------------------------------------------
//operator-=
Poly& Poly::operator-=(const Poly& r) {
    return (*this = *this - r);
}

//----------------------------------------------------------------------------
//operator*=
Poly& Poly::operator*=(const Poly& r) {
    return (*this = *this * r);
}

//----------------------------------------------------------------------------
//getCoeff
//returns the coefficient of the given power and returns 0 if not found
int Poly::getCoeff(const int c) const {
    if (c < 0 || c >= size) { //invalid entry
        return 0;
    }
    else {
        return arrayPtr[c];
    }
}

//----------------------------------------------------------------------------
//setCoeff
//sets the coefficient to the given power. If a negative power is given then
//false will be returned. 
bool Poly::setCoeff(const int c, int e) {
    if (e < 0) {
        return false;
    }
    else if (e >= size) {
        resize(e + 1);
    }
    arrayPtr[e] = c;
    return true;
}

//----------------------------------------------------------------------------
//Resize
//Private function used to resize and initialize the poly array
void Poly::resize(const int s) {
    int* temp = new int[s];
    int i = 0;
    for (i; i < size; i++) {
        temp[i] = arrayPtr[i];
    }

    for (i; i < s; i++) {
        temp[i] = 0;
    }

    size = s;
    delete[] arrayPtr;
    arrayPtr = temp;
    temp = nullptr;
}

//----------------------------------------------------------------------------
//Copy
//private deep copy function
void Poly::copy(const Poly& toCopy) {
    size = toCopy.size;
    arrayPtr = new int[size];
    for (int i = 0; i < size; i++) {
        arrayPtr[i] = toCopy.arrayPtr[i];
    }
}

//----------------------------------------------------------------------------



