
#ifndef MATRIX_H_
#define MATRIX_H_

#include <tuple>
#include "Searchable.h"
#include "StateValueContainer.h"
#include <vector>

using namespace std;
template<class T>
class Matrix : public Searchable<T> {
  vector<vector<Cell<T> *>> matrix;
  int rowsNumber;
  int columnsNumber;
  tuple<int, int> enteringPosition;
  tuple<int, int> exitingPosition;
 public:
  Matrix(int rows, int columns) : matrix(rows), rowsNumber(rows), columnsNumber(columns) {
    for (int i = 0; i < rows; i++)
      matrix[i].resize(columns);
  }

  State<T> *getInitialState() {
    State<T> *firstState = new State<T>();
    auto cell = this->matrix[get<0>(enteringPosition)][get<1>(enteringPosition)];
    firstState->setStateValue(cell);
    T val = firstState->getStateValue()->getValue();
    //TODO support -1 in the entering position
    firstState->setCost(val);
    firstState->setSelfCost(val);
    return firstState;
  }
  bool isGoalState(State<T> *state) {
    State<T> *goal = new State<T>();;
    goal->setStateValue(this->matrix[get<0>(exitingPosition)][get<1>(exitingPosition)]);
    return state->equal_to(goal);
  }
  vector<State<T> *> getAllPossibleStates(State<T> *state) {
    vector<State<T> *> statesVector;

    Cell<T> *cell = (Cell<T> *) state->getStateValue();

    if (cell->i() != rowsNumber - 1) {
      State<T> *downCell = new State<T>();;
      downCell->setCameFrom(state);
      downCell->setStepString("Down");
      downCell->setStateValue(matrix[cell->i() + 1][cell->j()]);
      T val = downCell->getStateValue()->getValue();
      if (val != -1) {
        downCell->setCost(val + state->getCost());
        downCell->setSelfCost(val);
        statesVector.push_back(downCell);
      } else {
        delete downCell;
      }

    }
    if (cell->j() != columnsNumber - 1) {
      State<T> *rightCell = new State<T>();
      rightCell->setCameFrom(state);
      rightCell->setStepString("Right");
      rightCell->setStateValue(matrix[cell->i()][cell->j() + 1]);
      T val = rightCell->getStateValue()->getValue();
      if (val != -1) {
        rightCell->setCost(val + state->getCost());
        rightCell->setSelfCost(val);
        statesVector.push_back(rightCell);
      } else {
        delete rightCell;
      }

    }

    return statesVector;
  }
  string to_string() {

  }

  double h(State<T> *s) {

    Cell<T> *cell = (Cell<T> *) s->getStateValue();

    try {

      double disX = 0;
      double disY = 0;
      int row = cell->i();
      int col = cell->j();

      for (int j = cell->j(); j < rowsNumber; j++)
        disX += (double) matrix[row][j]->getValue();

      for (int i = cell->i(); i < rowsNumber; i++)
        disY += (double) matrix[i][col]->getValue();

      return abs(disX) + abs(disY);

    } catch (...) {
      double val = (double) cell->getValue();
      double disX = 0;
      double disY = 0;
      int row = cell->i();
      int col = cell->j();

      for (int j = cell->j(); j < rowsNumber; j++)
        disX++;

      for (int i = cell->i(); i < rowsNumber; i++)
        disY++;

      return abs(disX) + abs(disY);
    }

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
    this->enteringPosition = tuple<int, int>(row, col);
  }

  void setExitingPositionRowAndCol(int row, int col) {
    this->exitingPosition = tuple<int, int>(row, col);
  }
};

#endif //MATRIX_H_



