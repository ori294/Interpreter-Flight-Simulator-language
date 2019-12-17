//
// Created by gadi on 12/12/2019.
//


#include <mutex>
#include "ConnectCommand.h"


std::mutex mutex_lock;

/**
 * @param list_of_strings
 * @return 0
 */
int connectControlClient::execute(list<string> list_of_strings) {
  SimulatorManager::getInstance()->set_client(this);
  list<string>::iterator it = list_of_strings.begin();
  char ip[(*it).length()]; //copy to array for strtok function
  std::strcpy(ip, (*it).c_str());
  it++;
  char port[(*it).length()]; //copy to array for strtok function
  std::strcpy(ip, (*it).c_str());
  int _port = atoi(port);
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
  this->get_info = thread(run_client_to_simulator, &this->commandsToSim, socket_client);
  get_info.join();
  //close the socket in the end of the program!!
  return 0;
}
/**
 * run in another thread until the program finish and send commands to simulator
 * @param commandsForS queue member of client for sending to simulator
 * @param socket_client
 */
void connectControlClient::run_client_to_simulator(queue<string> *commandsForS, int socket_client) {
  //run looop until end the program!
  while (!commandsForS->empty()) {
    mutex_lock.lock();
    const char *msg = commandsForS->front().c_str();
    int is_send = send(socket_client, msg, strlen(msg), 0);
    if (is_send == -1) {
      cout << "Error sending msg" << endl;
    }
  }
  mutex_lock.unlock();
}
/**
 * add one command to the queue of the client
 * @param s
 */
void connectControlClient::add_commands_to_queue(string s) {
  //lock the queue for the main thread!
  mutex_lock.lock();
  this->commandsToSim.push(s);
  mutex_lock.unlock();
}