#pragma once
#include "Figure.h"
#include "Functions.h"

class Box :public Figure
{   private:
    std::vector<double> min;
    std::vector<double> max;
public:
    Box()=default;
    Box(std::vector<double> v_min,std::vector<double> v_max);
    bool ray_intersection(std::vector<double> cam,std::vector<double> dir,double* result);
    double light(std::vector<double> cam, std::vector<double> dir, double dist, std::vector<double> light);
    double distance(std::vector<double> cam);
    ~Box()=default;
};
