//
// Created by gadi on 17/12/2019.
//
#include "DefineVarCommand.h"

/**
 * get list string of arguments and send that argument: name var ,arrow and path of command in simulator directory
 * @param list_of_strings
 * @return 0
 */
int DefineVarCommand::execute(list<string> list_of_strings) {

  list<string>::iterator it = list_of_strings.begin();
  string name_var = *it;
  bool arrow = false;
  string path;
  it++;
  if (*it == "->") {
    arrow = true;
  }
  it++;
  it++;
  path = removeSpaces(*it);
  SimulatorManager::getInstance()->update_symbol_table(name_var, arrow, path);
  return 0;
}

/**
 * removeSpaces: Get a string and remove all blank spaces
 * @param str a string
 * @return the trimmed string
 */
std::string DefineVarCommand::removeSpaces(std::string str) {
  str.erase(remove(str.begin(), str.end(), '"'), str.end());
  return str;
}