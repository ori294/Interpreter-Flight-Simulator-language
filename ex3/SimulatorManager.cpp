//
// Created by ori294 on 12/11/19.
//

#include "SimulatorManager.h"
#include "SymbolTableValue.h"

void SimulatorManager::setStringList(std::list<std::string> strList) {
  parser = new Parser(strList);
}

void SimulatorManager::runSimulator() {
  //loop running simulator
}

SimulatorManager::SimulatorManager() {
  //this->symbolTable = std::map<std::string, SymbolTableValue>();
};

void SimulatorManager::update_symbol_table(std::string VarName, bool bindDirection, std::string simAddress) {
  Expression* expression = new Value(0);
  SymbolTableValue* sym = new SymbolTableValue(expression, simAddress, bindDirection);
  symbolTable.insert({VarName, sym});
}


SimulatorManager* SimulatorManager::instance = nullptr;

SimulatorManager* SimulatorManager::getInstance() {
  if (instance == nullptr)
  {
    instance = new SimulatorManager();
  }
  return instance;
};