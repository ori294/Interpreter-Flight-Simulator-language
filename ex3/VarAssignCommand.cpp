//
// Created by ori294 on 12/17/19.
//

#include "VarAssignCommand.h"

/**
 * execute: assign a value to a variable inside the simulator.
 * @param list_of_strings: command arguments.
 * @return number of arguments
 */
int VarAssignCommand::execute(std::list<std::string> list_of_strings) {

  //get the symbol map and find the relevant variable.
  auto localMap = SimulatorManager::getInstance()->getSymbolMap();
  auto iter1 = localMap->find(*(list_of_strings.begin()));
  auto iterator2 = list_of_strings.begin();
  iterator2++;
  string check_expression = *iterator2;

  /*
   * send the variable value change command via the client. do it as string, as the simulator
   * requires to receive the variable path inside the simulator + the new value.
   */
  SimulatorManager::getInstance()->get_client()->add_commands_to_queue("set " +
      iter1->second->getSimAddress() + " " + to_string(SimulatorManager::getInstance()->
      get_interpreter()->change_var_to_value(check_expression)->calculate()) + "\r\n");

  return 2;
}
