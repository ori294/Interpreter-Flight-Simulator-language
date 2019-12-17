//
// Created by ori294 on 12/11/19.
//

#include "Parser.h"
#include "Commands/OpenServerCommand.h"
#include "Commands/ConnectCommand.h"

/**
 * get the next command and returns a pair containing the command and the list of args for it.
 * @return pair with command and list of args (as strings).
 */
std::pair<Command*,std::list<std::string>> Parser::getNextCommand() {
  if (!isEnded()) { //check that there're more commands in the queue
    Command* tempCommand;
    std::list<std::string> tempList;
    auto mapIterator = commandMap.find(*listIterator); //find the right command
    if (mapIterator != commandMap.end()) {
      tempCommand = mapIterator->second; //save the command
        listIterator++;
      for (int i = 0; i < tempCommand->get_num_of_arg(); i++) { //get the arguments for the command
        tempList.emplace_back(*listIterator);
        listIterator++;
      }
      std::pair<Command*,std::list<std::string>> tempPair(tempCommand,tempList);
      return tempPair;
    }
    NullCommand* null_command;
    std::pair<Command*,std::list<std::string>>(null_command, tempList);
  }
}

/**
 * check if there're more commands to perform
 * @return
 */
bool Parser::isEnded() {
  if (listIterator == commandList.end()) {
    return true;
  } else {
    return false;
  }
}
/**
 * Parser constructor
 * @param strList
 */
Parser::Parser(std::list<std::string> strList) {
  commandList = strList;
  listIterator = commandList.begin();

  //Add open server command to the map
  OpenServerCommand *ops = new OpenServerCommand();
  commandMap.insert({"OpenServerCommand", ops});

  //Add connect client command to the map
  //ConnectCommand *cnc = new ConnectCommand();
  //commandMap.insert({"ConnectCommand", cnc});

  //Add print command to the map
  PrintCommand print;
  commandMap.insert({"Print", &print});

  //Add sleep command to the map
  SleepCommand sleep;
  commandMap.insert({"Sleep", &sleep});

}
