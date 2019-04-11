

#ifndef LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
#define LOGIQUEFLOUE_ABSTRACTINTERPRETER_H

#include <fstream>
#include <string>
#include <map>

namespace fuzzylogic::interpreter {

    template<typename T>
    class AbstractInterpreter {

    private:
        std::map<std::string, T> memory;

    protected:
        typedef enum {
            INPUT,
            OUTPUT,
            TMP
        } MemoryType;

        T readInMemory(MemoryType type, const std::string &name) const;

        void writeInMemory(MemoryType type, const std::string &name, const T &value);

        void freeInMemory(MemoryType, const std::string &name);

    public:
        virtual void execute(const std::string &line) = 0;

        void executeFile(std::ifstream &fstream);
    };

    template<typename T>
    void AbstractInterpreter<T>::executeFile(std::ifstream &fstream) {

        std::string line;

        while (std::getline(fstream, line)) {
            execute(line);
            line.clear();
        }
    }


    template<typename T>
    T AbstractInterpreter<T>::readInMemory(MemoryType type, const std::string &name) const {

        std::string key = std::string(type) + name;

        if (memory.find(key) == memory.end()) {
            throw std::exception();
        }

        return memory[key];
    }

    template<typename T>
    void AbstractInterpreter<T>::writeInMemory(MemoryType type, const std::string &name, const T &value) {

        std::string key = std::string(type) + name;

        memory[key] = value;
    }

    template<typename T>
    void AbstractInterpreter<T>::freeInMemory(MemoryType type, const std::string &name) {

        std::string key = std::string(type) + name;

        if (memory.find(key) == memory.end()) {
            throw std::exception();
        }

        memory.erase(key);
    }
}

#endif //LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
