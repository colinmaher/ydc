// $Id: ubigint.cpp,v 1.14 2016-06-23 17:21:26-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include <algorithm>
using namespace std;


#include "ubigint.h"
#include "debug.h"

ubigint::ubigint(unsigned long that) {
    // DEBUGF('~', this << " -> " << uvalue)
}

ubigint::ubigint(const string &that)
{
    DEBUGF('~', "that = \"" << that << "\"");
    // reverse(that.begin(), that.end());
    // int n = that.length();

    unsigned char num;
    for (char digit : that)
    {
        if (not isdigit(digit))
        {
            throw invalid_argument("ubigint::ubigint(" + that + ")");
        }
        num = digit;
        ubig_value.push_back(num);
        // uvalue = uvalue * 10 + digit - '0';
    }

    reverse(ubig_value.begin(), ubig_value.end());

    // for (auto i = ubigint::ubig_value.begin(); i != ubigint::ubig_value.end(); ++i)
    //   cout << *i << ' ';
    // cout << endl;
}


ubigint ubigint::operator+(const ubigint &that) const
{
    ubigint answer;
    int quo = 0;
    int rem;
    int sum = 0;
    unsigned int i;

    for (i = 0; i < that.ubig_value.size(); ++i) {
        sum = (ubig_value[i] - 48) + (that.ubig_value[i] - 48);
        cout << "sum: " << sum << endl;
        if (quo > 0) {
            sum += quo;
        }

        quo = sum / 10;
        rem = sum % 10;
        cout << "rem: " << rem << endl;
        cout << "quo: " << (char)(quo+48) << endl;
        answer.ubig_value.push_back((unsigned char)rem+48);
    }
    cout << "made it here" << endl;
    cout << "i: " << i << endl;
    cout << "size:" << ubig_value.size() << endl;
    for (unsigned int j = i; j < ubig_value.size(); ++j) {
        cout << "here" << endl;
        sum = (ubig_value[j] - 48) + quo;
        quo = sum / 10;
        rem = sum % 10;
        answer.ubig_value.push_back((unsigned char)rem+48);
    }
    cout << "made it here2" << endl;
    if (quo > 0) {
        cout << "here2" << endl;
        cout << "quo: " << quo << endl;
        answer.ubig_value.push_back((unsigned char)quo+48);
    }
    cout << "made it here3" << endl;
    for (auto n = answer.ubig_value.rbegin(); n <= answer.ubig_value.rend(); ++n) {
        cout << "answer digits:" << *n << endl;
    }
    cout << "answer: " << answer << endl;
    return answer;
}

ubigint ubigint::operator-(const ubigint &that) const
{
    if (*this < that)
        throw domain_error("ubigint::operator-(a<b)");
    // return ubigint(uvalue - that.uvalue);
}

ubigint ubigint::operator*(const ubigint &that) const
{
    // return ubigint(uvalue * that.uvalue);
}

void ubigint::multiply_by_2()
{
    // uvalue *= 2;
}

void ubigint::divide_by_2()
{
    // uvalue /= 2;
}

struct quo_rem
{
    ubigint quotient;
    ubigint remainder;
};
quo_rem udivide(const ubigint &dividend, ubigint divisor)
{
    // Note: divisor is modified so pass by value (copy).
    ubigint zero{ 0 };
    if (divisor == zero)
        throw domain_error("udivide by zero");
    ubigint power_of_2{ 1 };
    ubigint quotient{ 0 };
    ubigint remainder{ dividend }; // left operand, dividend
    while (divisor < remainder)
    {
        divisor.multiply_by_2();
        power_of_2.multiply_by_2();
    }
    while (power_of_2 > zero)
    {
        if (divisor <= remainder)
        {
            remainder = remainder - divisor;
            quotient = quotient + power_of_2;
        }
        divisor.divide_by_2();
        power_of_2.divide_by_2();
    }
    return { .quotient = quotient,.remainder = remainder };
}

ubigint ubigint::operator/(const ubigint &that) const
{
    return udivide(*this, that).quotient;
}

ubigint ubigint::operator%(const ubigint &that) const
{
    return udivide(*this, that).remainder;
}

bool ubigint::operator==(const ubigint &that) const
{
    // return uvalue == that.uvalue;
}

bool ubigint::operator<(const ubigint &that) const
{

    // return uvalue < that.uvalue;
}

ostream &operator<<(ostream &out, const ubigint &that)
{
    string str = "";
    
    for (auto n = that.ubig_value.rbegin(); n <= that.ubig_value.rend(); ++n) {
        str += *n;
    }

    return out << str;
}
