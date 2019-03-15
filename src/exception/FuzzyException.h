#ifndef LOGIQUEFLOUE_FUZZYEXCEPTION_H
#define LOGIQUEFLOUE_FUZZYEXCEPTION_H

#include <exception>
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>

#define OPEN_FUZZY_SECURE_BLOCK try
#define CLOSE_FUZZY_SECURE_BLOCK catch(exception::FuzzyException &e) {e.printDebug(); CPPUNIT_FAIL("Fuzzy exception throw");}

namespace exception {

    class FuzzyException : std::runtime_error {

    private:
        const std::time_t time;
        const unsigned short errorCode;

    protected:
        explicit FuzzyException(const std::string &_message, unsigned short _errorCode);

    public:
        const std::string getMessage() const;

        std::string getTime() const;

        unsigned short getErrorCode() const;

        void printDebug() const;
    };
}


#endif //LOGIQUEFLOUE_FUZZYEXCEPTION_H
