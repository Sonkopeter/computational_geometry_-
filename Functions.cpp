#include "Functions.h"
double scalar_product(std::vector<double> v1, std::vector<double> v2)
{
    double result = (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
    return result;
}

void vector_product(std::vector<double>* v, std::vector<double> v1, std::vector<double> v2)
{
    (*v)[0] = v1[1] * v2[2] - v1[2] * v2[1];
    (*v)[1] = -(v1[0] * v2[2] - v1[2] * v2[0]);
    (*v)[2] = v1[0] * v2[1] - v1[1] * v2[0];

}
double length(std::vector<double> v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
}
std::vector<unsigned char> ray_trace(std::vector<double> cam, std::vector<double> dir, std::vector<Figure*> Figures, std::vector<double> light, std::vector<std::vector<unsigned char>> color) {
    double nearest = std::numeric_limits<double>::max();
    double result = 0; bool intersect = 0;

    for (size_t i = 0; i < Figures.size(); ++i) {
        if (Figures[i]->ray_intersection(cam, dir, &result) == 1) {
            intersect = 1;
            if (result < nearest) {
                nearest = result;
            }
        }
    }

    if (intersect == 1) {
        for (size_t i = 0; i < Figures.size(); ++i) {
            if (Figures[i]->ray_intersection(cam, dir, &result) == 1) {
                if (std::fabs(result - nearest) < std::numeric_limits<double>::epsilon()) {
                    double model_fong = Figures[i]->light(cam, dir, result, light);
                    std::vector<unsigned char> col(3);
                    for (size_t j = 0; j < col.size(); j++) {
                        col[j] = color[i][j] * model_fong;
                    }
                    return col;
                }
            }
        }
    }
    if (intersect == 0) {
        return { 255,255,255 };
    }

    return { 255,255,255 };
}
