/**
 * @mainpage Optimització i funcionament d'un supermercat.
 
Es construeix un programa amb disseny modular que simula l'optimització el funcionament d'un supermercat.
Utilitza les classes <em>Optimus</em>, <em>Cjt_Customers</em>, <em>Customer</em>, i <em>Product</em>.
*/

/** @file program.cc
    @brief Programa principal de la practica de PRO2: 'Optimització i funcionament d'un supermercat'.
*/

#include "Optimus.hh"

void inicialitzacio(Optimus& opt);
void carregar_informacio_de_vendes(Cjt_Customers& cjt_tots_customers);
void info_producte(const Optimus& opt);
void llistat_productes(const Optimus& opt);
void llargada_millor_cami(const Optimus& opt, const Cjt_Customers& cjt_tots_customers);
void simular_pagament(Optimus& opt, const Cjt_Customers& cjt_tots_customers);


/** @brief Programa principal */
int main()
{
  Optimus opt;
  Cjt_Customers cjt_tots_customers;
  string s = " ";
  while (s != "sortir" && cin >> s)
  {
    if (s == "inicialitzar") inicialitzacio(opt);
    else if (s == "carregar") carregar_informacio_de_vendes(cjt_tots_customers);
    else if (s == "informacio") info_producte(opt);
    else if (s == "productes") llistat_productes(opt);
    else if (s == "millor") {
      string s1;
      cin >> s1;
      if (s1 == "cami") llargada_millor_cami(opt, cjt_tots_customers);
    }
    else if (s == "simular") {
      string s1;
      cin >> s1;
      if (s1 == "pagament") simular_pagament(opt, cjt_tots_customers);
    }
  }
}

void inicialitzacio(Optimus& opt)
/** @brief Inicialitza tots els paràmetres necessaris del supermercat i tots els productes que conté aquest.
 *  \pre Cert.
 *  \post S'han inicialitzat correctament el supermercat amb RxC seccions, X caixes i N Product.
 */
{
  Optimus aux;
  opt = aux;
  int R, C, X, N;
  cin >> R >> C >> X >> N;
  opt.redimension_market(R, C, X, N);
  for (int i = 0; i < N; ++i) {
    Product p;
    p.read_product();
    opt.add_Product(p);
  }
}

void carregar_informacio_de_vendes(Cjt_Customers& cjt_tots_customers)
/** @brief Realitza el seguit d'operacions necessàries per a carregar la informació dels Customer.
 *  \pre Cert.
 *  \post El Cjt_Customers cjt_tots_customers té tota la informació sobre els Customer.
 */
{
  Cjt_Customers aux;
  cjt_tots_customers = aux;
  int L;
  cin >> L;
  cjt_tots_customers.redimension_Cjt_Customers(L);
  Customer c;
  for (int i = 0; i < L; ++i) {
    c.read_customer();
    cjt_tots_customers.add_Customer_to_cjt(c);
  }
}

void info_producte(const Optimus& opt)
/** @brief Extreu la informació d'un Product.
 *  \pre Cert.
 *  \post Escriu al canal estàndard de sortida la informació del Product s.
 */
{
  string s;
  cin >> s;
  Product p;
  p = opt.extract_Product(s);
  p.write_product(s);
}

void llistat_productes(const Optimus& opt)
/** @brief Extreu tots els Product d'una secció d'Optimus.
 *  \pre Cert.
 *  \post Escriu al canal estàndard de sortida tots els Product de la secció s.
 */
{
  string s;
  cin >> s;
  opt.write_section(s);
}

void llargada_millor_cami(const Optimus& opt, const Cjt_Customers& cjt_tots_customers)
/** @brief Calcula el camí més ràpid que passa per totes les seccions on hi han Products a la llista d'un Customer.
 *  \pre Cert.
 *  \post Escriu la llargada del millor camí i l'ordre d'aquests.
 */
{
  int n;
  cin >> n;
  Customer c;
  c = cjt_tots_customers.extract_Customer(n);
  opt.find_best_path(c, n);
}


void simular_pagament(Optimus& opt, const Cjt_Customers& cjt_tots_customers)
/** @brief Simula els pagament del supermercat amb certes configuracions diferents.
 *  \pre Cert.
 *  \post Escriu els temps per a cada Customer i el temps mitjà de tots els Customer per a cada configuració.
 */
{
  int M;
  cin >> M;
  opt.simulate_payment(cjt_tots_customers, M);
}