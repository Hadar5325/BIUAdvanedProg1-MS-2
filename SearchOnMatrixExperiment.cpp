//
// Created by amit on 21/01/2020.
//

#include "SearchOnMatrixExperiment.h"
#include "Server.h"
#include "Searchable.h"
#include "Matrix.h"

static const vector<string> splitByChar(string wholeString, char delimeter) {
  vector<string> tokens;
  string token;
  istringstream tokenStream(wholeString);
  while (getline(tokenStream, token, delimeter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void createExperimentFiles(vector<Matrix<double> *> vectorOfMatrices) {

  vector<Searcher<Cell<double>> *> searchers;
  searchers.push_back(new BestFS<Cell<double>>());
  searchers.push_back(new BFS<Cell<double>>());
  searchers.push_back(new DFS<Cell<double>>());
  searchers.push_back(new AStar<Cell<double>>());
  //for each searcher ,
  for (auto searcher : searchers) {
    string fileName = "../" + searcher->getSearcherName() + " Results";
    fstream file(fileName, ios::out);

    for (auto matrix : vectorOfMatrices) {
      //Write a first title
      file << "Matrix" + to_string(matrix->getRowsNumber()) + "x" + to_string(matrix->getColumnsNumber()) << endl;
      vector<int> sizesVector;
      for (int i = 0; i < 10; i++) {
        //Write a second title
        file << "Time #" + to_string(i) << endl;

        auto states = searcher->search(matrix);

        //build the path from the vector of states.
        string path;
        auto size = states.size();
        for (unsigned int i = 0; i < size - 1; i++) {
          auto state = states.at(i);
          path += state.getStepString() + " (" + to_string(state.getStateValue().getValue()) + ") ,";
        }

        //on the last one, dont add a comma after it.
        auto state = states.at(i);
        path += state.getStepString() + " (" + to_string(state.getStateValue().getValue()) + ")";

        file << path << endl;

        file << "Number of vertices : " << size << endl;
        file << "Total cost" << state.getCost() << endl;
        sizesVector.push_back(size);
      }

    }




    file.close();

  }

}

vector<Matrix<double> *> SearchOnMatrixExperiment::getVectorOfMatrices() {

  vector<Matrix<double> *> vectorOfMetrices;

  for (unsigned int i = 15; i <= 50; i++) {

    //open the file for reading.
    string fileName = "../matrices/Matrix" + to_string(i) + "x" + to_string(i) + ".txt";
    fstream file(fileName, ios::in);
    string line;

    Matrix<double> *matrix = new Matrix<double>(i, i);
    //read the values of the matrix, the dim is  ixi
    for (unsigned int row = 0; row < i; row++) {
      //read the line
      getline(file, line);
      //split the values
      vector<string> cellValues = splitByChar(line, ',');
      //build the matrix:
      unsigned int col = 0;
      for (string value : cellValues) {
        double val = stod(value);
        Cell<double> cell(row, col, val);
        matrix->insertToMatrix(cell);
      }

    }

    //the next 2 lines are the entering and exiting locations
    getline(file, line);
    vector<string> cellValues = splitByChar(line, ',');
    matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

    getline(file, line);
    cellValues = splitByChar(line, ',');
    matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

    //insert the matrix to the vector;

    vectorOfMetrices.push_back(matrix);

    file.close();
  }

  return vectorOfMetrices;

}

void SearchOnMatrixExperiment::experiment() {

  createExperimentFiles(getVectorOfMatrices());

}