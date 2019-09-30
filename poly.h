//----------------------------------------------------------------------------
//poly.h file
//A simple polynomial class 

#pragma once
#include <iostream>

using namespace std;

//----------------------------------------------------------------------------
//ADT Polynomial: This is a abstract data type using arrays to represents
//one polynomial. The subscript of the array is the exponent while the 
//element is the coefficient value.
//
//Implementation and assumptions:
//  -- Implemented as an array
//  -- Array is increased in size when needed and only to the needed ammount
//  -- Handles accessing non-existent term (returns 0)
//  -- Does not handle data type errors (entering char instead of int)
//----------------------------------------------------------------------------

class Poly {

    //outputs the polynomial as " +5x^3 -2x^2 +4" format with no new line
    friend ostream& operator<<(ostream&, const Poly&);

    //allows the user to enter the coefficient and exponent to change the
    //coefficient of the given exponent. This is done continuesly in a
    //loop with no error checking until the user enters "-1 -1"
    friend istream& operator>>(istream&, Poly&);

public:
    //constructor paramaters are coefficient and exponent if power is 
    //negative it will be set to 0
    Poly(const int = 0, int = 0); //constructor 
    Poly(const Poly&); //copy constructor
    ~Poly(); //deconstructor

    //operators
    Poly& operator=(const Poly&); //assignment operator 

    bool operator==(const Poly&) const; //equality operator
    bool operator!=(const Poly&) const; //inequality operator

    Poly operator+(const Poly&) const; //addition operator
    Poly operator-(const Poly&) const; //subtraction operator
    Poly operator*(const Poly&) const; //multiplication operator

    Poly& operator+=(const Poly&); //+= operator
    Poly& operator-=(const Poly&); //-= operator
    Poly& operator*=(const Poly&); //*= operator

    //returns coefficient of a given power, returns 0 if no power is located
    int getCoeff(const int) const; 

    //setCoeff allows the user to enter the coefficient and power to set the
    //coefficient of the given exponent. Returns false if negative power
    bool setCoeff(const int, int);

private:
    int size;
    int * arrayPtr = nullptr;
    void copy(const Poly&); //used to copy for constructor and = op
    void resize(const int); //used to resize the array when needed
};