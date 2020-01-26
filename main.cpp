#include "Server.h"
#include "Matrix.h"
#include "Searchable.h"
#include "SearchOnMatrixExperiment.h"
//#include "Searcher.h"

using namespace std;
using namespace server_side;

extern const vector<string> splitByChar(string wholeString, char delimeter);

void checkexample();
int main(int argc, char const *argv[]) {
  //boot::Main m;
  //m.main("5400");

 //checkexample();

  SearchOnMatrixExperiment *search_on_matrix_experiment = new SearchOnMatrixExperiment();
  search_on_matrix_experiment->experiment();

}
void checkexample() {
  vector<Searcher<double> *> searchers;
  searchers.push_back(new BestFS<double>());
  searchers.push_back(new DFS<double>());
  searchers.push_back(new AStar<double>());
  string fileName = "../matrix_test.txt";
  fstream file(fileName, ios::in);
  string line;
  Matrix<double> *matrix = new Matrix<double>(37, 37);
  //read the values of the matrix, the dim is  ixi
  for (unsigned int row = 0; row < 37; row++) {
    //read the line
    getline(file, line);
    //split the values
    vector<string> cellValues = splitByChar(line, ',');
    //build the matrix:
    unsigned int col = 0;
    for (string value : cellValues) {
      double val = stod(value);
      Cell<double> *cell = new Cell<double>(row, col);
      cell->setValue(val);
      matrix->insertToMatrix(cell);
      col++;
    }

  }

  //the next 2 lines are the entering and exiting locations
  getline(file, line);
  vector<string> cellValues = splitByChar(line, ',');
  matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

  getline(file, line);
  cellValues = splitByChar(line, ',');
  matrix->setExitingPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));
  file.close();

  for (auto s : searchers) {

    auto v = s->search(matrix);
    string path;
    auto size = v.size();
    unsigned int j = size - 1;
    State<double> *state = v.at(j);
    path += state->toString();

    for (j = size - 2; j >= 1; --j) {
      state = v.at(j);
      path += " ," + state->toString();
    }

    state = v.at(j);
    path += " ," + state->toString();

    cout << s->getSearcherName() << endl;
    cout << path << endl;
    cout << s->getNumberOfNodesEvaluated() << endl;

  }

  file.close();
}
