
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
