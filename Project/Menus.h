#pragma once

#include <iostream>
#include <fstream>
#include <string>


#include "defs.h"
#include "utils.h"
#include "Vende++.h"

using namespace std;

int infoInicial(string & loja, string & fichClients, string & fichProdutos, string & fichTransacoes);

void opcoesIniciais(VendeMaisMais & supermercado);

void opcoesGestaoClientes(VendeMaisMais & supermercado);
void opcoesEditClientes(VendeMaisMais & supermercado);
void opcoesGestaoProdutos(VendeMaisMais & supermercado);
void opcoesGestaoTransacoes(VendeMaisMais & supermercado);
void opcoesListTransacoes(VendeMaisMais & supermercado);
void opcoesGestaoPublicidade(VendeMaisMais & supermercado);


unsigned short int menuGestaoClientes();
unsigned short int menuEditClientes();
unsigned short int menuGestaoProdutos();
unsigned short int menuGestaoTransacoes();
unsigned short int menuListTransacoes();
unsigned short int menuGestaoPublicidade();