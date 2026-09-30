/** @file Optimus.hh
 *  @brief Especificació de la classe Optimus
 */

#ifndef _OPTIMUS_HH_
#define _OPTIMUS_HH_

#ifndef NO_DIAGRAM
/* Això fa que el doxygen no inglogui aquestes classes als diagrames modulars,
 * mentre que el compilador de c++ si que les processa correctament.
 */

#include <queue>
#include <map>
#include <list>

#endif

#include "Cjt_Customers.hh"

class Optimus {
  
// Tipus de mòdul: dades
  
/** @class Optimus
 *  @brief Representa un supermercat de la cadena Optimus.
 *
 *  Els atributs són el tamany d'Optimus, un map de Product, el nombre de caixes i un vector de queues d'strings.
 */
  
private:
  
  /** @brief Dimensions del supermercat. */
  int R, C;
  
  /** @brief Map amb tots els Product del supermercat ordenats lexicogràficament. */
  map<string, Product> map_products;
  
  /** @brief Nombre total de Product. */
  int midaBloc_p;
  
  /** @brief Nombre de caixes. */
  int X_caixes;
  
  /** @brief Vector de caixers. */
  vector< queue<string> > opt_caixers;

  /** @brief Booleà de correctesa d'Optimus. */
  bool correct_optimus;
  
  /** @brief Calcula el temps de compra d'un Customer.
   *  \pre El Customer és correcte.
   *  \post Retorna el temps de pagament del Customer.
   */
  int paying_time(Customer& c) const;
  
  /** @brief Actualitza les caixes a partir del temps de tiquet del Customer actual.
   *  \pre temps_recollida té un format vàlid, i 0 <= mida_min <= X_caixes - 2.
   *  \post Al sortir de la funció, les caixes han estat actualitzades.
   */  
  void refresh_cash(int temps_recollida, int mida_min);
  
  /** @brief Calcula les sortides de simular pagament per a una determinada configuració.
   *  \pre El Cjt_Customers està correctament inicialitzat.
   *  \post Escriu els resultats de cada configuració de caixes.
   */
  void config_m(const Cjt_Customers& cc, int x, int y);
  
public:
  
//Constructores
  
  /** @brief Creadora per defecte.
   *  S'executa automàticament al declarar Optimus opt.
   *  \pre Cert.
   *  \post El paràmetre implícit és un Optimus incorrecte.
   */
  Optimus();
  
  //Destructora
  
  /** @brief Destructora per defecte.
   *  \pre Cert.
   *  \post Cert.
   */
  ~Optimus();
  
//Modificadores
  
  /** @brief Modifica el tamany d'Optimus.
   *  \pre R, C, X i N són estrictament positius.
   *  \post Optimus passa a ser de RxC, amb X caixes i N Product.
   */
  void redimension_market(int R, int C, int X, int N);
  
  /** @brief Afegeix un Product al map_products d'Optimus.
      \pre Cert.
      \post El Product p ha estat afegit al paràmetre implícit.
   */
  void add_Product(const Product& p);
  
//Consultores
  
  /** @brief Consulta el nombre de Product que conté Optimus.
   *  \pre Cert.
   *  \post Retorna el nombre d'elements de map_products.
   */
  int consult_midaBloc_p() const;

  /** @brief Consulta un Product de nom s a Optimus.
   *  \pre Cert.
   *  \post Retorna el Product solicitat de nom s.
   */
  Product extract_Product(string s) const;
  
//Simuladores
  
  /** @brief Indica el millor camí per recórrer l'Optimus.
   *  \pre Cert.
   *  \post Obtenim el millor camí per a recórrer el supermercat passant per totes les seccions que necessita visitar el Customer c.
   */
  void find_best_path(const Customer& c, int i) const;
  
  /** @brief Indica com resulta la simulació de pagament amb diferents configuracions.
   *  \pre M es estrictament positiu.
   *  \post Escriu el temps mitjà de pagament per a cada configuració llegida.
   */
  void simulate_payment(const Cjt_Customers& cc, int M);
  
//Lectura i escriptura
  
  /** @brief Retorna el conjunt de Product d'una secció.
   *  \pre Cert.
   *  \post Retorna el total dels Product de la secció s.
   */
  void write_section(string s) const;

};
#endif