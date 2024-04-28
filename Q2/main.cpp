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
BFSResult breadthFirstSearch(const State &initial) {
  vector<vector<State>> openListHistory;
  vector<State> closedListHistory;
  vector<State> finalPath;

  vector<State> openList = {initial};
  unordered_set<string> exploredList;
  State currentNode = initial;

  while (!openList.empty()) {
    currentNode = openList.front();
    openListHistory.push_back(openList);

    if (currentNode.isGoal()) {
      closedListHistory.push_back(currentNode);

      while (currentNode.parent != nullptr) {
        currentNode.print(0);
        finalPath.push_back(currentNode);
        currentNode = *currentNode.parent;
      }

      return BFSResult(openListHistory, closedListHistory, finalPath);
    }

    vector<State> succ = currentNode.successors();
    for (const auto &next : succ) {
      if (exploredList.find(next.fingerprint()) == exploredList.end()) {
        string hash = next.fingerprint();
        exploredList.insert(hash);
        openList.push_back(next);
      }
    }

    closedListHistory.push_back(currentNode);
    openList.erase(openList.begin());
  }

  return BFSResult(openListHistory, closedListHistory, {});
}

int main() {
  State initial(0, 0, NONE);

  cout << "Initial state:" << endl;
  initial.print(0);

  cout << "Searching..." << endl;
  BFSResult result = breadthFirstSearch(initial);

  if (true) {
    // result.printPath();
    result.printProccessTable();
    // result.printSearchTree();
  }

  return 0;
}