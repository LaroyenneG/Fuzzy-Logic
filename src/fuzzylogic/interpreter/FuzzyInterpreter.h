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
#include "IsTriangle.h"

#include <stack>


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
#define INTERPRETER_RULES_COMMAND "Rules"
#define INTERPRETER_BUILD_SYSTEM_COMMAND "Build"
#define INTERPRETER_DEFINITION_COMMAND "Define"
#define INTERPRETER_DEFINITION_TRIANGLE "Triangle"
#define INTERPRETER_RULE_IF "If"
#define INTERPRETER_RULE_THEN "Then"
#define INTERPRETER_RULE_AND "And"
#define INTERPRETER_RULE_OR "Or"
#define INTERPRETER_RULE_NOT "Not"
#define INTERPRETER_RULE_IS "Is"
#define INTERPRETER_RULE_OPEN_EXPRESSION_CHAR '('
#define INTERPRETER_RULE_CLOSE_EXPRESSION_CHAR ')'




namespace fuzzylogic::interpreter {

    template<typename T>
    class FuzzyInterpreter : public AbstractInterpreter<T> {

    protected:
        typedef enum {
            MAMDANI,
            SUGENO
        } DefuzzType;
        typedef enum {
            OUTPUT_VAR,
            INPUT_VAR,
            Error
        } VarType;

    private:
        std::map<std::string, core::CoreObject<T> *> fuzzyOperatorContext;

        std::map<std::string, fuzzy::FuzzyFactory<T> *> factoryContext;

        std::map<const fuzzy::FuzzyFactory<T> *, DefuzzType> factoryType;

        std::map<std::string, core::ValueModel<T> *> variableContextAndName;

        std::map<const core::ValueModel<T> *, VarType> variableType;

        std::map<std::string, fuzzy::Is<T> *> definitionsContextAndName;

        std::map<std::string, std::vector<std::string>> rulesContext;

        std::map<std::string, core::Expression<T> *> systemContext;

    protected:
        core::Expression<T> *
        convertStringRuleToExpression(fuzzy::FuzzyFactory<T> *factory, const std::string &stringRule,
                                      const std::string &context);

        void buildMamdaniSystem(std::vector<std::string> args);

        void buildSugenoSystem(std::vector<std::string> args);

        bool nameIsAlreadyUsed(const std::string &name) const;

        void fullNameContextVerification(const std::string &fullName) const;

        void createFuzzySystem(std::vector<std::string> args);

        fuzzy::FuzzyFactory<T> *createCogFactory(std::vector<std::string> args);

        fuzzy::FuzzyFactory<T> *createSugenoFactory(std::vector<std::string> args);

        void createVariable(std::vector<std::string> args);

        void compute(std::vector<std::string> args);

        void createDefinition(std::vector<std::string> args);

        fuzzy::IsTriangle<T> *createTriangle(std::vector<std::string> args);

        bool operatorExistInContext(const std::string &context, const std::string &name) const;

        bool contextExist(const std::string &name) const;

        bool definitionExist(const std::string &name) const;

        bool variableExist(const std::string &name) const;

        VarType findVariableType(const core::ValueModel<T> *valueModel) const;

        std::string findOutputInContext(const std::string &context);

        std::vector<std::string> findInputsInContext(const std::string &context);

        bool operatorExist(const std::string &name) const;

        void createRules(std::vector<std::string> args);

        void buildSystem(std::vector<std::string> args);

        static std::string buildKeyWithContextAndName(const std::string &context, const std::string &name);

        static void buildFuzzyOperatorCollection(std::map<std::string, core::CoreObject<T> *> &map,
                                                 const std::string &context);

        static std::string extractLeftMemberInStringRule(const std::string &stringRule);

        static std::string extractRightMemberInStringRule(const std::string &stringRule);

        static std::string extractOperatorMemberInStringRule(const std::string &stringRule);

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

            createVariable(args);

        } else if (instruction == INTERPRETER_COMPUTE_COMMAND) {

            compute(args);

        } else if (instruction == INTERPRETER_DEFINITION_COMMAND) {

            createDefinition(args);

        } else if (instruction == INTERPRETER_RULES_COMMAND) {

            createRules(args);

        } else if (instruction == INTERPRETER_BUILD_SYSTEM_COMMAND) {

            buildSystem(args);

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

        for (auto pair : variableContextAndName) {
            delete pair.second;
        }

        for (auto pair : definitionsContextAndName) {
            delete pair.second;
        }
    }

    template<typename T>
    void FuzzyInterpreter<T>::createFuzzySystem(std::vector<std::string> args) {

        if (args.size() < 2) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string defuzzType = args[1];
        std::string contextName = args[0];

        if (contextExist(contextName)) {
            throw exception::InterpreterException("Fuzzy system name already used : " + contextName);
        }


        buildFuzzyOperatorCollection(fuzzyOperatorContext, contextName);

        args.erase(++args.begin());

        fuzzy::FuzzyFactory<T> *factory = nullptr;

        if (defuzzType == INTERPRETER_TYPE_COG) {
            factory = createCogFactory(args);
        } else if (defuzzType == INTERPRETER_TYPE_SUGENO) {
            factory = createSugenoFactory(args);
        } else {
            throw exception::InterpreterException("Un know " + defuzzType + "defuzzyfication");
        }

        factoryContext[contextName] = factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createCogFactory(std::vector<std::string> args) {

        if (args.size() != 6) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = args[0];

        for (unsigned int i = 1; i < args.size(); i++) {
            if (!operatorExistInContext(context, args[i])) {
                throw exception::InterpreterException("Error : " + args[i] + " not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[1])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[2])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[3])]);
        auto opThen = dynamic_cast<fuzzy::Then<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context,
                                                                                                     args[4])]);
        auto opAgg = dynamic_cast<fuzzy::Agg<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[5])]);
        auto opCogDefuzz = dynamic_cast<fuzzy::MamdaniDefuzz<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(
                context,
                INTERPRETER_COG_DEFUZZ_NAME)]);


        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opThen, opAgg, opCogDefuzz);

        factoryType[factory] = MAMDANI;

        return factory;
    }

    template<typename T>
    fuzzy::FuzzyFactory<T> *FuzzyInterpreter<T>::createSugenoFactory(std::vector<std::string> args) {

        if (args.size() != 4) {
            throw exception::InterpreterException("Not enough arguments");
        }

        std::string context = args[0];

        for (unsigned int i = 1; i < args.size(); i++) {
            if (!operatorExistInContext(context, args[i])) {
                throw exception::InterpreterException("Error : " + args[i] + " not exist");
            }
        }

        auto opNot = dynamic_cast<fuzzy::Not<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[1])]);
        auto opAnd = dynamic_cast<fuzzy::And<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[2])]);
        auto opOr = dynamic_cast<fuzzy::Or<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(context, args[3])]);
        auto opSugenoThen = dynamic_cast<fuzzy::SugenoThen<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(
                context,
                INTERPRETER_SUGENO_THEN_NAME)]);
        auto opSugenoDefuzz = dynamic_cast<fuzzy::SugenoDefuzz<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(
                context,
                INTERPRETER_SUGENO_DEFUZZ_NAME)]);
        auto opSugenoConclusion = dynamic_cast<fuzzy::SugenoConclusion<T> *>(fuzzyOperatorContext[buildKeyWithContextAndName(
                context, INTERPRETER_SUGENO_CONCLUSION_NAME)]);

        auto factory = new fuzzy::FuzzyFactory<T>(opNot, opAnd, opOr, opSugenoThen, opSugenoDefuzz,
                                                  opSugenoConclusion);
        factoryType[factory] = SUGENO;

        return factory;
    }

    template<typename T>
    bool FuzzyInterpreter<T>::operatorExistInContext(const std::string &context, const std::string &name) const {

        std::string key = buildKeyWithContextAndName(context, name);

        return fuzzyOperatorContext.find(key) != fuzzyOperatorContext.end();
    }

    template<typename T>
    bool FuzzyInterpreter<T>::contextExist(const std::string &name) const {

        return factoryContext.find(name) != factoryContext.end();
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::buildKeyWithContextAndName(const std::string &context, const std::string &name) {

        return context + INTERPRETER_CONTEXT_ACCESS + name;
    }

    template<typename T>
    void FuzzyInterpreter<T>::buildFuzzyOperatorCollection(std::map<std::string, core::CoreObject<T> *> &map,
                                                           const std::string &context) {

        map[buildKeyWithContextAndName(context, INTERPRETER_OR_MAX_NAME)] = new fuzzy::OrMax<T>();
        map[buildKeyWithContextAndName(context, INTERPRETER_AGG_MAX_NAME)] = new fuzzy::AggMax<T>();
        map[buildKeyWithContextAndName(context, INTERPRETER_NOT_MIN_NAME)] = new fuzzy::NotMinus1<T>();
        map[buildKeyWithContextAndName(context, INTERPRETER_AND_MIN_NAME)] = new fuzzy::AndMin<T>();
        map[buildKeyWithContextAndName(context, INTERPRETER_THEN_MIN_NAME)] = new fuzzy::ThenMin<T>();
        map[buildKeyWithContextAndName(context, INTERPRETER_COG_DEFUZZ_NAME)] = new fuzzy::CogDefuzz<T>();
    }

    template<typename T>
    void FuzzyInterpreter<T>::createVariable(std::vector<std::string> args) {

        if (args.size() != 2) {
            throw exception::InterpreterException("Var required two argument <Type> <name>");
        }

        std::string varTypeName = args[0];
        std::string fullName = args[1];

        fullNameContextVerification(fullName);

        if (nameIsAlreadyUsed(fullName)) {
            throw exception::InterpreterException("Name already exist : " + fullName);
        }

        VarType type = Error;

        if (varTypeName == INTERPRETER_INPUT_TYPE) {
            type = INPUT_VAR;
        } else if (varTypeName == INTERPRETER_OUTPUT_TYPE) {
            type = OUTPUT_VAR;
        } else {
            throw exception::InterpreterException("Invalid type name " + varTypeName);
        }

        auto valueModel = new core::ValueModel<T>();

        variableContextAndName[fullName] = valueModel;

        variableType[valueModel] = type;
    }

    template<typename T>
    void FuzzyInterpreter<T>::compute(std::vector<std::string> args) {

        if (!args.empty()) {
            throw exception::InterpreterException("Invalid compute argument number, required zero");
        }

        for (auto pair : factoryContext) {

            const std::string &context = pair.first;

            if (systemContext.find(context) != systemContext.end()) {

                std::vector<std::string> inputs = findInputsInContext(context);

                for (auto input : inputs) {

                    try {
                        T value(AbstractInterpreter<T>::readInMemory(AbstractInterpreter<T>::INPUT, input));

                        variableContextAndName[input]->setValue(value);

                    } catch (std::invalid_argument &e) {
                        std::cerr << "Attention, cannot read " + input + " value" << std::endl;
                    }
                }

                const core::Expression<T> *system = systemContext[context];

                T result = system->evaluate();

                std::string output = findOutputInContext(context);

                AbstractInterpreter<T>::writeInMemory(AbstractInterpreter<T>::OUTPUT, output, result);
            }
        }
    }

    template<typename T>
    typename FuzzyInterpreter<T>::VarType
    FuzzyInterpreter<T>::findVariableType(const core::ValueModel<T> *valueModel) const {

        auto it = variableType.find(valueModel);

        return (it != variableType.end()) ? it->second : Error;
    }

    template<typename T>
    void FuzzyInterpreter<T>::createDefinition(std::vector<std::string> args) {

        if (args.size() < 2) {
            throw exception::InterpreterException("Definition command required more arguments");
        }

        std::string fullName = args[1];

        fullNameContextVerification(fullName);

        if (nameIsAlreadyUsed(fullName)) {
            throw exception::InterpreterException("Name already exist : " + fullName);
        }

        std::string typeName = args[0];

        fuzzy::Is<T> *is = nullptr;

        args.erase(args.begin());
        args.erase(args.begin());

        if (typeName == INTERPRETER_DEFINITION_TRIANGLE) {

            is = createTriangle(args);

            /*
             * } else if(...) {
             * to complete
             */

        } else {
            throw exception::InterpreterException("Invalid definition type : " + typeName);
        }

        definitionsContextAndName[fullName] = is;
    }

    template<typename T>
    fuzzy::IsTriangle<T> *FuzzyInterpreter<T>::createTriangle(std::vector<std::string> args) {

        if (args.size() != 3) {
            throw exception::InterpreterException("Definition command required 3 arguments (min, middle, max)");
        }

        std::stringstream stringstream;
        for (const auto &arg : args) {
            stringstream << arg << std::endl;
        }

        T min(INFINITY);
        T middle(INFINITY);
        T max(INFINITY);

        stringstream >> min;
        stringstream >> middle;
        stringstream >> max;

        if (min == INFINITY || max == INFINITY || middle == INFINITY) {
            throw exception::InterpreterException("Invalid number format...");
        }

        return new fuzzy::IsTriangle<T>(min, middle, max);
    }

    template<typename T>
    void FuzzyInterpreter<T>::fullNameContextVerification(const std::string &fullName) const {

        std::vector<std::string> contextAndName = AbstractInterpreter<T>::lineToArgs(
                AbstractInterpreter<T>::stringReplace(fullName,
                                                      INTERPRETER_CONTEXT_ACCESS,
                                                      std::string(1, INTERPRETER_CHAR_TO_SPLIT_LINE)));

        if (contextAndName.size() != 2) {
            throw exception::InterpreterException("Invalid variable name : " + fullName);
        }

        if (!contextExist(contextAndName[0])) {
            throw exception::InterpreterException(
                    "Invalid variable context name : " + contextAndName[0] + " in " + fullName);
        }
    }

    template<typename T>
    bool FuzzyInterpreter<T>::nameIsAlreadyUsed(const std::string &name) const {

        return operatorExist(name) || variableExist(name) || definitionExist(name) || contextExist(name);
    }

    template<typename T>
    bool FuzzyInterpreter<T>::definitionExist(const std::string &name) const {

        return definitionsContextAndName.find(name) != definitionsContextAndName.end();
    }

    template<typename T>
    bool FuzzyInterpreter<T>::variableExist(const std::string &name) const {

        return variableContextAndName.find(name) != variableContextAndName.end();
    }

    template<typename T>
    bool FuzzyInterpreter<T>::operatorExist(const std::string &name) const {

        return fuzzyOperatorContext.find(name) != fuzzyOperatorContext.end();
    }

    template<typename T>
    void FuzzyInterpreter<T>::createRules(std::vector<std::string> args) {

        if (args.size() < 2) {
            throw exception::InterpreterException("Rules command requires more than two arguments");
        }

        std::string context = args[0];

        if (!contextExist(context)) {
            throw exception::InterpreterException("Invalid context : " + context);
        }

        if (rulesContext.find(context) != rulesContext.end()) {
            throw exception::InterpreterException("Rules already created");
        }

        args.erase(args.begin());

        std::vector<std::string> rules;

        for (unsigned int i = 0; i < args.size(); ++i) {

            std::string rule;

            while (i < args.size()) {

                if (args[i] == INTERPRETER_RULE_IF) {
                    break;
                }

                if (!rule.empty()) {
                    rule += INTERPRETER_CHAR_TO_SPLIT_LINE;
                }

                rule += args[i];

                i++;
            }

            if (!rule.empty()) {
                rules.push_back(AbstractInterpreter<T>::stringTrim(rule));
            }
        }

        rulesContext[context] = rules;
    }

    template<typename T>
    void FuzzyInterpreter<T>::buildSystem(std::vector<std::string> args) {

        if (args.empty()) {
            throw exception::InterpreterException("Missing context name to build");
        }

        std::string context = args[0];

        if (!contextExist(context)) {
            throw exception::InterpreterException("Invalid context : " + context);
        }

        if (rulesContext.find(context) == rulesContext.end()) {
            throw exception::InterpreterException("No rules in context : " + context);
        }

        if (systemContext.find(context) != systemContext.end()) {
            throw exception::InterpreterException("Fuzzy system " + context + " already build");
        }

        fuzzy::FuzzyFactory<T> *factory = factoryContext[context];
        DefuzzType type = factoryType[factory];

        switch (type) {

            case MAMDANI:
                buildMamdaniSystem(args);
                break;

            case SUGENO:
                buildSugenoSystem(args);
                break;

            default:
                std::cerr << "the impossible has happened" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    template<typename T>
    void FuzzyInterpreter<T>::buildMamdaniSystem(std::vector<std::string> args) {

        if (args.size() != 4) {
            throw exception::InterpreterException("missing <start> <end> <step> parameters");
        }

        std::string context = args[0];

        args.erase(args.begin());

        T start(INFINITY);
        T end(INFINITY);
        T step(INFINITY);

        std::stringstream stringstream;

        for (const auto &arg : args) {
            stringstream << arg << std::endl;
        }

        stringstream >> start;
        stringstream >> end;
        stringstream >> step;

        if (start == INFINITY || end == INFINITY || step == INFINITY) {
            throw exception::InterpreterException("Invalid format number");
        }

        fuzzy::FuzzyFactory<T> *factory = factoryContext[context];

        std::string outputKey = findOutputInContext(context);

        if (outputKey.empty()) {
            throw exception::InterpreterException("cannot build, missing output");
        }

        core::ValueModel<T> *output = variableContextAndName[outputKey];

        core::Expression<T> *rules = nullptr;

        const std::vector<std::string> &stringRules = rulesContext[context]; // cannot not existing (tested before function)

        for (const auto &stringRule : stringRules) {

            core::Expression<T> *rule = convertStringRuleToExpression(factory, stringRule, context);

            if (rules == nullptr) {
                rules = rule;
            } else {
                rules = factory->newAgg(rules, rule);
            }
        }

        if (rules == nullptr) {
            throw exception::InterpreterException("Rules are empty !");
        }

        core::Expression<T> *system = factory->newMamdaniDefuzz(output, rules, start, end, step);

        systemContext[context] = system;
    }

    template<typename T>
    void FuzzyInterpreter<T>::buildSugenoSystem(std::vector<std::string> args) {

        if (args.empty()) {

        }

        /* to complete */
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::findOutputInContext(const std::string &context) {

        std::string outputKey;

        for (auto pair : variableContextAndName) {

            const std::string &variableFullName = pair.first;

            std::vector<std::string> contextAndName = AbstractInterpreter<T>::lineToArgs(
                    AbstractInterpreter<T>::stringReplace(variableFullName, INTERPRETER_CONTEXT_ACCESS,
                                                          std::string(1, INTERPRETER_CHAR_TO_SPLIT_LINE)));

            if (!contextAndName.empty() && contextAndName[0] == context) {

                const core::ValueModel<T> *valueModel = variableContextAndName[variableFullName];

                if (findVariableType(valueModel) == OUTPUT_VAR) {

                    if (!outputKey.empty()) {
                        throw exception::InterpreterException("Multiple output in : " + context);
                    }

                    outputKey = variableFullName;
                }
            }
        }

        return outputKey;
    }

    template<typename T>
    std::vector<std::string> FuzzyInterpreter<T>::findInputsInContext(const std::string &context) {

        std::vector<std::string> inputs;

        for (auto pair : variableContextAndName) {

            const std::string &variableFullName = pair.first;

            std::vector<std::string> contextAndName = AbstractInterpreter<T>::lineToArgs(
                    AbstractInterpreter<T>::stringReplace(variableFullName, INTERPRETER_CONTEXT_ACCESS,
                                                          std::string(1, INTERPRETER_CHAR_TO_SPLIT_LINE)));

            if (!contextAndName.empty() && contextAndName[0] == context) {

                const core::ValueModel<T> *valueModel = variableContextAndName[variableFullName];

                if (findVariableType(valueModel) == INPUT_VAR) {
                    inputs.push_back(variableFullName);
                }
            }
        }

        return inputs;
    }

    template<typename T>
    core::Expression<T> *
    FuzzyInterpreter<T>::convertStringRuleToExpression(fuzzy::FuzzyFactory<T> *factory, const std::string &stringRule,
                                                       const std::string &context) {

        core::Expression<T> *expression = nullptr;

        if (stringRule.size() < 2 || stringRule.front() != INTERPRETER_RULE_OPEN_EXPRESSION_CHAR ||
            stringRule.back() != INTERPRETER_RULE_CLOSE_EXPRESSION_CHAR) {

            std::string variableKey = buildKeyWithContextAndName(context, stringRule);

            if (!variableExist(variableKey)) {
                throw exception::InterpreterException("Un known variable : " + stringRule);
            }

            expression = variableContextAndName[variableKey];

        } else {

            std::string expressionString = stringRule;
            expressionString.erase(expressionString.begin());
            expressionString.pop_back();

            std::string stringLeft = extractLeftMemberInStringRule(expressionString);
            std::string stringRight = extractRightMemberInStringRule(expressionString);
            std::string stringOperator = extractOperatorMemberInStringRule(expressionString);

            if (stringOperator == INTERPRETER_RULE_THEN) {

                expression = factory->newThen(convertStringRuleToExpression(factory, stringLeft, context),
                                              convertStringRuleToExpression(factory, stringRight, context));

            } else if (stringOperator == INTERPRETER_RULE_OR) {

                expression = factory->newOr(convertStringRuleToExpression(factory, stringLeft, context),
                                            convertStringRuleToExpression(factory, stringRight, context));

            } else if (stringOperator == INTERPRETER_RULE_AND) {

                expression = factory->newAnd(convertStringRuleToExpression(factory, stringLeft, context),
                                             convertStringRuleToExpression(factory, stringRight, context));

            } else if (stringOperator == INTERPRETER_RULE_NOT) {

                if (!stringLeft.empty()) {
                    throw exception::InterpreterException(
                            "Invalid rule : " + stringRule + " not operator haven't left operand " + stringLeft);
                }

                expression = factory->newNot(convertStringRuleToExpression(factory, stringRight, context));

            } else if (stringOperator == INTERPRETER_RULE_IS) {

                std::string definitionKey = buildKeyWithContextAndName(context, stringRight);

                if (!definitionExist(definitionKey)) {
                    throw exception::InterpreterException("Un known shape : " + stringRight);
                }


                fuzzy::Is<T> *shape = definitionsContextAndName[definitionKey];

                expression = factory->newIs(shape, convertStringRuleToExpression(factory, stringLeft, context));

                /*
                 * } else if (..) {
                 *
                 * to complete
                 *
                 */

            } else {
                throw exception::InterpreterException(
                        "Invalid rule : " + stringRule + " un known operator " + stringOperator);
            }
        }

        return expression;
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::extractLeftMemberInStringRule(const std::string &stringRule) {

        std::string sLeft;

        if (!stringRule.empty()) {

            int cursor = 0;
            unsigned int index = 0;

            if (stringRule[index] == INTERPRETER_RULE_OPEN_EXPRESSION_CHAR) {

                do {
                    if (stringRule[index] == INTERPRETER_RULE_OPEN_EXPRESSION_CHAR) {
                        cursor++;
                    }

                    if (stringRule[index] == INTERPRETER_RULE_CLOSE_EXPRESSION_CHAR) {
                        cursor--;
                    }

                    sLeft += stringRule[index];

                    index++;

                } while (index < stringRule.size() && cursor > 0);

            } else {

                std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(stringRule);

                if (args.size() == 3) {
                    sLeft = args.front();
                }
            }
        }

        return AbstractInterpreter<T>::stringTrim(sLeft);
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::extractRightMemberInStringRule(const std::string &stringRule) {

        std::string sRight;

        if (!stringRule.empty()) {

            int cursor = 0;
            unsigned int index = stringRule.size() - 1;

            if (stringRule[index] == INTERPRETER_RULE_CLOSE_EXPRESSION_CHAR) {

                do {
                    if (stringRule[index] == INTERPRETER_RULE_OPEN_EXPRESSION_CHAR) {
                        cursor--;
                    }

                    if (stringRule[index] == INTERPRETER_RULE_CLOSE_EXPRESSION_CHAR) {
                        cursor++;
                    }

                    sRight = stringRule[index] + sRight;

                    index--;

                } while (index >= 0 && cursor > 0);
            } else {

                std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(stringRule);

                if (args.size() >= 2) {
                    sRight = args.back();
                }
            }
        }


        return AbstractInterpreter<T>::stringTrim(sRight);
    }

    template<typename T>
    std::string FuzzyInterpreter<T>::extractOperatorMemberInStringRule(const std::string &stringRule) {

        std::string sOperator;


        if (!stringRule.empty()) {

            int cursor = 0;
            unsigned int index = 0;

            if (stringRule[index] == INTERPRETER_RULE_OPEN_EXPRESSION_CHAR) {

                do {
                    if (stringRule[index] == INTERPRETER_RULE_OPEN_EXPRESSION_CHAR) {
                        cursor++;
                    }

                    if (stringRule[index] == INTERPRETER_RULE_CLOSE_EXPRESSION_CHAR) {
                        cursor--;
                    }

                    index++;

                } while (index < stringRule.size() && cursor > 0);
            }

            while (index < stringRule.size()) {

                if (stringRule[index] == INTERPRETER_RULE_OPEN_EXPRESSION_CHAR) {
                    break;
                }

                sOperator += stringRule[index];

                index++;
            }

            if (sOperator.find(INTERPRETER_CHAR_TO_SPLIT_LINE) != std::string::npos) {

                std::vector<std::string> args = AbstractInterpreter<T>::lineToArgs(sOperator);

                if (args.size() <= 3) {
                    sOperator = args[args.size() / 2];
                }
            }
        }

        return AbstractInterpreter<T>::stringTrim(sOperator);
    }
}

#endif //LOGIQUEFLOUE_FUZZYMONITOR_H