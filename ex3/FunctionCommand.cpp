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

  int var_is_double_flag = 0;
  auto map = SimulatorManager::getInstance()->getLocalSymbolMap();
  if (std::regex_search(*vars.begin(), std::regex("[0-9.]+"))) {
    double value = stod(*vars.begin());
    map->insert({this->funcVariable, value});
    var_is_double_flag = 1;
  }


  this->parser->startOver(4); //start over + 4 steps (get to the 4th string)
  while (!this->parser->isEnded()) {
    auto tempPair = parser->getNextCommand();
    //check if we got a valid command and not null.
    if (tempPair.first != nullptr && tempPair.first->get_num_of_arg() != -1) {
      tempPair.first->execute(tempPair.second);
    }
  }

  if (var_is_double_flag) {
    map->erase(this->funcVariable);
  }


  return 1;
}

/**
 * get_num_of_arg: returns the number of arguments for this type of command.
 * @return integer, the length of the argument list.
 */
int FunctionCommand::get_num_of_arg() {return 1;}