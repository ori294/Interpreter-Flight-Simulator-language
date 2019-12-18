//
// Created by ori294 on 12/18/19.
//

#ifndef EX3_COMMANDS_LOOPCOMMAND_H_
#define EX3_COMMANDS_LOOPCOMMAND_H_

#include "Command.h"
#include "ConditionParser.h"
#include "../SimulatorManager.h"
#include "../SymbolTableValue.h"

class LoopCommand: public Command {

 private:
  std::map<std::string, SymbolTableValue*> LoopSymbolTable;
  std::map<std::string, float> LoopLocalSymbolTable;
  ConditionParser* parser;
  int execute(std::list<std::string> L) override;
  int get_num_of_arg() override {return 1;}

 public:
  LoopCommand();
};

#endif //EX3_COMMANDS_LOOPCOMMAND_H_
