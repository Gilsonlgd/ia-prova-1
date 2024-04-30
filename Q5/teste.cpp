#include <queue>
#include <string>

#include <iostream>

using namespace std;

int main() {
  priority_queue<int> pq;
  pq.push(6);
  pq.push(2);
  pq.push(0);
  pq.push(9);
  pq.push(5);

  for (int i = 0; i < 5; i++) {
    cout << pq.top() << " ";
    pq.pop();
  }
  return 0;
}