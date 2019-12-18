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
    line = removeTabs(line);

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
      strList.push_back(removeSpaces(leftSide));
      strList.push_back(removeSpaces(rightSide));

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
    } else if (std::regex_search(line, std::regex("Print"))) {
      strList.push_back("Print");
      std::string text = line.substr(6, line.length());
      text = removeBrackets(text);
      strList.push_back(text);
    } else {
      char char_array[line.length()]; //copy to array for strtok function
      std::strcpy(char_array, line.c_str());
      char *token = strtok(char_array, " ,(,)");
      if (token != nullptr) {
        strList.push_back(token);
      }

      //strtok loop = keep cutting string until strtok gives null
      while (token != nullptr) {
        token = strtok(nullptr, " ,(,)");
        if (token != nullptr) {
          strList.push_back(token);
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


//openDataServer;5400;connectControlClient;"127.0.0.1";5402;simvar;warp;->;sim;"/sim/time/warp";simvar;magnetos;->;sim;"/controls/switches/magnetos";simvar;throttle;->;sim;"/controls/engines/current-engine/throttle";simvar;mixture;->;sim;"/controls/engines/current-engine/mixture";simvar;masterbat;->;sim;"/controls/switches/master-bat";simvar;masterlat;->;sim;"/controls/switches/master-alt";simvar;masteravionics;->;sim;"/controls/switches/master-avionics";simvar;brakeparking;->;sim;"/sim/model/c172p/brake-parking";simvar;primer;->;sim;"/controls/engines/engine/primer";simvar;starter;->;sim;"/controls/switches/starter";simvar;autostart;->;sim;"/engines/active-engine/auto-start";simvar;breaks;->;sim;"/controls/flight/speedbrake";simvar;heading;<-;sim;"/instrumentation/heading-indicator/offset-deg";simvar;airspeed;<-;sim;"/instrumentation/airspeed-indicator/indicated-speed-kt";simvar;roll;<-;sim;"/instrumentation/attitude-indicator/indicated-roll-deg";simvar;pitch;<-;sim;"/instrumentation/attitude-indicator/internal-pitch-deg";simvar;rudder;->;sim;"/controls/flight/rudder";simvar;aileron;->;sim;"/controls/flight/aileron";simvar;elevator;->;sim;"/controls/flight/elevator";simvar;alt;<-;sim;"/instrumentation/altimeter/indicated-altitude-ft";simvar;rpm;<-;sim;"/engines/engine/rpm";Print;"waiting 2 minutes for gui");Sleep;120000;Print;"let's start");=;warp; 32000;Sleep;1000;=;magnetos; 3;=;throttle; 0.2;=;mixture; 0.949;=;masterbat; 1;=;masterlat; 1;=;masteravionics; 1;=;brakeparking; 0;=;primer; 3;=;starter; 1;=;autostart; 1;Print;"engine is warming...");Print;rpm);while;rpm;<=;750;{;Print;rpm);};Sleep;5000;Print;"let's fly");var;h0;=;heading;=;breaks; 0;=;throttle; 1;