#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Data.h"
#include "utils.h"



using namespace std;


class Transacao {
 private:
  unsigned int idCliente;
  Data data; // na forma DD/MM/AAAAA
  vector<string> produtos;

 public:
  Transacao() {};
  Transacao(ifstream & in); // trabsacao na forma de  idCliente ; data ; lista de produtos
  Transacao(int id, Data date, vector <string> prods);
  unsigned int getIdCliente() const;
  Data getDataTrans() const;
  vector<string> getprods() const;
  void setProds(vector<string> newproducts);
  void save(ofstream & out) const; // guarda a transacao
  friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao
  friend bool operadorTrans(const Transacao &trans1, const Transacao &trans2);
  friend bool operadorTransData(const Transacao &trans1, const Transacao &trans2);
};