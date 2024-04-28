#include <algorithm>
#include <cstddef>
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
BFSResult breadthFirstSearch(State *initial) {
  vector<vector<State *>> openListHistory;
  vector<State *> closedListHistory;

  vector<State *> openList = {initial}; /*Vector used like a queue*/
  unordered_set<string> exploredList;
  State *currentNode = initial;

  while (!openList.empty()) {
    currentNode = openList.front(); /*Get the first element of the queue*/
    openListHistory.push_back(openList);

    if (currentNode->isGoal()) {
      closedListHistory.push_back(currentNode);
      return BFSResult(openListHistory, closedListHistory, currentNode);
    }

    vector<State *> succ = currentNode->successors();
    for (auto next : succ) {
      string hash = next->fingerprint();
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.push_back(next); /*Insert the new node in the end*/
      }
    }

    closedListHistory.push_back(currentNode);
    openList.erase(openList.begin()); /*Remove the first element*/
  }

  return BFSResult(openListHistory, closedListHistory, nullptr);
}

int main() {
  State *initial = new State(0, 0, NONE, nullptr);

  cout << "Initial state:" << endl;
  initial->print(0);

  cout << "Searching..." << endl;
  BFSResult result = breadthFirstSearch(initial);

  if (result.isValid()) {
    result.printPath();
    // result.printProccessTable();
  } else {
    cout << "No solution found" << endl;
  }

  return 0;
}