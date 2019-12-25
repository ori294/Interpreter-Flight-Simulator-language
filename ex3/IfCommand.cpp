//
// Created by ori294 on 12/22/19.
//

#include "IfCommand.h"

/**
 * Executes the loop command
 * @param commands list of commands as strings
 * @return an integer type
 */
int IfCommand::execute(std::list<std::string> commands) {
  if (isConditionSatisfied()) {
    ConditionParser::startOver(4);
    cout << "execute conditional code:" << endl;
    ConditionParser::execute(std::list<std::string>(commands));
  }
  return 0;
}

/**
 * CTOR: Init local symbol table.
 * it copies the symbol tables from the main loop of the code.
 */
IfCommand::IfCommand(std::list<std::string>* commands) : ConditionParser(commands) {
  //do nothing
}

/**
 * returns the number of aruments for this conditional command
 * @return the length of the aruments list.
 */
int IfCommand::get_num_of_arg() {return listLength;}
