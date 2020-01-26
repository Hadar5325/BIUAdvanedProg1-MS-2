//
// Created by amit on 22/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__STATEVALUECONTAINER_H_
#define BIUADVANEDPROG1_MS_2__STATEVALUECONTAINER_H_

#include <string>
#include <type_traits>
using namespace std;

/**
 *
 * Abstact class for a value container for State<T>
 *
 * @tparam T innver value type
 */
template<class T>
class StateValueContainer {

 public:
  virtual const T getValue() = 0;
  virtual bool equal_to(StateValueContainer<T> *s) {};
  virtual string identifier() = 0;

};

template<class T>
class Cell : public StateValueContainer<T> { // A matrix cell is a state value container.

 private:
  int row;//row of the cell of the matrix
  int col;//col of the cell of the matrix.
  T value; //the inner value of the cell - the value that is stored, in our case is the double costs.

 public:
  Cell<T>(int rowNum, int colNum) : row(rowNum), col(colNum) {

  }
  Cell<T>(int rowNum, int colNum, T val) : row(rowNum), col(colNum), value(val) {}
  const int i() {
    return row;
  }
  const int j() {
    return col;
  }
  void setValue(T value) {
    this->value = value;
  }
  const T getValue() {
    return value;
  }

  bool equal_to(StateValueContainer<T> *c) {
    Cell<T> *cell = (Cell<T> *) c;

    //Check if the rows and cols are equal
    return this->col == cell->col && this->row == cell->row;
  }



  string identifier() { //used for hashmaps for states.
    return to_string(row) + "," + to_string(col);
  }
};
#endif //BIUADVANEDPROG1_MS_2__STATEVALUECONTAINER_H_

