#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#include "BFSResult.h"
#include "State.h"

/* Function: breadthFirstSearch
 * Description: Performs a breadth-first search to find the solution
 */
BFSResult breadthFirstSearch(const State &initial) {
  queue<vector<State>> frontier;
  unordered_set<string> explored;

  vector<vector<State>> openList;
  vector<State> closedList;

  frontier.push({initial});

  /* Iterate over the frontier */
  while (!frontier.empty()) {
    vector<State> currentPath = frontier.front();
    State lastState = currentPath.back();

    frontier.pop();
    openList.push_back(currentPath);

    if (lastState.isGoal()) {
      // Encontramos uma solução, retornamos o caminho até aqui
      return BFSResult(openList, closedList, currentPath);
    }

    vector<State> succ = lastState.successors();
    for (const auto &next : succ) {
      /* Check if the state has already been visited */
      string hash = next.fingerprint();
      if (explored.find(hash) == explored.end()) {
        explored.insert(hash);

        /* Add the new state to the path */
        vector<State> newPath = currentPath;
        newPath.push_back(next);

        /* Add the new path to the frontier */
        frontier.push(newPath);
      }
    }

    closedList.push_back(lastState);
  }

  cout << "No solution found." << endl;
  // Retornamos um vetor vazio se não encontrarmos uma solução
  return BFSResult(openList, closedList, {});
}

int main() {
  State initial(0, 0, NONE);

  cout << "Initial state:" << endl;
  initial.print(0);

  cout << "Searching..." << endl;
  BFSResult result = breadthFirstSearch(initial);

  if (result.isValid()) {
    result.printPath();
    // result.printProccessTable();
    // result.printSearchTree();
  }

  return 0;
}