//
// Created by ori294 on 12/10/19.
//

#define MAX_LENGTH 1024
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
    line = removeTabs(line);
    line = ltrim(line);

   /**
    * Lexer case: Function Define
    */
    if (std::regex_search(line, std::regex("var")) && std::regex_search(line, std::regex("()"))
      && !std::regex_search(line, std::regex("sim")) && !std::regex_search(line, std::regex("="))) {
      char char_array[MAX_LENGTH]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      strList.push_back("funcdef");

      //strtok for delimiters - first time
      char *token = strtok(char_array, " ,(,)");
      if (token != nullptr) {
        strList.push_back(removeSpaces(token));
      }
      //strtok loop = keep cutting string until strtok gives null
      while (token != nullptr) {
        token = strtok(nullptr, " ");
        if (token != nullptr) {
          strList.push_back(removeBrackets(token));
        }
      }
    }
    /**
    * Lexer case: Variable Define
    */
    else if (std::regex_search(line, std::regex("var"))) {
      char char_array[MAX_LENGTH]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());

      //strtok for delimiters - first time
      char *token = strtok(char_array, " ,(,)");
      if (token != nullptr) {
        if (std::regex_search(line, std::regex("sim"))) {
          strList.push_back("simvar");
          while (token != nullptr) {
            token = strtok(nullptr, " ,(,)");
            if (token != nullptr) {
              strList.push_back(token);
            }
          }
        } else {
          strList.push_back("var");
          line = removeSpaces(line.substr(4, line.length()));
          char char_array[MAX_LENGTH]; //copy to array for strtok function
          std::strcpy(char_array, line.c_str());
          int equalPos = 0;
          unsigned int j = 0;
          for (; j < line.length(); j++) { //find the position of '='
            if (char_array[j] == '=') {
              equalPos = j;
              break;
            }
          }
          //cut the string into two sides of the assigment.
          std::string leftSide = line.substr(0, equalPos);
          std::string rightSide = line.substr(equalPos+1, line.length());

          //expressions of the format: x = y will turn into "= x y"
          strList.push_back(removeSpaces(leftSide));
          strList.push_back("=");
          strList.push_back(removeSpaces(rightSide));
          }
      }
    }
    /**
    * Lexer case: X Equals Y command, and it's not a loop command.
    */
    else if (std::regex_search(line, std::regex("="))  && !std::regex_search(line, std::regex("while"))
              &&  !std::regex_search(line, std::regex("if"))){
      line = removeSpaces(line);
      char char_array[MAX_LENGTH]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());

      int equalPos = 0;
      unsigned int j = 0;
      for (; j < line.length(); j++) { //find the position of '='
        if (char_array[j] == '=') {
          equalPos = j;
          break;
        }
      }
      //cut the string into two sides of the assigment.
      std::string leftSide = line.substr(0, equalPos);
      std::string rightSide = line.substr(equalPos+1, line.length()-equalPos);

      //expressions of the format: x = y will turn into "= x y"
      strList.push_back("=");
      strList.push_back(removeSpaces(leftSide));
      strList.push_back(removeSpaces(rightSide));

      //handle while statements
    }
    /**
    * Lexer case: While loop.
    */
    else if (std::regex_search(line, std::regex("while "))) {
      line = removeSpaces(line);
      char char_array[MAX_LENGTH]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      strList.push_back("while");

      int equalPos = 0;
      std::string condition;
      unsigned int j = 5;
      unsigned offSet = 5;
      for (; j < line.length(); j++) { //find the position of '='
        if (char_array[j] == '<' || char_array[j] == '=' || char_array[j] == '>' || char_array[j] == '!') {
          equalPos = j;
          condition = char_array[j];

          if (char_array[j+1] == '=') {
            condition += "=";
            equalPos++;
            offSet++;
            j++;
          }
          break;
        }
      }
      //cut the string into two sides of the assigment.
      std::string leftSide = line.substr(5, equalPos-offSet);
      std::string rightSide = line.substr(equalPos+1, line.length()- equalPos - 2);

      //expressions of the format: x = y will turn into "= x y"
      strList.push_back(removeSpaces(leftSide));
      strList.push_back(condition);
      strList.push_back(removeSpaces(rightSide));
      strList.push_back("{");

      //handle if statements
    }
    /**
    * Lexer case: If Command.
    */
    else if (std::regex_search(line, std::regex("if "))) {
      line = removeSpaces(line);
      char char_array[MAX_LENGTH]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      strList.push_back("if");

      int equalPos = 0;
      std::string condition;
      unsigned int j = 2;
      unsigned offSet = 2;
      for (; j < line.length(); j++) { //find the position of '='
        if (char_array[j] == '<' || char_array[j] == '=' || char_array[j] == '>' || char_array[j] == '!') {
          equalPos = j;
          condition = char_array[j];

          if (char_array[j+1] == '=') {
            condition += "=";
            equalPos++;
            offSet++;
            j++;
          }
          break;
        }
      }
      //cut the string into two sides of the assigment.
      std::string leftSide = line.substr(2, equalPos-offSet);
      std::string rightSide = line.substr(equalPos+1, line.length()- equalPos - 2);

      //expressions of the format: x = y will turn into "= x y"
      strList.push_back(removeSpaces(leftSide));
      strList.push_back(condition);
      strList.push_back(removeSpaces(rightSide));
      strList.push_back("{");

      //handles single scope closer
    }
    /**
    * Lexer case: End of while/If/Function bracket.
    */
    else if (std::regex_search(line, std::regex("\\}"))) {
      strList.push_back("}");
    }
    /**
    * Lexer case: Print string command.
    */
    else if (std::regex_search(line, std::regex("Print")) && std::regex_search(line, std::regex("\""))) {
      strList.push_back("Print");
      std::string text = line.substr(6, line.length());
      strList.push_back(removeBrackets(text));
    }
    /**
    * Lexer case: Print Expression or Variable command.
    */
    else if (std::regex_search(line, std::regex("Print"))) {
      strList.push_back("Print");
      std::string text = removeSpaces(line.substr(6, line.length()));
      strList.push_back(removeBrackets(text));
    }
    /**
    * Lexer case: Default (mainly sleep command or other single variable commands like connect client).
    */
    else {
      char char_array[MAX_LENGTH]; //copy to array for strtok function
      std::strcpy(char_array, removeSpaces(line).c_str());
      char *token = strtok(char_array, " ,(,)");
      if (token != nullptr) {
        strList.push_back(removeSpaces(token));
      }
      //strtok loop = keep cutting string until strtok gives null
      while (token != nullptr) {
        token = strtok(nullptr, " ,(,)");
        if (token != nullptr) {
          strList.push_back(removeSpaces(token));
        }
      }
    }
  }
  readFile.close(); //close the file
  return strList;
}

/**
 * removeTabs: Get a string and remove all tabs (spaces from it)
 * @param str a string
 * @return the trimmed string
 */
std::string Lexer::removeTabs(std::string str) {
  str.erase(remove(str.begin(), str.end(), '\t'), str.end());
  return str;
}

/**
 * removeSpaces: Get a string and remove all blank spaces
 * @param str a string
 * @return the trimmed string
 */
std::string Lexer::removeSpaces(std::string str) {
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  return str;
}
/**
 * removeSpaces: Get a string and remove all brackets from it
 * @return the trimmed string
 */
std::string Lexer::removeBrackets(std::string str) {
  str.erase(remove(str.begin(), str.end(), ')'), str.end());
  str.erase(remove(str.begin(), str.end(), '('), str.end());
  return str;
}

/**
 * ltrim: trim a string (from it's left side) from spaces.
 * @return the trimmed string
 */
std::string& Lexer::ltrim(std::string &str)
{
  auto it2 = std::find_if( str.begin() ,str.end() ,[](char ch){
    return !std::isspace<char>(ch, std::locale::classic());});
  str.erase( str.begin() , it2);
  return str;
}
