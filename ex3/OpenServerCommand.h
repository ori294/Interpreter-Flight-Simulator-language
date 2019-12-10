//
// Created by gadi on 10/12/2019.
//
#ifndef INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_
#define INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_

#include <string>
#include <iostream>
#include "Command.h"
#include <list>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
using namespace std;

class OpenServerCommand : public Command {

 public:
  static void get_data_from_air_plane(int client_socket) {
    char buffer[1024] = {0};
    int data = read(client_socket, buffer, 1024);
    cout << buffer << endl;
  }
  int execute(list<string> list_of_strings) override {
    //fix the port!!!
    int port = 5400;
    int socket_Server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_Server == -1) {

      cerr << "can't open server" << endl;
      return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(socket_Server, (struct sockaddr *) &address, sizeof(address)) == -1) {
      cerr << "can't bind server" << endl;
      return -2;
    }
    if (listen(socket_Server, 1) == -1) {
      cerr << "can't listen server" << endl;
      return -3;
    }
    int client_socket = accept(socket_Server, (struct sockaddr *) &address, (socklen_t *) &address);
    if (client_socket == -1) {
      cerr << "can't accept client" << endl;
      return -3;
    }
    get_data_from_air_plane(client_socket);
    //std::thread get_info(get_data_from_air_plane, client_socket);
    return 2;
  }
};

#endif //INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_
