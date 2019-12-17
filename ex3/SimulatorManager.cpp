//
// Created by ori294 on 12/11/19.
//

#include "SimulatorManager.h"
#include "SymbolTableValue.h"

/**
 * Set the list of strings for the parser.
 * @param strList
 */
void SimulatorManager::setStringList(std::list<std::string> strList) {
  parser = new Parser(strList);
}
/**
 * run the simulator.
 */
void SimulatorManager::runSimulator() {
  while (!parser->isEnded()) {
    parser->getNextCommand().first->execute(parser->getNextCommand().second);
    sleep(1);
  }
}
/**
 * update the symbol table from outside the manager.
 * @param VarName Variable name
 * @param bindDirection will be true if and only if the bind direction is right.
 * @param simAddress the adress in the simulator.
 */
void SimulatorManager::update_symbol_table(std::string VarName, bool bindDirection, std::string simAddress) {
  Expression *expression = new Value(0);
  SymbolTableValue *sym = new SymbolTableValue(expression, simAddress, bindDirection);
  symbolTable.insert({VarName, sym});
}
/**
 * Singleton class.
 */
SimulatorManager *SimulatorManager::instance = nullptr;
/**
 * Get the instance of the SimulatorManager. Call CTOR upon calling it for the first time.
 * @return
 */
SimulatorManager *SimulatorManager::getInstance() {
  if (instance == nullptr) {
    instance = new SimulatorManager();
  }
  return instance;
};
/**
 * Simulator manager CTOR.
 */
SimulatorManager::SimulatorManager() {
  //this->symbolTable = std::map<std::string, SymbolTableValue>();
}
/**
 * set server member
 * @param ser
 */
void SimulatorManager::set_server(OpenServerCommand *ser) {
  this->server = ser;
}
/**
 * set client member
 * @param cli
 */
void SimulatorManager::set_client(connectControlClient *cli) {
  this->client = cli;
}
/**
 * getter server
 * @return pointer to server
 */
OpenServerCommand *SimulatorManager::get_server() {
  return this->server;
}
/**
 * geter client
 * @return pointer to client
 */
connectControlClient *SimulatorManager::get_client() {
  return this->client;
};