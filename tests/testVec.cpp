#include "gtest/gtest.h"

#include "vec.h"

TEST(VecTests, testMod) {
    vec a(3.5, 4.5);

    ASSERT_NEAR(a.mod(), 5.7008771255, vec::eps);
}

TEST(VecTests, testNorm) {
    vec a(3.5, 4.5);

    ASSERT_NEAR(a.norm().mod(), 1, vec::eps);
    ASSERT_NEAR(a.norm() % a, 0, vec::eps);
}

TEST(VecTests, testOrtnorm) {
    vec a(1, 1);
    vec b = a.ortnorm();
    ASSERT_NEAR(a * b, 0, vec::eps);
    ASSERT_NEAR(b.mod(), 1, vec::eps);
}

TEST(VecTests, testDist) {
    vec a(1.2, 1.5);
    vec b(6.7, -5.9);
    ASSERT_NEAR(vec::dist(a, b),9.220086767487604, vec::eps);
}

TEST(VecTests, testCheckCollisionTrue) {
    vec a(-1.89,2.22);
    vec b(1.03,-1.1);
    vec c(0.83,1.98);
    vec d(-1.29,-0.74);

    ASSERT_EQ(vec::check_collision(a, b, c, d), true);
}

TEST(VecTests, testCheckCollisionTrueTouch) {
    vec a(-4.25,2.08);
    vec b(0.75,-0.88);
    vec c(0.03,-3.66);
    vec d(0.75,-0.88);

    ASSERT_EQ(vec::check_collision(a, b, c, d), true);
}

TEST(VecTests, testCheckCollisionFalse) {
    vec a(-3.49,2.16);
    vec b(0.63,-1.1);
    vec c(-3.89,-3.34);
    vec d(-2.57,-0.48);

    ASSERT_EQ(vec::check_collision(a, b, c, d), false);
}

TEST(VecTests, testCheckCollisionFalseClose) {
    vec a(-4.19,-0.08);
    vec b(-0.77,4.54);
    vec c(-2.60694,2.05565);
    vec d(1.87,-0.26);

    ASSERT_EQ(vec::check_collision(a, b, c, d), false);
}

TEST(vecTests, testGetAngle1) {
    vec v1(2, 5);
    vec v2(4,7);

    long double angle = vec::get_angle(v1, v2);

    ASSERT_NEAR(angle, 0.138639737, vec::eps);
}

TEST(vecTests, testGetAngle2) {
    vec v1(2, 5);
    vec v2(4,7);

    long double angle = vec::get_angle(v2, v1);

    ASSERT_NEAR(angle, 0.138639737, vec::eps);
}

TEST(vecTests, testGetAngle3) {
    vec v1(5, 1);
    vec v2(-5,1);

    long double angle = vec::get_angle(v1, v2);

    ASSERT_NEAR(angle, 2.74680153359, vec::eps);
}



