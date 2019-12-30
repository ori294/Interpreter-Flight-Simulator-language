//
// Created by ori294 on 12/22/19.
//

#ifndef EX3_COMMANDS_IFCOMMAND_H_
#define EX3_COMMANDS_IFCOMMAND_H_

#include "Command.h"
#include "SimulatorManager.h"
#include "ConditionParser.h"

/**
 * IfCommand: for method documentation please refer to .cpp
 */
class IfCommand : public  ConditionParser {
  int execute(std::list<std::string> L);
  int get_num_of_arg();

 public:
  IfCommand(std::list<std::string>* L);
  //destructor is left as default.
};

#endif //EX3_COMMANDS_IFCOMMAND_H_
