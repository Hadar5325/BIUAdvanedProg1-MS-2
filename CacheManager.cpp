//
// Created by amit on 21/11/2019.
//

#include "CacheManager.h"
template<class Solution>
bool FileCacheManager<Solution>::isCached(string p) {
  return this->stringGCM.isCached(p);
}
template<class Solution>
Solution FileCacheManager<Solution>::getSolutionToProblem(string p) {
  return this->stringGCM.get(p);
}
template<class Solution>
void FileCacheManager<Solution>::saveSolutionForProblem(string problem, Solution solution) {

  this->stringGCM.insert(problem, solution);

}