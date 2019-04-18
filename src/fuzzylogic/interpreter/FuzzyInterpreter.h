#ifndef LOGIQUEFLOUE_FUZZYMONITOR_H
#define LOGIQUEFLOUE_FUZZYMONITOR_H


#include <fuzzylogic.h>
#include "AbstractInterpreter.h"
#include "Expression.h"
#include "OrMax.h"
#include "AggMax.h"
#include "InterpreterException.h"

#define INTERPRETEUR_ORMAXNAME "orMax"
#define INTERPRETEUR_AGGMAXNAME "aggMax"
#define INTERPRETEUR_CREATE_FUZZYSYSTEM "fuzzySystem"
#define INTERPRETEUR_TYPE_COG "typeCog"
#define INTERPRETEUR_TYPE_SUGENO "typeSugeno"

namespace fuzzylogic::interpreter {

    template<typename T>
    class FuzzyInterpreter : public AbstractInterpreter<T> {

    protected:
        typedef enum {
            COG,
            SUGENO
        } DefuzzType;

    private:
        const std::map<std::string, const core::Expression<T> *> fuzzyCollection;

        static std::map<std::string, core::Expression<T> *> buildFuzzyCollection();

        std::map<std::string, fuzzy::FuzzyFactory<T> *> context;

        std::map<fuzzy::FuzzyFactory<T> *, DefuzzType> factoryType;

        void createFuzzySystem(const std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createCogFactory();

        fuzzy::FuzzyFactory<T> *createSugenoFactory();

    public:
        FuzzyInterpreter();

        ~FuzzyInterpreter();

        void execute(const std::string &line) override;
    };

    template<typename T>
    void FuzzyInterpreter<T>::execute(const std::string &line) {

        std::string intruction = AbstractInterpreter<T>::getInstructionName(line);

        std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(line);

        args.erase(args.begin());

        std::cout << line << std::endl;

    }

    template<typename T>
    std::map<std::string, core::Expression<T> *> FuzzyInterpreter<T>::buildFuzzyCollection() {

        std::map<std::string, core::Expression<T> *> collection;

        collection[INTERPRETEUR_ORMAXNAME] = new fuzzy::OrMax<T>();
        collection[INTERPRETEUR_AGGMAXNAME] = new fuzzy::AggMax<T>();


        return collection;
    }

    template<typename T>
    FuzzyInterpreter<T>::FuzzyInterpreter() : fuzzyCollection(buildFuzzyCollection()) {

    }

    template<typename T>
    FuzzyInterpreter<T>::~FuzzyInterpreter() {

        for (auto &pair:fuzzyCollection) {
            delete pair.second;
        }

        fuzzyCollection.clear();
    }

    template<typename T>
    void FuzzyInterpreter<T>::createFuzzySystem(const std::vector<std::string> &arguments) {

        if (arguments.size() < 2) {
            throw exception::InterpreterException("Not enough arguments");
        }

        fuzzy::FuzzyFactory<T> *factory = nullptr;

        if (arguments[1] == INTERPRETEUR_TYPE_COG) {
            factory = createCogFactory();
        } else if (arguments[1] == INTERPRETEUR_TYPE_SUGENO) {
            factory = createSugenoFactory();
        }

        context[arguments[0]] = factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createCogFactory() {

        fuzzy::FuzzyFactory<T> *factory = nullptr;
        factoryType[factory] = COG;

        return factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createSugenoFactory() {

        fuzzy::FuzzyFactory<T> *factory = nullptr;
        factoryType[factory] = SUGENO;

        return factory;
    }

}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H