//
// Created by gadi on 17/12/2019.
//

#ifndef EX3_COMMANDS_DEFINEVARCOMMAND_H_
#define EX3_COMMANDS_DEFINEVARCOMMAND_H_

#include "Command.h"
#include "../SimulatorManager.h"

using namespace std;
class DefineVarCommand : public Command {

 public:
  int execute(list<string> list_of_strings) override;
  int get_num_of_arg() override {return 4;};
  string removeSpaces(string str);
};

#endif //EX3_COMMANDS_DEFINEVARCOMMAND_H_