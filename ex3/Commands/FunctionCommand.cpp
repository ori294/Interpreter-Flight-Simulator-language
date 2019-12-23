//
// Created by ori294 on 12/17/19.
//

#include "FunctionCommand.h"


FunctionCommand::FunctionCommand(std::list<std::string> comms) {
  commandList = comms;
  this->parser = new Parser(commandList);

  auto iter = comms.begin();
  iter++; iter++;

  this->funcVariable = *iter;
}

int FunctionCommand::execute(std::list<std::string> vars) {
  this->parser->startOver(4);
  while (!this->parser->isEnded()) {
    auto tempPair = parser->getNextCommand();
    if (tempPair.first != nullptr && tempPair.first->get_num_of_arg() != -1) {
      if (*(tempPair.second.begin()) == this->funcVariable) {
        tempPair.first->execute(vars);
      } else {
        tempPair.first->execute(tempPair.second);
      }
    }
    sleep(1);
  }
}

int FunctionCommand::get_num_of_arg() {return 1;}