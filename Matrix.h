
template<class T>
class Cell {

 private:
  int col;
  int row;
  T value;

 public:
  const int col_num() {
    return col;
  }
  const int row_num() {
    return row;
  }
  const T getValue() {
    return value;
  }

};

template<class T>
class Matrix {
  Cell<T> **matrix;
  int rowsNumber;
  int columnsNumber;
 public:
  Matrix(int rows, int columns) : matrix(new Cell<T> *[columns]), rowsNumber(rows), columnsNumber(columns) {
  }
  Cell<T> operator [] (int rowNum, int colNum) {
    return matrix[rowNum][colNum];
  }

  const int getRowsNumber() {
    return rowsNumber;
  }
  const int getColumnsNumber() {
    return columnsNumber;
  }
};




