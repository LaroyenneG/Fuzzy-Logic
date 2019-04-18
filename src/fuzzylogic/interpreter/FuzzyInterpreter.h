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
        const std::map<std::string, const core::BinaryExpression<T> *> fuzzyCollection;

        static std::map<std::string, const core::BinaryExpression<T> *> buildFuzzyCollection();

        std::map<std::string, fuzzy::FuzzyFactory<T> *> context;

        std::map<fuzzy::FuzzyFactory<T> *, DefuzzType> factoryType;

        void createFuzzySystem(std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createCogFactory(std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createSugenoFactory(std::vector<std::string> &arguments);

    public:
        FuzzyInterpreter();

        ~FuzzyInterpreter();

        void execute(const std::string &line) override;

        bool operatorExist(const std::string &name) const;

        bool contextExist(const std::string &name) const;
    };

    template<typename T>
    void FuzzyInterpreter<T>::execute(const std::string &line) {

        std::string intruction = AbstractInterpreter<T>::getInstructionName(line);

        std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(line);

        args.erase(args.begin());

        std::cout << line << std::endl;

    }

    template<typename T>
    std::map<std::string, const core::BinaryExpression<T> *> FuzzyInterpreter<T>::buildFuzzyCollection() {

        std::map<std::string, const core::BinaryExpression<T> *> collection;

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
    }

    template<typename T>
    void FuzzyInterpreter<T>::createFuzzySystem(std::vector<std::string> &arguments) {

        if (arguments.size() < 2) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string defuzzType = arguments[1];
        std::string contextName = arguments[0];

        fuzzy::FuzzyFactory<T> *factory = nullptr;

        if (defuzzType == INTERPRETEUR_TYPE_COG) {
            factory = createCogFactory(arguments);
        } else if (defuzzType == INTERPRETEUR_TYPE_SUGENO) {
            factory = createSugenoFactory(arguments);
        }

        context[contextName] = factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createCogFactory(std::vector<std::string> &arguments) {

        if (arguments.size() < 6) {
            throw exception::InterpreterException("Not enough arguments");
        }

        for (auto &argument : arguments) {
            if (!operatorExist(argument)) {
                throw exception::InterpreterException("Error : " + argument + "not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyCollection[arguments[0]]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyCollection[arguments[1]]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyCollection[arguments[2]]);
        auto opThen = dynamic_cast<fuzzy::Then<T> *>(fuzzyCollection[arguments[3]]);
        auto opAgg = dynamic_cast<fuzzy::Agg<T> *>(fuzzyCollection[arguments[4]]);
        auto opCogDefuzz = dynamic_cast<fuzzy::CogDefuzz<T> *>(fuzzyCollection[arguments[5]]);


        fuzzy::FuzzyFactory<T> *factory = new fuzzy::FuzzyFactory(opNot, opAnd, opOr, opThen, opAgg, opCogDefuzz);
        factoryType[factory] = COG;

        return factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createSugenoFactory(std::vector<std::string> &arguments) {

        if (arguments.size() < 6) {
            throw exception::InterpreterException("Not enough arguments");
        }

        for (auto &argument : arguments) {
            if (!operatorExist(argument)) {
                throw exception::InterpreterException("Error : " + argument + "not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyCollection[arguments[0]]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyCollection[arguments[1]]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyCollection[arguments[2]]);
        auto opSugenoThen = dynamic_cast<fuzzy::SugenoThen<T> *>(fuzzyCollection[arguments[3]]);
        auto opSugenoDefuzz = dynamic_cast<fuzzy::SugenoDefuzz<T> *>(fuzzyCollection[arguments[4]]);
        auto opSugenoConclusion = dynamic_cast<fuzzy::SugenoConclusion<T> *>(fuzzyCollection[arguments[5]]);

        fuzzy::FuzzyFactory<T> *factory = new fuzzy::FuzzyFactory(opNot, opAnd, opOr, opSugenoThen, opSugenoDefuzz,
                                                                  opSugenoConclusion);
        factoryType[factory] = SUGENO;

        return factory;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::operatorExist(const std::string &name) const {

        for (auto &pair : fuzzyCollection) {
            if (pair.first == name) {
                return true;
            }
        }

        return false;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::contextExist(const std::string &name) const {

        for (auto &pair : context) {
            if (pair.first == name) {
                return true;
            }
        }

        return false;
    }
}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H