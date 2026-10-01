#include "CuaIOParInt.hh"
#include <iostream>


int main() {
  //Lectura
  queue<ParInt> q;
  LlegirCuaParInt(q);
  
  //Distribucio
  queue<ParInt> q1;
  queue<ParInt> q2;
  
  int t1 = 0;
  int t2 = 0;
  while (!q.empty()) {
    ParInt par = q.front();
    q.pop();
    if (t1 <= t2) {
      q1.push(par);
      t1 += par.segon();
    }
    else {
      q2.push(par);
      t2 += par.segon();
    }
  }
  
  //Escriptura
  EscriureCuaParInt(q1);
  cout << endl;
  EscriureCuaParInt(q2);  
}
