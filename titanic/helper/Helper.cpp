

#include "Helper.h"


double Helper::estimateOrdinateValue(double abscissa, const std::map<double, double> &points) {

    std::list<std::pair<double, double>> sortedPoints;

    for (auto &point : points) {
        sortedPoints.push_front(point);
    }

    sortedPoints.sort([](const std::pair<double, double> &p1, const std::pair<double, double> &p2) {
        return p1.first < p2.first;
    });

    double value = 0.0;

    if (sortedPoints.size() >= 2) {

        std::pair<double, double> leftPoint(0.0, 0.0);

        bool initLeft = false;

        for (auto it = sortedPoints.begin(); it != sortedPoints.end(); it++) {

            std::pair<double, double> point = *it;

            if (!initLeft) {
                leftPoint = point;
                initLeft = true;
            }

            if (leftPoint.first < point.first && point.first <= abscissa) {
                leftPoint = point;
            }
        }


        std::pair<double, double> rightPoint(0.0, 0.0);

        bool initRight = false;

        for (auto it = sortedPoints.rbegin(); it != sortedPoints.rend(); it++) {

            std::pair<double, double> point = *it;

            if (!initRight) {
                rightPoint = point;
                initRight = true;
            }

            if (rightPoint.first > point.first && point.first >= abscissa) {
                rightPoint = point;
            }
        }


        if (initRight && initLeft && leftPoint.first != rightPoint.first) {

            double a = (rightPoint.second - leftPoint.second) / (rightPoint.first - leftPoint.first);

            double b = leftPoint.second - a * leftPoint.first;

            value = a * (leftPoint.first - abscissa) + b;
        }
    }

    return value;
}

std::map<double, double> Helper::loadCoefficients(std::string filePath) {

    std::map<double, double> coefficients;

    std::ifstream ifstream(filePath);

    while (ifstream) {

        double x = 0.0;
        double y = 0.0;

        ifstream >> x;
        ifstream >> y;

        if (!ifstream) {
            break;
        }

        coefficients[x] = y;
    }

    ifstream.close();

    return coefficients;
}