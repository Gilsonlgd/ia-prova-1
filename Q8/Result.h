#ifndef RESULT_H
#define RESULT_H

#include "../cpp-text-table/TextTable.h"
#include "State.h"

#include <vector>
#include <fstream>

using namespace std;

class Result {
private:
  vector<vector<State *>> openList;
  vector<State *> closedList;
  State *goal = nullptr;

  vector<State *> getPath() const {
    vector<State *> path;
    State *current = this->goal;

    while (current != nullptr) {
      path.insert(path.begin(), current);
      current = current->getParent();
    }

    return path;
  }

public:
  Result(vector<vector<State *>> openList, vector<State *> closedList,
         State *goal) {
    this->openList = openList;
    this->closedList = closedList;
    this->goal = goal;
  }

  bool isValid() const { return this->goal != nullptr; }

  void printPath(CostType type = REAL_COST) const {
    cout << "Path:" << endl;
    vector<State *> path = this->getPath();
    int index = 0;
    for (const auto &state : path) {
      if (index > 0)
        state->print(index, type);
      index++;
    }
  }

  void printProccessTable(CostType type = REAL_COST) const {
    TextTable t('-', '|', '+');
    t.add("Nodos Abertos");
    t.add("Nodos Fechados");
    t.endOfRow();

    for (int i = 0; i < this->openList.size(); i++) {
      string openedNodes = "";
      for (int j = 0; j < this->openList[i].size(); j++) {
        openedNodes += this->openList[i][j]->fingerprint(type) + " ";
      }
      t.add(openedNodes);
      t.add(this->closedList[i]->fingerprint(type));
      t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
  }
};

#endif