#include <algorithm>
#include <cstddef>
#include <iostream>
#include <list>
#include <queue>
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
Result greedyBestFirstSearchCost(State *initial, CostType type = REAL_COST) {
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
      string hash = next->fingerprint(type);
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.push_back(next);
        openList.sort([type](State *a, State *b) {
          return a->getCost(type) < b->getCost(type);
        });
      }
    }

    closedListHistory.push_back(currentNode);
  }

  return Result(openListHistory, closedListHistory, nullptr);
}

/* Function: greedyBestFirstSearchHeu
 * Description: Performs a greedy best-first search to find the solution
 */
Result greedyBestFirstSearchHeu(State *initial) {
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
      string hash = next->fingerprint(HEURISTIC_COST);
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.push_back(next);
        openList.sort([](State *a, State *b) {
          return a->getHeuristic() < b->getHeuristic();
        });
      }
    }

    closedListHistory.push_back(currentNode);
  }

  return Result(openListHistory, closedListHistory, nullptr);
}

/* Function: aStarSearch
 * Description: Performs a greedy best-first search to find the solution
 */
Result aStarSearch(State *initial) {
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
      string hash = next->fingerprint(REAL_COST);
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.push_back(next);
        openList.sort([](State *a, State *b) {
          return a->getCost(REAL_COST) < b->getCost(REAL_COST);
        });
      }
    }

    closedListHistory.push_back(currentNode);
  }

  return Result(openListHistory, closedListHistory, nullptr);
}

int main() {
  State *initial = new State();

  vector<vector<int>> *board =
      new vector<vector<int>>({{1, 2, 3}, {EMPTY, 6, 4}, {8, 7, 5}});
  initial = new State(board, make_tuple(1, 0));

  cout << "Initial state:" << endl;
  initial->print(0);

  cout << "Searching..." << endl;
  // Result result = greedyBestFirstSearchCost(initial, COST_1);
  // Result result = greedyBestFirstSearchHeu(initial);
  Result result = aStarSearch(initial);

  if (result.isValid()) {
    result.printPath(REAL_COST);
    // result.printProccessTable(REAL_COST);
  } else {
    cout << "No solution found" << endl;
  }

  return 0;
}