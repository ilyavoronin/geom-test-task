#include "CutBuilder.h"

bool CutBuilder::check_equal(vec a, vec b, vec c, double l) {
    double side = vec::dist(a, b);
    double t = l / sin(PI / 3) + l / tan(PI / 3);
    return t + vec::eps < side;
}


//we want to find 'beautiful' solution
std::vector <vec> CutBuilder::find_sol_equal(vec a, vec b, vec c, double l) {
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

std::vector <vec> CutBuilder::get_cuts(vec a, vec b, vec c, vec p_ab, vec p_bc, vec p_ca, double l) {
    vec ort_ab = (b - a).ortnorm();
    vec ort_bc = (c - b).ortnorm();
    vec ort_ca = (a - c).ortnorm();
    return {p_ab + ort_ab * l, p_ab - ort_ab * l,
            p_bc + ort_bc * l, p_bc - ort_bc * l,
            p_ca + ort_ca * l, p_ca - ort_ca * l
    };
}

//this function might be slow if ITER is too big
bool CutBuilder::check_any(vec a, vec b, vec c, double l, std::vector <vec> &points) {
    vec vec_ab = (b - a).norm();
    vec vec_bc = (c - b).norm();
    vec vec_ca = (a - c).norm();
    double step_ab = ((b - a).mod() - 3 * vec::eps) / ITER;
    double step_bc = ((c - b).mod() - 3 * vec::eps) / ITER;
    double step_ca = ((a - c).mod() - 3 * vec::eps) / ITER;
    for (int n1 = 0; n1 < ITER; n1++) {
        for (int n2 = 0; n2 < ITER; n2++) {
            for (int n3 = 0; n3 < ITER; n3++) {
                vec p_ab = a + vec_ab * (step_ab * (double)n1);
                vec p_bc = b + vec_bc * (step_bc * (double)n2);
                vec p_ca = c + vec_ca * (step_ca * (double)n3);
                points = get_cuts(a, b, c, p_ab, p_bc, p_ca, l);
                if (!vec::check_collision(points[0], points[1], points[2], points[3]) &&
                    !vec::check_collision(points[0], points[1], points[4], points[5]) &&
                    !vec::check_collision(points[2], points[3], points[4], points[5])) {
                    return true;
                }
            }
        }
    }
    return false;
}


//we want to find 'beautiful' solution
std::vector <vec> CutBuilder::find_sol_any(vec a, vec b, vec c, double l) {
    double le = l, ri = std::min((b - a).mod(), std::min((c - b).mod(), (a - c).mod()));
    //le is always suitable as the length of the cut
    //we don't want to do too many iterations of binary search
    std::vector <vec> points;
    for (int i = 0; i < BIN_INTER; i++) {
        double mid = (le + ri) / 2;
        if (check_any(a, b, c, mid, points)) {
            le = mid;
        }
        else {
            ri = mid;
        }
    }
    check_any(a, b, c, le, points);
    return points;
}