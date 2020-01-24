#ifndef STATE_H
#define STATE_H

#include <string>
#include "StateValueContainer.h"
using namespace std;
template<class T>
class State {
 private:
  StateValueContainer<T> *state;
  double selfCost;
  double cost;
  double fCost;
  State<T> *cameFrom;
  string stepString;

 public:
  State<T>() {
    cost = 0;
    cameFrom = nullptr;
    stepString = "";
    fCost = 0;
  }

  bool equal_to(State<T> *state) {
    return this->state->equal_to(state->state);
  }
  void setCameFrom(State<T> *u) {
    this->cameFrom = u;
  }
  State<T> *getCameFrom() {
    return cameFrom;
  }
  void setSelfCost(double sCost) {
    this->selfCost = sCost;
  }
  double getSelfCost() {
    return this->selfCost;
  }

  void setCost(double stateCost) {
    this->cost = stateCost;
  }

  double getCost() {
    return cost;
  }

  void setFCost(double f) {
    fCost = f;
  }

  double getFCost() {
    return fCost;
  }

  void setStateValue(StateValueContainer<T> *value) {
    this->state = value;
  }
  StateValueContainer<T> *getStateValue() {
    return state;
  }

  void setStepString(string step) {

    this->stepString = step;
  }
  string getStepString() {

    return this->stepString;
  }

  string toString() {
    string s = to_string(cost);
    if (std::is_same<T, float>::value
        || std::is_same<T, int>::value
        || std::is_same<T, double>::value)
      s = to_string((int) cost);
    return stepString + " (" + s + ")";

  }

  string identifier() {
    return this->state->identifier();
  }

};

#endif