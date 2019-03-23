#ifndef LOGIQUEFLOUE_HELPER_H
#define LOGIQUEFLOUE_HELPER_H


#include <iostream>
#include <list>
#include <map>
#include <fstream>


class Helper {

public:
    static double estimateOrdinateValue(double abscissa, const std::map<double, double> &points);

    static std::map<double, double> loadCoefficients(std::string filePath);
};


#endif //LOGIQUEFLOUE_HELPER_H
