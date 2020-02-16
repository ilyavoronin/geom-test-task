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

long double CutBuilder::metric1(long double dist_ab, long double dist_bc, long double dist_ca,
                                long double mid_dist_ab, long double mid_dist_bc, long double mid_dist_ca) {
    return (2 * mid_dist_ab / dist_ab) * (2 * mid_dist_bc / dist_bc) * (2 * mid_dist_ca / dist_ca);
}

//this function might be slow if ITER is too big
bool CutBuilder::check_any(vec a, vec b, vec c, long double l, std::vector <vec> &points, bool find_any) {
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
    vec point_beg_ca = c + (a - c).norm() * beg_ca;
    vec mid_ab = a + (b - a).norm() * (beg_ab + end_ab) / 2;
    vec mid_bc = b + (c - b).norm() * (beg_bc + end_bc) / 2;
    vec mid_ca = c + (a - c).norm() * (beg_ca + end_ca) / 2;
    vec best_ab = a;
    vec best_bc = b;
    vec best_ca = c;
    bool already_find = false;
    long double best_metric = 1;
    long double cur_metric;
    for (int n1 = 0; n1 < ITER + 1; n1++) {
        for (int n2 = 0; n2 < ITER + 1; n2++) {
            for (int n3 = 0; n3 < ITER + 1; n3++) {
                vec p_ab = point_beg_ab + vec_ab * (step_ab * (long double)n1);
                vec p_bc = point_beg_bc + vec_bc * (step_bc * (long double)n2);
                vec p_ca = point_beg_ca + vec_ca * (step_ca * (long double)n3);
                if (!find_any && already_find) {
                    cur_metric = metric1((end_ab - beg_ab),
                                         (end_bc - beg_bc),
                                         (end_ca - beg_ca),
                                         vec::dist(best_ab, mid_ab),
                                         vec::dist(best_bc, mid_bc),
                                         vec::dist(best_ca, mid_ca) );
                    if (cur_metric > best_metric) {
                        continue;
                    }
                }
                std::vector <vec> cuts = get_cuts(a, b, c, p_ab, p_bc, p_ca, l);
                if (!vec::check_collision(cuts[0], cuts[1], cuts[2], cuts[3]) &&
                    !vec::check_collision(cuts[0], cuts[1], cuts[4], cuts[5]) &&
                    !vec::check_collision(cuts[2], cuts[3], cuts[4], cuts[5])) {
                    if (find_any) {
                        points = {p_ab, p_bc, p_ca};
                        return true;
                    }
                    else {
                        already_find = true;
                        best_ab = p_ab;
                        best_bc = p_bc;
                        best_ca = p_ca;
                        best_metric = cur_metric;
                    }
                }
            }
        }
    }
    if (!find_any) {
        points = {best_ab, best_bc, best_ca};
        return already_find;
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
        if (check_any(a, b, c, mid, points, true)) {
            le = mid;
        }
        else {
            ri = mid;
        }
    }
    check_any(a, b, c, le, points, false);
    points = get_cuts(a, b, c, points[0], points[1], points[2], l);
    return points;
}