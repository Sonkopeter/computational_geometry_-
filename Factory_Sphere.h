#pragma once
#include "Sphere.h"
#include "Factory.h"
#include "Figure.h"
class Factory_Sphere : public Factory {
public:
    Factory_Sphere() = default;
    Figure* Create(double radius, std::vector<double> centre) override {
        return new Sphere(radius, centre);
    }
    Figure* Create(std::vector<double> p1, std::vector<double> p2, std::vector<double> p3, std::vector<double> p4)override {
        p1 = p1;
        p2 = p2;
        p3 = p3;
        p4 = p4;
        return new Sphere();
    }
    Figure* Create(std::vector<double> min, std::vector<double> max) override {
        min = min;
        max = max;
        return new Sphere();
    }
    ~Factory_Sphere() = default;
};
