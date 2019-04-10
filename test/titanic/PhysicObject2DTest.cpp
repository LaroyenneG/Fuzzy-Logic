#include "PhysicObject2DTest.h"


void PhysicObject2DTest::testCircleSolver() {

    Point solution{{2.32, 3.67}};
    Point p1{{9.0, 4.0}};
    Point p2{{8.5, 1.12}};
    Point p3{{8.93, 2.67}};

    Point center = PhysicObject2D::circleCenterSolver(p1, p2, p3);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[X_DIM_VALUE], center[X_DIM_VALUE], 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[Y_DIM_VALUE], center[Y_DIM_VALUE], 0.001);
}

void PhysicObject2DTest::testCircleSolverWithBigCircle() {

    Point solution{{-5.0, -6.0}};
    Point p1{{10590.72, 5497.09}};
    Point p2{{10590.77, 5497}};
    Point p3{{10590.87, 5496.8}};

    Point center = PhysicObject2D::circleCenterSolver(p1, p2, p3);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[X_DIM_VALUE], center[X_DIM_VALUE], 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[Y_DIM_VALUE], center[Y_DIM_VALUE], 0.001);
}
