
#include <vector>
#include <string>
#include "State.h"
using namespace std;


template<class T>
class Searchable {
  virtual State<T> getInitialState() = 0;
  virtual bool isGoalState(State<T> state) = 0;
  virtual vector<State<T>> getAllPossibleStates(State<T> state) = 0;
  virtual string to_string() = 0;
};

