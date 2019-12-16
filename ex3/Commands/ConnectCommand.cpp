//
// Created by gadi on 12/12/2019.
//


#include "ConnectCommand.h"

int connectControlClient::execute(list<string> list_of_strings) {
  char *port;
  char *ip;
  int _port;
  char char_array[(*list_of_strings.begin()).length()];
  std::strcpy(char_array, (*list_of_strings.begin()).c_str());
  //strtok for delimiters - first time
  char *token = strtok(char_array, ",");
  if (token != nullptr) {
    ip = token;
  }
  token = strtok(nullptr, ",");
  if (token != nullptr) {
    port = token;
    _port = atoi(port);
  }

  //check if the iterator move by value or reference!!!
  int socket_client = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_client == -1) {
    cerr << "can not create a client socket" << endl;
    return -1;
  }
  //create client socket
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip);
  address.sin_port = htons(_port);
  char buffer[1024] = {0};
  int data_read;
  int is_connect = connect(socket_client, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    return -2;
  }

  /**
   * check the connect between client and simulator
   */
  char msg1[] = "set controls/flight/rudder -1\r\n";
  char msg2[] = "set controls/flight/rudder 1\r\n";
  int flag = 0;
  for (int k = 0; k < 10; k++) {
    if (flag) {
      int is_send = send(socket_client, msg1, strlen(msg1), 0);
      if (is_send == -1) {
        cout << "Error sending msg" << endl;
      }
      flag = 0;
    } else {
      int is_send = send(socket_client, msg2, strlen(msg2), 0);
      if (is_send == -1) {
        cout << "Error sending msg" << endl;
      }
      flag = 1;
    }
    sleep(1);
  }
  /**
   * end check.
   */

  //close the socket in the end of the program
  return this->numOfArg + 1;
}

int connectControlClient::get_num_of_arg() {
  return this->numOfArg;
}