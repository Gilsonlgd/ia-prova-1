#ifndef BFSRESULT_H
#define BFSRESULT_H

#include "../cpp-text-table/TextTable.h"
#include "State.h"

#include <vector>

using namespace std;

class BFSResult {
public:
  vector<vector<State>> openList;
  vector<State> closedList;
  vector<State> path;

  BFSResult(vector<vector<State>> openList,
            vector<State> closedList, vector<State> path) {
    this->openList = openList;
    this->closedList = closedList;
    this->path = path;
  }

  bool isValid() const { return !path.empty(); }

  void printPath() const {
    cout << "Path:" << endl;
    int index = 1;
    for (const auto &state : this->path) {
      state.print(index);
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
        openedNodes += this->openList[i][j].fingerprint() + " ";
      }
      t.add(openedNodes);
      t.add(this->closedList[i].fingerprint());
      t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
  }

  void printSearchTree() const {
    cout << "Search Tree:" << endl;
    for (int i = 0; i < this->openList.size(); i++) {
      cout << "Level " << i << ":" << endl;
      for (int j = this->openList[i].size() - 1; j >= 0; j--) {
        this->openList[i][j].print(j + 1);
      }
    }
  }
};

#endif