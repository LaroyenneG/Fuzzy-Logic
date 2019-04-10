#ifndef LOGIQUEFLOUE_BLACKBOX_H
#define LOGIQUEFLOUE_BLACKBOX_H

#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include <mutex>

namespace model {

    class BlackBox {

    private:
        std::mutex mutex;

        std::map<std::string, std::queue<std::string>> data;

    public:
        explicit BlackBox() = default;

        void collectData(const std::string &column, const std::string &value);

        void collectData(const std::string &column, double value);

        void collectData(const std::string &column, long value);

        void collectData(const std::string &column, char value);

        std::string toString() const;

        void flush();

        void clear();

        friend std::ostream &operator<<(std::ostream &ostream, const BlackBox &blackBox);

        ~BlackBox();
    };
}

#endif //LOGIQUEFLOUE_BLACKBOX_H
