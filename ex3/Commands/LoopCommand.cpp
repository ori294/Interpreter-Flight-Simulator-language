//
// Created by ori294 on 12/18/19.
//

#include "LoopCommand.h"

int LoopCommand::execute(std::list<std::string> L) {
  this->parser = new ConditionParser();


}

/**
 * CTOR: Init local symbol table.
 */
LoopCommand::LoopCommand() {
  auto symbolMap = SimulatorManager::getInstance()->getSymbolMap();
  auto localMap = SimulatorManager::getInstance()->getLocalSymbolMap();
  auto symbolIterator = symbolMap->begin();
  auto localIterator = localMap->begin();

  while (symbolIterator != symbolMap->end()) {
    this->LoopSymbolTable.insert(*symbolIterator);
  }
  while (localIterator != localMap->end()) {
    this->LoopLocalSymbolTable.insert(*localIterator);
  }
}
