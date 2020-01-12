//
// Created by amit on 12/01/2020.
//

#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "Server.h"
using namespace server_side;

mutex m;
int client_socket;
int sockserver;
bool done = false;
sockaddr_in address1;

void MySerialServer::open(int port, ClientHandler *c) {
  sockserver = socket(AF_INET, SOCK_STREAM, 0);
  if (sockserver == -1) {
    std::cerr << "Cannot create a socket" << std::endl;
    throw "error occoured at opening a server";
  }
  int portNum = port;
  address1.sin_family = AF_INET;
  address1.sin_addr.s_addr = INADDR_ANY;
  address1.sin_port = htons(portNum);
  //"bind" step of opening the server
  if (bind(sockserver, (sockaddr *) &address1, sizeof(address1)) == -1) {
    std::cerr << "Cannot bind socket to ip" << std::endl;
    throw "error occoured at opening a server";
  }
  //"listen" step of opening the server
  if (listen(sockserver, SOMAXCONN) == -1) {
    std::cerr << "Error during listen command" << std::endl;
    throw "error occoured at opening a server";
  }

  start(c);
  stop();

}
const vector<string> splitByChar(string wholeString, char delimeter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(wholeString);
  while (getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}
void acceptFunc(int socket_server, sockaddr_in &address1) {
  m.lock();
  //Accept the client.
  client_socket = accept(socket_server, (struct sockaddr *) &address1, (socklen_t *) &address1);
  cout << "Accepting client...." << endl;
  if (client_socket == -1) {
    cerr << "Could not accept client" << endl;
    throw "At accepting a client.";
  }
  cout << "Client Connected" << endl;
  m.unlock();
}
void acceptClients(ClientHandler *c) {
  while () {

    //creating thread with accept step through acceptFunc
    thread acceptT(acceptFunc, sockserver, std::ref(address1));
    //wait for it to stop
    acceptT.join();

    char inputBuffer[1024] = {0};
    char outputBuffer[1024] = {0};
    int vl = read(client_socket, inputBuffer, 1024);

    vector<string> lines = splitByChar(inputBuffer, '\n');
    for(string line : lines){

      c->handleClient(line, outputBuffer);

      send(client_socket , outputBuffer , strlen(outputBuffer) , 0 );

    }
    while (inputBuffer != "end" && vl != -1) {
      int vl = read(client_socket, inputBuffer, 1024);
    }
  }

}
void MySerialServer::start(ClientHandler *c) {
  thread acceptClientsT(acceptClients, c);
  acceptClientsT.join();
}

void MySerialServer::stop() {
  close(sockserver);
}

void boot::Main::main(string port) {

  unsigned int capacity = 5;
  CacheManager<string> *cm = new FileCacheManager<string>(5);
  Solver<string, string> *solver = new StringReverser();
  ClientHandler *ch = new MyTestClientHandler();

  Server *server = new MySerialServer();
  server->open(stoi(port), ch);

}

