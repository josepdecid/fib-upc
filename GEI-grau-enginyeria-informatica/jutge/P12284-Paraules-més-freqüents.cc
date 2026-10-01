#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct quant{
  string s;
  int q;
};

bool ordre(const quant& a, const quant& b){
  if(a.q == b.q) return a.s < b.s;
  else return a.q > b.q;
}


int main(){
  int n, k;
  while(cin >> n >> k){
  vector<string> paraules(n);
  for(int i = 0; i < n; ++i) cin >> paraules[i];
  sort(paraules.begin(),paraules.end());
    
  vector<quant> cont(n);
  cont[0].q = 1;
  cont[0].s = paraules[0];
  int temp = 0;
  for(int i = 1; i < n; ++i){
    if(paraules[temp] == paraules[i]){
      ++cont[temp].q;
      cont[i].q = 0;
    }
    else {
      cont[i].q = 1;
      cont[i].s = paraules[i];
      temp = i;
    }
  }
  
  sort(cont.begin(),cont.end(),ordre);
  
  for(int i = 0; i < k; ++i) cout << cont[i].s << endl;
  cout << "----------" << endl;
  
  }
  
}