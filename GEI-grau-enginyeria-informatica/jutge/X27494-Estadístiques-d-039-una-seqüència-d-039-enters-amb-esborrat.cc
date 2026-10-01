#include <iostream>
#include <vector>
#include <list>
using namespace std;


struct Pair {
  int val;
  int freq;
};

//Afegir element a la llista
void plus_list(list<Pair>& l, int el, int& max, int &min, double& ave) {
  list<Pair>::iterator it= l.begin();
  bool found = false;
  while (it != l.end() && !found) {
    Pair p = *it;
    if (p.val == el) found = true;
    else ++it;
  }
  if (!found) {
    Pair p;
    p.val = el;
    p.freq = 1;
    l.insert(it, p);
    if (max < 0 && min < 0) max = min = el;
    else if (el > max) max = el;
    else if (el < min) min = el;
  }
  else {
    Pair p = *it;
    ++p.freq;
    *it = p;
  }
  //Càlcul AVERAGE
  ave = 0;
  int count = 0;
  for (it = l.begin(); it != l.end(); ++it) {
    Pair p = *it;
    ave += p.val * p.freq;
    count += p.freq;
  }
  ave /= count;
}


//Eliminar element de la llista
void minu_list(list<Pair>& l, int el, int& max, int &min, double& ave) {
  if (!l.empty()) {
    list<Pair>::iterator it = l.begin();
    bool found = false;
    //Eliminar
    while (!found && it != l.end()) {
      Pair p = *it;
      if (p.val == el) {
	if (p.freq == 1) it = l.erase(it); 
	else {
	  --p.freq;
	  *it = p;
	  ++it;
	}
      }
      else ++it;
    }
    //Max i Min
    if (l.empty()) max = min = 0;
    else {
      it = l.begin();
      Pair p = *it;
      max = min = p.val;
      for (it = l.begin(); it != l.end(); ++it) {
	Pair aux = *it;
	if (aux.val > max) max = aux.val;
	else if (aux.val < min) min = aux.val;
      }
    }
    //Càlcul AVERAGE
    ave = 0;
    int count = 0;
    for (it = l.begin(); it != l.end(); ++it) {
      Pair p = *it;
      ave += p.val * p.freq;
      count += p.freq;
    }
    ave /= count;
  }
  if (l.empty()) max = min = -1;
}


int main() {
  list<Pair> l;
  int op, el;
  bool finish = false;
  int max, min;
  max = min = -1;
  double ave = 0;
  while (!finish && cin >> op >> el) {
    if (op == -1) plus_list(l, el, max, min, ave);
    else if (op == -2) minu_list(l, el, max, min, ave);
    else if (op == 0 && el == 0) finish = true;
    if (!finish) {
      if (max == -1 && min == -1) cout << "0" << endl;
      else cout << min << " " << max << " " << ave <<  endl;
    }
  }
}
