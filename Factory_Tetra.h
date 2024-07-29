#pragma once
#include "Tetra.h"
#include "Factory.h"
#include "Figure.h"
class Factory_tetra: public Factory {
public:
    Factory_tetra() = default;
    Figure* Create(std::vector<double> p1,std::vector<double> p2,std::vector<double> p3,std::vector<double> p4)override {
        return new Tetrahedron(p1,p2,p3,p4);
    }
    Figure* Create(std::vector<double> min,std::vector<double> max) override {
        min=min;
        max=max;
        return new Tetrahedron();
    }
    Figure* Create(double radius, std::vector<double> centre) override {
        centre=centre;
        radius=radius;
        return new Tetrahedron();
    }
    ~Factory_tetra() = default;
};
