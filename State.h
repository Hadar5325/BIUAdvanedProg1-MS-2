
#include <string>
template<class T>
class State {
 private:
  T state;
  double cost;
  State<T> *cameFrom;

 public:
  State<T>() {
    cost = 0;
    cameFrom = nullptr;
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
    this->cost = cameFrom == nullptr ? stateCost : stateCost + cameFrom->cost;
  }

  double getCost() {
    return cost;
  }
  void setStateValue(T value) {
    this->state = value;
  }
  const T getStateValue() {
    return state;
  }

};




