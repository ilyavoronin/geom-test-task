#include "CutBuilder.h"

bool CutBuilder::check_equal(vec a, vec b, vec c, long double l) {
    long double side = vec::dist(a, b);
    long double t = l / sin(PI / 3) + l / tan(PI / 3);
    return t + vec::eps < side;
}


//we want to find 'beautiful' solution
std::vector <vec> CutBuilder::find_sol_equal(vec a, vec b, vec c, long double l) {
    long double maxl = (b - a).mod() / (1 / sin(PI/3) + 1 / tan(PI/3));
    long double beg = maxl / sin(PI / 3) + vec::eps;
    vec p1 = (a + (b - a).norm() * beg) + (a - b).ortnorm() * l;
    vec p2 = (a + (b - a).norm() * beg) - (a - b).ortnorm() * l;
    vec p3 = (b + (c - b).norm() * beg) + (c - b).ortnorm() * l;
    vec p4 = (b + (c - b).norm() * beg) - (c - b).ortnorm() * l;
    vec p5 = (c + (a - c).norm() * beg) + (a - c).ortnorm() * l;
    vec p6 = (c + (a - c).norm() * beg) - (a - c).ortnorm() * l;
    if (!vec::check_collision(p1, p2, p3, p4) &&
        !vec::check_collision(p3, p4, p5, p6) &&
        !vec::check_collision(p5, p6, p1, p2)) {
        return {p1, p2, p3, p4, p5, p6};
    }
}

std::vector <vec> CutBuilder::get_cuts(vec a, vec b, vec c, vec p_ab, vec p_bc, vec p_ca, long double l) {
    vec ort_ab = (b - a).ortnorm();
    vec ort_bc = (c - b).ortnorm();
    vec ort_ca = (a - c).ortnorm();
    return {p_ab + ort_ab * l, p_ab - ort_ab * l,
            p_bc + ort_bc * l, p_bc - ort_bc * l,
            p_ca + ort_ca * l, p_ca - ort_ca * l
    };
}

//this function might be slow if ITER is too big
bool CutBuilder::check_any(vec a, vec b, vec c, long double l, std::vector <vec> &points) {
    vec vec_ab = (b - a).norm();
    vec vec_bc = (c - b).norm();
    vec vec_ca = (a - c).norm();
    long double angle_abc = vec::get_angle((a - b), (c - b));
    long double angle_bca = vec::get_angle((b - c), (a - c));
    long double angle_cab = vec::get_angle((c - a), (b - a));
    long double beg_ab, end_ab, beg_bc, end_bc, beg_ca, end_ca;

    if (angle_cab < PI / 2) {
        beg_ab = l / tan(angle_cab) + vec::eps;
        end_ca = (c - a).mod() - beg_ab - vec::eps;
    }
    else {
        beg_ab = 0 + vec::eps;
        end_ca = (c - a).mod() - vec::eps;
    }

    if (angle_abc < PI / 2) {
        beg_bc = l / tan(angle_abc) + vec::eps;
        end_ab = (b - a).mod() - beg_bc - vec::eps;
    }
    else {
        beg_bc = 0 + vec::eps;
        end_ab = (b - a).mod();
    }

    if (angle_bca < PI / 2) {
        beg_ca = l / tan(angle_bca) + vec::eps;
        end_bc = (c - b).mod() - beg_ca - vec::eps;
    }
    else {
        beg_ca = 0 + vec::eps;
        end_bc = (c - b).mod() - vec::eps;
    }
    if (beg_ab > end_ab || beg_bc > end_bc || beg_ca > end_ca) {
        return false;
    }
    long double step_ab = (end_ab - beg_ab) / ITER;
    long double step_bc = (end_bc - beg_bc) / ITER;
    long double step_ca = (end_ca - beg_ca) / ITER;
    vec point_beg_ab = a + (b - a).norm() * beg_ab;
    vec point_beg_bc = b + (c - b).norm() * beg_bc;
    vec point_beg_ca = c + (c - a).norm() * beg_ca;
    for (int n1 = 0; n1 < ITER + 1; n1++) {
        for (int n2 = 0; n2 < ITER + 1; n2++) {
            for (int n3 = 0; n3 < ITER + 1; n3++) {
                vec p_ab = point_beg_ab + vec_ab * (step_ab * (long double)n1);
                vec p_bc = point_beg_bc + vec_bc * (step_bc * (long double)n2);
                vec p_ca = point_beg_ca + vec_ca * (step_ca * (long double)n3);
                std::vector <vec> cuts = get_cuts(a, b, c, p_ab, p_bc, p_ca, l);
                if (!vec::check_collision(cuts[0], cuts[1], cuts[2], cuts[3]) &&
                    !vec::check_collision(cuts[0], cuts[1], cuts[4], cuts[5]) &&
                    !vec::check_collision(cuts[2], cuts[3], cuts[4], cuts[5])) {
                    points = {p_ab, p_bc, p_ca};
                    return true;
                }
            }
        }
    }
    return false;
}


//we want to find 'beautiful' solution
std::vector <vec> CutBuilder::find_sol_any(vec a, vec b, vec c, long double l) {
    long double le = l, ri = std::min((b - a).mod(), std::min((c - b).mod(), (a - c).mod()));
    //le is always suitable as the length of the cut
    //we don't want to do too many iterations of binary search
    std::vector <vec> points;
    for (int i = 0; i < BIN_INTER; i++) {
        long double mid = (le + ri) / 2;
        if (check_any(a, b, c, mid, points)) {
            le = mid;
        }
        else {
            ri = mid;
        }
    }
    check_any(a, b, c, le, points);
    points = get_cuts(a, b, c, points[0], points[1], points[2], l);
    return points;
}