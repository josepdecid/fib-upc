#include <iostream>
#include <queue>
using namespace std;

int main() {
  int n;
  char action;
  priority_queue<int> pq;
  while (cin >> action) {
    switch (action) {
      case 'S':
	cin >> n;
	pq.push(n);
	break;
      case 'A':
	if (pq.empty()) cout << "error!" << endl;
	else cout << pq.top() << endl;
	break;
      case 'R':
	if (pq.empty()) cout << "error!" << endl;
	else pq.pop();
	break;
      case 'I':
	if (pq.empty()) cout << "error!" << endl;
	else {
	  int aux = pq.top();
	  pq.pop();
	  cin >> n;
	  aux += n;
	  pq.push(aux);
	}
	break;
      case 'D':
	if (pq.empty()) cout << "error!" << endl;
	else {
	  int aux = pq.top();
	  pq.pop();
	  cin >> n;
	  aux -= n;
	  pq.push(aux);
	}
	break;
      default:
	break;
    }
  }
}
