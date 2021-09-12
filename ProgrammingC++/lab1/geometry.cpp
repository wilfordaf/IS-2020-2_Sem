#include "geometry.h"
#include <iostream>
#define PI 3.14159265359

double LenBetweenPoints(Point A, Point B){
    return sqrt(pow(A.getX() - B.getX(), 2) + pow(A.getY() - B.getY(), 2));
}

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(int x_, int y_){
    x = x_;
    y = y_;
};

Point &Point::operator= (const Point &other){
    if (this != &other){
        x = other.getX();
        y = other.getY();
    }
    return *this;
};

Point::Point(const Point &other){
    x = other.getX();
    y = other.getY();
};

int Point::getX() const{
    return x;
}

int Point::getY() const{
    return y;
}

void Point::print_dot(){
    std::cout << "x = " << x << " y = " << y;
}

PolygonalChain::PolygonalChain(int AmountOfPoints_, Point *points_){
    AmountOfPoints = AmountOfPoints_;
    points = new Point[AmountOfPoints];
    std::copy(points_, points_ + AmountOfPoints_, points);
};

PolygonalChain::PolygonalChain(const PolygonalChain &other){
    AmountOfPoints = other.getN();
    points = new Point[AmountOfPoints];
    std::copy(other.getPointer(), other.getPointer() + other.getN(), points);
};

PolygonalChain &PolygonalChain::operator= (const PolygonalChain &other){
    if (this != &other){
        AmountOfPoints = other.getN();
        delete []points;
        points = new Point[AmountOfPoints];
        std::copy(other.getPointer(), other.getPointer() + other.getN(), points);
    }
    return *this;
};

PolygonalChain::~PolygonalChain(){
    delete[] points;
};

int PolygonalChain::getN() const{
    return AmountOfPoints;
}

Point PolygonalChain::getPoint(int number) const{
    return points[number];
}
Point* PolygonalChain::getPointer() const{
    return points;
}
double PolygonalChain::perimeter() const{
    double perimeter_ = 0;
    for(int i = 0; i < getN()-1; i++){
        perimeter_ += LenBetweenPoints(getPoint(i), getPoint(i+1));;
    }
    return perimeter_;
}

ClosedPolygonalChain &ClosedPolygonalChain::operator= (const ClosedPolygonalChain& other) = default;
ClosedPolygonalChain::ClosedPolygonalChain(int AmountOfPoints_, Point *points_): PolygonalChain(AmountOfPoints_, points_){};
ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain &other): PolygonalChain(other){};
ClosedPolygonalChain::~ClosedPolygonalChain() {};



double ClosedPolygonalChain::perimeter() const{
    double perimeter_ = PolygonalChain::perimeter();
    perimeter_ += LenBetweenPoints(getPoint(0), getPoint(getN()-1));
    return perimeter_;
}

Polygon::Polygon(int AmountOfPoints_, Point *points_): ClosedPolygonalChain(AmountOfPoints_, points_){};
Polygon::Polygon(const Polygon &other): ClosedPolygonalChain(other){};
Polygon::~Polygon() {};
Polygon &Polygon::operator= (const Polygon &other) = default;

double Polygon::area() const{
    int area = 0;
    for(int i = 0; i < getN() - 1; i++){
        area += getPoint(i).getX() * getPoint(i + 1).getY();
        area -= getPoint(i + 1).getX() * getPoint(i).getY();
    }
    return 0.5 * abs(area);
}


Triangle::Triangle(int AmountOfPoints_, Point *points_): Polygon(AmountOfPoints_, points_){};
Triangle::Triangle(const Triangle &other): Polygon(other){};
Triangle::~Triangle() {};
Triangle &Triangle::operator= (const Triangle &other) = default;

bool Triangle::hasRightAngle() const{
    Point vectAB(getPoint(0).getX() - getPoint(1).getX(), getPoint(0).getY() - getPoint(1).getY());
    Point vectBC(getPoint(1).getX() - getPoint(2).getX(), getPoint(1).getY() - getPoint(2).getY());
    Point vectAC(getPoint(0).getX() - getPoint(2).getX(), getPoint(0).getY() - getPoint(2).getY());

    double alpha = vectAB.getX() * vectBC.getX() + vectAB.getY() * vectBC.getY();
    double beta = vectBC.getX() * vectAC.getX() + vectBC.getY() * vectAC.getY();
    double gamma = vectAB.getX() * vectAC.getX() + vectAB.getY() * vectAC.getY();

    return (alpha == 0) || (beta == 0) || (gamma == 0);
}

Trapezoid::Trapezoid(int AmountOfPoints_, Point *points_): Polygon(AmountOfPoints_, points_){};
Trapezoid::Trapezoid(const Trapezoid &other): Polygon(other){};
Trapezoid::~Trapezoid() {};
Trapezoid &Trapezoid::operator= (const Trapezoid &other) = default;

double Trapezoid::height() const{
    return 2 * area() / (LenBetweenPoints(getPoint(1), getPoint(2)) + LenBetweenPoints(getPoint(0), getPoint(3)));
}

RegularPolygon::RegularPolygon(int AmountOfPoints_, Point *points_): Polygon(AmountOfPoints_, points_){};
RegularPolygon::RegularPolygon(const RegularPolygon &other): Polygon(other){};
RegularPolygon::~RegularPolygon() {};
RegularPolygon &RegularPolygon::operator= (const RegularPolygon &other) = default;

double RegularPolygon::perimeter() const{
    return getN() * LenBetweenPoints(getPoint(0), getPoint(1));
}

double RegularPolygon::area() const{
    return getN() * pow(LenBetweenPoints(getPoint(0), getPoint(1)), 2) / (4 * tan(PI / getN()));
}
