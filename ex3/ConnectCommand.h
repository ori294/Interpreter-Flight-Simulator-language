//
// Created by gadi on 12/12/2019.
//

#ifndef EX3_EX3_CONNECTCOMMAND_H_
#define EX3_EX3_CONNECTCOMMAND_H_

#include "Command.h"
#include <thread>
#include <queue>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unordered_map>
#include "SimulatorManager.h"

using namespace std;

class connectControlClient : public Command {
 private:
  queue<string> commandsToSim;
 public:
  int socket_client;
  thread get_info;
  int execute(list<string> list_of_strings) override;
  int get_num_of_arg() override;
  void add_commands_to_queue(string s);
  static void run_client_to_simulator(queue<string> *commandsForS, int socket_client);
  string removeSpaces(string str);
};

#endif //EX3_EX3_CONNECTCOMMAND_H_