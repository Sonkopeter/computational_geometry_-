#pragma once
#include "Figure.h"
double scalar_product(std::vector<double> v1, std::vector<double> v2);
void vector_product(std::vector<double>* v, std::vector<double> v1, std::vector<double> v2);
double length(std::vector<double> v);
std::vector<unsigned char> ray_trace(std::vector<double> cam, std::vector<double> dir, std::vector<Figure*> Figures, std::vector<double> light, std::vector<std::vector<unsigned char>> color);