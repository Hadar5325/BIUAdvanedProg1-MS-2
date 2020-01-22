#ifndef STATE_H
#define STATE_H

#include <string>
#include "StateValue.h";
using namespace std;
template<class T>
class State {
 private:
  StateValue<T> state;
  double cost;
  State<T> *cameFrom;
  string stepString;

 public:
  State<T>() {
    cost = 0;
    cameFrom = nullptr;
    stepString = "";
  }

  bool equal_to(State<T> state) {
    return this->state.equal_to(state.state);
  }
  void setCameFrom(State<T> *u) {
    this->cameFrom = u;
  }
  State<T> *getCameFrom() {
    return cameFrom;
  }
  void setCost(double stateCost) {
    this->cost = stateCost;//== nullptr ? stateCost : stateCost + cameFrom->cost;
  }

  double getCost() {
    return cost;
  }
  void setStateValue(T value) {
    this->state = value;
  }
  const StateValue<T> getStateValue() {
    return state;
  }

  void setStepString(string step){

    this->stepString = step;
  }
  string getStepString(){

    return stepString;
  }



};

#endif