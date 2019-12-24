//
// Created by ori294 on 12/17/19.
//

#include "VarAssignCommand.h"

int VarAssignCommand::execute(std::list<std::string> list_of_strings) {
  auto localMap = SimulatorManager::getInstance()->getSymbolMap();
  auto iter1 = localMap->find(*(list_of_strings.begin()));
  auto iterator2 = list_of_strings.begin();
  iterator2++;
  string check_expression = *iterator2;

  SimulatorManager::getInstance()->get_client()->add_commands_to_queue("set " +
      iter1->second->getSimAddress() + " " + to_string(SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(
      check_expression)->calculate()) + "\r\n");

  return 0;
}
