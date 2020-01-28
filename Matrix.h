
#ifndef MATRIX_H_
#define MATRIX_H_

#include <tuple>
#include "Searchable.h"
#include "StateValueContainer.h"
#include <vector>
#include <iostream>

using namespace std;
template<class T>
class Matrix : public Searchable<T> {
  //Matrix as vector of vector of cells
  vector<vector<Cell<T> *>> matrix;
  tuple<int, int> enteringPosition;
  tuple<int, int> exitingPosition;
  //string representation of the matrix.
  string matrixString;
  int rowsNumber;
  int columnsNumber;
  //all possible states of the matrix cells
  vector<vector<State<T> *>> allStates;

  //map<string, vector<State<T>*>> neighborsMap;
 public:
  Matrix(int rows, int columns) : matrix(rows), allStates(rows), rowsNumber(rows), columnsNumber(columns) {
    //Initialize the "matrix" - the vector of vectors of cells.
    for (int i = 0; i < rows; i++)
      matrix[i].resize(columns);
    //Initialize matrix of states
    for (int i = 0; i < rows; i++)
      allStates[i].resize(columns);

  }

  State<T> *getInitialState() {
    int i = get<0>(enteringPosition);
    int j = get<1>(enteringPosition);
    allStates[i][j]->setCost(allStates[i][j]->getSelfCost());
    return allStates[i][j];
  }

  bool isGoalState(State<T> *state) {
    int i = get<0>(exitingPosition);
    int j = get<1>(exitingPosition);
    return state->equal_to(allStates[i][j]);
  }
  vector<State<T> *> getAllPossibleStates(State<T> *state) {

    Cell<T> *cell = (Cell<T> *) state->getStateValue();
    //Vector of the states neighbors.
    vector<State<T> *> statesVector;
    map<string, string> neighborsDirectionsMap;

    //convert the state value to cell<T>* so we can handle it - we are in the implementation of cells matrix.

    //Create states by the right cell and down cell of the current state - if exists (if is by wall).
    int i = cell->i();
    int j = cell->j();
    if (i >= 0 && i <= columnsNumber - 1 && j >= 0 && j <= columnsNumber - 1) { //as long as it in the matrix limits
      if (i < rowsNumber - 1) {
        //if the value is minus 1, ignore the cell and dont add it to the neighbors.
        if (matrix[i + 1][j]->getValue() != -1) {
          statesVector.push_back(allStates[i + 1][j]);
          //add the direction to the map of neighbors directions for the current state
          neighborsDirectionsMap.insert(make_pair(allStates[i + 1][j]->getIndetifier(), "Down"));

        }
      }
      if (j < columnsNumber - 1) {

        //if the value is minus 1, ignore the cell and dont add it to the neighbors.
        if (matrix[i][j + 1]->getValue() != -1) {
          statesVector.push_back(allStates[i][j + 1]);
          //add the direction to the map of neighbors directions for the current state
          neighborsDirectionsMap.insert(make_pair(allStates[i][j + 1]->getIndetifier(), "Right"));
        }

      }

      if (i > 0) {

        if (matrix[i - 1][j]->getValue() != -1) {
          statesVector.push_back(allStates[i - 1][j]);
          //add the direction to the map of neighbors directions for the current state
          neighborsDirectionsMap.insert(make_pair(allStates[i - 1][j]->getIndetifier(), "Up"));
        }

      }
      if (j > 0) {
        //if the value is minus 1, ignore the cell and dont add it to the neighbors.
        if (matrix[i][j - 1]->getValue() != -1) {
          statesVector.push_back(allStates[i][j - 1]);
          //add the direction to the map of neighbors directions for the current state
          neighborsDirectionsMap.insert(make_pair(allStates[i][j - 1]->getIndetifier(), "Left"));
        }
      }
    }

    state->setNeighborsDirections(neighborsDirectionsMap);

    return statesVector;
  }

  vector<State<T>*> getAllStates(){

    vector<State<T>*> all;
    for(int i = 0; i < rowsNumber; i++){
      for(int j = 0; j < columnsNumber; j++){
        all.push_back(allStates[i][j]);
      }
    }

    return all;

  }
  operator string() const {
    return matrixString;
  }

  void setString(string matrixS) {
    matrixString = matrixS;
  }

  double heuristicsFunction(State<T> *s) {
    //https://www.geeksforgeeks.org/a-search-algorithm/
    //Used for the Astar algorithm.

    Cell<T> *cell = (Cell<T> *) s->getStateValue();
    double disX = 0;
    double disY = 0;
    disX = cell->i() - get<0>(exitingPosition);
    disY = cell->j() - get<1>(exitingPosition);
    return abs(disX) + abs(disY);

  }
  void insertToMatrix(Cell<T> *c) {
    auto i = c->i();
    auto j = c->j();
    this->matrix[i][j] = c;

    State<T> *state = new State<T>();
    state->setStateValue(matrix[i][j]);
    state->setSelfCost(c->getValue());
    allStates[i][j] = state;
  }

  void resetAllStates() {
    for (int i = 0; i < rowsNumber; i++) {
      for (int j = 0; j < rowsNumber; j++) {
        State<T> *state = new State<T>();
        state->setStateValue(matrix[i][j]);
        state->setSelfCost(matrix[i][j]->getValue());
        allStates[i][j] = state;
      }
    }

  }

  const Cell<T> *getCell(int i, int j) {
    return matrix[i][j];
  }

  const int getRowsNumber() {
    return rowsNumber;
  }
  const int getColumnsNumber() {
    return columnsNumber;
  }

  void setEnteringPositionRowAndCol(int row, int col) {
    //entering position for the searching.

    int i = row;
    int j = col;

    this->enteringPosition = tuple<int, int>(i, j);

  }

  void setExitingPositionRowAndCol(int row, int col) {

    //exiting position for the searching.

    int i = row;
    int j = col;

    this->exitingPosition = tuple<int, int>(i, j);
  }

  ~Matrix() {
    matrix.clear();
  }

};

#endif //MATRIX_H_



