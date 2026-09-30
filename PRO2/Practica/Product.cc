/** @file Product.cc
 *  @brief Implementació de la classe Product
 */

#include "Product.hh"

Product::Product ()
{
  correct_product = false;
}

Product::~Product() {};

string Product::consult_producte_id() const
{
  return producte_id;
}

double Product::consult_preu() const
{
  return preu;
}

string Product::consult_seccio() const
{
  return seccio;  
}

int Product::consult_temps_cobrament() const
{
  return temps_cobrament;
}

bool Product::consult_correct_product() const
{
  return correct_product;
}

void Product::read_product()
{
  cin >> producte_id >> preu >> seccio >> temps_cobrament;
  if (temps_cobrament > 0 && preu > 0) correct_product = true;
}

void Product::write_product(string s) const
{
  cout << "informacio " << s << ":" << endl;
  if (correct_product)
  {
    cout << producte_id << " " << preu << " " << seccio << " " << temps_cobrament << endl << endl;;
  }
  else cout << "error" << endl << endl;
}