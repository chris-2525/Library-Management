// Final Project Milestone 5
// Date Module
// File	Streamable.cpp
// Version 1.0
// Author	Christine Ang; Student ID#: 121559223
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
// I have done all the coding by myself and only copied the code 
// that my professor provided to complete my workshops and assignments
// 
/////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Streamable.h"
using namespace std;
namespace sdds {
    ostream& operator<<(ostream& ostr, const Streamable& str) {

        if (str) {
            str.write(ostr);
        }

        return ostr;
    }
    istream& operator>>(istream& istr, Streamable& str) {

        str.read(istr);

        return istr;

    }
}