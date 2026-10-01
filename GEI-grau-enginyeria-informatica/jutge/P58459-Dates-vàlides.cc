#include <iostream>
using namespace std;


//Pre: Llegeix una data
//Post: Sabem si es correcta o no
bool es_data_valida(int d, int m, int a) {
	if (m == 1 or m == 3 or m == 5 or m == 7 or m == 8 or m == 10 or m == 12) {
		if (d <= 31 and d > 0) return true;
		else return false;
	}
	else if (m == 2) {
		if (a%4 == 0) {
			if ((a%100 != 0) or (a%100 == 0 && (a/100)%4 == 0))
				if (d <= 29 and d > 0) return true;
				else return false;
			else {
				if (d <= 28 and d > 0) return true;
				else return false;
			}
		}
		else {
			if (d <= 28 and d > 0) return true;
			else return false;
		}
	}
	else {
		if (m > 0 and m < 12) {
			if (d <= 30 and d > 0) return true;
			else return false;
		}
		else return false;
	}
}