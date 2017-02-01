#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Data.h"
#include "utils.h"

using namespace std;


class Cliente {
 private:
  unsigned int id;
  string nome;
  Data cartaoCliente;
  float volCompras;

 public:
  Cliente() {};
  Cliente(ifstream & in);
  Cliente(int id1, string name, Data date, float volc);
  string getNome() const;
  unsigned int getId() const;
  Data getData() const;
  float getVolCompras() const;
  void setNome(string name);
  void setData(Data date);
  void setVol(float vol);
  void save(ofstream & out) const;
  friend ostream& operator<<(ostream& out, const Cliente & cli);  // mostra informacao do cliente no ecra
  friend bool operadorClie(const Cliente &cli1, const Cliente &cli2); // compara 2 clientes (1 cliente e menor que outro se o seu nome for "alfabeticamente" inferior)
};