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

  auto symbolMap = SimulatorManager::getInstance()->getSymbolMap();
  auto localMap = SimulatorManager::getInstance()->getLocalSymbolMap();
  list<string>::iterator it = list_of_strings.begin();
  string name_var = *it;
  it++;
  it++;

  auto iter = symbolMap->find(*it);
  if (iter != symbolMap->end()) {
    float value = SimulatorManager::getInstance()->get_server()->get_value(iter->second->getSimAddress());
    localMap->insert({name_var, value});
  } else if (std::regex_match(*it, std::regex("[-0-9.]+"))) {
    localMap->insert({name_var, stof(*it)});
  }
  return 0;
}
