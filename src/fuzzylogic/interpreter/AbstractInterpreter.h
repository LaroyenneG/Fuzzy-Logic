

#ifndef LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
#define LOGIQUEFLOUE_ABSTRACTINTERPRETER_H

#include <fstream>
#include <string>
#include <map>
#include <algorithm>

#define INTERPRETER_MULTI_LINES_OPEN_CHAR '{'
#define INTERPRETER_MULTI_LINES_CLOSE_CHAR '}'
#define INTERPRETER_CHAR_TO_SPLIT_LINE ' '
#define INTERPRETER_KEY_SEPARATOR_CHAR ':'

namespace fuzzylogic::interpreter {

    template<typename T>
    class AbstractInterpreter {

    private:
        std::string stringBuffer;

        std::map<std::string, T> memory;

        void lineReaderExecution(const std::string &line);

    protected:
        virtual void execute(const std::string &line) = 0;

    public:
        typedef enum {
            INPUT,
            OUTPUT,
            TMP
        } MemoryType;

        const T &readInMemory(MemoryType type, const std::string &name) const;

        void writeInMemory(MemoryType type, const std::string &name, const T &value);

        void freeInMemory(MemoryType, const std::string &name);

        virtual ~AbstractInterpreter() = default;

        void executeFile(std::ifstream &fstream);

        void executeLine(const std::string &line);

        static std::string extractFirstArgument(const std::string &line);

        static std::vector<std::string> lineToArgs(const std::string &line);

        static std::string stringReplace(const std::string &string, const std::string &a, const std::string &b);
    };

    template<typename T>
    void AbstractInterpreter<T>::executeFile(std::ifstream &fstream) {

        std::string line;

        int lineCount = 1;

        try {

            while (std::getline(fstream, line)) {
                lineReaderExecution(line);
                line.clear();
                lineCount++;
            }

        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            std::cerr << "At line : " << lineCount << std::endl;
            exit(EXIT_FAILURE);
        }
    }


    template<typename T>
    const T &AbstractInterpreter<T>::readInMemory(MemoryType type, const std::string &name) const {

        std::string key = std::to_string(type) + INTERPRETER_KEY_SEPARATOR_CHAR + name;

        auto it = memory.find(key);

        if (it == memory.end()) {
            throw std::invalid_argument("Invalid variable name");
        }

        return it->second;
    }

    template<typename T>
    void AbstractInterpreter<T>::writeInMemory(MemoryType type, const std::string &name, const T &value) {

        std::string key = std::to_string(type) + INTERPRETER_KEY_SEPARATOR_CHAR + name;

        memory[key] = value;
    }

    template<typename T>
    void AbstractInterpreter<T>::freeInMemory(MemoryType type, const std::string &name) {

        std::string key = std::to_string(type) + INTERPRETER_KEY_SEPARATOR_CHAR + name;

        if (memory.find(key) == memory.end()) {
            throw std::invalid_argument("invalid variable name");
        }

        memory.erase(key);
    }

    template<typename T>
    std::string AbstractInterpreter<T>::extractFirstArgument(const std::string &line) {

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

    template<typename T>
    std::string
    AbstractInterpreter<T>::stringReplace(const std::string &string, const std::string &a, const std::string &b) {

        std::string result;

        for (unsigned int i = 0; i < string.size(); i++) {

            unsigned int charCounter = 0;
            bool pattern = true;

            for (unsigned int j = i, k = 0; j < string.size() && k < a.size(); j++, k++) {

                if (string[j] != a[k]) {
                    pattern = false;
                } else {
                    charCounter++;
                }
            }

            if (pattern && charCounter == a.size()) {
                result += b;
                i += charCounter - 1;
            } else {
                result += string[i];
            }
        }

        return result;
    }

    template<typename T>
    void AbstractInterpreter<T>::lineReaderExecution(const std::string &line) {

        std::string nLine;

        if (stringBuffer.empty()) {
            nLine = line;
        } else {
            stringBuffer += line;
        }

        size_t openPosition = nLine.find(INTERPRETER_MULTI_LINES_OPEN_CHAR);
        size_t closePosition = stringBuffer.find(INTERPRETER_MULTI_LINES_CLOSE_CHAR);

        if (openPosition != std::string::npos) {

            std::string cleanLine = line;

            cleanLine.erase(openPosition);

            stringBuffer += cleanLine;

            nLine.clear();
        }

        if (closePosition != std::string::npos) {

            std::string cleanLine = stringBuffer;

            cleanLine.erase(closePosition);

            nLine = cleanLine;

            stringBuffer.clear();
        }

        if (!nLine.empty()) {
            execute(nLine);
        }
    }

    template<typename T>
    void AbstractInterpreter<T>::executeLine(const std::string &line) {

        try {
            execute(line);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

#endif //LOGIQUEFLOUE_ABSTRACTINTERPRETER_H
