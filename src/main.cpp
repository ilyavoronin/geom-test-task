#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

#include "vec.h"
#include "CutBuilder.h"

int main() {
    std::cout << std::setprecision(11);
    std::cout << std::fixed;
    vec a, b, c;
    long double l;
    std::cin >> a >> b >> c;
    std::cin >> l;
    l /= 2;
    long double side_size = (b - a).mod();
    CutBuilder cutBuilder;
    if (fabs((b - c).mod() - side_size) < 0.1 && fabs((c - a).mod() - side_size) < 0.1) {
        //this branch is for triangles with equal sides
        if (!cutBuilder.check_equal(a, b, c, l)) {
            std::cout << "Impossible\n";
            return 0;
        }
        std::vector<vec> ans = cutBuilder.find_sol_equal(a, b, c, l);
        std::cout << ans[0] << " : " << ans[1] << "\n";
        std::cout << ans[2] << " : " << ans[3] << "\n";
        std::cout << ans[4] << " : " << ans[5] << "\n";
    }
    else {
        std::vector <vec> ans;
        if (!cutBuilder.check_any(a, b, c, l, ans, true)) {
            std::cout << "Impossible\n";
            return 0;
        }
        ans = cutBuilder.find_sol_any(a, b, c, l);
        std::cout << ans[0] << " : " << ans[1] << "\n";
        std::cout << ans[2] << " : " << ans[3] << "\n";
        std::cout << ans[4] << " : " << ans[5] << "\n";
    }
    return 0;
}