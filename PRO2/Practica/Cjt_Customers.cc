/** @file Cjt_Customers.cc
 *  @brief Implementació de la classe Cjt_Customers
 */

#include "Cjt_Customers.hh"

Cjt_Customers::Cjt_Customers()
{
  vec_customer = vector<Customer> (0);
  midaBloc_c = 0;
}

Cjt_Customers::~Cjt_Customers() {}

void Cjt_Customers::redimension_Cjt_Customers(int L)
{
  vec_customer = vector<Customer> (L);
  midaBloc_c = L;
}

void Cjt_Customers::add_Customer_to_cjt(const Customer& c)
{
  vec_customer[c.consult_comprador_id() - 1] = c;
}

int Cjt_Customers::consult_number_Customer() const
{
  return midaBloc_c;
}

Customer Cjt_Customers::extract_Customer(int id) const
{
  if (id > midaBloc_c)
  {
    Customer c;
    return c;
  }
  else return vec_customer[id - 1];
}