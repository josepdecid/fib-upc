/** @file Customer.hh
 *  @brief Especificació de la classe Customer
 */

#ifndef _CUSTOMER_HH_
#define _CUSTOMER_HH_

#ifndef NO_DIAGRAM
/* Això fa que el doxygen no inglogui aquestes classes als diagrames modulars,
 * mentre que el compilador de c++ si que les processa correctament.
 */

#include <vector>

#endif

#include "Product.hh"

class Customer {
  
// Tipus de mòdul: Dades
  
/** @class Customer
 *  @brief Representa un client de la cadena Optimus.
 *
 *  Els atributs són un identificador de client, instant recollida tiquet, nombre de productes, vector de productes comprats i un booleà de correctesa. 
 */
  
private:
  
  /** @brief Id del client. */
  int comprador_id;
  
  /** @brief Instant de recollida del tiquet. */
  string instant_recollida_tiquet;
  
  /** @brief Nombre de productes comprats. */
  int NL;
  
  /** @brief Vector dels Product comprats. */
  vector< pair<string, int> > vec_prod_comprats;
  
  /** @brief Booleà que indica si el client és correcte. */
  bool correct_customer;
  
public:
  
//Constructores
  
  /** @brief Creadora per defecte.
   *  S'executa automàticament al declarar un Customer c.
   *  \pre Cert.
   *  \post El parametre implícit és un Customer sense dades.
   */
  Customer();
  
//Destructora
  
  /** @brief Destructora per defecte.
   *  \pre Cert.
   *  \post Cert.
   */
  ~Customer();
  
//Consultores
  
  /** @brief Cosultora comprador_id.
   *  \pre Cert.
   *  \post Retorna la id del paràmetre implícit.
   */
  int consult_comprador_id() const;
  
  /** @brief Consultora instant_recollida_tiquet.
   *  \pre Cert.
   *  \post Retorna l'instant de recollida del tiquet en format hh:mm:ss del paràmetre implícit.
   */
  string consult_instant_recollida_tiquet() const;
  
  /** @brief Consultora NL.
   *  \pre Cert.
   *  \post Retorna el nombre de Product diferents comprats pel paràmetre implícit.
   */
  int consult_NL() const;
  
  /** @brief Consultora vec_prod_comprats[i].
   *  \pre Cert.
   *  \post Retorna l'i-èssim parell de producte-quantitat comprats del paràmetre implícit.
   */
  pair<string, int> consult_vec_prod_comprats(int i) const;
  
  /** @brief Consultora correct_customer.
   *  \pre Cert.
   *  \post Retorna l'estat de correctesa del paràmetre implícit.
   */
  bool consult_correct_customer() const;
  
  /** @brief Consultora quantitat de productes comprats.
   *  \pre Cert.
   *  \post Retorna el total de productes comprats del paràmetre implícit.
   */
  int consult_cart_quantity() const;
  
// Lectura i escriptura
  
  /** @brief Operació de lectura.
      \pre Hi ha preparats al canal estàndard d'entrada una cadena de caràcters, dos enters i un seguit de productes.
      \post El paràmetre implícit passa a tenir els atributs llegits del canal estàndard d'entrada.
   */
  void read_customer();

};
#endif