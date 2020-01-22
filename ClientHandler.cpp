
#include <unistd.h>
#include <sys/socket.h>
#include "ClientHandler.h"
#include "Matrix.h"
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
  //bool stopHandling = false;
  if (vl != -1) {

  }

  string input = "";
  string end = inputBuffer;
  while (vl != -1 && end.find("end") == string::npos) {
    input += inputBuffer;
    vl = read(client_port, inputBuffer, 1024);
    end = inputBuffer;
  }
  vector<string> lines = splitByChar(input, '\n');
  int columnsNumber = lines.at(0).size();
  int rowsNumber = lines.size() - 2;

  Matrix<double> *matrix = new Matrix<double>(rowsNumber, columnsNumber);

  //build the matrix:
  unsigned int row;
  for (row = 0; row < rowsNumber; row++) {
    unsigned int col = 0;
    string line = lines.at(row);
    vector<string> cellValues = splitByChar(line, ',');
    for (string value : cellValues) {
      double val = stod(value);
      Cell<double> cell(row, col, val);
      matrix->insertToMatrix(cell);
      col++;
    }
  }

  //the next 2 lines are the entering and exiting locations
  string line = lines.at(row);
  vector<string> cellValues = splitByChar(line, ',');
  matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));
  row++;
  line = lines.at(row);
  cellValues = splitByChar(line, ',');
  matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

  for (string line : lines) {
    if (line == "end") {
      stopHandling = true;
      break;
    }
    try {
      //outputBuffer = this->c->getSolutionToProblem(line)
    } catch (...) {
      //solutionString = this->solver.solve(line);
      //this->c->
      //outputBuffer = this->solver.solve(line);
    }
    send(client_port, outputBuffer, strlen(outputBuffer), 0);
  }
  if (stopHandling)
    break;

}


