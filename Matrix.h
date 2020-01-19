
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

template<class T>
class Matrix : public Searchable<T> {
  Cell<T> **matrix;
  int rowsNumber;
  int columnsNumber;
 public:
  Matrix(int rows, int columns) : matrix(new Cell<T> *[columns]), rowsNumber(rows), columnsNumber(columns) {

  }

  State<Cell<T>> getInitialState() {
    State<Cell<T>> firstState = matrix[0][0];
    return;
  }
  bool isGoalState(State<T> state) {
    State<Cell<T>> *goal = new State<Cell<T>>();
    goal->setStateValue(this->matrix[rowsNumber - 1][columnsNumber - 1]);
    return state.equal_to(goal);
  }
  vector<State<Cell<T>>> getAllPossibleStates(State<T> state) {
    vector<State<Cell<T>>> statesVector;

    Cell<T> cell = state.getStateValue();

    if (cell.i() != rowsNumber - 1) {
      State<T> rightCell;
      rightCell.setCameFrom(this);
      statesVector.push_back(matrix[cell.i() + 1][cell.j()]);
    }
    if (cell.i() != columnsNumber - 1){
      State<T> leftCell;
      leftCell.setCameFrom(this);
      statesVector.push_back(matrix[cell.i()][cell.j() + 1]);
    }

    return statesVector;
  }
  string to_string() {

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




