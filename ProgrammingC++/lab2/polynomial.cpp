#include "polynomial.h"

Polynomial::Polynomial(){
    minDeg = 0;
    maxDeg = 0;
    Pcoefficients = new int[1]{0};
}

Polynomial::Polynomial(int minDeg_, int maxDeg_, int* Pcoefficients_){
    minDeg = minDeg_;
    maxDeg = maxDeg_;
    Pcoefficients = new int[maxDeg - minDeg + 1];
    std::copy(Pcoefficients_, Pcoefficients_ + maxDeg - minDeg + 1, Pcoefficients);
}

Polynomial::Polynomial(const Polynomial &other){
    minDeg = other.minDeg;
    maxDeg = other.maxDeg;
    Pcoefficients = new int[maxDeg - minDeg + 1];
    std::copy(other.Pcoefficients, other.Pcoefficients + other.maxDeg - other.minDeg + 1, Pcoefficients);
}

Polynomial::~Polynomial(){
    delete[] Pcoefficients;
}

int Polynomial::getMin() const{
    return minDeg;
}

int Polynomial::getMax() const{
    return maxDeg;
}

Polynomial& Polynomial::makeCorrect(){
    int cnt = 0;
    int minimum = minDeg;
    int maximum = maxDeg;
    bool didSTH = false;
    while ((Pcoefficients[minimum - minDeg] == 0) || (Pcoefficients[maximum - minimum + cnt] == 0)){
        if (minimum == maximum){
            break;
        }
        if(Pcoefficients[minimum - minDeg] == 0){
            minimum++;
            cnt++;
        }
        if(Pcoefficients[maximum - minimum + cnt] == 0){
            maximum--;
        }
        didSTH = true;
    }
    //fixed do nothing if its already ok
    if (didSTH){
        int* newCoefficients = new int[maximum - minimum + 1];
        std::copy(Pcoefficients + minimum - minDeg, Pcoefficients + maximum - minimum + cnt + 1, newCoefficients);
        *this = Polynomial(minimum, maximum, newCoefficients);
        delete[] newCoefficients;
    }
    return *this;
}

Polynomial& Polynomial::operator= (const Polynomial& other){
    if (this != &other){
         minDeg = other.minDeg;
         maxDeg = other.maxDeg;
         delete[] Pcoefficients;
         Pcoefficients = new int[maxDeg - minDeg + 1];
         std::copy(other.Pcoefficients, other.Pcoefficients + other.maxDeg - other.minDeg + 1, Pcoefficients);
    }
    return *this;
}

bool Polynomial::operator== (const Polynomial& other){
    Polynomial p1 = *this;
    Polynomial p2 = other;
    p1.makeCorrect();
    p2.makeCorrect();
    if (p1.minDeg != p2.minDeg || p1.maxDeg != p2.maxDeg){
        return false;
    }
    for (int i = 0; i < p1.maxDeg - p1.minDeg + 1; i++){
        if (p1.Pcoefficients[i] != p2.Pcoefficients[i]){
            return false;
        }
    }
    return true;
}

bool Polynomial::operator!= (const Polynomial& other){
    return !(*this == other);
}

//fixed + from +=
Polynomial Polynomial::operator+ (const Polynomial& other) const{
    Polynomial temp = *this;
    temp += other;
    return temp;
}

Polynomial& Polynomial::operator+= (const Polynomial& other){
    if (minDeg <= other.minDeg && maxDeg >= other.maxDeg){
        for (int i = 0; i < other.maxDeg - other.minDeg + 1; i++){
            Pcoefficients[i - minDeg + other.minDeg] += other.Pcoefficients[i];
        }
        return *this;
    }
    else{
        int minimum = std::min(minDeg, other.minDeg);
        int maximum = std::max(maxDeg, other.maxDeg);
        int *coefficients = new int[maximum - minimum + 1];
        std::fill(coefficients, coefficients + maximum - minimum + 1, 0);
        for (int i = minDeg; i < maxDeg + 1; i++){
            coefficients[i - minimum]+= Pcoefficients[i - minDeg];
        }
        for (int i = other.minDeg; i < other.maxDeg + 1; i++){
            coefficients[i - minimum] += other.Pcoefficients[i - other.minDeg];
        }
        Polynomial temp = Polynomial(minimum, maximum, coefficients);
        delete[] coefficients;
        *this = temp;
        return *this;
    }
}

Polynomial Polynomial::operator- (const Polynomial& other) const{
    Polynomial temp;
    temp -= *this;
    temp -= other;
    return temp;
}

Polynomial& Polynomial::operator-= (const Polynomial& other){
    *this += -other;
    return *this;
}

Polynomial Polynomial::operator- () const{
    Polynomial tempO = *this;
    tempO *= -1;
    return tempO;
}

Polynomial Polynomial::operator* (const Polynomial& other) const{
    Polynomial temp = *this;
    temp *= other;
    return temp;
}

Polynomial Polynomial::operator* (int n) const{
    Polynomial temp = *this;
    temp *= n;
    return temp;
}

Polynomial operator*(int n, const Polynomial& p){
    Polynomial temp = p * n;
    return temp;
}

Polynomial& Polynomial::operator*= (int n){
    //fixed for_each
    std::for_each(Pcoefficients, Pcoefficients + maxDeg - minDeg + 1, [&n](int &number){number *= n;});
    return *this;
}

Polynomial& Polynomial::operator*= (const Polynomial& other){
    if ((maxDeg == 0 && minDeg == 0 && Pcoefficients[0] == 0)||(other.maxDeg == 0 && other.minDeg == 0 && other.Pcoefficients[0] == 0)){
        Polynomial temp;
        *this = temp;
        return *this;
    }
    int *coefficients = new int[maxDeg + other.maxDeg - minDeg - other.minDeg + 1];
    std::fill(coefficients, coefficients + maxDeg + other.maxDeg - minDeg - other.minDeg + 1, 0);
    for (int i = 0; i < maxDeg - minDeg + 1; i++){
        for (int j = 0; j < other.maxDeg - other.minDeg + 1; j++){
            coefficients[i + j] += Pcoefficients[i]*other.Pcoefficients[j];
        }
    }
    Polynomial temp = Polynomial(minDeg + other.minDeg, maxDeg + other.maxDeg, coefficients);
    delete[] coefficients;
    *this = temp;
    return *this;
}

Polynomial Polynomial::operator/ (int n) const{
    Polynomial temp = *this;
    temp /= n;
    return temp;
}

Polynomial& Polynomial::operator/= (int n){
    for (int i = 0; i < maxDeg - minDeg + 1; i++){
        Pcoefficients[i] /= n;
    }
    return *this;
}

double Polynomial::get(double n) const{
    double reccur = pow(n, minDeg);
    double answer = 0;
    for (int i = minDeg; i < maxDeg + 1; i++){
        answer += Pcoefficients[i-minDeg] * reccur;
        reccur *= n;
    }
    return answer;
}

std::ostream& operator<< (std::ostream& out, const Polynomial& p){
    for(int i = p.maxDeg - p.minDeg; i > -1; i--){
        if(p.Pcoefficients[i] > 0 && i != p.maxDeg - p.minDeg){
            out << "+";
        }
        if(p.Pcoefficients[i] == 1){
            if(p.minDeg + i == 1){
                out << "x";
            }
            else if(p.minDeg + i != 0){
                out << "x^" << p.minDeg + i;
            }
            else{
                out << "1";
            }
        }
        else if(p.Pcoefficients[i] == -1){
            out << "-";
            if(p.minDeg + i == 1){
                out << "x";
            }
            else if(p.minDeg + i != 0){
                out << "x^" << p.minDeg + i;
            }
            else{
                out << "1";
            }
        }
        else if(p.Pcoefficients[i] == 0){
            if(p.minDeg == 0 && p.maxDeg == 0){
                out << "0";
            }
        }
        else{
            out << p.Pcoefficients[i];
            if(p.minDeg + i == 1){
                out << "x";
            }
            else if(p.minDeg + i != 0){
                out << "x^" << p.minDeg + i;
            }
        }
    }
    return out;
};

std::istream& operator>> (std::istream& in, Polynomial& p){
    int minimum;
    int maximum;
    in >> minimum >> maximum;
    int* coefficients = new int[maximum - minimum + 1];
    for (int i = 0; i < maximum - minimum + 1; i++){
        in >> coefficients[i];
    }
    p = Polynomial(minimum, maximum, coefficients);
    delete[] coefficients;
    return in;
}

int& Polynomial::operator[](int index){
    if (index >= minDeg && index <= maxDeg){
        return Pcoefficients[index - minDeg];
    }
    if (index > maxDeg){
        int* coefficients = new int[index - minDeg + 1];
        std::copy(Pcoefficients, Pcoefficients + maxDeg - minDeg + 1, coefficients);
        std::fill(coefficients + maxDeg - minDeg + 1, coefficients + index - minDeg + 1, 0);
        *this = Polynomial(minDeg, index, coefficients);
        delete[] coefficients;
        return Pcoefficients[index - minDeg];
    }
    int* coefficients = new int[maxDeg - index + 1];
    std::copy(Pcoefficients, Pcoefficients + maxDeg - minDeg + 1, coefficients - index);
    std::fill(coefficients, coefficients - index + 1, 0);
    *this = Polynomial(index, maxDeg, coefficients);
    delete[] coefficients;
    return Pcoefficients[index - minDeg];
}

int Polynomial::operator[](int index) const{
    if (index >= minDeg && index <= maxDeg){
        return Pcoefficients[index - minDeg];
    }
    return 0;
}
