//
// Created by ori294 on 12/11/19.
//

#include "Parser.h"

Command* Parser::getNextCommand() {
  if (!isEnded()) {
    auto mapIterator = commandMap.find(*listIterator);
    if (mapIterator != commandMap.end()) {
      listIterator++;
      return mapIterator->second;
    }
  }
  //TO DO: return some kind of null command!
}

std::string Parser::getString(int inc) {
  for (int i = 0; i < inc; i++) {
    std::string tempStr = *listIterator;
    listIterator++;
    return tempStr;
  }
}

bool Parser::isEnded() {
  if (listIterator == commandList.end()) {
    return true;
  } else {
    return false;
  }
}
Parser::Parser(std::list<std::string> strList) {
  commandList = strList;
  listIterator = commandList.begin();

  //Add print command to the map
  PrintCommand print;
  commandMap.insert({"Print", &print});

  //Add sleep command to the map
  SleepCommand sleep;
  commandMap.insert({"Print", &sleep});

}
