

#ifndef LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
#define LOGIQUEFLOUE_ABSTRACTINTERPRETER_H

#include <fstream>
#include <string>
#include <map>

#define INTERPRETER_CHAR_TO_SPLIT_LINE ' '

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

        static std::string getInstructionName(const std::string &line);

        static std::vector<std::string> lineToArgs(const std::string &line);
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

    template<typename T>
    std::string AbstractInterpreter<T>::getInstructionName(const std::string &line) {

        std::string name;

        unsigned int index = 0;

        while (index < line.size()) {

            char c = line[index];

            if (c == INTERPRETER_CHAR_TO_SPLIT_LINE) {
                break;
            }

            name += c;

            index++;
        }

        return name;
    }

    template<typename T>
    std::vector<std::string> AbstractInterpreter<T>::lineToArgs(const std::string &line) {

        std::vector<std::string> args;

        unsigned int index = 0;

        while (index < line.size()) {

            std::string arg;

            while (index < line.size()) {

                char c = line[index];

                if (c == INTERPRETER_CHAR_TO_SPLIT_LINE) {
                    break;
                }

                arg += c;

                index++;
            }

            if (!arg.empty()) {
                args.push_back(arg);
            }

            index++;
        }

        return args;
    }
}

#endif //LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
