#include "vec.h"

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
    os << a.x_ << " " << a.y_;
    return os;
}