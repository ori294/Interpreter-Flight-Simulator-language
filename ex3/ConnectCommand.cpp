//
// Created by gadi on 12/12/2019.
//


#include "ConnectCommand.h"

int connectControlClient::execute(list<string> list_of_strings, list<string>::iterator indicator) {
  indicator++;
  string number_port = *indicator;
  int port = atoi(number_port.c_str());
  //check if the iterator move by value or reference!!!
  int socket_client = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_client == -1) {
    cerr << "can not create a client socket" << endl;
    return -1;
  }
  //create client socket
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(5402);
  char buffer[1024] = {0};
  int data_read;
  int is_connect = connect(socket_client, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    return -2;
  }
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

  //close the socket in the end of the program
  return 3;
}
