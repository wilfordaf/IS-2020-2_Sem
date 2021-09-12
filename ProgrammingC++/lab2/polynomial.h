#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <math.h>
#include <algorithm>

class Polynomial{
protected:
    int minDeg;
    int maxDeg;
    int *Pcoefficients;
public:
    Polynomial();
    Polynomial(int, int, int*);
    Polynomial(const Polynomial&);
    ~Polynomial();
    int getMin() const;
    int getMax() const;
    Polynomial& makeCorrect();
    Polynomial& operator= (const Polynomial&);
    bool operator== (const Polynomial&);
    bool operator!= (const Polynomial&);
    Polynomial operator+ (const Polynomial&) const;
    Polynomial& operator+= (const Polynomial&);
    Polynomial operator- (const Polynomial&) const;
    Polynomial operator- () const;
    Polynomial& operator-= (const Polynomial&);
    Polynomial operator* (const Polynomial&) const;
    Polynomial operator* (int) const;
    friend Polynomial operator* (int, const Polynomial&);
    Polynomial& operator*= (const Polynomial&);
    Polynomial& operator*= (int);
    Polynomial operator/ (int) const;
    Polynomial& operator/= (int);
    double get(double) const;
    friend std::ostream& operator<< (std::ostream&, const Polynomial&);
    friend std::istream& operator>> (std::istream&, Polynomial&);
    int& operator[](int);
    int operator[](int) const;
};

#endif // POLYNOMIAL_H
