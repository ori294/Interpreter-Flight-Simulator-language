//
// Created by ori294 on 12/17/19.
//

#include "SimulatorManager.h"
#include <bits/stdc++.h>

/**
 * get list string of arguments and send that argument: name var ,arrow and path of command in simulator directory
 * @param list_of_strings
 * @return 0
 */
int DefineLocalVarCommand::execute(list<string> list_of_strings) {

  auto localMap = SimulatorManager::getInstance()->getLocalSymbolMap();
  list<string>::iterator iterator = list_of_strings.begin();
  string name_var = *iterator;
  iterator++;
  iterator++;

  Expression* tempEx = SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(*iterator);

  localMap->insert({name_var, tempEx->calculate()});
  if (left != nullptr) {
    delete tempEx;
  }
  return 1;
}
