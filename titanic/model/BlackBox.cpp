#include "BlackBox.h"

namespace model {

    void BlackBox::collectData(const std::string &column, const std::string &value) {
        data[column].push(value);
    }

    void BlackBox::collectData(const std::string &column, double value) {
        collectData(column, std::to_string(value));
    }

    void BlackBox::collectData(const std::string &column, long value) {
        collectData(column, std::to_string(value));
    }

    void BlackBox::collectData(const std::string &column, char value) {
        collectData(column, std::to_string(value));
    }

    std::string BlackBox::toString() const {

        std::stringstream stringstream;

        std::vector<std::queue<std::string>> columns; // not by reference because cannot used pop in const function

        std::string header;

        for (auto &pair : data) {

            if (!header.empty()) {
                header.append("\t");
            }

            header.append(pair.first);

            columns.push_back(pair.second);
        }

        stringstream << header << std::endl;


        bool complete = false;

        while (!complete) {

            complete = true;

            std::string line;

            for (auto &column : columns) {

                if (!line.empty()) {
                    line.append("\t");
                }

                if (!column.empty()) {
                    line.append(column.front());
                    column.pop();
                    complete = false;
                }
            }

            stringstream << line << std::endl;
        }

        return stringstream.str();
    }

    std::ostream &operator<<(std::ostream &ostream, const BlackBox &blackBox) {

        ostream << blackBox.toString();

        return ostream;
    }

    void BlackBox::flush() {

        for (auto &pair : data) {
            while (!pair.second.empty()) {
                pair.second.pop();
            }
        }
    }

    void BlackBox::clear() {

        data.clear();
    }
}