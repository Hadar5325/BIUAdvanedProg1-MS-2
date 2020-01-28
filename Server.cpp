//
// Created by amit on 12/01/2020.
//

#define MAX_CLIENTS_NUM 10
#define TIMEOUT_SECONDS 120

#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "Server.h"
#include "AStar.h"
using namespace server_side;

mutex cacheMutex;
int serverSocket;
bool done = false;
bool canStopHandle = false;
sockaddr_in address1;
bool canStart = false;

void Server::open(int port, ClientHandler *c) {

  cout << "Opening server at port " << port << endl;
  cout << "On any error of opening the server, try again and insert different port number (5400 is recommended)"
       << endl;
  cout << "Make sure that your clients connect on the the same port that you inserted." << endl;

  this_thread::sleep_for(5s);
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
    std::cerr << "Error at binding" << std::endl;
    throw "error occoured at opening a server (already used port?)";
  }
  //"listen" step of opening the server
  if (listen(serverSocket, SOMAXCONN) == -1) {
    std::cerr << "Error during listening" << std::endl;
    throw "error occoured at opening a server";
  }

  //set timeout
  struct timeval tv;
  tv.tv_sec = TIMEOUT_SECONDS;
  tv.tv_usec = 0;
  setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

  start(c);

}
void handleClientsFunc(ClientHandler *c) {
  //Accept the client.
  cacheMutex.lock();
  cout << "Waiting for client(s) " << endl;
  cacheMutex.unlock();
  while (true) { // while its not time out, accept clients
    int client_socket = accept(serverSocket, (struct sockaddr *) &address1, (socklen_t *) &address1);
    if (client_socket == -1) {
      if (errno == EWOULDBLOCK || errno == EAGAIN) {//TIMEOUT
        cacheMutex.lock();
        cout << "Server timout" << endl;
        close(serverSocket);
        cacheMutex.unlock();
        exit(-1);
      }
      cacheMutex.lock();
      cerr << "Could not accept client " << endl;
      cacheMutex.unlock();
    } else {
      this_thread::sleep_for(1s);
      cacheMutex.lock();
      cout << "Client Connected at " << to_string(client_socket) << endl;
      cout << "Handling client at " << to_string(client_socket) << endl;
      cacheMutex.unlock();

      try {
        c->handleClient(client_socket);
        cacheMutex.lock();
        cout << "Client handled at " << to_string(client_socket) << endl;
        cacheMutex.unlock();
      } catch (const char *e) {
        cerr << "Problem handling client at " << client_socket << " :"<< endl;
        cout<<e<<endl;
      }
    }
  }

}

void MyParallelServer::start(ClientHandler *c) {
  //create an array of threads, each thread for a client.

  //each thread is a serial client accepting loop so we can support 10 clients in the same time.
  thread clients[MAX_CLIENTS_NUM];
  for (int i = 0; i < MAX_CLIENTS_NUM; i++) {
    clients[i] = thread(handleClientsFunc, c);
  }
  //Although there's no need because the only way to top is the timeout, but it is a good practice.
  for (int i = 0; i < MAX_CLIENTS_NUM; i++) {
    clients[i].join();
  }
}

void MySerialServer::start(ClientHandler *c) {
  //the function is a serial client accepting.
  handleClientsFunc(c);
}

void MySerialServer::stop() {
  close(serverSocket);
  exit(-1);
}
void MyParallelServer::stop() {
  close(serverSocket);
  exit(-1);
}

void boot::Main::main(string port) {


  //Current cache manager of a problem of matrix of doubles, and solution of string
  CacheManager<Matrix<double>, string> *cm = new FileCacheManager<Matrix<double>>();

  //Here I choose the Astar algorithm as the best one for the OA solver - MatrixProblemSolverOA of matrix of double.
  Solver<Matrix<double>, string> *solver = new MatrixProblemSolverOA<double>(new AStar<double>);

  //Client handler - custom cilent handler for the matrix searching problem.
  ClientHandler *ch = new MatrixSearchingClientHandler(solver, cm);

  Server *server = new MyParallelServer();

  try {
    //open and start accpting clients
    int p = stoi(port);
    server->open(p, ch);
  } catch (const char *e) {
    cout << e << endl;
    server->stop();
  }

}

