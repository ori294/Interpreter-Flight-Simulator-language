//
// Created by gadi on 12/12/2019.
//

#include "OpenServerCommand.h"

/**
 * remove \n: Get a string and remove all blank spaces
 * @param str a string
 * @return the trimmed string
 */
std::string OpenServerCommand::removeSpaces(std::string str) {
  str.erase(remove(str.begin(), str.end(), '\n'), str.end());
  return str;
}

void OpenServerCommand::split_and_update_data(char *buffer, map<int, pair<string, string>> *map_data) {
  char *tokens;
  int indicator = 0;
  tokens = strtok(buffer, ",");
  SimulatorManager::getInstance()->mutex_lock3.try_lock();
  (*map_data)[indicator].second = tokens;
  while (indicator < 36) {
    indicator++;
    tokens = strtok(nullptr, ",");
    if (indicator == 35) {
      string number = removeSpaces(tokens);
      (*map_data)[indicator].second = number;
      return;
    }
    (*map_data)[indicator].second = tokens;
  }
  SimulatorManager::getInstance()->mutex_lock3.unlock();
}

/**
 * func get data about the airplane and update in the data_map
 * @param client_socket
 */

void OpenServerCommand::get_data_from_air_plane(int client_socket, map<int, pair<string, string>> *map_data) {
  char buffer[500] = {0};
  int data = read(client_socket, buffer, 500);
  split_and_update_data(buffer, map_data);
  while (!SimulatorManager::getInstance()->check_end()) {
    data = read(client_socket, buffer, 500);
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

  auto tempIter = list_of_strings.begin();
  SimulatorManager::getInstance()->set_server(this);
  string my_port = to_string(SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(
      *tempIter)->calculate());
  int port = atoi(my_port.c_str());
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
  client_socket = accept(socket_Server, (struct sockaddr *) &address, (socklen_t *) &address);
  if (client_socket == -1) {
    cerr << "can't accept client" << endl;
    return -3;
  }
  //sending thread to the func "get_data_from_air_plane" and make multi-threads
  this->get_info = thread(get_data_from_air_plane, client_socket, &this->data_about_airplane);
  return this->numOfArg + 1;
}
/**
 * getter value of specific variable in map of data_about_airplane
 * @param s
 * @return value
 */
float OpenServerCommand::get_value(const string &s) {
  int i = 0;
  float value = 0;
  SimulatorManager::getInstance()->mutex_lock3.try_lock();
  while (i < 36) {
    if (this->data_about_airplane[i].first == s) {
      value = stof(this->data_about_airplane[i].second);
      SimulatorManager::getInstance()->mutex_lock3.unlock();
      break;
    }
    i++;
  }
  return value;
}