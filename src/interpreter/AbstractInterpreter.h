

#ifndef LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
#define LOGIQUEFLOUE_ABSTRACTINTERPRETER_H

#include <fstream>
#include <string>
#include <map>

namespace interpreter {

    template<typename T>
    class AbstractInterpreter {

    private:
        std::map<std::string, T> freeMemory;

    public:
        virtual void execute(std::string line) = 0;

        void execute(std::fstream fstream);

        T readInMemory(std::string key) const;

        void writeInMemory(std::string key, const T &value);
    };

    template<typename T>
    void AbstractInterpreter<T>::execute(std::fstream fstream) {

        std::string line;

        while (std::getline(fstream, line)) {
            execute(line);
        }
    }

    template<typename T>
    T AbstractInterpreter<T>::readInMemory(std::string key) const {

        if (freeMemory.find(key) == freeMemory.end()) {
            throw std::exception();
        }

        return freeMemory[key];
    }

    template<typename T>
    void AbstractInterpreter<T>::writeInMemory(std::string key, const T &value) {

        freeMemory[key] = value;
    }
}

#endif //LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
