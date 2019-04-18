#ifndef LOGIQUEFLOUE_FUZZYMONITOR_H
#define LOGIQUEFLOUE_FUZZYMONITOR_H

#include "ValueModel.h"
#include "CoreObject.h"
#include "AbstractInterpreter.h"
#include "Expression.h"
#include "OrMax.h"
#include "AggMax.h"
#include "InterpreterException.h"

#define INTERPRETER_OR_MAX_NAME "OrMax"
#define INTERPRETEUR_AGG_MAX_NAME "AggMax"
#define INTERPRETEUR_AND_MIN_NAME "AndMin"
#define INTERPRETEUR_NOT_MIN_NAME "NotMin"
#define INTERPRETEUR_THEN_MIN_NAME "ThenMin"
#define INTERPRETEUR_COG_DEFUZZ_NAME "CogDefuzz"
#define INTERPRETEUR_SUGENO_THEN_NAME "SugenoThen"
#define INTERPRETEUR_SUGENO_DEFUZZ_NAME "SugenoDefuzz"
#define INTERPRETEUR_SUGENO_CONCLUSION_NAME "SugenoConclusion"
#define INTERPRETER_CREATE_FUZZYSYSTEM "FuzzySystem"
#define INTERPRETEUR_TYPE_COG "Cog"
#define INTERPRETEUR_TYPE_SUGENO "Sugeno"
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

        std::map<std::string, fuzzy::FuzzyFactory<T> *> factoryContext;

        std::map<const fuzzy::FuzzyFactory<T> *, DefuzzType> factoryType;

        std::map<std::string, core::ValueModel<T> *> inputsContext;

        void createFuzzySystem(std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createCogFactory(std::vector<std::string> &arguments);

        fuzzy::FuzzyFactory<T> *createSugenoFactory(std::vector<std::string> &arguments);

        static std::string buildContextKey(const std::string &context, const std::string &name);

        static void buildFuzzyOperatorCollection(std::map<std::string, core::CoreObject<T> *> &map,
                                                 const std::string &context);

    public:
        FuzzyInterpreter();

        ~FuzzyInterpreter();

        void execute(const std::string &line) override;

        bool operatorExistInContext(const std::string &context, const std::string &name) const;

        bool contextExist(const std::string &name) const;
    };

    template<typename T>
    void FuzzyInterpreter<T>::execute(const std::string &line) {

        std::string instruction = AbstractInterpreter<T>::getInstructionName(line);

        std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(line);

        args.erase(args.begin());

        if (instruction == INTERPRETER_CREATE_FUZZYSYSTEM) {
            createFuzzySystem(args);
        } else {
            throw exception::InterpreterException("Invalid command : " + instruction);
        }
    }

    template<typename T>
    FuzzyInterpreter<T>::FuzzyInterpreter() = default;

    template<typename T>
    FuzzyInterpreter<T>::~FuzzyInterpreter() {

        for (auto &pair:fuzzyOperatorContext) {
            delete pair.second;
        }

        for (auto &pair:factoryContext) {
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

        buildFuzzyOperatorCollection(fuzzyOperatorContext, contextName);

        arguments.erase(++arguments.begin());

        fuzzy::FuzzyFactory<T> *factory = nullptr;

        if (defuzzType == INTERPRETEUR_TYPE_COG) {
            factory = createCogFactory(arguments);
        } else if (defuzzType == INTERPRETEUR_TYPE_SUGENO) {
            factory = createSugenoFactory(arguments);
        }

        factoryContext[contextName] = factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createCogFactory(std::vector<std::string> &arguments) {

        if (arguments.size() < 6) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = arguments[0];

        for (unsigned int i = 1; i < arguments.size(); i++) {
            if (!operatorExistInContext(context, arguments[i])) {
                throw exception::InterpreterException("Error : " + arguments[i] + " not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[1])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[2])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[3])]);
        auto opThen = dynamic_cast<fuzzy::Then<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[4])]);
        auto opAgg = dynamic_cast<fuzzy::Agg<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[5])]);
        auto opCogDefuzz = dynamic_cast<fuzzy::MamdaniDefuzz<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                        INTERPRETEUR_COG_DEFUZZ_NAME)]);


        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opThen, opAgg, opCogDefuzz);

        factoryType[factory] = COG;

        return factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createSugenoFactory(std::vector<std::string> &arguments) {

        if (arguments.size() < 4) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = arguments[0];

        for (unsigned int i = 1; i < arguments.size(); i++) {
            if (!operatorExistInContext(context, arguments[i])) {
                throw exception::InterpreterException("Error : " + arguments[i] + " not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[1])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[2])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildContextKey(context, arguments[3])]);
        auto opSugenoThen = dynamic_cast<fuzzy::SugenoThen<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                      INTERPRETEUR_SUGENO_THEN_NAME)]);
        auto opSugenoDefuzz = dynamic_cast<fuzzy::SugenoDefuzz<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                          INTERPRETEUR_SUGENO_DEFUZZ_NAME)]);
        auto opSugenoConclusion = dynamic_cast<fuzzy::SugenoConclusion<T> *>(fuzzyOperatorContext[buildContextKey(
                context, INTERPRETEUR_SUGENO_CONCLUSION_NAME)]);

        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opSugenoThen, opSugenoDefuzz,
                                                  opSugenoConclusion);
        factoryType[factory] = SUGENO;

        return factory;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::operatorExistInContext(const std::string &context, const std::string &name) const {

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

    template<typename T>
    void FuzzyInterpreter<T>::buildFuzzyOperatorCollection(std::map<std::string, core::CoreObject<T> *> &map,
                                                           const std::string &context) {

        map[buildContextKey(context, INTERPRETER_OR_MAX_NAME)] = new fuzzy::OrMax<T>();
        map[buildContextKey(context, INTERPRETEUR_AGG_MAX_NAME)] = new fuzzy::AggMax<T>();
        map[buildContextKey(context, INTERPRETEUR_NOT_MIN_NAME)] = new fuzzy::NotMinus1<T>();
        map[buildContextKey(context, INTERPRETEUR_AND_MIN_NAME)] = new fuzzy::AndMin<T>();
        map[buildContextKey(context, INTERPRETEUR_THEN_MIN_NAME)] = new fuzzy::ThenMin<T>();
        map[buildContextKey(context, INTERPRETEUR_COG_DEFUZZ_NAME)] = new fuzzy::CogDefuzz<T>();
    }
}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H