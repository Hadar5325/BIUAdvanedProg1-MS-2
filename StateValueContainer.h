//
// Created by amit on 22/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__STATEVALUECONTAINER_H_
#define BIUADVANEDPROG1_MS_2__STATEVALUECONTAINER_H_

#include <string>
#include <type_traits>
using namespace std;
template<class T>
class StateValueContainer {

 public:
  //TODO make this const
  virtual const T getValue() = 0;
  virtual bool equal_to(StateValueContainer<T> *s) {};
  virtual string identifier() = 0;

};

template<class T>
class Cell : public StateValueContainer<T> {

 private:
  int row;
  int col;
  T value;

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
    return this->col == cell->col && this->row == cell->row;
  }



  string identifier() {
    return to_string(row) + "," + to_string(row);
  }
};
#endif //BIUADVANEDPROG1_MS_2__STATEVALUECONTAINER_H_

