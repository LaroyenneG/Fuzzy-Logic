#include "ShapeTest.h"

#define FILE_PATH "../assets/patatoide.shape"

void ShapeTest::testAddPoint() {

    Shape<double> shape;

    CPPUNIT_ASSERT(shape.xSize() == 0);
    CPPUNIT_ASSERT(shape.xSize() == 0);

    shape.addPoint(6.0, 0.5);

    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(shape.xSize()));
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(shape.ySize()));

    try {
        shape.addPoint(6.0, 0.5);
        CPPUNIT_FAIL("throw");
    } catch (exception::PointAlreadyAddedShapeException &e) {

    }

    shape.addPoint(-4.6, 8.6);
}

void ShapeTest::testReadFile() {

    std::ifstream ifstream(FILE_PATH);

    Shape<double> shape(ifstream);

    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(shape.xSize()));
    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(shape.ySize()));

    CPPUNIT_ASSERT_EQUAL(1.5, shape.getX(0));
    CPPUNIT_ASSERT_EQUAL(3.5, shape.getY(0));
}

void ShapeTest::testWriteFile() {

    std::stringstream stringstream;

    std::ifstream ifstream(FILE_PATH);

    Shape<double> shape(ifstream);

    shape.serialize(stringstream);
}

void ShapeTest::testWriteAndRead() {

    std::ifstream ifstream(FILE_PATH);

    Shape<double> origin(ifstream);

    std::stringstream data;
    origin.serialize(data);

    Shape<double> clone(data);


    CPPUNIT_ASSERT(origin == clone);
}



