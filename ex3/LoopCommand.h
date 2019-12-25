//
// Created by ori294 on 12/18/19.
//

#ifndef EX3_COMMANDS_LOOPCOMMAND_H_
#define EX3_COMMANDS_LOOPCOMMAND_H_

#include "Command.h"
#include "SimulatorManager.h"
#include "ConditionParser.h"

 class LoopCommand: public ConditionParser {

  int execute(std::list<std::string> L);
  int get_num_of_arg();

 public:
  LoopCommand(std::list<std::string>* L);
  //~LoopCommand(); //Delete father
};

#endif //EX3_COMMANDS_LOOPCOMMAND_H_
