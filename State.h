
template<class T>
class State {
 private:
  T state;
  double cost;
  State<T> cameFrom;

 public:
  bool equals(State<T> state);
};



