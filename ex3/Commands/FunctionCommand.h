//
// Created by ori294 on 12/17/19.
//

#ifndef EX3_COMMANDS_FUNCTIONCOMMAND_H_
#define EX3_COMMANDS_FUNCTIONCOMMAND_H_

#include "Command.h"
#include "../SimulatorManager.h"

class FunctionCommand : public Command {
 private:
  std::list<std::string> commandList;
  std::string funcVariable;
  class Parser* parser;

 public:
  FunctionCommand(std::list<std::string> L);
  int execute(std::list<std::string> L);
  int get_num_of_arg();
};

#endif //EX3_COMMANDS_FUNCTIONCOMMAND_H_
