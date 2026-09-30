/** @file Cjt_Customers.hh
 *  @brief Especificació de la classe Cjt_Customers
 */

#ifndef _CJT_CUSTOMERS_HH_
#define _CJT_CUSTOMERS_HH_

#include "Customer.hh"

class Cjt_Customers {
  
// Tipus de mòdul: dades
  
/** @class Cjt_Customers
 *  @brief Representa un conjunt de Customer de la cadena Optimus. 
 *
 *  Els atributs son un vector de Customer i la mida d'aquest.
 */
  
private:
  
  /** @brief Vector de Customer. */
  vector<Customer> vec_customer;
  
  /** @brief Nombre de Customer. */
  int midaBloc_c;
  

public:
  
//Constructores
  
  /** @brief Creadora per defecte.
   *  S'executa automàticament al declarar un Cjt_customer cc.
   *  \pre Cert.
   *  \post El paràmetre implícit és un vector de Customer de mida 0.
   */
  Cjt_Customers();  
  
//Destructores
  
  /** @brief Destructora per defecte.
   *  \pre Cert.
   *  \post Cert.
   */
  ~Cjt_Customers();
  
//Modificadores
  
  /** @brief Modifica el tamany del vector de Customer.
   *  \pre L és positiu.
   *  \post El vector de Customer passa a ser de tamany L.
   */
  void redimension_Cjt_Customers(int L);
  
  /** @brief Afegeix un Customer al Cjt_Customer.
   *  \pre El Customer és correcte i no es troba ja al paràmetre implícit.
   *  \post El Customer amb id L ha sigut afegit al paràmetre implícit.
   */
  void add_Customer_to_cjt(const Customer& c);
  
//Consultores
  
  /** @brief Consultora del nombre de Customer del vector.
   *  \pre Cert.
   *  \post Retorna el nombre de Customer.
   */
  int consult_number_Customer() const;
  
  /** @brief Consultora del Customer id.
   *  \pre Cert.
   *  \post Retorna el Customer amb identificació id, o un Customer incorrecte si no s'ha trobat.
   */
  Customer extract_Customer(int id) const;
  
};
#endif