#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <omp.h>
#include <map>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stddef.h>
#include <limits>

class Figure {
protected:
public:
    Figure() = default;
    virtual bool ray_intersection(std::vector<double> cam, std::vector<double> dir, double* result) = 0;
    virtual double light(std::vector<double> cam, std::vector<double> dir, double result, std::vector<double> light) = 0;
    virtual double distance(std::vector<double> cam)=0;
    virtual ~Figure() = default;
};

