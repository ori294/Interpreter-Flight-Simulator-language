//
// Created by ori294 on 12/10/19.
//

#include "Lexer.h"

/**
 * readFile reads a given txt file and than lexing it to a list of strings.
 * @param fileName
 * @return the list of strings
 */
std::list<std::string> Lexer::readFile(std::string fileName) {

  // open the file, throw exception if file doesn't exists.
  std::fstream readFile(fileName, std::ios::in);
  if (!readFile) {
    throw "error opening commands file";
  }

  //Main loop - read line each time
  while (!readFile.eof()) {
    std::string line;
    std::getline(readFile, line);
    line = removeSpaces(line);

    //Handle var declarations
    if (std::regex_search(line, std::regex("var"))) {
      char char_array[line.length()]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());

      //strtok for delimiters - first time
      char *token = strtok(char_array, " ,(,)");
      if (token != nullptr) {
        if (std::regex_search(line, std::regex("sim"))) {
          strList.push_back("simvar");
        } else {
          strList.push_back("var");
        }
      }
      //strtok loop = keep cutting string until strtok gives null
      while (token != nullptr) {
        token = strtok(nullptr, " ,(,)");
        if (token != nullptr) {
          strList.push_back(token);
        }
      }
      //Handle variable assignments, this case doesn't handle var x = y, the var case handles it
    } else if (std::regex_search(line, std::regex(" = "))){
      char char_array[line.length()]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());

      int equalPos = 0;
      int j = 0;
      for (; j < line.length(); j++) { //find the position of '='
        if (char_array[j] == '=') {
          equalPos = j;
          break;
        }
      }
      //cut the string into two sides of the assigment.
      std::string leftSide = line.substr(0, equalPos-1);
      std::string rightSide = line.substr(equalPos+1, line.length());

      //expressions of the format: x = y will turn into "= x y"
      strList.push_back("=");
      strList.push_back(leftSide);
      strList.push_back(rightSide);

      //handle while statements
    } else if (std::regex_search(line, std::regex("while "))) {
      char char_array[line.length()]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      strList.push_back("while");

      //strtok for delimiters - first time
      char *token = strtok(char_array, " ");
      if (token != nullptr) {
        //strList.push_back(token);
      }
      //strtok loop = keep cutting string until strtok gives null
      while (token != nullptr) {
        token = strtok(nullptr, " ");
        if (token != nullptr) {
          strList.push_back(token);
        }
      }
      //handle if statements
    } else if (std::regex_search(line, std::regex("if "))) {
      char char_array[line.length()]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      strList.push_back("if");

      //strtok for delimiters - first time
      char *token = strtok(char_array, " ");
      if (token != nullptr) {
        //strList.push_back(token);
      }
      //strtok loop = keep cutting string until strtok gives null
      while (token != nullptr) {
        token = strtok(nullptr, " ");
        if (token != nullptr) {
          strList.push_back(token);
        }
      }
      //handles single scope closer
    } else if (std::regex_search(line, std::regex("\\}"))) {
      strList.push_back("}");
      //handle all other cases, like function and expression
    } else {
      char char_array[line.length()]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      char *token = strtok(char_array, " ,(,)");
      if (token != NULL) {
        strList.push_back(token);
      }

      //strtok loop = keep cutting string until strtok gives null
      while (token != NULL) {
        token = strtok(NULL, " ,(,)");
        if (token != NULL) {
          strList.push_back(token);
        }
      }
    }
  }
  readFile.close(); //close the file
  return strList;
}

/**
 * removeSpaces: Get a string and remove all tabs (spaces from it)
 * @param str a string
 * @return the trimmed string
 */
std::string Lexer::removeSpaces(std::string str) {
  str.erase(remove(str.begin(), str.end(), '\t'), str.end());
  return str;
}

/**
 * removeSpaces: Get a string and remove all brackets from it (right scope opening brackets)
 * @param str a string
 * @return the trimmed string
 */
std::string Lexer::removeBrackets(std::string str) {
  str.erase(remove(str.begin(), str.end(), '{'), str.end());
  return str;
}
