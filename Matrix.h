
#include <tuple>
#include "Searchable.h"
#include "StateValue.h";

template<class T>
class Cell : public StateValue<T> {

 private:
  int row;
  int col;
  T value;

 public:
  Cell<T>() {
    row = 0;
    col = 0;
  }
  Cell<T>(int rowNum, int colNum, T val) : row(rowNum), col(colNum), value(val) {}
  const int i() {
    return col;
  }
  const int j() {
    return row;
  }
  const T getValue() const {
    return value;
  }

  bool equal_to(Cell<T> cell) {
    return this->col == cell.col && this->row == cell.row;
  }

};

template<class T>
class Matrix : public Searchable<Cell<T>> {
  Cell<T> **matrix;
  int rowsNumber;
  int columnsNumber;
  tuple<int, int> enteringPosition;
  tuple<int, int> exitingPosition;
 public:
  Matrix(int rows, int columns) : matrix(new Cell<T> *[columns]), rowsNumber(rows), columnsNumber(columns) {

    for (unsigned i = 0; i < rows; i++)
      for (unsigned j = 0; j < columns; j++)
        matrix[i][j] = nullptr;
  }

  State<Cell<T>> getInitialState() {
    State<Cell<T>> firstState;
    firstState.setStateValue(this->matrix[get<0>(enteringPosition)][get<1>(enteringPosition)]);

    return firstState;
  }
  bool isGoalState(State<Cell<T>> state) {
    State<Cell<T>> goal;
    goal.setStateValue(this->matrix[get<0>(exitingPosition)][get<1>(exitingPosition)]);
    return state.equal_to(goal);
  }
  vector<State<Cell<T>>> getAllPossibleStates(State<Cell<T>> *state) {
    vector<State<Cell<T>>> statesVector;

    Cell<T> cell = (Cell<T>) state->getStateValue();

    if (cell.i() != rowsNumber - 1) {
      State<Cell<T>> downCell;
      downCell.setCameFrom(state);
      downCell.setStepString("Down");
      downCell.setStateValue(matrix[cell.i() + 1][cell.j()]);
      statesVector.push_back(downCell);
    }
    if (cell.j() != columnsNumber - 1) {
      State<Cell<T>> rightCell;
      rightCell.setCameFrom(state);
      rightCell.setStepString("Right");
      rightCell.setStateValue(matrix[cell.i()][cell.j() + 1]);
      statesVector.push_back(rightCell);
    }

    return statesVector;
  }
  string to_string() {

  }

  double h(State<Cell<T>> s) {

    Cell<T> cell = (Cell<T>) s.getStateValue();

    try {

      double disX = 0;
      double disY = 0;
      int row = cell.i();
      int col = cell.j();

      for (int j = cell.j(); j < rowsNumber; j++)
        disX += (double) matrix[row][j].getValue();

      for (int i = cell.i(); i < rowsNumber; i++)
        disY += (double) matrix[i][col].getValue();

      return abs(disX) + abs(disY);

    } catch (...) {
      double val = (double) cell.getValue();
      double disX = 0;
      double disY = 0;
      int row = cell.i();
      int col = cell.j();

      for (int j = cell.j(); j < rowsNumber; j++)
        disX++;

      for (int i = cell.i(); i < rowsNumber; i++)
        disY++;

      return abs(disX) + abs(disY);
    }

  }
  void insertToMatrix(Cell<T> c) {

    matrix[c.i()][c.j()] = c;

  }
  const Cell<T> getCell(int i, int j) {
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




