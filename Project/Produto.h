#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "utils.h"


using namespace std;



class Produto {
 private:
  string nome;
  float custo;


 public:
  Produto() { };
  Produto(ifstream & in);
  Produto(string name, float cost);
  string getNome() const;
  float getCusto() const;
  void setNome(string name);
  void setCusto(float cost);
  void setCusto(string cost);
  void save(ofstream & out) const;
  friend ostream& operator<<(ostream& out, const Produto & prod); // mostra um produto
  friend bool operadorProd(const Produto &prod1, const Produto &prod2); // compara 2 produtos (1 produto e mais pequeno que outro se o seu nome for "alfabeticamente inferior"
};


