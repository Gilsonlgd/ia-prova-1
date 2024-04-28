#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#include "State.h"

int MIN_OPERATORS = 1; // Minimum number of operators to move the boat
int MAX_OPERATORS = 2; // Maximum number of operators to move the boat

/* Function: breadthFirstSearch
 * Description: Performs a breadth-first search to find the solution
 */
vector<State *> breadthFirstSearch(State *initial) {
  vector<State *> openList = {initial}; /* Vector used like a queue */
  unordered_set<string> exploredList;
  State *currentNode = initial;

  /* Iterate over the frontier */
  while (!openList.empty()) {
    currentNode = openList.front(); /* Get the first element of the queue */

    if (currentNode->isGoal()) {
      vector<State *> path;
      State *current = currentNode;

      while (current != nullptr) {
        path.insert(path.begin(), current);
        current = current->getParent();
      }

      return path;
    }

    vector<State *> succ =
        currentNode->successors(MAX_OPERATORS, MIN_OPERATORS);
    for (const auto &next : succ) {
      /* Check if the state has already been visited */
      string hash = next->fingerprint();
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.push_back(next); /* Insert the new node in the end */
      }
    }
    openList.erase(openList.begin()); /* Remove the first element */
  }

  return vector<State *>{}; // Empty vector
}

/* Function: handleInput
 * Description: Handles the input from the user
 */
void handleInput(int *n_missionaries, int *n_cannibals, int *n_operators) {
  cout << "Number of missionaries: ";
  cin >> *n_missionaries;
  cout << "Number of cannibals: ";
  cin >> *n_cannibals;
  cout << "Number of operators: ";
  cin >> *n_operators;
  cout << endl;
}

int main() {
  int n_missionaries = 3;
  int n_cannibals = 3;

  handleInput(&n_missionaries, &n_cannibals, &MAX_OPERATORS);
  State *initial = new State(n_missionaries, n_cannibals, 0, 0, true, nullptr);

  cout << "Initial state:" << endl;
  initial->print();

  cout << "Searching..." << endl;
  vector<State*> result = breadthFirstSearch(initial);

  if (!result.empty()) {
    cout << "Path:" << endl;
    int index = 1;
    for (const auto &state : result) {
      state->print(index);
      index++;
    }
  }

  return 0;
}