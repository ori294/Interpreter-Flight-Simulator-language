//
// Created by gadi on 12/12/2019.
//

#include "OpenServerCommand.h"

/**
 * func get data about the airplane and update in the data_map
 * @param client_socket
 */
static void get_data_from_air_plane(int client_socket) {
  char buffer[1024] = {0};
  int data = read(client_socket, buffer, 1024);
  while (data != -1) {
    cout << buffer << endl;
    data = read(client_socket, buffer, 1024);
  }
}

/**
 * create socket server and wait for the connecting of the simulator .
 * after the connecting sending new thread of server-simulator in func get_data_from_air_plane
 * @param list_of_strings
 * @param indicator point on the string we need
 * @return indicator for how many steps jump on the list
 */
int OpenServerCommand::execute(list<string> list_of_strings, list<string>::iterator indicator) {
  string number_port = *indicator;
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
  //sendig thead to the func "get_data_from_air_plane" and make multi-threads
  this->get_info = thread(get_data_from_air_plane, client_socket);
  get_info.join();
  return 2;
}
