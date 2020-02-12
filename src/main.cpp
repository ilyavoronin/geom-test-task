#include <iostream>
#include <cmath>
#include <vector>

#include "vec.h"

const double PI = M_PI;

bool check(vec a, vec b, vec c, double l) {
    double side = vec::dist(a, b);
    double t = l / sin(PI / 3) + l / tan(PI / 3);
    return t + vec::eps < side;
}

std::vector <vec> find_sol(vec a, vec b, vec c, double l) {
    double le = l / tan(PI / 3);
    double ri = (b - a).mod() / 2;
    vec p1, p2, p3, p4, p5, p6;
    while (ri - le > vec::eps) {
        p1 = (a + (b - a).norm() * ri) + (a - b).ortnorm() * l;
        p2 = (a + (b - a).norm() * ri) - (a - b).ortnorm() * l;
        p3 = (b + (c - b).norm() * ri) + (c - b).ortnorm() * l;
        p4 = (b + (c - b).norm() * ri) - (c - b).ortnorm() * l;
        p5 = (c + (a - c).norm() * ri) + (a - c).ortnorm() * l;
        p6 = (c + (a - c).norm() * ri) - (a - c).ortnorm() * l;
        if (!vec::check_collision(p1, p2, p3, p4)) {
            return {p1, p2, p3, p4, p5, p6};
        }
        ri = (le + ri) / 2;
    }
    return {p1, p2, p3, p4, p5, p6};
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
    std::vector <vec> ans = find_sol(a, b, c, l);
    std::cout << ans[0] << ", " << ans[1] << "\n";
    std::cout << ans[2] << " : " << ans[3] << "\n";
    std::cout << ans[4] << " : " << ans[5] << "\n";
    return 0;
}