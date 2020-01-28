#ifndef STATE_H
#define STATE_H

#include <string>
#include "StateValueContainer.h"
#include <iostream>
#include <map>
using namespace std;
template<class T>
class State {
 private:
  //The value container of the state
  StateValueContainer<T> *stateValue;
  //Self cost to enter the state
  double selfCost;
  //Accumulated cost of the path.
  double cost;
  //F costs score - currnet cost + value of the hueristcs function.
  double fCost;
  State<T> *cameFrom;
  //step string representation
  string stepString;
  //neighbors map for directions -the keys are the identifier of the neighbor
  map<string, string> neighborsDirections;

 public:
  State<T>() {
    cost = 0;
    cameFrom = nullptr;
    stepString = "";
    fCost = 0;
  }

  bool equal_to(State<T> *state) {
    return this->stateValue->equal_to(state->stateValue);
  }
  void setCameFrom(State<T> *u) {
    this->cameFrom = u;
    this->cost = cameFrom->cost + this->selfCost;
    this->stepString = u->neighborsDirections[this->getIndetifier()];
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
    this->stateValue = value;
  }
  StateValueContainer<T> *getStateValue() {
    return stateValue;
  }

  void setStepString(string step) {

    this->stepString = step;
  }
  string getStepString() {

    return this->stepString;
  }

  string toString() {
    //if is a number cant it to int.
    string s = to_string(cost);
    if (std::is_same<T, float>::value
        || std::is_same<T, int>::value
        || std::is_same<T, double>::value)
      s = to_string((int) cost);
    return stepString + " (" + s + ")";

  }

  string getIndetifier() {
    string str = this->stateValue->identifier();
    return str;
  }

  void setNeighborsDirections(map<string, string> neighborsDirectionsMap) {
    neighborsDirections = neighborsDirectionsMap;
  }
  string getDirectionOfNeighbor(string identifingString) {

    return neighborsDirections[identifingString];

  }
};

#endif