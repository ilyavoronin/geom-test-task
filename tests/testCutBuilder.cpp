#include "gtest/gtest.h"

#include "CutBuilder.h"

bool check_collisions(std::vector <vec> &p) {
    return vec::check_collision(p[0], p[1], p[2], p[3]) ||
           vec::check_collision(p[0], p[1], p[4], p[5]) ||
           vec::check_collision(p[2], p[3], p[4], p[5]);
}

bool check_collisions_sides(std::vector <vec> &p, vec a, vec b, vec c) {
    return vec::check_collision(p[0], p[1], b, c) ||
           vec::check_collision(p[0], p[1], c, a) ||
           vec::check_collision(p[2], p[3], a, b) ||
           vec::check_collision(p[2], p[3], c, a) ||
           vec::check_collision(p[4], p[5], a, b) ||
           vec::check_collision(p[4], p[5], b, c);
}

vec gen_equal_triangle(vec a, vec b) {
    vec r = (b - a);
    vec n(r.x() * cos(M_PI/3) - r.y() * sin(M_PI/3), r.x() * sin(M_PI / 3) + r.y() * cos(M_PI / 3));
    return a + n;
}

TEST(CutBuilderEqual, testCheckTrue) {
    vec a(-7.45, 1.12);
    vec b(-3.13, -2.14);
    vec c = gen_equal_triangle(a, b);
    long double l = 2;

    bool actual = CutBuilder().check_equal(a, b, c, l);
    bool expected = true;

    ASSERT_EQ(actual, expected);
}

TEST(CutBuilderEqual, testCheckTrueBorderCase) {
    vec a(-7.45, 1.12);
    vec b(-3.13, -2.14);
    vec c = gen_equal_triangle(a, b);
    long double l = 3.12;

    bool actual = CutBuilder().check_equal(a, b, c, l);
    bool expected = true;

    ASSERT_EQ(actual, expected);
}

TEST(CutBuilderEqual, testCheckFalseBorderCase) {
    vec a(-7.45, 1.12);
    vec b(-3.13, -2.14);
    vec c = gen_equal_triangle(a, b);
    long double l = 3.13;

    bool actual = CutBuilder().check_equal(a, b, c, l);
    bool expected = false;

    ASSERT_EQ(actual, expected);
}

TEST(CutBuilderEqual, testFindSolution1) {
    vec a(-7.45, 1.12);
    vec b(-3.13, -2.14);
    vec c = gen_equal_triangle(a, b);
    long double l = 0.1;

    std::vector <vec> p = CutBuilder().find_sol_equal(a, b, c, l);
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderEqual, testFindSolution2) {
    vec a(-7.45, 1.12);
    vec b(-3.13, -2.14);
    vec c = gen_equal_triangle(a, b);
    long double f1 = (b - a).mod();
    long double f2 = (c - b).mod();
    long double f3 = (c - a).mod();
    long double l = 3.12;

    std::vector <vec> p = CutBuilder().find_sol_equal(a, b, c, l);
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}