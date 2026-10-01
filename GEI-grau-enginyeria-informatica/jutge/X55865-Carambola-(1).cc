#include <iostream>
#include <vector>
using namespace std;


typedef vector< vector<char> > Tauler;

struct Bola {
	int x_ant, y_ant;	//Posicio anterior de la bola
	int x_act, y_act;	//Posicio actual de la bola
	int x_seg, y_seg;	//Posicio seguent de la bola
};



//Actualitza el tauler amb les noves posicions de la bola ø
void new_tauler(Tauler& M, Bola& b) {
	M[b.x_ant][b.y_ant] = '=';
	M[b.x_act][b.y_act] = 'B';
}


//Diu si la bola està a una cantonada
//Pre: la bola està dins del tauler
bool corner(const Bola& b, int f, int c) {
	if ((b.x_act == 0 || b.x_act == f-1) && (b.y_act == 0 || b.y_act == c-1)) return true;
	return false;
}


//Diu si la bola es pot seguir movent o si s'ha de parar
//ja sigui cantonada o que troba la vermella
bool move(const Tauler& t, Bola& b, int f, int c) {
	if (corner(b, f, c)) {
		if (b.x_act == 0) b.x_seg = 1;
		if (b.x_act == f - 1) b.x_seg = f - 2;
		if (b.y_act == 0) b.y_seg = 1;
		if (b.y_act == c - 1) b.y_seg = c - 2;
	}
	//Actualitzacio posicions
	b.x_ant = b.x_act;
	b.y_ant = b.y_act;
	b.x_act = b.x_seg;
	b.y_act = b.y_seg;
	b.x_seg = 2*b.x_act - b.x_ant;
	b.y_seg = 2*b.y_act - b.y_ant;
	bool edge_f = false;
	bool edge_c = false;
	if (b.x_act == 0 || b.x_act == f-1) edge_f = true;
	if (b.y_act == 0 || b.y_act == c-1) edge_c = true;
	if (edge_f && edge_c) {
		b.x_seg = b.x_act;
		b.y_seg = b.y_act;
	}
	else if (edge_f) b.x_seg = b.x_ant;
	else if (edge_c) b.y_seg = b.y_ant;
	if (edge_f || edge_c || t[b.x_act][b.y_act] == 'b') return true;
	else return false;
}


//Mou la bola fins que xoca
void moure_fins_xocar(Tauler& t, Bola& b) {
	int f = t.size();
	int c = t[0].size();
	while (!move(t, b, f, c)) new_tauler(t, b);
}


//Retorna la funcio fins a 4 possibles rebots per a que segueixi el joc
//Pre: xocs = 0
bool play(Tauler& t, Bola& b, int xocs, int f, int c) {
	if (xocs < 4) {
		moure_fins_xocar(t, b);
		bool xoc = false;
		if (t[b.x_act][b.y_act] == 'b') xoc = true;
		new_tauler(t, b);
		if (xoc) {
			return xocs == 3;
		}
		if (corner(b, f, c)) return false;
		else cout << "(" << b.x_act << "," << b.y_act << ")";
		return play(t, b, xocs+1, f, c);
	}
	return false;
}


//Escriu el tauler resultant ø
void write_matrix(const Tauler& T) {
	int f = T.size();
	int c = T[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << T[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


//Pre: Llegeix un seguit de Taulers tamany fxc i la posicio de 2 boles ø
//Post: Per a cada cas escriu els punts on rebota, si ho fa, si fa carambola
//		i el nou tauler modificat
int main() {
	int f, c;
	while (cin >> f >> c) {
		Bola b;
		int x, y;
		cin >> b.x_act >> b.y_act >> x >> y;
		Tauler M(f, vector<char> (c, '.'));
		M[b.x_act][b.y_act] = 'B';
		M[x][y] = 'b';
		if (play(M, b, 0, f, c)) cout << ": si" << endl;
		else cout << ": no" << endl;
		new_tauler(M, b);
		write_matrix(M);
	}
}
