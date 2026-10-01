/** @file Product.hh
 *  @brief Especificació de la classe Product
 */

#ifndef _PRODUCT_HH_
#define _PRODUCT_HH_

#ifndef NO_DIAGRAM
/* Això fa que el doxygen no inglogui aquestes classes als diagrames modulars,
 * mentre que el compilador de c++ si que les processa correctament.
 */

#include <iostream>
#include <string>

#endif

using namespace std;

class Product {
  
// Tipus de mòdul: Dades
  
/** @class Product
 *  @brief Representa un producte del supermercat.
 *  
 *  Els atributs són el seu nom, preu, secció on trobar-lo i temps de cobrament i correctesa d'ell mateix.
 */

private:
  
  /** @brief Identificador únic de producte. */
  string producte_id;
  
  /** @brief Preu del producte. */
  double preu;
  
  /** @brief Secció on està el producte. */
  string seccio;
  
  /** @brief Temps de cobrament del producte. */
  int temps_cobrament;
  
  /** @brief Correctesa del producte. */
  bool correct_product;
  
public:
  
//Constructores
  
  /** @brief Creadora per defecte.
   *  S'executa automàticament al declarar un Product p;
   *  \pre Cert.
   *  \post El parametre implicit és un Product sense dades correctes d'inicialització.
   */
  Product ();
  
//Destructora
  
  /** @brief Destructora per defecte.
   *  \pre Cert.
   *  \post Cert.
   */
  ~Product ();

//Modificadores
  
//Consultores

  /** @brief Consultora producte_id.
   *  \pre Cert.
   *  \post Retorna el producte_id del paràmetre implícit.
   */
  string consult_producte_id() const;

  /** @brief Consultora preu.
   *  \pre Cert.
   *  \post Retorna el preu del paràmetre implícit.
   */
  double consult_preu() const;

  /** @brief Consultora secció.
   *  \pre Cert.
   *  \post Retorna la secció on està el paràmetre implícit.
   */
  string consult_seccio() const;

  /** @brief Consultora temps de cobrament.
   *  \pre Cert.
   *  \post Retorna el temps de cobrament del paràmetre implícit.
   */
  int consult_temps_cobrament() const;
  
  /** @brief Consultora correctesa del producte.
   *  \pre Cert.
   *  \post Retorna si el producte ha estat inicialitzat correctament.
   */
  bool consult_correct_product() const;
  
//Lectura i escriptura.
  
  /** @brief Operació de lectura.
   *  \pre Hi ha preparats al canal estàndard d'entrada una cadena de caràcters, un double, un altre string i un enter no negatiu.
   *  \post El paràmetre implícit passa a tenir els atributs llegits a través del canal estàndard d'entrada.
   */
  void read_product();
  
  /** @brief Operació d'escriptura.
   *  \pre Cert.
   *  \post S'han escrit al canal estàndard de sortida els atributs del paràmetre implícit.
   */
  void write_product(string s) const;
  
};
#endif