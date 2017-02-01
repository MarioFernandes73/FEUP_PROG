#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <map>
#include<algorithm>
#include <ctime>

#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Transacao.h"
#include "Produto.h"
#include "utils.h"


using namespace std;

class VendeMaisMais{
 private:
  string loja; // nome da loja
  string fichClientes, fichProdutos, fichTransacoes; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
  bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
  bool produtosAlterados;
  unsigned int nClientes; // number of current clients in the clients file
  unsigned int nProds; //number of current products in the products file
  unsigned int nTrans; //number of current transactions in the transaction file
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<int, int> transacaoIdx; // multima para "traduzir" o identificador do
				   // cliente nos indices das suas
				   // transacoes no vetor de
				   // transacoes

 public:
  VendeMaisMais(string nomeloja, string fichClients, string fichProdutos, string fichTransacoes);
  int CheckClient(string nome);
  void listarClientesOrdemAlfa() const;
  void listarProdutosOrdemAlfa() const;
  void listarTransacoesOrdemID_Data() const;
  void listarTransacoesClient();
  void listarTransacoesData() const;
  void listarTransacoesDuasDatas() const;
  void mostraInformacaoCliente(string nome) const;
  void createClient();
  void createProduct();
  void createTransaction();
  void editClientName();
  void editClientDate();
  void editClientVol();
  void editProduct();
  void removeClient();
  void removeProduct();
  void removeTransaction();
  int removeTransaction2(int id);
  void publicity();
  void saveChanges() const;
  multimap<int,float> bottom10();
  map<int, string> indiceProds();
  void publicityBottom10();

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
};

