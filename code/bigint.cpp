// $Id: bigint.cpp,v 1.76 2016-06-14 16:34:24-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"

bigint::bigint(long that) :
    uvalue(that), is_negative(that < 0) {
    DEBUGF('~', this << " -> " << uvalue)
}

bigint::bigint(const ubigint& uvalue, bool is_negative) :
    uvalue(uvalue), is_negative(is_negative) {

}

bigint::bigint(const string& that)
{
    is_negative = that.size() > 0 and that[0] == '_';
    //cout << "uvalue = ubigint" << endl;
    uvalue = ubigint(that.substr(is_negative ? 1 : 0));
}

bigint bigint::operator+() const
{
    return *this;
}

bigint bigint::operator-() const
{
    return { uvalue, not is_negative };
}

bigint bigint::operator+(const bigint& that) const
{
    bool sign;
    ubigint result;
    bigint answer;

    if (is_negative == that.is_negative) {
        sign = that.is_negative;
        if (*this < that) {
            result = that.uvalue + uvalue;
        }
        else {
            result = uvalue + that.uvalue;
        }
    }
    else {
        if (*this < that) {
            //cout << "reached big op + <" << endl;
            sign = that.is_negative;
            result = that.uvalue - uvalue;
        }
        else {
            //cout << "reached big op + else" << endl;
            sign = is_negative;
            result = uvalue - that.uvalue;
        }
    }
    answer = bigint(result, sign);
    //cout << "answer: " << answer << endl;
    return answer;
}

bigint bigint::operator-(const bigint& that) const
{
    bool sign;
    ubigint result;

    if (is_negative == that.is_negative) {
        //cout << "in bigint - op" << endl;
        if (*this < that) {
            //cout << "in uvalue < that" << endl;
            sign = !(that.is_negative);
            result = that.uvalue - uvalue;
        }
        else {
            sign = is_negative;
            result = uvalue - that.uvalue;
        }
    }
    else {
        if (*this < that) {
            //cout << "in uvalue < that" << endl;
            sign = that.is_negative;
            result = that.uvalue + uvalue;
        }
        else {
            sign = false;
            result = uvalue - that.uvalue;
        }
    }
    return { result, sign };
}

bigint bigint::operator*(const bigint& that) const
{
    bigint result = uvalue * that.uvalue;
    return result;
}

bigint bigint::operator/(const bigint& that) const
{
    bigint result = uvalue / that.uvalue;
    return result;
}

bigint bigint::operator%(const bigint& that) const
{
    bigint result = uvalue % that.uvalue;
    return result;
}

bool bigint::operator==(const bigint& that) const
{
    return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator<(const bigint& that) const
{
    //cout << "bigint op < reached" << endl;
    if (is_negative != that.is_negative)
        return is_negative;
    return is_negative ? uvalue > that.uvalue
        : uvalue < that.uvalue;
}

ostream& operator<<(ostream& out, const bigint& that)
{
    if (that.is_negative) {
        return out << "-" << that.uvalue;
    }
    else {
        return out << that.uvalue;
    }
}
