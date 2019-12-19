//
// Created by ori294 on 12/18/19.
//

#include "SingleCommands.h"

/**
 * Execute the print command
 * @param comList list of arguments
 * @return return an integer type
 */
int PrintCommand::execute(std::list<std::string> comList) {

  //get localMap and symbolMap
  auto symbolMap = SimulatorManager::getInstance()->getSymbolMap();
  auto localMap = SimulatorManager::getInstance()->getLocalSymbolMap();

  //find the argument in the maps
  auto iter = symbolMap->find(*comList.begin());
  auto localIter = localMap->find(*comList.begin());
  if (iter != symbolMap->end()) {// if found
    if (iter->second->getBind()) { //bind right
      std::cout << iter->second->getExpression()->calculate() << std::endl;
    } else { //bind left
      float value = SimulatorManager::getInstance()->get_server()->get_value(iter->second->getSimAddress());
      std::cout << value << std::endl;
    }
  } else if (localIter != localMap->end()) { //else: check if its the local map
    auto value = localIter->second;
    std::cout << value << std::endl;
  } else { //else:
    std::cout << *comList.begin() << std::endl;
  }
  return 1;
}

