#ifndef GEOM_TEST_TASK_VEC_H
#define GEOM_TEST_TASK_VEC_H


struct vec {
    vec(double x_, double y_) : x(x_), y(y_) {}
    vec& operator+=(const vec& ot);
    vec operator+(const vec& ot);
    vec& operator-=(const vec& ot);
    vec operator-(const vec& ot);
    //scalar product
    double operator*(const vec& ot);
    //cross product
    double operator%(const vec& ot);
    double x, y;
};


#endif //GEOM_TEST_TASK_VEC_H
