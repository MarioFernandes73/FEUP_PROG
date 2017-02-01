#include "Menus.h"

#define nome "nomes.txt"


int infoInicial(string & loja, string & fichClientes, string & fichProdutos, string & fichTransacoes) {

	ifstream in;
	ofstream out;
	string temp;
	stringstream ss;
	string password;

	in.open(nome);
	if (in.is_open())
	{
		cout << "Welcome to the supermarket software!" << endl;
		cout << "Please write the name of your store: ";
		getline(cin, loja);
		while (!in.eof())
		{
			getline(in, temp);
			if (temp == loja)
			{
				getline(in, fichClientes);
				getline(in, fichProdutos);
				getline(in, fichTransacoes);
				getline(in, password);
				in.close();
				cout << "Success finding the files!" << endl;
				cout << "Please insert the password of " << loja << ": ";
				getline(cin, temp);
				if (temp == password)
				{
					cout << "Success!" << endl;
					system("pause");
					return 1;
				}
				else
				{
					cout << "Sorry, wrong password." << endl;
					return 0;
				}
			}
		}
		in.close();


		cout << "There are no records of that store, would you like to create a new store?" << endl;
		if (YesNo())
		{
			
			int k = 1;
			string l;

			in.open(nome);

			while (!in.eof())
			{
				getline(in, temp);
				if (temp == "")
					break;
				getline(in, temp);
				getline(in, temp);
				getline(in, temp);
				getline(in, temp);
				k++;
			}

			ss << k;
			ss >> l;
			ss.clear();
			ss.str("");
			fichClientes = l.append("clients.txt");

			ss << k;
			ss >> l;
			ss.clear();
			ss.str("");
			fichProdutos = l.append("products.txt");

			ss << k;
			ss >> l;
			ss.clear();
			ss.str("");
			fichTransacoes = l.append("transactions.txt");

			cout << "Please create your password: ";
			getline(cin, password);
			
			out.open(nome, ios::app);
			out << endl << loja << endl << fichClientes << endl << fichProdutos << endl << fichTransacoes << endl << password;
			out.close();
			out.open(fichClientes);
			out << 0;
			out.close();
			out.open(fichProdutos);
			out << 0;
			out.close();
			out.open(fichTransacoes);
			out << 0;
			out.close();

			cout << "Success!" << endl;
			system("pause");

			return 1;
		}
		else
		{
			cout << "Do you have any existent files in the project directory?" << endl;
			if (YesNo())
			{
				do
				{
					cout << "Existent clients file: ";
					getline(cin, temp);
				} while (!checkFile(temp));
				
				fichClientes = temp;

				do
				{
					cout << "Existent products file: ";
					getline(cin, temp);
				} while (!checkFile(temp));

				fichProdutos = temp;

				do
				{
					cout << "Existent transaction file: ";
					getline(cin, temp);
				} while (!checkFile(temp));

				fichTransacoes = temp;

			}
			else
			{
				cout << "Sorry, we need the files to continue." << endl;
			}
			return 0;
		}
	}
	else
	{
		cout << "Welcome to the supermarket software!" << endl;
		cout << "We see it's your first time using this software!" << endl;
		cout << "We will create a file in which stores are registered automatically." << endl;
		out.open(nome);
		out.close();
		cout << "The program will now exit, please restart the program, thank you for using our software!" << endl;
		return 0;
	}
}


/******************************************
* Gestao de Clientes
******************************************/
void opcoesGestaoClientes(VendeMaisMais & supermercado){
  unsigned int opcao;
  string name;

  while((opcao = menuGestaoClientes()))
    switch (opcao){
	case 1: supermercado.listarClientesOrdemAlfa();
      break;
	case 2:cout << "Please insert either the client name or the client ID: ";
		getline(cin, name);
		supermercado.mostraInformacaoCliente(name);
      break;
	case 3:supermercado.createClient();
      break;
	case 4:opcoesEditClientes(supermercado);
      break;
	case 5:supermercado.removeClient();
		break;
    }
}

void opcoesEditClientes(VendeMaisMais & supermercado) {
	unsigned int opcao;
	string name;

	while ((opcao = menuEditClientes()))
		switch (opcao) {
		case 1: supermercado.editClientName();
			break;
		case 2:supermercado.editClientDate();
			break;
		case 3:supermercado.editClientVol();
			break;
		}
}


unsigned short int menuGestaoClientes() {
	unsigned short int opcao;

	system("cls");
	cout << TAB_BIG << "Clients management Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List all clients" << endl;
	cout << TAB << "2 - List specific client" << endl;
	cout << TAB << "3 - Create a client" << endl;
	cout << TAB << "4 - Edit a client" << endl;
	cout << TAB << "5 - Remove a client" << endl;
	cout << TAB << "0 - Return to initial menu" << endl << endl;
	cout << TAB << "Please insert the number of your option here: ";
	opcao = leUnsignedShortInt(0, 5);

	if (opcao == 0)
		return 0;

	return opcao;
}

unsigned short int menuEditClientes() {
	unsigned short int opcao;

	system("cls");
	cout << TAB_BIG << "Clients edit Menu" << endl;
	cout << endl;
	cout << TAB << "1 - Edit a name" << endl;
	cout << TAB << "2 - Edit a creation date" << endl;
	cout << TAB << "3 - Edit a purchase volume" << endl;
	cout << TAB << "0 - Return to initial menu" << endl << endl;
	cout << TAB << "Please insert the number of your option here: ";
	opcao = leUnsignedShortInt(0, 3);

	if (opcao == 0)
		return 0;

	return opcao;
}


/******************************************
* Gestao de Produtos
******************************************/
void opcoesGestaoProdutos(VendeMaisMais & supermercado) {
	unsigned int opcao;

	while ((opcao = menuGestaoProdutos()))
		switch (opcao) {
		case 1: supermercado.listarProdutosOrdemAlfa();
			break;
		case 2: supermercado.createProduct();
			break;
		case 3:supermercado.editProduct();
			break;
		case 4:supermercado.removeProduct();
			break;
		}
}


unsigned short int menuGestaoProdutos()
{
	unsigned short int opcao;

	system("cls");
	cout << TAB_BIG << "Products management Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List all products" << endl;
	cout << TAB << "2 - Add a product" << endl;
	cout << TAB << "3 - Edit a product" << endl;
	cout << TAB << "4 - Remove a product" << endl;
	cout << TAB << "0 - Return to initial menu" << endl << endl;
	cout << TAB "Please insert the number of your option here: ";
	opcao = leUnsignedShortInt(0, 4);

	if (opcao == 0)
		return 0;

	return opcao;
}


/******************************************
 * Gestao de Transacoes
 ******************************************/


void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
  unsigned int opcao;

  while((opcao = menuGestaoTransacoes()))
    switch (opcao){
	case 1:opcoesListTransacoes(supermercado);
      break;
	case 2:supermercado.createTransaction();
      break;
	case 3:supermercado.removeTransaction();
      break;
    }
}


void opcoesListTransacoes(VendeMaisMais & supermercado) {
	unsigned int opcao;

	while ((opcao = menuListTransacoes()))
		switch (opcao) {
		case 1:supermercado.listarTransacoesOrdemID_Data();
			break;
		case 2:supermercado.listarTransacoesClient();
			break;
		case 3:supermercado.listarTransacoesData();
			break;
		case 4:supermercado.listarTransacoesDuasDatas();
			break;
		}
}


unsigned short int menuGestaoTransacoes()
{
	unsigned short int opcao;

	system("cls");
	cout << TAB_BIG << "Transactions management Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List transactions" << endl;
	cout << TAB << "2 - Add a transaction" << endl;
	cout << TAB << "3 - Remove a transaction" << endl;
	cout << TAB << "0 - Return to initial menu" << endl << endl;
	cout << TAB "Please insert the number of your option here: ";
	opcao = leUnsignedShortInt(0, 3);

	if (opcao == 0)
		return 0;

	return opcao;
}

unsigned short int menuListTransacoes()
{
	unsigned short int opcao;

	system("cls");
	cout << TAB_BIG << "Transactions list Menu" << endl;
	cout << endl;
	cout << TAB << "1 - List all transactions" << endl;
	cout << TAB << "2 - List transactions from 1 client" << endl;
	cout << TAB << "3 - List transactions from a specific date" << endl;
	cout << TAB << "4 - List transactions between 2 dates" << endl;
	cout << TAB << "0 - Return to Transactions management Menu" << endl << endl;
	cout << TAB "Please insert the number of your option here: ";
	opcao = leUnsignedShortInt(0, 4);

	if (opcao == 0)
		return 0;

	return opcao;
}


/******************************************
* Gestao de Publicidade
******************************************/

void opcoesGestaoPublicidade(VendeMaisMais & supermercado) {
	unsigned int opcao;

	while ((opcao = menuGestaoPublicidade()))
		switch (opcao) {
		case 1:supermercado.publicity();
			break;
		case 2:supermercado.publicityBottom10();
			break;
		}
}


unsigned short int menuGestaoPublicidade()
{
	unsigned short int opcao;

	system("cls");
	cout << TAB_BIG << "Publicity" << endl;
	cout << endl;
	cout << TAB << "1 - Target Publicity" << endl;
	cout << TAB << "2 - Bottom 10 Publicity" << endl;
	cout << TAB << "0 - Return to Initial menu" << endl << endl;
	cout << TAB "Please insert the number of your option here: ";
	opcao = leUnsignedShortInt(0, 2);

	if (opcao == 0)
		return 0;

	return opcao;
}




/******************************************
 * Menu Inicial
 ******************************************/
unsigned short int menuInicial(){
  unsigned short int opcao=9;

  while (opcao == 9)
  {

	  clearScreen();
	  cout << TAB_BIG << "Initial menu" << endl;
	  cout << endl;
	  cout << TAB << "1 - Clients management" << endl;
	  cout << TAB << "2 - Products management" << endl;
	  cout << TAB << "3 - Transactions management" << endl;
	  cout << TAB << "4 - Publicity" << endl;
	  cout << TAB << "0 - Exit" << endl << endl;
	  cout << TAB << "Please insert the number of your option here: ";
	  opcao = leUnsignedShortInt(0, 4);

  }

  if(opcao == 0)
    return 0;

  return opcao;
}

void opcoesIniciais(VendeMaisMais & supermercado){
  unsigned int opcao;


  while((opcao = menuInicial()))
    switch (opcao){
    case 1: opcoesGestaoClientes(supermercado);
      break;
	case 2: opcoesGestaoProdutos(supermercado);
      break;
    case 3: opcoesGestaoTransacoes(supermercado);
      break;
	case 4: opcoesGestaoPublicidade(supermercado);
      break;
    }

  supermercado.saveChanges();
}