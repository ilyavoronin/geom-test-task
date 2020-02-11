#ifndef GEOM_TEST_TASK_VEC_H
#define GEOM_TEST_TASK_VEC_H

#include <fstream>

class vec {
public:
    explicit vec(double x_ = 0, double y_ = 0) : x_(x_), y_(y_) {}
    vec& operator+=(const vec &ot);
    vec operator+(const vec &ot);
    vec& operator-=(const vec &ot);
    vec operator-(const vec &ot);
    //scalar product
    double operator*(const vec &ot);
    //cross product
    double operator%(const vec &ot);
    friend std::istream& operator>>(std::istream &is, vec &a);
    friend std::ostream& operator<<(std::ostream &os, vec &a);
    double x() { return x_; }
    double y() { return y_; }

    static double dist(vec &a, vec &b);

private:
    double x_, y_;
};


#endif //GEOM_TEST_TASK_VEC_H
