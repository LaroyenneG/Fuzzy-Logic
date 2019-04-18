#ifndef LOGIQUEFLOUE_FUZZYMONITOR_H
#define LOGIQUEFLOUE_FUZZYMONITOR_H


#include "CoreObject.h"
#include "AbstractInterpreter.h"
#include "Expression.h"
#include "OrMax.h"
#include "AggMax.h"
#include "InterpreterException.h"

#define INTERPRETEUR_OR_MAX_NAME "orMax"
#define INTERPRETEUR_AGG_MAX_NAME "aggMax"
#define INTERPRETEUR_AND_MIN_NAME "andMin"
#define INTERPRETEUR_NOT_MIN_NAME "notMin"
#define INTERPRETEUR_THEN_MIN_NAME "thenMin"
#define INTERPRETEUR_COG_DEFUZZ_NAME "cogDefuzz"
#define INTERPRETEUR_CREATE_FUZZYSYSTEM "fuzzySystem"
#define INTERPRETEUR_TYPE_COG "typeCog"
#define INTERPRETEUR_TYPE_SUGENO "typeSugeno"
#define INTERPRETEUR_CONTEXT_ACCESS "->"

namespace fuzzylogic::interpreter {

    template<typename T>
    class FuzzyInterpreter : public AbstractInterpreter<T> {

    protected:
        typedef enum {
            COG,
            SUGENO
        } DefuzzType;

    private:
        std::map<std::string, core::CoreObject<T> *> fuzzyOperatorContext;

        static std::map<std::string, core::CoreObject<T> *> buildFuzzyCollection(const std::string &context);

        std::map<std::string, fuzzy::FuzzyFactory<T> *> factoryContext;

        std::map<fuzzy::FuzzyFactory<T> *, DefuzzType> factoryType;

        void createFuzzySystem(std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createCogFactory(std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createSugenoFactory(std::vector<std::string> &arguments);

        static std::string buildContextKey(const std::string &context, const std::string &name);

    public:
        FuzzyInterpreter();

        ~FuzzyInterpreter();

        void execute(const std::string &line) override;

        bool operatorExist(const std::string &context, const std::string &name) const;

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
    std::map<std::string, core::CoreObject<T> *> FuzzyInterpreter<T>::buildFuzzyCollection(const std::string &context) {

        std::map<std::string, core::CoreObject<T> *> collection;

        std::string front = context + INTERPRETEUR_CONTEXT_ACCESS;

        collection[front + INTERPRETEUR_OR_MAX_NAME] = new fuzzy::OrMax<T>();
        collection[front + INTERPRETEUR_AGG_MAX_NAME] = new fuzzy::AggMax<T>();
        collection[front + INTERPRETEUR_NOT_MIN_NAME] = new fuzzy::NotMinus1<T>();
        collection[front + INTERPRETEUR_AND_MIN_NAME] = new fuzzy::AndMin<T>();
        collection[front + INTERPRETEUR_THEN_MIN_NAME] = new fuzzy::ThenMin<T>();
        collection[front + INTERPRETEUR_COG_DEFUZZ_NAME] = new fuzzy::CogDefuzz<T>();


        return collection;
    }

    template<typename T>
    FuzzyInterpreter<T>::FuzzyInterpreter() {

    }

    template<typename T>
    FuzzyInterpreter<T>::~FuzzyInterpreter() {

        for (auto &pair:fuzzyOperatorContext) {
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

        arguments.erase(++arguments.begin());

        fuzzy::FuzzyFactory<T> *factory = nullptr;

        if (defuzzType == INTERPRETEUR_TYPE_COG) {
            factory = createCogFactory(arguments);
        } else if (defuzzType == INTERPRETEUR_TYPE_SUGENO) {
            factory = createSugenoFactory(arguments);
        }

        factoryContext[contextName] = factory;
        fuzzyOperatorContext[contextName] = buildFuzzyCollection(factoryContext);
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createCogFactory(std::vector<std::string> &arguments) {

        if (arguments.size() < 7) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = arguments[0];

        for (auto &argument : arguments) {
            if (!operatorExist(context, argument)) {
                throw exception::InterpreterException("Error : " + argument + "not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[0])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[1])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[2])]);
        auto opThen = dynamic_cast<fuzzy::Then<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[3])]);
        auto opAgg = dynamic_cast<fuzzy::Agg<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[4])]);
        auto opCogDefuzz = dynamic_cast<fuzzy::MamdaniDefuzz<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                        arguments[5])]);


        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opThen, opAgg, opCogDefuzz);

        factoryType[factory] = COG;

        return factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createSugenoFactory(std::vector<std::string> &arguments) {

        if (arguments.size() < 7) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = arguments[0];

        for (auto &argument : arguments) {
            if (!operatorExist(context, argument)) {
                throw exception::InterpreterException("Error : " + argument + "not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[0])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[1])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[2])]);
        auto opSugenoThen = dynamic_cast<fuzzy::SugenoThen<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                      arguments[3])]);
        auto opSugenoDefuzz = dynamic_cast<fuzzy::SugenoDefuzz<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                          arguments[4])]);
        auto opSugenoConclusion = dynamic_cast<fuzzy::SugenoConclusion<T> *>(fuzzyOperatorContext[buildContextKey(
                context, arguments[5])]);

        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opSugenoThen, opSugenoDefuzz,
                                                                  opSugenoConclusion);
        factoryType[factory] = SUGENO;

        return factory;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::operatorExist(const std::string &context, const std::string &name) const {

        std::string key = buildContextKey(context, name);

        for (auto &pair : fuzzyOperatorContext) {
            if (pair.first == key) {
                return true;
            }
        }

        return false;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::contextExist(const std::string &name) const {

        for (auto &pair : factoryContext) {
            if (pair.first == name) {
                return true;
            }
        }

        return false;
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::buildContextKey(const std::string &context, const std::string &name) {

        return context + INTERPRETEUR_CONTEXT_ACCESS + name;
    }
}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H