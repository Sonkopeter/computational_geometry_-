#pragma once
#include "Box.h"
#include "Factory.h"
#include "Figure.h"
class Factory_box : public Factory {
public:
    Factory_box() = default;
    Figure* Create(std::vector<double> min, std::vector<double> max) override {
        return new Box(min, max);
    }
    Figure* Create(double radius, std::vector<double> centre) override {
        centre = centre;
        radius = radius;
        return new Box();
    }
    Figure* Create(std::vector<double> p1, std::vector<double> p2, std::vector<double> p3, std::vector<double> p4)override {
        p1 = p1;
        p2 = p2;
        p3 = p3;
        p4 = p4;
        return new Box();
    }
    ~Factory_box() = default;
};
