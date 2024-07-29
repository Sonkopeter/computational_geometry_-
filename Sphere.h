#pragma once
#include "Figure.h"
#include "Functions.h"
class Sphere : public Figure {
private:
    double radius;
    std::vector<double> centre;
public:
    Sphere() = default;
    Sphere(double r, std::vector<double> v);
    bool ray_intersection(std::vector<double> cam, std::vector<double> dir, double* r);
    double light(std::vector<double> cam, std::vector<double> dir, double d, std::vector<double> light);
    double distance(std::vector<double> cam);
    ~Sphere()=default;
};

