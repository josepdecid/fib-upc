#include <iostream>
#include <vector>
using namespace std;
 
 
struct Parell {
        int valor; // != 0
        int pos; // >=0
};
 
typedef vector<Parell> Vec_Com; //Ordenat per pos
 
void llegeix(Vec_Com& v) {
        int v_tam = v.size();
        char c;
        for (int i = 0; i < v_tam; ++i) {
                cin >> v[i].valor >> c >> v[i].pos;
        }
}
 
Vec_Com suma(const Vec_Com& v1, const Vec_Com& v2) {
        int tam_v1 = v1.size();
        int tam_v2 = v2.size();
        Vec_Com sum(tam_v1 + tam_v2);
        int i = 0;
        int j = 0;
        int k = 0;
        while (i < tam_v1 && j < tam_v2) {
                if (v1[i].pos < v2[j].pos) {
                    sum[k] = v1[i];
                    ++k;
                    ++i;
                }
                else if (v1[i].pos > v2[j].pos) {
                    sum[k] = v2[j];
                    ++k;
                    ++j;
                }
                else {
					if (v1[i].valor + v2[j].valor != 0) {
						sum[k].valor = v1[i].valor + v2[j].valor;
						sum[k].pos = v1[i].pos;
						++k;
					}
					++i;
					++j;
                }
        }
        while (i < tam_v1) {
			sum[k] = v1[i];
			++k;
			++i;
		}
		while (j < tam_v2) {
			sum[k] = v2[j];
			++k;
			++j;
		}
		Vec_Com sum_comp(k);
		for (int p = 0; p < k; ++p) sum_comp[p] = sum[p];
		return sum_comp;
}
 
 
//Pre: Llegeix n parells de vectors comprimits
//Post: Escriu el vector comprimit resultant de la suma de cada parella
int main() {
        int n, tam;
        cin >> n;
        while (n != 0) {
                cin >> tam;
                Vec_Com v1(tam);
                llegeix(v1);
                cin >> tam;
                Vec_Com v2(tam);
                llegeix(v2);
                Vec_Com resultat = suma(v1, v2);
                int tam_res = resultat.size();
                if (tam_res == 1 && resultat[0].pos == -1) cout << 0 << endl;
                else {
                        int count = 0;
                        for (int i = 0; i < tam_res; ++i) {
                                if (resultat[i].valor != 0) ++count;
                        }
                        cout << count;
                        for (int i = 0; i < tam_res; ++i) {
                                cout <<" " <<resultat[i].valor << ";" << resultat[i].pos;
                        }
                        cout << endl;
                }
                --n;
        }
}