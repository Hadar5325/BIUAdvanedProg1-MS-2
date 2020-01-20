
#include <unistd.h>
#include <sys/socket.h>
#include "ClientHandler.h"
const vector<string> splitByChar(string wholeString, char delimeter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(wholeString);
  while (getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}
void MyTestClientHandler::handleClient(int client_port) {
  char inputBuffer[1024] = {0};
  char outputBuffer[1024] = {0};
  string solutionString;
  int vl = read(client_port, inputBuffer, 1024);
  bool stopHandling = false;
  while (vl != -1) {
    vector<string> lines = splitByChar(inputBuffer, '\n');
    for (string line : lines) {
      if (line == "end"){
        stopHandling = true;
        break;
      }
      try {
        outputBuffer = this->c->getSolutionToProblem(line)
      } catch (...) {
        solutionString = this->solver.solve(line);
        this->c->
        outputBuffer = this->solver.solve(line);
      }
      send(client_port, outputBuffer, strlen(outputBuffer), 0);
    }
    if(stopHandling)
      break;
  }

}


