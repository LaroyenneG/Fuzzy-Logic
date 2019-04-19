#ifndef LOGIQUEFLOUE_FUZZYMONITOR_H
#define LOGIQUEFLOUE_FUZZYMONITOR_H

#include "Is.h"
#include "ValueModel.h"
#include "CoreObject.h"
#include "AbstractInterpreter.h"
#include "Expression.h"
#include "OrMax.h"
#include "AggMax.h"
#include "InterpreterException.h"

#define INTERPRETER_OR_MAX_NAME "OrMax"
#define INTERPRETER_AGG_MAX_NAME "AggMax"
#define INTERPRETER_AND_MIN_NAME "AndMin"
#define INTERPRETER_NOT_MIN_NAME "NotMin"
#define INTERPRETER_THEN_MIN_NAME "ThenMin"
#define INTERPRETER_COG_DEFUZZ_NAME "CogDefuzz"
#define INTERPRETER_SUGENO_THEN_NAME "SugenoThen"
#define INTERPRETER_SUGENO_DEFUZZ_NAME "SugenoDefuzz"
#define INTERPRETER_SUGENO_CONCLUSION_NAME "SugenoConclusion"
#define INTERPRETER_CREATE_FUZZY_SYSTEM_COMMAND "FuzzySystem"
#define INTERPRETER_TYPE_COG "Cog"
#define INTERPRETER_TYPE_SUGENO "Sugeno"
#define INTERPRETER_CONTEXT_ACCESS "->"
#define INTERPRETER_VAR_DECLARATION_COMMAND "Var"
#define INTERPRETER_INPUT_TYPE "Input"
#define INTERPRETER_OUTPUT_TYPE "Output"
#define INTERPRETER_COMPUTE_COMMAND "Compute"
#define INTERPRETER_DEFINITION_COMMAND "Define"

namespace fuzzylogic::interpreter {

    template<typename T>
    class FuzzyInterpreter : public AbstractInterpreter<T> {

    protected:
        typedef enum {
            COG,
            SUGENO
        } DefuzzType;
        typedef enum {
            Output,
            Input,
            Error
        } VarType;

    private:
        std::map<std::string, core::CoreObject<T> *> fuzzyOperatorContext;

        std::map<std::string, fuzzy::FuzzyFactory<T> *> factoryContext;

        std::map<const fuzzy::FuzzyFactory<T> *, DefuzzType> factoryType;

        std::map<std::string, core::ValueModel<T> *> varContext;

        std::map<const core::ValueModel<T> *, VarType> varType;

        std::map<std::string, fuzzy::Is<T> *> definitionsContext;

    protected:

        void createFuzzySystem(std::vector<std::string> &args);

        fuzzy::FuzzyFactory<T> *createCogFactory(std::vector<std::string> &args);

        fuzzy::FuzzyFactory<T> *createSugenoFactory(std::vector<std::string> &args);

        void createVar(std::vector<std::string> &args);

        void compute(std::vector<std::string> &args);

        void definition(std::vector<std::string> &args);

        bool operatorExistInContext(const std::string &context, const std::string &name) const;

        bool contextExist(const std::string &name) const;

        VarType getVarType(const core::ValueModel<T> *valueModel) const;

        static std::string buildContextKey(const std::string &context, const std::string &name);

        static void buildFuzzyOperatorCollection(std::map<std::string, core::CoreObject<T> *> &map,
                                                 const std::string &context);

    public:
        FuzzyInterpreter();

        ~FuzzyInterpreter();

        void execute(const std::string &line) override;
    };

    template<typename T>
    void FuzzyInterpreter<T>::execute(const std::string &line) {

        std::string instruction = AbstractInterpreter<T>::extractFirstArgument(line);

        std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(line);

        args.erase(args.begin());

        if (instruction == INTERPRETER_CREATE_FUZZY_SYSTEM_COMMAND) {

            createFuzzySystem(args);

        } else if (instruction == INTERPRETER_VAR_DECLARATION_COMMAND) {

            createVar(args);

        } else if (instruction == INTERPRETER_COMPUTE_COMMAND) {

            compute(args);

        } else if (instruction == INTERPRETER_DEFINITION_COMMAND) {

            definition(args);

        } else {
            throw exception::InterpreterException("Invalid command : " + instruction);
        }
    }

    template<typename T>
    FuzzyInterpreter<T>::FuzzyInterpreter() = default;

    template<typename T>
    FuzzyInterpreter<T>::~FuzzyInterpreter() {

        for (auto pair : fuzzyOperatorContext) {
            delete pair.second;
        }

        for (auto pair : factoryContext) {
            delete pair.second;
        }

        for (auto pair : varContext) {
            delete pair.second;
        }

        for (auto pair : definitionsContext) {
            delete pair.second;
        }
    }

    template<typename T>
    void FuzzyInterpreter<T>::createFuzzySystem(std::vector<std::string> &args) {

        if (args.size() < 2) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string defuzzType = args[1];
        std::string contextName = args[0];

        buildFuzzyOperatorCollection(fuzzyOperatorContext, contextName);

        args.erase(++args.begin());

        fuzzy::FuzzyFactory<T> *factory = nullptr;

        if (defuzzType == INTERPRETER_TYPE_COG) {
            factory = createCogFactory(args);
        } else if (defuzzType == INTERPRETER_TYPE_SUGENO) {
            factory = createSugenoFactory(args);
        }

        factoryContext[contextName] = factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createCogFactory(std::vector<std::string> &args) {

        if (args.size() != 6) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = args[0];

        for (unsigned int i = 1; i < args.size(); i++) {
            if (!operatorExistInContext(context, args[i])) {
                throw exception::InterpreterException("Error : " + args[i] + " not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildContextKey(context, args[1])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildContextKey(context, args[2])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildContextKey(context, args[3])]);
        auto opThen = dynamic_cast<fuzzy::Then<T> *>(fuzzyOperatorContext[buildContextKey(context, args[4])]);
        auto opAgg = dynamic_cast<fuzzy::Agg<T> *>(fuzzyOperatorContext[buildContextKey(context, args[5])]);
        auto opCogDefuzz = dynamic_cast<fuzzy::MamdaniDefuzz<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                        INTERPRETER_COG_DEFUZZ_NAME)]);


        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opThen, opAgg, opCogDefuzz);

        factoryType[factory] = COG;

        return factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createSugenoFactory(std::vector<std::string> &args) {

        if (args.size() != 4) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = args[0];

        for (unsigned int i = 1; i < args.size(); i++) {
            if (!operatorExistInContext(context, args[i])) {
                throw exception::InterpreterException("Error : " + args[i] + " not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildContextKey(context, args[1])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildContextKey(context, args[2])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildContextKey(context, args[3])]);
        auto opSugenoThen = dynamic_cast<fuzzy::SugenoThen<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                      INTERPRETER_SUGENO_THEN_NAME)]);
        auto opSugenoDefuzz = dynamic_cast<fuzzy::SugenoDefuzz<T> *>(fuzzyOperatorContext[buildContextKey(context,
                                                                                                          INTERPRETER_SUGENO_DEFUZZ_NAME)]);
        auto opSugenoConclusion = dynamic_cast<fuzzy::SugenoConclusion<T> *>(fuzzyOperatorContext[buildContextKey(
                context, INTERPRETER_SUGENO_CONCLUSION_NAME)]);

        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opSugenoThen, opSugenoDefuzz,
                                                  opSugenoConclusion);
        factoryType[factory] = SUGENO;

        return factory;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::operatorExistInContext(const std::string &context, const std::string &name) const {

        std::string key = buildContextKey(context, name);

        return fuzzyOperatorContext.find(key) != fuzzyOperatorContext.end();
    }

    template<typename T>
    bool FuzzyInterpreter<T>::contextExist(const std::string &name) const {

        return factoryContext.find(name) != factoryContext.end();
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::buildContextKey(const std::string &context, const std::string &name) {

        return context + INTERPRETER_CONTEXT_ACCESS + name;
    }

    template<typename T>
    void FuzzyInterpreter<T>::buildFuzzyOperatorCollection(std::map<std::string, core::CoreObject<T> *> &map,
                                                           const std::string &context) {

        map[buildContextKey(context, INTERPRETER_OR_MAX_NAME)] = new fuzzy::OrMax<T>();
        map[buildContextKey(context, INTERPRETER_AGG_MAX_NAME)] = new fuzzy::AggMax<T>();
        map[buildContextKey(context, INTERPRETER_NOT_MIN_NAME)] = new fuzzy::NotMinus1<T>();
        map[buildContextKey(context, INTERPRETER_AND_MIN_NAME)] = new fuzzy::AndMin<T>();
        map[buildContextKey(context, INTERPRETER_THEN_MIN_NAME)] = new fuzzy::ThenMin<T>();
        map[buildContextKey(context, INTERPRETER_COG_DEFUZZ_NAME)] = new fuzzy::CogDefuzz<T>();
    }

    template<typename T>
    void FuzzyInterpreter<T>::createVar(std::vector<std::string> &args) {

        if (args.size() != 2) {
            throw exception::InterpreterException("Var required two argument <Type> <name>");
        }

        std::string varTypeName = args[0];
        std::string completeName = args[1];

        std::vector<std::string> contextAndName = AbstractInterpreter<T>::lineToArgs(
                AbstractInterpreter<T>::stringReplace(completeName,
                                                      INTERPRETER_CONTEXT_ACCESS,
                                                      " "));

        if (contextAndName.size() != 2) {
            throw exception::InterpreterException("Invalid var name : " + completeName);
        }

        if (!contextExist(contextAndName[0])) {
            throw exception::InterpreterException("Context name : " + contextAndName[0]);
        }

        VarType type = Error;

        if (varTypeName == INTERPRETER_INPUT_TYPE) {
            type = Input;
        } else if (varTypeName == INTERPRETER_OUTPUT_TYPE) {
            type = Output;
        } else {
            throw exception::InterpreterException("Invalid type name " + varTypeName);
        }

        auto valueModel = new core::ValueModel<T>();

        varContext[completeName] = valueModel;

        varType[valueModel] = type;
    }

    template<typename T>
    void FuzzyInterpreter<T>::compute(std::vector<std::string> &args) {

        if (!args.empty()) {
            throw exception::InterpreterException("Invalid Compute argument number, required zero");
        }


    }

    template<typename T>
    typename FuzzyInterpreter<T>::VarType FuzzyInterpreter<T>::getVarType(const core::ValueModel<T> *valueModel) const {

        auto it = varType.find(valueModel);

        return (it != varType.end()) ? it->second : Error;
    }

    template<typename T>
    void FuzzyInterpreter<T>::definition(std::vector<std::string> &args) {

        if (args.empty()) {
            throw exception::InterpreterException("Definition command required more arguments");
        }


    }
}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H