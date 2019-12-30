//
// Created by ori294 on 12/17/19.
//

#include "FunctionCommand.h"

/**
 * FunctionCommand CTOR: init parser with commands and init func variable.
 * @param comms list of strings that holds commands
 */
FunctionCommand::FunctionCommand(std::list<std::string> comms) {
  commandList = comms;
  this->parser = new Parser(commandList);

  auto iter = comms.begin();
  iter++; iter++;

  this->funcVariable = *iter;
}

/**
 * execute: run the lines of code inside the command, whenever executing a command with the func
 * variable: replace it with the run-time argument.
 * @param vars run-time argument for the func.
 * @return integer, the length of the argument list.
 */
int FunctionCommand::execute(std::list<std::string> vars) {
  this->parser->startOver(4); //start over + 4 steps (get to the 4th string)
  while (!this->parser->isEnded()) {
    auto tempPair = parser->getNextCommand();
    //check if we got a valid command and not null.
    if (tempPair.first != nullptr && tempPair.first->get_num_of_arg() != -1) {
      if (*(tempPair.second.begin()) == this->funcVariable) {
        tempPair.first->execute(vars);
      } else {
        tempPair.first->execute(tempPair.second);
      }
    }
    sleep(1);
  }
  return 1;
}

/**
 * get_num_of_arg: returns the number of arguments for this type of command.
 * @return integer, the length of the argument list.
 */
int FunctionCommand::get_num_of_arg() {return 1;}