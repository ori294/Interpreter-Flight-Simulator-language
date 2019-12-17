//
// Created by ori294 on 12/17/19.
//

#include "VarAssignCommand.h"

int VarAssignCommand::execute(std::list<std::string> list_of_strings) {
  //std::map<std::string, SymbolTableValue*>
  auto localMap = SimulatorManager::getInstance()->getSymbolMap();
  //std::map<std::string, SymbolTableValue*>::iterator
  auto iter1 = localMap->find(*(list_of_strings.begin()));

  if (iter1 != localMap->end()) {
    if (iter1->second->getBind()) { //if it's (right)client-bind.
      //Here we should send the client the command
      auto iter2 = list_of_strings.begin();
      iter2++;

      SimulatorManager::getInstance()->get_client()->add_commands_to_queue("set " +
      iter1->second->getSimAddress() + " " + *iter2 + "\r\n");
    }
  }
}