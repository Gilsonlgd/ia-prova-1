#include <iostream>
using namespace std;

#include "Tree.h"
#include <queue>

int main() {
  queue<int> *values = new queue<int>(
      {20, 33, -45, 31, 24, 25, -10, 20, 40, -25, 18, -42, 24, -19, 36, -41});
  Tree *tree = new Tree(5, values);

  // tree->minMaxPropagation();
  // tree->alfaBetaLRPropagation();
  tree->alfaBetaRLPropagation();
  tree->printTree();

  return 0;
}