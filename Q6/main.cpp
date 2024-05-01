#include <algorithm>
#include <cstddef>
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

#include "Result.h"
#include "State.h"

/* Function: listToVec
 * Description: Converts a list of State pointers to a vector of State pointers
 */
vector<State *> listToVec(list<State *> l) {
  vector<State *> v;
  for (auto i : l) {
    v.push_back(i);
  }
  return v;
}

/* Function: greedyBestFirstSearch
 * Description: Performs a greedy best-first search to find the solution
 */
Result greedyBestFirstSearch(State *initial) {
  vector<vector<State *>> openListHistory;
  vector<State *> closedListHistory;

  list<State *> openList;
  unordered_set<string> exploredList;
  State *currentNode = initial;

  openList.push_back(initial);

  while (!openList.empty()) {
    currentNode = openList.front();
    openListHistory.push_back(listToVec(openList));
    openList.pop_front();

    if (currentNode->isGoal()) {
      closedListHistory.push_back(currentNode);
      return Result(openListHistory, closedListHistory, currentNode);
    }

    vector<State *> succ = currentNode->successors();
    for (auto next : succ) {
      string hash = next->fingerprint();
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.push_back(next);
        openList.sort([](State *a, State *b) { return a->getHeuristic() < b->getHeuristic(); });
      }
    }

    closedListHistory.push_back(currentNode);
  }

  return Result(openListHistory, closedListHistory, nullptr);
}

int main() {
  State *initial = new State(0, City("c", 0), City("a", 0), 0, nullptr);

  cout << "Initial state:" << endl;
  initial->print(0);

  cout << "Searching..." << endl;
  Result result = greedyBestFirstSearch(initial);

  if (result.isValid()) {
    result.printPath();
    // result.printProccessTable();
  } else {
    cout << "No solution found" << endl;
  }

  return 0;
}