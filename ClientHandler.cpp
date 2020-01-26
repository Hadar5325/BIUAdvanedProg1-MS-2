
#include <unistd.h>
#include <sys/socket.h>
#include "ClientHandler.h"
#include "Matrix.h"
#include "Searchable.h"

const vector<string> splitByChar(string wholeString, char delimeter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(wholeString);
  while (getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}
void MatrixSearchingClientHandler::handleClient(int client_port) {
  const char *outputBuffer = "";
  string solutionString;

  //read from the client
  string input;
  ClientHandler::readFromClient(client_port, input);

  cout << "after reading" << endl;

  input.erase(remove(input.begin(), input.end(), ' '), input.end());
  string problem = input.substr(0, input.find_first_of("end"));
  vector<string> lines = splitByChar(problem, '\n');
  int columnsNumber = splitByChar(lines.at(0), ',').size();
  int rowsNumber = 0;
  for (string line : lines) {
    auto v = splitByChar(line, ',');
    if (v.size() == columnsNumber)
      rowsNumber++;

  }

  Matrix<double> *matrix = new Matrix<double>(rowsNumber, columnsNumber);
  matrix->setString(problem);

  //build the matrix:
  unsigned int row;
  for (row = 0; row < rowsNumber; row++) {
    unsigned int col = 0;
    string line = lines.at(row);
    vector<string> cellValues = splitByChar(line, ',');
    for (string value : cellValues) {
      if (value == "") continue;
      try {
        double val = stod(value);
        Cell<double> *cell = new Cell<double>(row, col, val);
        matrix->insertToMatrix(cell);
        col++;
      } catch (...) {
        cout << "Can not convert value of matrix to double" << endl;
      }
    }
  }

  //the next 2 lines are the entering and exiting locations

  string line = lines.at(row);
  vector<string> cellValues = splitByChar(line, ',');
  matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));
  row++;
  line = lines.at(row);
  cellValues = splitByChar(line, ',');
  matrix->setExitingPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

  if (this->c->isCached(matrix)) {
    try {
      solutionString = this->c->getSolutionToProblem(matrix) + '\n';
      outputBuffer = solutionString.c_str();
      send(client_port, outputBuffer, strlen(outputBuffer), 0);
      close(client_port);
    } catch (const char *e) {
      cout << e << endl;
      solutionString = this->solver->solve(matrix);
      this->c->saveSolutionForProblem(matrix, solutionString);
      solutionString += '\n';
      outputBuffer = solutionString.c_str();
      send(client_port, outputBuffer, strlen(outputBuffer), 0);
      close(client_port);

    }
  } else {
    try {
      cacheMutex.lock();
      solutionString = this->solver->solve(matrix);
      cout << solutionString << endl;
      cacheMutex.unlock();
      this->c->saveSolutionForProblem(matrix, solutionString);
      solutionString += '\n';
      outputBuffer = solutionString.c_str();
      send(client_port, outputBuffer, strlen(outputBuffer), 0);
      close(client_port);
    } catch (const char *e) {
      close(client_port);
      cout << e << endl;
    }

  }

}

void MyTestClientHandler::handleClient(int client_port) {
  string solutionString;
  const char *outputBuffer = "";
  //read from the client
  string input;

  cout << "after handleing" << endl;
  ClientHandler::readFromClient(client_port, input);

  string problem = input.substr(0, input.find_first_of("end"));
  if (this->c->isCached(&problem)) { //if already has solution
    solutionString = this->c->getSolutionToProblem(&problem) + '\n';
    outputBuffer = solutionString.c_str();
    //send the solution to client.
    send(client_port, outputBuffer, strlen(outputBuffer), 0);
    cout << "after handleing" << endl;

  } else {
    //solver it with the solver, and save the solution.
    solutionString = this->solver->solve(&problem);
    this->c->saveSolutionForProblem(&problem, solutionString);
    solutionString += '\n';
    outputBuffer = solutionString.c_str();
    //send the solution to client.
    send(client_port, outputBuffer, strlen(outputBuffer), 0);
    cout << "after handleing" << endl;
  }

}
void sleepFunc() {
  this_thread::sleep_for(1500ms);
}
void ClientHandler::readFromClient(int client_port, string &input) const {
  input = "";
  char inputBuffer[2048] = {0};
  string end = "";
  while (true) {

    int vl = read(client_port, inputBuffer, 2048);
    if (vl == -1) {
      break;
    }
    end = inputBuffer;
    input += inputBuffer;
    if (end.find("end") != string::npos)
      break;
    thread sleepT(sleepFunc);
    sleepT.join();
  }

}


