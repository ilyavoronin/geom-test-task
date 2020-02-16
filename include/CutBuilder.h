#ifndef GEOM_TEST_TASK_CUTBUILDER_H
#define GEOM_TEST_TASK_CUTBUILDER_H

#include <cmath>
#include <vector>

#include "vec.h"

class CutBuilder {
public:
    bool check_equal(vec a, vec b, vec c, long double l);
    std::vector <vec> find_sol_equal(vec a, vec b, vec c, long double l);
    std::vector <vec> get_cuts(vec a, vec b, vec c, vec p_ab, vec p_bc, vec p_ca, long double l);
    bool check_any(vec a, vec b, vec c, long double l, std::vector <vec> &points);
    std::vector <vec> find_sol_any(vec a, vec b, vec c, long double l);

private:
    const long double PI = M_PI;
    const int ITER = 100;
    const int BIN_INTER = 5;
};


#endif //GEOM_TEST_TASK_CUTBUILDER_H
