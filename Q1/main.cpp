#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#include "State.h"

int MIN_OPERATORS = 1;
int MAX_OPERATORS = 2;

vector<State> successors(const State &state) {
  vector<State> succ;

  if (state.boat_left) {
    for (int m = 0; m <= MAX_OPERATORS; m++) {
      for (int c = 0; c <= MAX_OPERATORS; c++) {
        if (m + c >= MIN_OPERATORS &&
            m + c <= MAX_OPERATORS) { // Move at most MAX_OPERATORS people
          State next(state.left.missionaries - m, state.left.cannibals - c,
                     state.right.missionaries + m, state.right.cannibals + c,
                     false); // Move boat to right
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
          State next(state.left.missionaries + m, state.left.cannibals + c,
                     state.right.missionaries - m, state.right.cannibals - c,
                     true); // Move boat to left
          if (next.isValid()) {
            succ.push_back(next);
          }
        }
      }
    }
  }

  return succ;
}

vector<State> breadthFirstSearch(const State &initial) {
  queue<State> path;
  list<State> visited;
  path.push(initial);
  int count = 0;

  while (!path.empty()) {
    queue<vector<State>> frontier;
    unordered_set<string> explored;

    vector<State> path{initial};
    frontier.push(path);

    // Enquanto houver caminhos para explorar
    while (!frontier.empty()) {
      path = frontier.front();
      frontier.pop();
      State lastState = path.back();

      if (lastState.isGoal()) {
        return path;
      }

      // Gera todos os sucessores do último estado do caminho
      vector<State> succ = successors(lastState);

      // Para cada sucessor
      for (const auto &next : succ) {
        // Verifica se o estado já foi explorado
        string hash = to_string(next.left.missionaries) +
                      to_string(next.left.cannibals) +
                      to_string(next.boat_left);
        if (explored.find(hash) == explored.end()) {
          explored.insert(hash);

          // Adiciona o novo estado ao caminho
          vector<State> newPath = path;
          newPath.push_back(next);

          // Adiciona o novo caminho à fronteira
          frontier.push(newPath);
        }
      }
    }

    cout << "No solution found." << endl;
  }
}

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
  initial.print(0);

  cout << "Searching..." << endl;
  vector<State> result = breadthFirstSearch(initial);

  cout << "Path:" << endl;

  int index = 1;
  for (const auto &state : result) {
    state.print(index);
    index++;
  }

  return 0;
}