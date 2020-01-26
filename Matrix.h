
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
 public:
  Matrix(int rows, int columns) : matrix(rows), rowsNumber(rows), columnsNumber(columns) {
    //Initialize the "matrix" - the vector of vectors of cells.
    for (int i = 0; i < rows; i++)
      matrix[i].resize(columns);
  }

  State<T> *getInitialState() {
    //Create a new state with the cell of the entering position in the matrix.
    State<T> *firstState = new State<T>();
    auto cell = this->matrix[get<0>(enteringPosition)][get<1>(enteringPosition)];
    firstState->setStateValue(cell);
    T val = firstState->getStateValue()->getValue();
    firstState->setCost(val);
    firstState->setSelfCost(val);
    return firstState;
  }

  bool isGoalState(State<T> *state) {
    //Create a new state with the cell of the exiting position in the matrix.
    State<T> *goal = new State<T>();;
    goal->setStateValue(this->matrix[get<0>(exitingPosition)][get<1>(exitingPosition)]);
    return state->equal_to(goal);
  }
  vector<State<T> *> getAllPossibleStates(State<T> *state) {
    //Vector of the states neighbors.
    vector<State<T> *> statesVector;

    //convert the state value to cell<T>* so we can handle it - we are in the implementation of cells matrix.
    Cell<T> *cell = (Cell<T> *) state->getStateValue();


    //Create states by the right cell and down cell of the current state - if exists (if is by wall).
    int i = cell->i();
    int j = cell->j();
    if (i < rowsNumber - 1 && j >= 0 && j <=columnsNumber - 1) {
      State<T> *downCell = new State<T>();
      downCell->setStateValue(matrix[i + 1][j]);
      T val;
      val = downCell->getStateValue()->getValue();

      //if the value is minus 1, ignore the cell and dont add it to the neighbors.
      if (val != -1) {
        downCell->setStepString("Down");
        downCell->setSelfCost(val);
        statesVector.push_back(downCell);
      } else {
        delete downCell;
      }

    }
    if (j < columnsNumber - 1 && i >= 0 && i <=columnsNumber - 1) {
      State<T> *rightCell = new State<T>();
      rightCell->setStateValue(matrix[i][j + 1]);
      T val = rightCell->getStateValue()->getValue();
      //if the value is minus 1, ignore the cell and dont add it to the neighbors.
      if (val != -1) {
        rightCell->setStepString("Right");
        rightCell->setSelfCost(val);
        //rightCell->setCameFrom(state);
        statesVector.push_back(rightCell);
      } else {
        delete rightCell;
      }

    }

    if (i > 0 && j >= 0 && j <=columnsNumber - 1) {
      State<T> *upCell = new State<T>();;
      upCell->setStateValue(matrix[i - 1][j]);
      T val = upCell->getStateValue()->getValue();
      //if the value is minus 1, ignore the cell and dont add it to the neighbors.
      if (val != -1) {
        upCell->setSelfCost(val);
        upCell->setStepString("Up");
        //upCell->setCameFrom(state);
        statesVector.push_back(upCell);
      } else {
        delete upCell;
      }

    }
    if (j > 0 && i >= 0 && i <=columnsNumber - 1) {
      State<T> *leftCell = new State<T>();
      leftCell->setStateValue(matrix[i][j - 1]);
      T val = leftCell->getStateValue()->getValue();
      //if the value is minus 1, ignore the cell and dont add it to the neighbors.
      if (val != -1) {
        leftCell->setSelfCost(val);
        leftCell->setStepString("Left");
        //leftCell->setCameFrom(state);
        statesVector.push_back(leftCell);
      } else {
        delete leftCell;
      }

    }
    return statesVector;
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



