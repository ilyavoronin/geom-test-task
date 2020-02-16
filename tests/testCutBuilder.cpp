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

bool check_size(std::vector <vec> &p, double l) {
    return (fabs(vec::dist(p[0], p[1]) - 2 * l) < 0.1 &&
            fabs(vec::dist(p[2], p[3]) - 2 * l) < 0.1 &&
            fabs(vec::dist(p[4], p[5]) - 2 * l) < 0.1);
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
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderEqual, testFindSolution2) {
    vec a(-7.45, 1.12);
    vec b(-3.13, -2.14);
    vec c = gen_equal_triangle(a, b);
    long double l = 3.12;

    std::vector <vec> p = CutBuilder().find_sol_equal(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderAny, testFindSolutionAllAnglesAcuse1) {
    vec a(-9.51214,4.57306);
    vec b(-1.61897,6.40868);
    vec c(-5.72794,-1.21621);
    long double l = 4;
    std::vector <vec> p;

    ASSERT_TRUE(CutBuilder().check_any(a, b, c, l, p));

    p = CutBuilder().find_sol_any(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderAny, testFindSolutionAllAnglesAcuse2) {
    vec a(-9.51214,4.57306);
    vec b(-1.61897,6.40868);
    vec c(-5.72794,-1.21621);
    long double l = 4;
    std::vector <vec> p;

    ASSERT_TRUE(CutBuilder().check_any(a, b, c, l, p));

    p = CutBuilder().find_sol_any(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderAny, testFindSolutionObtuseB) {
    vec a(-6.90959,16.51979);
    vec b(-1.61897,6.40868);
    vec c(-5.72794,-1.21621);
    long double l = 4;
    std::vector <vec> p;

    ASSERT_TRUE(CutBuilder().check_any(a, b, c, l, p));

    p = CutBuilder().find_sol_any(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderAny, testFindSolutionObtuseA) {
    vec c(-6.90959,16.51979);
    vec a(-1.61897,6.40868);
    vec b(-5.72794,-1.21621);
    long double l = 4;
    std::vector <vec> p;

    ASSERT_TRUE(CutBuilder().check_any(a, b, c, l, p));

    p = CutBuilder().find_sol_any(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}


TEST(CutBuilderAny, testFindSolutionObtuseC) {
    vec b(-6.90959,16.51979);
    vec c(-1.61897,6.40868);
    vec a(-5.72794,-1.21621);
    long double l = 4;
    std::vector <vec> p;

    ASSERT_TRUE(CutBuilder().check_any(a, b, c, l, p));

    p = CutBuilder().find_sol_any(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderAny, testFindSolutionObtuseC2) {
    vec a(-6.90959,16.51979);
    vec c(-1.61897,6.40868);
    vec b(-5.72794,-1.21621);
    long double l = 4;
    std::vector <vec> p;

    ASSERT_TRUE(CutBuilder().check_any(a, b, c, l, p));

    p = CutBuilder().find_sol_any(a, b, c, l);
    ASSERT_TRUE(check_size(p, l));
    ASSERT_FALSE(check_collisions(p));
    ASSERT_FALSE(check_collisions_sides(p, a, b, c));
}

TEST(CutBuilderAny, testFindSolutionFalse) {
    vec a(-6.90959,16.51979);
    vec c(-1.61897,6.40868);
    vec b(-5.72794,-1.21621);
    long double l = 7;
    std::vector <vec> p;

    ASSERT_FALSE(CutBuilder().check_any(a, b, c, l, p));
}