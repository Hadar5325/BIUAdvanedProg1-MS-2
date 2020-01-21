#include "Server.h"
#include "Matrix.h"
#include "Searchable.h"

using namespace std;
using namespace server_side;



int main(int argc, char const *argv[]) {
  //boot::Main m;
  //m.main(argv[1]);


  //Searchables - matrices , the template type is Cell of double.
  vector<Searchable<Cell<double>> *> vectorOfSearchables;

  for (unsigned int i = 15; i <= 50; i++) {

    //open the file for reading.
    string fileName = "../matrices/Matrix" + to_string(i) + "x" + to_string(i) + ".txt";
    fstream file(fileName, ios::in);
    string line;

    Matrix<double> *matrix = new Matrix<double>(i, i);
    //read the values of the matrix, the dim is  ixi
    for (unsigned int row = 0; row < i; row++) {
      //read the line
      getline(file, line);
      //split the values
      vector<string> cellValues = splitByChar(line, ',');
      //build the matrix:
      unsigned int col = 0;
      for (string value : cellValues) {
        double val = stod(value);
        Cell<double> cell(row, col, val);
        matrix->insertToMatrix(cell);
      }

    }

    //the next 2 lines are the entering and exiting locations
    getline(file, line);
    vector<string> cellValues = splitByChar(line, ',');
    matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

    getline(file, line);
    cellValues = splitByChar(line, ',');
    matrix->setEnteringPositionRowAndCol(stod(cellValues.at(0)), stod(cellValues.at(1)));

    //insert the matrix to the vector;

    vectorOfSearchables.push_back(matrix);

    file.close();
  }

  vector<Searcher<Cell<double>> *> searchers;
  searchers.push_back(new BestFS<Cell<double>>());
  searchers.push_back(new BFS<Cell<double>>());
  searchers.push_back(new DFS<Cell<double>>());
  searchers.push_back(new AStar<Cell<double>>());
  //
  for (auto searcher : searchers) {
    for (auto matrix : vectorOfSearchables) {
      for (int i = 0; i < 10; i++) {



      }

    }

  }

}