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
vector<State> breadthFirstSearch(const State &initial) {
  queue<vector<State>> frontier;
  unordered_set<string> explored;

  vector<State> path{initial};
  frontier.push(path);

  /* Iterate over the frontier */
  while (!frontier.empty()) {
    path = frontier.front();
    frontier.pop();
    State lastState = path.back();

    if (lastState.isGoal()) {
      return path;
    }

    vector<State> succ = lastState.successors(MAX_OPERATORS, MIN_OPERATORS);
    for (const auto &next : succ) {
      /* Check if the state has already been visited */
      string hash = next.fingerprint();
      if (explored.find(hash) == explored.end()) {
        explored.insert(hash);

        /* Add the new state to the path */
        vector<State> newPath = path;
        newPath.push_back(next);

        /* Add the new path to the frontier */
        frontier.push(newPath);
      }
    }
  }

  cout << "No solution found." << endl;
  return vector<State>{}; // Empty vector
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
  State initial(n_missionaries, n_cannibals, 0, 0, true);

  cout << "Initial state:" << endl;
  initial.print();

  cout << "Searching..." << endl;
  vector<State> result = breadthFirstSearch(initial);

  if (!result.empty()) {
    cout << "Path:" << endl;
    int index = 1;
    for (const auto &state : result) {
      state.print(index);
      index++;
    }
  }

  return 0;
}