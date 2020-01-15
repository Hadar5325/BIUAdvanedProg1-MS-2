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
int serverSocket;
bool done = false;
sockaddr_in address1;

const vector<string> splitByChar(string wholeString, char delimeter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(wholeString);
  while (getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void Server::open(int port, ClientHandler *c) {

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    std::cerr << "Cannot create a socket" << std::endl;
    throw "error occoured at opening a server";
  }
  int portNum = port;
  address1.sin_family = AF_INET;
  address1.sin_addr.s_addr = INADDR_ANY;
  address1.sin_port = htons(portNum);
  //"bind" step of opening the server
  if (bind(serverSocket, (sockaddr *) &address1, sizeof(address1)) == -1) {
    std::cerr << "Cannot bind socket to ip" << std::endl;
    throw "error occoured at opening a server";
  }
  //"listen" step of opening the server
  if (listen(serverSocket, SOMAXCONN) == -1) {
    std::cerr << "Error during listen command" << std::endl;
    throw "error occoured at opening a server";
  }

}
void MySerialServer::open(int port, ClientHandler *c) {
  Server::open(port,c);
  start(c);
}

void acceptFunc(int socket_server, sockaddr_in &address1) {
  //TODO add timeout
  //m.lock();
  //Accept the client.
  client_socket = accept(socket_server, (struct sockaddr *) &address1, (socklen_t *) &address1);
  cout << "Accepting client...." << endl;
  if (client_socket == -1) {
    cerr << "Could not accept client" << endl;
    throw "At accepting a client.";
  }
  cout << "Client Connected at" << to_string(client_socket) << "socket " << endl;
  //m.unlock();
}


void acceptClients(ClientHandler *c) {
  while () {
    //creating thread with accept step through acceptFunc
    thread acceptT(acceptFunc, serverSocket, std::ref(address1));
    //wait for it to stop
    acceptT.join();
    c->handleClient(client_socket);
  }
}
void MySerialServer::start(ClientHandler *c) {
  thread acceptClientsT(acceptClients, c);
  acceptClientsT.join();
}

void MySerialServer::stop() {
  close(serverSocket);
}

void boot::Main::main(string port) {

  //unsigned int capacity = 5;
  CacheManager<string, string> *cm = new FileCacheManager<string>();
  Solver<string, string> *solver = new StringReverser();
  ClientHandler *ch = new MyTestClientHandler(solver, cm);

  Server *server = new MySerialServer();
  server->open(stoi(port), ch);
}

