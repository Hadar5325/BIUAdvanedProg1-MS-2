
#include "Searchable.h"
template<class T>
class Cell {

 private:
  int col;
  int row;
  T value;

 public:
  const int i() {
    return col;
  }
  const int j() {
    return row;
  }
  const T getValue() {
    return value;
  }

  bool equal_to(Cell<T> cell) {
    return this->col == cell.col && this->row == cell.row;
  }

};

template<class T> //TODO support start and goal cells
class Matrix : public Searchable<Cell<T>> {
  Cell<T> **matrix;
  int rowsNumber;
  int columnsNumber;
 public:
  Matrix(int rows, int columns) : matrix(new Cell<T> *[columns]), rowsNumber(rows), columnsNumber(columns) {

  }

  State<Cell<T>> getInitialState() {
    State<Cell<T>> firstState;
    firstState->setStateValue(this->matrix[0][0]);

    return firstState;
  }
  bool isGoalState(State<T> state) {

    State<Cell<T>> goal;
    goal->setStateValue(this->matrix[rowsNumber - 1][columnsNumber - 1]);
    return state.equal_to(goal);
  }
  vector<State<Cell<T>>> getAllPossibleStates(State<T> state) {
    vector<State<Cell<T>>> statesVector;

    Cell<T> cell = (Cell<T>) state.getStateValue();

    if (cell.i() != rowsNumber - 1) {
      State<T> downCell;
      downCell.setCameFrom(state);
      downCell.setStepString("Down");
      downCell.setStateValue(matrix[cell.i() + 1][cell.j()]);
      statesVector.push_back(downCell);
    }
    if (cell.j() != columnsNumber - 1) {
      State<T> rightCell;
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
        disX += (double)matrix[row][j].getValue();

      for (int i = cell.i(); i < rowsNumber; i++)
        disY += (double)matrix[i][col];

      return abs(disX) + abs(disY);

    } catch (...) {
      double val = (double) cell.getValue();
      double disX = 0;
      double disY = 0;
      int row = cell.i();
      int col = cell.j();

      for (int j = cell.j(); j < rowsNumber; j++)
        disX ++;

      for (int i = cell.i(); i < rowsNumber; i++)
        disY ++;

      return abs(disX) + abs(disY);
    }

  }
  void insertToMatrix(int i, int j, Cell<T> c) {
    matrix[i][j] = c;

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
};




