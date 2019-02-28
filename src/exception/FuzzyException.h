#ifndef LOGIQUEFLOUE_FUZZYEXCEPTION_H
#define LOGIQUEFLOUE_FUZZYEXCEPTION_H

#include <exception>
#include <string>
#include <ctime>
#include <iomanip>

namespace exception {

    class FuzzyException : std::exception {

    private:
        const std::string &message;
        const std::time_t time;
        const unsigned short errorCode;

    protected:
        explicit FuzzyException(const std::string &_message, unsigned short _errorCode);

    public:
        const std::string &getMessage() const;

        std::string getTime() const;

        unsigned short getErrorCode() const;
    };
}


#endif //LOGIQUEFLOUE_FUZZYEXCEPTION_H
