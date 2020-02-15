#ifndef GEOM_TEST_TASK_VEC_H
#define GEOM_TEST_TASK_VEC_H

#include <fstream>

class vec {
public:
    constexpr static long double eps = 1e-9;

    explicit vec(long double x_ = 0, long double y_ = 0) : x_(x_), y_(y_) {}
    vec& operator+=(const vec &ot);
    vec operator+(const vec &ot);
    vec& operator-=(const vec &ot);
    vec operator-(const vec &ot);
    vec operator*(long double a);
    vec operator/(long double a);
    //scalar product
    long double operator*(const vec &ot);
    //cross product
    long double operator%(const vec &ot);
    friend std::istream& operator>>(std::istream &is, vec &a);
    friend std::ostream& operator<<(std::ostream &os, vec &a);
    long double x() { return x_; }
    long double y() { return y_; }
    vec ortnorm();
    vec norm();
    long double mod();

    static long double dist(vec &a, vec &b);
    static bool check_collision(vec a1, vec a2, vec b1, vec b2);
    static long double get_angle(vec a, vec b);
private:
    long double x_, y_;
};


#endif //GEOM_TEST_TASK_VEC_H
