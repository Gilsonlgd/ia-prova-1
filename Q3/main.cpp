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

#include "DFSResult.h"
#include "State.h"

/* Function: depthFirstSearch
 * Description: Performs a depth-first search to find the solution
 */
DFSResult depthFirstSearch(State *initial) {
  vector<vector<State *>> openListHistory;
  vector<State *> closedListHistory;

  vector<State *> openList = {initial}; /*Vector used like a stack*/
  unordered_set<string> exploredList;
  State *currentNode = initial;

  while (!openList.empty()) {
    currentNode = openList.front(); /* Get the top element of the stack */
    openListHistory.push_back(openList); 
    openList.erase(openList.begin()); /* Remove the top element */

    if (currentNode->isGoal()) {
      closedListHistory.push_back(currentNode);
      return DFSResult(openListHistory, closedListHistory, currentNode);
    }

    vector<State *> succ = currentNode->successors();
    for (auto next : succ) {
      string hash = next->fingerprint();
      if (exploredList.find(hash) == exploredList.end()) {
        exploredList.insert(hash);
        openList.insert(openList.begin(),
                        next); /* Insert the new node at the top */
      }
    }
    closedListHistory.push_back(currentNode);
  }

  return DFSResult(openListHistory, closedListHistory, nullptr);
}

int main() {
  State *initial = new State(NONE, LEFT, LEFT, LEFT, LEFT, nullptr);

  cout << "Initial state:" << endl;
  initial->print(0);

  cout << "Searching..." << endl;
  DFSResult result = depthFirstSearch(initial);

  if (true) {
    result.printPath();
    // result.printProccessTable();
  } else {
    cout << "No solution found" << endl;
  }

  return 0;
}