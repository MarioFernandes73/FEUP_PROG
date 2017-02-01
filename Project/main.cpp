#include <iostream>
#include <string>
#include <vector>
#include<Windows.h>

#include "Vende++.h"
#include "Menus.h"
#include "utils.h"




int main() {

	string nomeloja = "", fichClients = "", fichProdutos = "", fichTransacoes = "";
	
	
	// pede a informacoo sobre o nome da loja e os 3 ficheiros com
	// informacoo de clientes, produtos e transacoes
	int k = infoInicial(nomeloja, fichClients, fichProdutos, fichTransacoes);
	if (k == 0)
		return 0;
	else
	{
		VendeMaisMais supermercado(nomeloja, fichClients, fichProdutos, fichTransacoes);
	}
	

	// cria uma loja
	VendeMaisMais supermercado(nomeloja, fichClients, fichProdutos, fichTransacoes);
	cout << supermercado << endl;  // mostra estatisticas da loja
	system("pause");
	system("cls");

	opcoesIniciais(supermercado);
	

	return 0;
}