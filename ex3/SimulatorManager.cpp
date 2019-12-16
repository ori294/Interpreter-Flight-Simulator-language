//
// Created by ori294 on 12/11/19.
//

#include "SimulatorManager.h"

void SimulatorManager::setStringList(std::list<std::string> strList) {
  parser = new Parser(strList);
}

void SimulatorManager::runSimulator() {
  //loop running simulator
}

SimulatorManager::SimulatorManager() {
  //Do nothing
};

SimulatorManager* SimulatorManager::instance = nullptr;

SimulatorManager* SimulatorManager::getInstance() {
  if (instance == nullptr)
  {
    instance = new SimulatorManager();
  }
  return instance;
};