/** @file Customer.cc
 *  @brief Implementació de la classe Customer
 */

#include "Customer.hh"

Customer::Customer()
{
  comprador_id = 0;
  instant_recollida_tiquet = "none";
  NL = -1;
  vec_prod_comprats = vector< pair<string, int> > (0);
  correct_customer = false;
}


Customer::~Customer() {}


int Customer::consult_comprador_id() const
{
  return comprador_id;
}

string Customer::consult_instant_recollida_tiquet() const
{
  return instant_recollida_tiquet;
}

int Customer::consult_NL() const
{
  return NL;
}

pair<string, int> Customer::consult_vec_prod_comprats(int i) const
{
  return vec_prod_comprats[i];
}

bool Customer::consult_correct_customer() const
{
  return correct_customer;
}

int Customer::consult_cart_quantity() const
{
  int result = 0;
  for (int i = 0; i < NL; ++i)
  {
    result += vec_prod_comprats[i].second;
  }
  return result;
}


void Customer::read_customer()
{
  cin >> comprador_id >> instant_recollida_tiquet >> NL;
  vec_prod_comprats = vector< pair<string, int> >(NL);
  for (int i = 0; i < NL; ++i)
  {
    cin >> vec_prod_comprats[i].first >> vec_prod_comprats[i].second;
  }
  if (comprador_id > 0 && NL >= 0) correct_customer = true;
}