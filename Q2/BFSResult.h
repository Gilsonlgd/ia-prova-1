#ifndef BFSRESULT_H
#define BFSRESULT_H

#include "../cpp-text-table/TextTable.h"
#include "State.h"

#include <vector>

using namespace std;

class BFSResult {
private:
  vector<vector<State *>> openList;
  vector<State *> closedList;
  State *goal = nullptr;

  vector<State *> getPath() const {
    vector<State *> path;
    State *current = this->goal;

    while (current != nullptr) {
      path.insert(path.begin(), current);
      current = current->parent;
    }

    return path;
  }

public:
  BFSResult(vector<vector<State *>> openList, vector<State *> closedList,
            State *goal) {
    this->openList = openList;
    this->closedList = closedList;
    this->goal = goal;
  }

  bool isValid() const { return this->goal != nullptr; }

  void printPath() const {
    cout << "Path:" << endl;
    vector<State *> path = this->getPath();
    int index = 1;
    for (const auto &state : path) {
      state->print(index);
      index++;
    }
  }

  void printProccessTable() const {
    TextTable t('-', '|', '+');
    t.add("Nodos Abertos");
    t.add("Nodos Fechados");
    t.endOfRow();

    for (int i = 0; i < this->openList.size(); i++) {
      string openedNodes = "";
      for (int j = 0; j < this->openList[i].size(); j++) {
        openedNodes += this->openList[i][j]->fingerprint() + " ";
      }
      t.add(openedNodes);
      t.add(this->closedList[i]->fingerprint());
      t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
  }
};

#endif