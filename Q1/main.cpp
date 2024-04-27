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
/*  Function: successors
 * Description: Generates all possible states that can be reached from the
 * current state
 */
vector<State> successors(const State &state) {
  vector<State> succ;

  if (state.boat_left) {
    for (int m = 0; m <= MAX_OPERATORS; m++) {
      for (int c = 0; c <= MAX_OPERATORS; c++) {
        if (m + c >= MIN_OPERATORS &&
            m + c <= MAX_OPERATORS) { /* Move at most MAX_OPERATORS people */
          int n_ml = state.left.missionaries - m;
          int n_cl = state.left.cannibals - c;
          int n_mr = state.right.missionaries + m;
          int n_cr = state.right.cannibals + c;
          State next(n_ml, n_cl, n_mr, n_cr, false); /* Move boat to right */

          if (next.isValid()) {
            succ.push_back(next);
          }
        }
      }
    }
  } else { // Boat is on the right side
    for (int m = 0; m <= MAX_OPERATORS; m++) {
      for (int c = 0; c <= MAX_OPERATORS; c++) {
        if (m + c >= MIN_OPERATORS &&
            m + c <= MAX_OPERATORS) { // Move at most MAX_OPERATORS people
          int n_ml = state.left.missionaries + m;
          int n_cl = state.left.cannibals + c;
          int n_mr = state.right.missionaries - m;
          int n_cr = state.right.cannibals - c;
          State next(n_ml, n_cl, n_mr, n_cr, true); // Move boat to left

          if (next.isValid()) {
            succ.push_back(next);
          }
        }
      }
    }
  }

  return succ;
}

/* Function: breadthFirstSearch
 * Description: Performs a breadth-first search to find the solution
 */
vector<State> breadthFirstSearch(const State &initial) {
  queue<State> path;
  list<State> visited;
  path.push(initial);

  while (!path.empty()) {
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

      /* Generate successors of the last state */
      vector<State> succ = successors(lastState);

      for (const auto &next : succ) {
        /* Check if the state has already been visited */
        string hash = to_string(next.left.missionaries) +
                      to_string(next.left.cannibals) +
                      to_string(next.boat_left);
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
    break;
  }
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