//
// Created by gadi on 12/12/2019.
//

#include "OpenServerCommand.h"


void OpenServerCommand::split_and_update_data(char *buffer, map<int, pair<string, string>> *map_data) {
  char *tokens;
  int indicator = 0;
  tokens = strtok(buffer, ",");
  (*map_data)[indicator].second = tokens;
  while (indicator < 23) {
    indicator++;
    tokens = strtok(nullptr, ",");
    (*map_data)[indicator].second = tokens;
  }
}

/**
 * func get data about the airplane and update in the data_map
 * @param client_socket
 */

void OpenServerCommand::get_data_from_air_plane(int client_socket, map<int, pair<string, string>> *map_data) {
  char buffer[1024] = {0};
  int data = read(client_socket, buffer, 1024);
  split_and_update_data(buffer, map_data);
  while (data != -1) {
    data = read(client_socket, buffer, 1024);
    split_and_update_data(buffer, map_data);
  }
}

/**
 * create socket server and wait for the connecting of the simulator .
 * after the connecting sending new thread of server-simulator in func get_data_from_air_plane
 * @param list_of_strings
 * @param indicator point on the string we need
 * @return indicator for how many steps jump on the list
 */
int OpenServerCommand::execute(list<string> list_of_strings) {
  SimulatorManager::getInstance()->set_server(this);
  string number_port = *list_of_strings.begin();
  int port = atoi(number_port.c_str());
  int socket_Server = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_Server == -1) {

    cerr << "can't open server" << endl;
    return -1;
  }

  //create server socket
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
  //sending thread to the func "get_data_from_air_plane" and make multi-threads
  this->get_info = thread(get_data_from_air_plane, client_socket, &this->data_about_airplane);
  get_info.join();
  //close socket!!!
  return this->numOfArg + 1;
}
/**
 * getter value of specific variable in map of data_about_airplane
 * @param s
 * @return value
 */
float OpenServerCommand::get_value(string s) {
  float value = 0;
  auto it = this->data_about_airplane.begin();
  while (it != this->data_about_airplane.end()) {
    if (it->second.first == s) {
      value = stof(it->second.second);
      break;
    }
  }
  return value;
}