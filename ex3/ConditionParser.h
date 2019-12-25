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

class ConditionParser: public Command {

 protected:
  int listLength;

 private:
  Expression* condition;
  class Parser* parser;
  Expression* updateCondition(std::list<std::string>* L);
  std::map<std::string, SymbolTableValue*> LoopSymbolTable;
  std::map<std::string, float> LoopLocalSymbolTable;

 public:
  explicit ConditionParser(std::list<std::string>* strList);
  double isConditionSatisfied();

  ~ConditionParser();
  int execute(std::list<std::string> L) override;
  void startOver(int i);
  int get_num_of_arg() override;
};

#endif //EX3_COMMANDS_CONDITIONPARSER_H_
