//
// Created by ori294 on 12/17/19.
//

#include "DefineLocalVarCommand.h"
#include <bits/stdc++.h>

/**
 * get list string of arguments and send that argument: name var ,arrow and path of command in simulator directory
 * @param list_of_strings
 * @return 0
 */
int DefineLocalVarCommand::execute(list<string> list_of_strings) {

  auto localMap = SimulatorManager::getInstance()->getSymbolMap();
  list<string>::iterator it = list_of_strings.begin();
  string name_var = *it;
  it++; it++;

  if (localMap->find(*it) != localMap->end()) {
    //ask the value from the server
  } else if (std::regex_match(*it, std::regex("[-0-9.]+"))) {
    //local assigmnet with local number.
  }
  return 0;
}
