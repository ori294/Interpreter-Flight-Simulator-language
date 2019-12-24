//
// Created by ori294 on 12/11/19.
//

#ifndef EX3_COMMANDS_SINGLECOMMANDS_H_
#define EX3_COMMANDS_SINGLECOMMANDS_H_
#include "Command.h"
#include "../SimulatorManager.h"
#include "Expressions/Expression.h"
#include "Expressions/Interpreter.h"
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <string>

class PrintCommand: public Command {
  int get_num_of_arg() override {return 1;}
  int execute(std::list<std::string> comList) override;
};

class SleepCommand: public Command {

  int get_num_of_arg() override {return 1;}

  int execute(std::list<std::string> comList) override;
};

class NullCommand: public Command {
  int get_num_of_arg() override {return -1;}
  int execute(std::list<std::string> comList) override {
    //do nothing
  }
};


#endif //EX3_COMMANDS_SINGLECOMMANDS_H_
