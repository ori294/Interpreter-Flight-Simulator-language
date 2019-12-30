//
// Created by ori294 on 12/18/19.
//

#ifndef EX3_COMMANDS_CONDITIONPARSER_H_
#define EX3_COMMANDS_CONDITIONPARSER_H_

#include "SymbolTableValue.h"
#include "Command.h"
#include "Interpreter.h"
#include "SimulatorManager.h"
#include "ExpressionKinds.h"
#include "Expression.h"

/**
 * ConditionParser: for method documentation please refer to .cpp
 */
class ConditionParser: public Command {

 protected:
  int listLength; //command list length

 private:
  Expression* condition;
  class Parser* parser;
  Expression* updateCondition(std::list<std::string>* L);

 public:
  explicit ConditionParser(std::list<std::string>* strList);
  double isConditionSatisfied();

  ~ConditionParser();
  int execute(std::list<std::string> L) override;
  void startOver(int i);
  int get_num_of_arg() override;
};

#endif //EX3_COMMANDS_CONDITIONPARSER_H_
