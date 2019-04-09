#include "ShapeTest.h"

#define FILE_PATH "../assets/patatoide.shape"

void ShapeTest::testAddPoint() {

    Shape<double> shape;

    shape.addPoint(6.0, 0.5);

    CPPUNIT_ASSERT_THROW(shape.addPoint(6.0, 0.5), exception::PointAlreadyAddedShapeException);

    for (auto point : shape) {
        CPPUNIT_ASSERT_EQUAL(6.0, point.first);
        CPPUNIT_ASSERT_EQUAL(0.5, point.second);
    }

    shape.addPoint(-4.6, 8.6);
}

void ShapeTest::testReadFile() {

    std::ifstream ifstream(FILE_PATH);

    Shape<double> shape(ifstream);

    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(shape.size()));
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

    CPPUNIT_ASSERT_EQUAL(origin, clone);
}



