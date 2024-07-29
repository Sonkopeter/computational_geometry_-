#pragma once
#include "Figure.h"
class Factory {
public:
	Factory() = default;
    virtual Figure* Create(double radius, std::vector<double> centre) = 0;
    virtual Figure* Create(std::vector<double> min, std::vector<double> max) = 0;
    virtual Figure* Create(std::vector<double> p1, std::vector<double> p2, std::vector<double> p3, std::vector<double> p4) = 0;
    virtual ~Factory()=default;

};
