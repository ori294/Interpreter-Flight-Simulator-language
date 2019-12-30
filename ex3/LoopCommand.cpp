//
// Created by ori294 on 12/18/19.
//
#include "LoopCommand.h"

/**
 * Executes the loop command
 * @param commands list of commands as strings
 * @return an integer type
 */
int LoopCommand::execute(std::list<std::string> commands) {
  while (isConditionSatisfied()) {
    ConditionParser::execute(std::list<std::string>(commands));
    ConditionParser::startOver(4);
  }
  return 0;
}

/**
 * CTOR: Init local symbol table.
 */
LoopCommand::LoopCommand(std::list<std::string>* commands) : ConditionParser(commands) {
  //the construction happens only in the father (ConditionParser).
}

/**
 * returns the number of aruments for this conditional command
 * @return the length of the aruments list.
 */
int LoopCommand::get_num_of_arg() {return listLength;}

