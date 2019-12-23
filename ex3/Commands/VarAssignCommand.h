//
// Created by ori294 on 12/17/19.
//

#ifndef EX3_COMMANDS_VARASSIGNCOMMAND_H_
#define EX3_COMMANDS_VARASSIGNCOMMAND_H_
#include "Command.h"
#include "../SimulatorManager.h"

class VarAssignCommand: public Command {
 public:
  int execute(std::list<std::string> list_of_strings) override;
  int get_num_of_arg() override {return 2;};
};

#endif //EX3_COMMANDS_VARASSIGNCOMMAND_H_
