#include <iostream>
#include <set>
#include <string>
using namespace std;
 
 
void is_activity(set<string>& aa, set<string>& aux){
  set<string>::iterator it = aa.begin();
  while(it != aa.end()){
    if(aux.find(*it) == aux.end()) it = aa.erase(it);
    else ++it;
  }
}
 
void is_not_act(set<string>& na, set<string>& aux){
  set<string>::iterator it = na.begin();
  while(it != na.end()){
    if(aux.find(*it) != aux.end()) it = na.erase(it);
    else ++it;
  }
}
 
void write_output(set<string> aa, set<string> na){
  set<string>::iterator it = aa.begin();
  cout << "Totes les activitats:";
  while(it != aa.end()){
    cout << " " << *it;
    ++it;
  }
  cout << endl;
  it = na.begin();
  cout << "Cap activitat:";
  while(it != na.end()){
    cout << " " << *it;
    ++it;
  }
  cout << endl;
}
 
 
int main(){
  set<string> aa;	// All activities
  set<string> na;	// None activities
  string s;
  while(cin >> s and s != "."){
    aa.insert(s);
    na.insert(s);
  }
  int n;
  cin >> n;
  for(int i = 0; i < n; ++i){
    set<string> aux;
    while(cin >> s and s != ".") aux.insert(s);
    is_activity(aa, aux);
    is_not_act(na, aux);
  }
  write_output(aa, na);
}
