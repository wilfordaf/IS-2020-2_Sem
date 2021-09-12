#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include <math.h>
class Point{
private:
    int x;
    int y;

public:
    Point();
    Point(int, int);
    Point(const Point&);
    Point& operator= (const Point& other);
    int getX() const;
    int getY() const;
    void print_dot();
};

double LenBetweenPoints(Point, Point);

class PolygonalChain{
private:
    int AmountOfPoints;
    Point *points;

public:
    PolygonalChain(int, Point*);
    PolygonalChain(const PolygonalChain&);
    PolygonalChain& operator= (const PolygonalChain&);
    virtual ~PolygonalChain();
    int getN() const;
    Point* getPointer() const;
    Point getPoint(int number) const;
    virtual double perimeter() const;

};

class ClosedPolygonalChain: public PolygonalChain{
private:
    int AmountOfPoints;
    Point *points;

public:
    ClosedPolygonalChain(int, Point*);
    ClosedPolygonalChain(const ClosedPolygonalChain&);
    ClosedPolygonalChain& operator=(const ClosedPolygonalChain& other);
    //fixed use default
    ~ClosedPolygonalChain();
    double perimeter() const override;
};

class Polygon: public ClosedPolygonalChain{
private:
    int AmountOfPoints;
    Point *points;

public:
    Polygon(int, Point*);
    Polygon(const Polygon&);
    Polygon& operator=(const Polygon& other);
    ~Polygon();
    virtual double area() const;
};

class Triangle: public Polygon{
private:
    int AmountOfPoints;
    Point *points;

public:
    Triangle(int, Point*);
    Triangle(const Triangle&);
    Triangle& operator=(const Triangle& other);

    ~Triangle();
    bool hasRightAngle() const;
};

class Trapezoid: public Polygon{
private:
    int AmountOfPoints;
    Point *points;

public:
    Trapezoid(int, Point*);
    Trapezoid(const Trapezoid&);
    Trapezoid& operator=(const Trapezoid& other);
    ~Trapezoid();
    double height() const;

};

class RegularPolygon: public Polygon{
private:
    int AmountOfPoints;
    Point *points;

public:
    RegularPolygon(int, Point*);
    RegularPolygon(const RegularPolygon&);
    //fixed it looks like it doesnt work, mb i am wrong but i need proofs
    RegularPolygon& operator=(const RegularPolygon& other);
    double perimeter() const override;
    double area() const override;
    ~RegularPolygon();
};

#endif // GEOMETRY_H
