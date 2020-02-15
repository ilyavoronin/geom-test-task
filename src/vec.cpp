#include "vec.h"

#include <cmath>

vec& vec::operator+=(const vec& ot) {
    x_ += ot.x_;
    y_ += ot.y_;
    return *this;
}

vec vec::operator+(const vec& ot) {
    return vec(x_ + ot.x_, y_ + ot.y_);
}

vec& vec::operator-=(const vec& ot) {
    x_ -= ot.x_;
    y_ -= ot.y_;
    return *this;
}

vec vec::operator-(const vec &ot) {
    return vec(x_ - ot.x_, y_ - ot.y_);
}

vec vec::operator*(double a) {
    return vec(x_ * a, y_ * a);
}

vec vec::operator/(double a) {
    return vec(x_ / a, y_ / a);
}

double vec::operator*(const vec& ot) {
    return x_ * ot.x_ + y_ * ot.y_;
}

double vec::operator%(const vec& ot) {
    return x_ * ot.y_ - y_ * ot.x_;
}

std::istream& operator>>(std::istream &is, vec &a) {
    is >> a.x_ >> a.y_;
    return is;
}

std::ostream& operator<<(std::ostream& os, vec &a) {
    os << "(" << a.x_ << ", " << a.y_ << ")";
    return os;
}

double vec::dist(vec &a, vec &b) {
    return sqrt((a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_));
}

bool vec::check_collision(vec a1, vec a2, vec b1, vec b2) {
    if (fabs((a2 - a1) % (b2 - b1)) < eps) {
        //they are on the same line
        double x1 = std::min(a1.x_, a2.x_);
        double x2 = std::max(a1.x_, a2.x_);
        double x3 = std::min(b1.x_, b2.x_);
        double x4 = std::max(b1.x_, b2.x_);

        //check if projection intersects
        return (x1 <= x3 && x3 <= x2) || (x1 <= x4 && x4 <= x2);
    }
    else {
        //check if b1 and b2 on different sides from vector (a1, a2)
        bool c1 = ((a2 - a1) % (b1 - a1)) * ((a2 - a1) % (b2 - a1)) < eps;
        //check if a1 and a2 on different sides from vector (b1, b2)
        bool c2 = ((b2 - b1) % (a1 - b1)) * ((b2 - b1) % (a2 - b1)) < eps;
        return c1 && c2;
    }
}

double vec::mod() {
    return sqrt(x_ * x_ + y_ * y_);
}

vec vec::norm() {
    return vec(x_, y_) / this->mod();
}

vec vec::ortnorm() {
    vec ort(-y_, x_);
    return ort / ort.mod();
}

double vec::get_angle(vec a, vec b) {
    double ang = atan2(a * b, a % b);
    if (ang < 0) {
        ang += M_PI;
    }
    return ang;
}