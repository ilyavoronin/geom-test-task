#include "vec.h"

vec& vec::operator+=(const vec& ot) {
    x += ot.x;
    y += ot.y;
    return *this;
}

vec vec::operator+(const vec& ot) {
    return vec(x + ot.x, y + ot.y);
}

vec& vec::operator-=(const vec& ot) {
    x -= ot.x;
    y -= ot.y;
    return *this;
}

vec vec::operator-(const vec& ot) {
    return vec(x - ot.x, y - ot.y);
}

double vec::operator*(const vec& ot) {
    return x * ot.x + y * ot.y;
}

double vec::operator%(const vec& ot) {
    return x * ot.y - y * ot.x;
}