#include "Server.h"
#include "Matrix.h"
#include "Searchable.h"
#include "SearchOnMatrixExperiment.h"

using namespace std;
using namespace server_side;



int main(int argc, char const *argv[]) {
  //boot::Main m;
  //m.main(argv[1]);

  SearchOnMatrixExperiment * search_on_matrix_experiment = new SearchOnMatrixExperiment() ;
  search_on_matrix_experiment->experiment();
}