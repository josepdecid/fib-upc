#include <iostream>
using namespace std;


//Un nombre es ascendent si ala dreta d'una xifra hi ha la mateixa xifra +1
//Si la xifra es 9 ha d'haver-hi un 0
bool es_ascendent(int n) {
	int comp = n%10;
	n = n/10;
	while (n != 0) {
		if ((n%10 + 1)%10 != comp) return false;
		else {
			comp = n%10;
			n = n/10;
		}
	} 
	return true;
}

//Pre: Llegeix un natural
//Post: Escriu si es ascendent
int main() {
	bool s2 = false;
	int x, fi = 0;
	while (not s2 && cin >> x) {
		if (fi == 0) {
			if (es_ascendent(x)) ++fi;
		}
		else if (fi == 1) {
			if (es_ascendent(x)) ++fi;
			else --fi;
		}
		if (fi == 2) s2 = true;
	}
	if (fi == 2) cout << "SI" << endl;
	else cout << "NO" << endl;
}