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
    cout << "execute conditional code:" << endl;
    ConditionParser::execute(std::list<std::string>(commands));
    ConditionParser::startOver(4);
  }
  return 0;
}

/**
 * CTOR: Init local symbol table.
 * it copies the symbol tables from the main loop of the code.
 */
LoopCommand::LoopCommand(std::list<std::string>* commands) : ConditionParser(commands) {
  //do nothing
}

/**
 * returns the number of aruments for this conditional command
 * @return the length of the aruments list.
 */
int LoopCommand::get_num_of_arg() {return listLength;}

