#include "ShapeTest.h"

#define FILE_PATH "../assets/patatoide.shape"

void ShapeTest::testAddPoint() {

    Shape<double> shape;

    shape.addPoint(6.0, 0.5);

    try {
        shape.addPoint(6.0, 0.5);
        CPPUNIT_FAIL("throw");
    } catch (exception::PointAlreadyAddedShapeException &e) {
    }

    for (auto it = shape.begin(); it != shape.end(); it++) {
        CPPUNIT_ASSERT_EQUAL(6.0, (*it).first);
        CPPUNIT_ASSERT_EQUAL(0.5, (*it).second);
    }

    shape.addPoint(-4.6, 8.6);
}

void ShapeTest::testReadFile() {

    std::ifstream ifstream(FILE_PATH);

    Shape<double> shape(ifstream);
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



