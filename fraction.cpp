#include "fraction.h"

static int32_t gcd(int32_t a,int32_t b) {
    int32_t
            r;

    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

//  Fraction(int32_t _num=0,int32_t _den=1);
Fraction::Fraction(int32_t _num,int32_t _den) {

    if (_den < 0) {
        _num = -_num;
        _den = -_den;
    }

    int32_t
            g = gcd(_num,_den);

    num = _num / g;
    den = _den / g;
}

//  ~Fraction();
Fraction::~Fraction() { }

//  Fraction operator+(Fraction rhs);
Fraction Fraction::operator+(Fraction rhs) {
    int32_t
            n,d;

    n = num * rhs.den + den * rhs.num;
    d = den * rhs.den;

    return Fraction(n,d);
}

//  Fraction operator-(Fraction rhs);
Fraction Fraction::operator-(Fraction rhs) {
    int32_t
            n,d;

    n = num * rhs.den - den * rhs.num;
    d = den * rhs.den;

    return Fraction(n,d);
}

//  Fraction operator*(Fraction rhs);
Fraction Fraction::operator*(Fraction rhs) {
    int32_t
            n,d;

    n = num * rhs.num;
    d = den * rhs.den;

    return Fraction(n,d);
}

//  Fraction operator/(Fraction rhs);
Fraction Fraction::operator/(Fraction rhs) {
    int32_t
            n,d;

    n = num * rhs.den;
    d = den * rhs.num;

    return Fraction(n,d);
}

//  Fraction operator=(Fraction rhs);
Fraction Fraction::operator=(Fraction rhs) {

    num = rhs.num;
    den = rhs.den;

    return rhs;
}

//  bool operator==(Fraction rhs);
bool Fraction::operator==(Fraction rhs) {

    return num == rhs.num && den == rhs.den;
}

//  bool operator!=(Fraction rhs);
bool Fraction::operator!=(Fraction rhs) {

    return num != rhs.num || den != rhs.den;
}

//  bool operator<=(Fraction rhs);
bool Fraction::operator<=(Fraction rhs) {

    return num * rhs.den <= den * rhs.num;
}

//  bool operator>=(Fraction rhs);
bool Fraction::operator>=(Fraction rhs) {

    return num * rhs.den >= den * rhs.num;
}

//  bool operator<(Fraction rhs);
bool Fraction::operator<(Fraction rhs) {

    return num * rhs.den < den * rhs.num;
}

//  bool operator>(Fraction rhs);
bool Fraction::operator>(Fraction rhs) {

    return num * rhs.den > den * rhs.num;
}

// std::istream &operator>>(std::istream &,Fraction &);
std::istream &operator>>(std::istream &is,Fraction &f) {
    int32_t
            n,d;
    char
            slash;

    is >> n >> slash >> d;

    f = Fraction(n,d);

    return is;
}

// std::ostream &operator<<(std::ostream &,Fraction);
std::ostream &operator<<(std::ostream &os,Fraction f) {

    os << f.getNum() << " / " << f.getDen();

    return os;
}


