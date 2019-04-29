#include "PhysicObject2DTest.h"


void PhysicObject2DTest::testCircleSolver() {

    Point solution{{2.32, 3.67}};
    Point p1{{9.0, 4.0}};
    Point p2{{8.5, 1.12}};
    Point p3{{8.93, 2.67}};

    Point center = PhysicObject2D::circleCenterSolver(p1, p2, p3);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[X_DIM_VALUE], center[X_DIM_VALUE], 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[Y_DIM_VALUE], center[Y_DIM_VALUE], 0.01);
}

void PhysicObject2DTest::testCircleSolverWithBigCircle() {

    Point solution{{0, 0}};
    Point p1{{100, 0}};
    Point p2{{99.98, 1.8}};
    Point p3{{99.95, 3.19}};

    Point center = PhysicObject2D::circleCenterSolver(p1, p2, p3);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[X_DIM_VALUE], center[X_DIM_VALUE], 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(solution[Y_DIM_VALUE], center[Y_DIM_VALUE], 0.01);
}

void PhysicObject2DTest::testEstimateOrdinateValue() {

    std::map<double, double> points{{{1.0, 0.0}, {0.1, 5.0}}};

    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(0.1, points), 5.0, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(1.0, points), 0.0, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(0.9 / 2.0, points), 3.0, 0.1);

    points[5.0] = 6.0;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(0.1, points), 5.0, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(1.0, points), 0.0, 0.01);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(0.9 / 2.0, points), 3.0, 0.1);

    points[7.0] = 6.0;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(100.0, points), 6.0, 0.01);

    points[-1.0] = -5.0;
    points[-2.0] = -5.0;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(-100.0, points), -5.0, 0.01);


    std::map<double, double> points2{{{0.0, 0.0}, {1.0, 10.0}}};

    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(0.5, points2), 5.0, 0.01);

    points2[1.0] = -10;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(PhysicObject2D::estimateOrdinateValue(0.5, points2), -5.0, 0.01);
}
