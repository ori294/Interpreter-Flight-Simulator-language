//
// Created by gadi on 12/12/2019.
//

#ifndef EX3_EX3_CONNECTCOMMAND_H_
#define EX3_EX3_CONNECTCOMMAND_H_

#include <thread>
#include <queue>
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
  queue<string> commandsToSim;
 public:
  int execute(list<string> list_of_strings) override;
  int get_num_of_arg() override { return 2; }
  void add_commands_to_queue(string s);
  static void run_client_to_simulator(queue<string> *commandsForS, int socket_client);
};

#endif //EX3_EX3_CONNECTCOMMAND_H_