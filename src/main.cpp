#include <iostream>
#include <cmath>

#include "vec.h"

const double PI = M_PI;
const double eps = 1e-9;

bool check(vec a, vec b, vec c, double l) {
    double side = vec::dist(a, b);
    double t = l / sin(PI / 3) + l / tan(PI / 3);
    return t + eps < side;
}


int main() {
    vec a, b, c;
    double l;
    std::cin >> a >> b >> c;
    std::cin >> l;
    if (!check(a, b, c, l)) {
        std::cout << "Impossible\n";
        return 0;
    }
    return 0;
}
