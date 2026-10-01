#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
 
struct Info{
    char contingut;  // Escombraries del lloc.
    int energia;     // Energia que pot aconseguir del lloc.
};
 
typedef vector< vector<Info> > Camp;
 
void Read(Camp& M){
	int f = M.size();
	int c = M[0].size();
    for(int i=0; i<f; ++i){
        for(int j=0; j<c; ++j){
            cin >> M[i][j].contingut;
        }
    }
    char ene;
    for(int k=0; k<f; ++k){
        for(int l=0; l<c; ++l){
            cin >> ene;
            ene -= '0';
            M[k][l].energia = ene;
        }
    }
}
 
void Recorregut(Camp& M, int& f, int& c, int& energia, string s, int& escombraries){
	int i = 0;
	int tam = s.size();
	while (i < tam && energia > 0) {
		//Nord
		if (s[i] == 'N') {
			while (energia > 0 && M[f-1][c].contingut != 'X'){
				if (M[f][c].contingut != '.'){
					escombraries += M[f][c].contingut - '0';
					M[f][c].contingut = '.';
					--energia;
				}
				energia += M[f][c].energia;
				M[f][c].energia = 0;
				if (energia > 0) --f;
			}
		}
		//Sud
		else if (s[i] == 'S') {
			while (energia > 0 && M[f+1][c].contingut != 'X'){
				if (M[f][c].contingut != '.'){
					escombraries += M[f][c].contingut - '0';
					M[f][c].contingut = '.';
					--energia;
				}
				energia += M[f][c].energia;
				M[f][c].energia = 0;
				if (energia > 0) ++f;
			}
		}
		//Est
		else if (s[i] == 'E') {
			while (energia > 0 && M[f][c+1].contingut != 'X'){
				if (M[f][c].contingut != '.'){
					escombraries += M[f][c].contingut - '0';
					M[f][c].contingut = '.';
					--energia;
				}
				energia += M[f][c].energia;
				M[f][c].energia = 0;
				if (energia > 0) ++c;
			}
		}
		//Oest
		else if (s[i] == 'O') {
			while (energia > 0 && M[f][c-1].contingut != 'X'){
				if (M[f][c].contingut != '.'){
					escombraries += M[f][c].contingut - '0';
					M[f][c].contingut = '.';
					--energia;
				}
				energia += M[f][c].energia;
				M[f][c].energia = 0;
				if (energia > 0) --c;
			}
		}
		++i;
	}
	if (energia > 0 && M[f][c].contingut != '.') escombraries += M[f][c].contingut - '0';
}
 
void Write(int escombraries, int energia, int f, int c){
    cout << "escombraries: " << escombraries << endl;
    cout << "energia: " << energia << endl;
    cout << "posicio: (" << f << "," << c << ")" << endl;
}
 
 
int main(){
    int f, c;
    cin >> f >> c;
    Camp M(f, vector<Info> (c));
    Read(M);
    int energia, escombraries = 0;
    string s;
    cin >> f >> c >> energia >> s;
    Recorregut(M, f, c, energia, s, escombraries);
    Write(escombraries, energia, f, c);
}
