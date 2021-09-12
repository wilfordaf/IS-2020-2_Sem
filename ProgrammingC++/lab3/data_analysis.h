#ifndef DATA_ANALYSIS_H
#define DATA_ANALYSIS_H
#include "pugixml-1.11\src\pugixml.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <math.h>

const double DEG_to_KM = 56.76476;

class Point{
private:
    double x;
    double y;

public:
    Point();
    Point(double, double);
    double getX() const;
    double getY() const;
};

class Station
{
private:
    std::string type_of_vehicle;
    std::vector<std::string> streets;
    std::vector<std::string> routes;
    Point coordinates;

public:
    Station(std::vector<std::string>&);
    int getSizeStr() const;
    int getSizeRte() const;
    Point getCoord() const;
    double distBetweenSt(const Station&) const;
    std::string getStreet(int) const;
    std::string getRoute(int) const;
    std::string getVehicle() const;
};

class Solution_of_lab
{
private:
    const char* name_of_file;
public:
    Solution_of_lab(const char*);
    std::vector<Station> parseToStations() const;
    std::vector<std::map<std::string, std::vector<Station>>> parseToRoutes(std::vector<Station>&) const;
    void task1_solution(std::vector<std::map<std::string, std::vector<Station>>>&) const;
    void task2_solution(std::vector<std::map<std::string, std::vector<Station>>>&) const;
    void task3_solution(std::vector<Station>&) const;

};

double lenOfRoute(const std::vector<Station>&);

#endif // DATA_ANALYSIS_H
