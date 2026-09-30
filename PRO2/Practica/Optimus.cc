/** @file Optimus.cc
 *  @brief Implementació de la classe Optimus
 */

#include "Optimus.hh"


void swap(string& a, string& b)
/** @brief Intercanvia els valors d'a i b.
 *  \pre Cert.
 *  \post a val b i b val a.
 */
{
  string aux = a;
  a = b;
  b = aux;
}

int absolute(int n)
/** @brief Calcula el valor absolut d'un enter.
 *  \pre Cert.
 *  \post Retorna n en valor absolut.
 */
{
  if (n < 0) n *= -1;
  return n;
}

int dist(string s1, string s2)
/** @brief Retorna la distància entre dos seccions.
 *  \pre s1 i s2 són strings de format A1.
 *  \post Retorna la distància entre les seccions s1 i s2.
 */
{
  if (s1 == s2) return 0;
  return absolute((s2[0] - 'A') - (s1[0] - 'A')) + absolute((s2[1] - '1') - (s1[1] - '1'));
}

void test_permutation(const vector<string>& u, vector<string>& optimus_path, int& total_distance)
/** @brief Comprova si la permutació actual genera el camí més curt per recórrer el camí donat.
 *  \pre u i optimus_path contenen els mateixos elements encara que no ordenats, total_distance >= 0.
 *  \post optimus_path passa a tenir l'ordre d'u i total_distance la nova distància si el camí és més curt.
 */
{
  int distancia_auxiliar = 0;
  int i = 0;
  while (i < u.size() - 1 && distancia_auxiliar <= total_distance)
  {
    distancia_auxiliar += dist(u[i], u[i+1]);
    ++i;
  }
  if (distancia_auxiliar < total_distance)
  {
    total_distance = distancia_auxiliar;
    optimus_path = u;
  }
  else if (distancia_auxiliar == total_distance)
  {
    int i = 1;
    bool found_difference = false;
    while (i < u.size() - 1 && !found_difference)
    {
      if (u[i] != optimus_path[i])
      {
	found_difference = true;
	if (u[i] < optimus_path[i]) optimus_path = u;
      }
      else ++i;
    }
  }
}

void permutations_recursive(int n, vector<string>& u, int l, vector<string>& optimus_path, int& total_distance)
/** @brief De forma recursiva genera totes les permutacions del vector u.
 *  \pre n > 0, 0 <= l <= n.
 *  \post Ha generat totes les permutacions dels elements d'u amb prefix u[1..l].
 */
{
  if (l + 1 == n) test_permutation(u, optimus_path, total_distance);
  else
  {
    int i = l;
    //Inv: Ha generat totes les permutacions de u[1..l] amb els valors [l + 1.. i - 1] a la posicio l + 1.
    while (i < n)
    {
      swap(u[l], u[i]);
      permutations_recursive(n, u, l + 1, optimus_path, total_distance);
      swap(u[l], u[i]);
      ++i;
    }
  }
}

int string_to_int(string s)
/** @brief Converteix una hora a segons en format d'enter.
 *  \pre s està en format hh:mm:ss.
 *  \post Retorna l'hora en segons.
 */
{
  return ((s[0] - '0')*10 + (s[1] - '0'))*3600 + ((s[3] - '0')*10 + (s[4] - '0'))*60 + (s[6] - '0')*10 + (s[7] - '0');
}

string int_to_string(int s)
/** @brief Converteix s segons a una hora en string.
 *  \pre s és positiu.
 *  \post Retorna un string hora en format hh:mm:ss.
 */
{
  string res = "00:00:00";
  int aux = (s/3600)%24;
  s -= aux * 3600;
  res[0] = aux/10 + '0';
  res[1] = aux%10 + '0';
  aux = (s/60);
  s -= aux * 60;
  res[3] = aux/10 + '0';
  res[4] = aux%10 + '0';
  res[6] = s/10 + '0';
  res[7] = s%10 + '0';
  return res;
}

//Private Operations

int Optimus::paying_time(Customer& c) const
{
  int time = 0;
  for (int i = 0; i < c.consult_NL(); ++i)
  {
    pair<string, int> buy = c.consult_vec_prod_comprats(i);
    Product p = extract_Product(buy.first);
    int aux = buy.second;
    time += p.consult_temps_cobrament() * aux;
  }
  return time;
}

void Optimus::refresh_cash(int temps_recollida, int mida_min)
{
  string s_temps_recollida = int_to_string(temps_recollida);
  for (int i = X_caixes - 1; i >= mida_min; --i)
  {
    while (!opt_caixers[i].empty() && opt_caixers[i].front() < s_temps_recollida)
    {
      opt_caixers[i].pop();
    }
  }
}

void Optimus::config_m(const Cjt_Customers& cc, int x, int y)
{
  //Fem reset dels caixers abans de cada configuració
  vector< queue<string> > aux(X_caixes);
  opt_caixers = aux;
  //Suma temps tots clients
  int suma_tp = 0;
  for (int i = 0; i < cc.consult_number_Customer(); ++i)
  {
    //Extreure client
    Customer c = cc.extract_Customer(i+1);
    int nom_caixa = X_caixes - 1;
    int temps_recollida = string_to_int(c.consult_instant_recollida_tiquet());
    refresh_cash(temps_recollida, X_caixes - (x + y));
    if (c.consult_cart_quantity() <= 10)
    //Recorre totes les caixes normals i ràpides
    {
      for (int j = X_caixes - 1; j >= X_caixes - (x + y); --j)
	//La caixa nom_caixa serà la caixa de [X_caixes-1..j] amb menys clients 
      {
	if (opt_caixers[j].size() < opt_caixers[nom_caixa].size()) nom_caixa = j;
      }
    }
    else
    //Recorre totes les caixes normals
    {
      for (int j = X_caixes - 1; j >= X_caixes - x; --j)
      //La caixa nom_caixa serà la caixa de [X_caixes-1..j] amb menys clients 
      {
	if (opt_caixers[j].size() < opt_caixers[nom_caixa].size()) nom_caixa = j;
      }
    }
    int cash_time = paying_time(c);
    int queue_time = 0;
    int temps_arribada_caixa = temps_recollida + (X_caixes - (nom_caixa + 1));
    if (!opt_caixers[nom_caixa].empty()) queue_time += string_to_int(opt_caixers[nom_caixa].back()) - temps_arribada_caixa + 1;
    temps_arribada_caixa += queue_time;
    suma_tp += cash_time + (X_caixes - (nom_caixa + 1)) + queue_time; //Temps pagament + temps desplaçament + temps cua
    int temps = temps_arribada_caixa + cash_time;
    opt_caixers[nom_caixa].push(int_to_string(temps - 1));
    cout << c.consult_comprador_id() << " " << nom_caixa + 1 << " " << int_to_string(temps_arribada_caixa) << " " << int_to_string(temps - 1) << endl;
  }
  cout << int_to_string(suma_tp) << endl;
}


//Public Operations

Optimus::Optimus()
{
  R = 0;
  C = 0;
  midaBloc_p = 0;
  X_caixes = 0;
  opt_caixers = vector< queue<string> > (0);
  correct_optimus = false;
}

Optimus::~Optimus() {}

void Optimus::redimension_market(int R, int C, int X, int N)
{ 
  this->R = R;
  this->C = C;
  this->X_caixes = X;
  midaBloc_p = N;
  opt_caixers = vector< queue<string> > (X);
  correct_optimus = (R > 0 && C > 0 && X_caixes > 0 && midaBloc_p > 0);
}

void Optimus::add_Product(const Product& p)
{
  map_products.insert(make_pair(p.consult_producte_id(), p));
  ++midaBloc_p;
}

int Optimus::consult_midaBloc_p() const
{
  return midaBloc_p;
}

Product Optimus::extract_Product(string s) const
{
  map<string, Product>::const_iterator it = map_products.find(s);
  if (it == map_products.end())
  {
    Product p;
    return p;
  }
  return it->second;
}

void Optimus::find_best_path(const Customer& c, int i) const
{
  cout << "millor cami " << i << ":" << endl;
  if (!c.consult_correct_customer() || !this->correct_optimus) cout << "error" << endl << endl;
  else {
    int total_distance = (R*C)+1; 
    vector<string> optimus_path;
    list<string> l;
    l.push_back("A1");
    for (int i = 0; i < c.consult_NL(); ++i)
    {
      pair<string, int> v = c.consult_vec_prod_comprats(i);
      string s = extract_Product(v.first).consult_seccio();
      list<string>::iterator it = l.begin();
      bool already = false;
      while (it != l.end() && !already)
      {
	if (*it == s) already = true;
	++it;
      }
      if (!already) l.push_back(s);
    }
    list<string>::iterator it = l.begin();
    bool already = false;
    string exit = "A-";
    exit[1] = this->C + '0';
    while (it != l.end() && !already)
    {
      if (*it == exit) already = true;
      else ++it;
    }
    if (!already) l.push_back(exit);
    else
    {
      it = l.erase(it);
      l.push_back(exit);
    }
    it = l.begin();
    vector<string> u(l.size());
    for (int i = 0; i < l.size(); ++i)
    {
      u[i] = *it;
      ++it;
    }
    optimus_path = u;
    if (optimus_path.size() == 2)
    {
      cout << dist(optimus_path[0], optimus_path[1]) << endl;
    }
    else
    {
      permutations_recursive(u.size() - 1, u, 1, optimus_path, total_distance);
      cout << total_distance << endl;
    }
    for (int i = 0; i < optimus_path.size(); ++i) cout << optimus_path[i] << " ";
    cout << endl << endl;
  }
}


void Optimus::simulate_payment(const Cjt_Customers& cc, int M){
  cout << "simular pagament:" << endl;
  if (cc.consult_number_Customer() > 0)
  {
    int x, y;
    for (int i = 0; i < M; ++i)
    {
      //x caixes normals i y ràpides
      cin >> x >> y;
      config_m(cc, x, y);
    }
    cout << endl;
  }
  else cout << "error" << endl << endl;
}


void Optimus::write_section(string s) const
{
  cout << "productes " << s << ":" << endl;
  if (s[1] < '1' || s[1] > char(C + '0') || s[0] < 'A' || s[0] >= char(R + 'A')) cout << "error" << endl << endl; 
  else
  {
    map<string, Product>::const_iterator it = map_products.begin();
    bool empty = true;
    while (it != map_products.end())
    {
      if (it->second.consult_seccio() == s) {
	if (empty) empty = false;
	else cout << endl;
	cout << it->second.consult_producte_id();
      }
      ++it;
    }
    if (empty) cout << "seccio buida";
    cout << endl << endl;
  }
}