//
// Created by gadi on 12/12/2019.
//

#ifndef EX3_EX3_CONNECTCOMMAND_H_
#define EX3_EX3_CONNECTCOMMAND_H_

#include <thread>
#include "Command.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include<arpa/inet.h>
#include <unordered_map>
using namespace std;

class connectControlClient : public Command {
 private:
  thread get_info;
  unordered_map<string, string> data_about_airplane;
 public:
  int execute(list<string> list_of_strings) override;
  int get_num_of_arg() override {return 2;}

};

#endif //EX3_EX3_CONNECTCOMMAND_H_