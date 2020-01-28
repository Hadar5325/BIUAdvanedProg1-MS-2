#pragma once
#include <vector>
#include <string>
#include "State.h"
using namespace std;

template<class T>
class Searchable {
 public:
  //Get the entering position on the searchable.
  virtual State<T> *getInitialState() = 0;
  //Checks if the states is the goal position of the searchable.
  virtual bool isGoalState(State<T> *state) = 0;
  //Get all neihbors of the states in the searchable.
  virtual vector<State<T> *> getAllPossibleStates(State<T> *state) = 0;
  //Casting function to string for the searchable.
  virtual operator std::string() const = 0;
  //Heuristics function for the AStar algorithm
  virtual double heuristicsFunction(State<T> *s) = 0;
  virtual vector<State<T> *> getAllStates() = 0;
};

