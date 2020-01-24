//
// Created by amit on 21/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__SEARCHONMATRIXEXPERIMENT_H_
#define BIUADVANEDPROG1_MS_2__SEARCHONMATRIXEXPERIMENT_H_

#include "Matrix.h"

class SearchOnMatrixExperiment {
 private:
  vector<Matrix<double> *> createVectorOfMatrices();
  void createExperimentFiles(vector<Matrix<double> *> vectorOfMetrices);
 public:
  void experiment();
};

#endif //BIUADVANEDPROG1_MS_2__SEARCHONMATRIXEXPERIMENT_H_
