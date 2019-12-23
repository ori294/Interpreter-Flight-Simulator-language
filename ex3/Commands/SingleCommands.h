//
// Created by ori294 on 12/11/19.
//

#ifndef EX3_COMMANDS_SINGLECOMMANDS_H_
#define EX3_COMMANDS_SINGLECOMMANDS_H_
#include "Command.h"
#include "../SimulatorManager.h"
#include <chrono>
#include <thread>
#include <string>

class PrintCommand: public Command {
  int get_num_of_arg() override {return 1;}
  int execute(std::list<std::string> comList) override;
};

class SleepCommand: public Command {

  int get_num_of_arg() override {return 1;}

  int execute(std::list<std::string> comList) override {
    char char_array[comList.begin()->length()]; //copy to array for atoi function
    strcpy(char_array, comList.begin()->c_str());
    int sleepDuration = std::atoi(char_array);
    std::cout << "sleeping for " << sleepDuration << " ms" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    return 1;
  }
};

class NullCommand: public Command {
  int get_num_of_arg() override {return -1;}
  int execute(std::list<std::string> comList) override {
    //do nothing
  }
};


#endif //EX3_COMMANDS_SINGLECOMMANDS_H_
