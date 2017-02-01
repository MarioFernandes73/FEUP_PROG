#include "Vende++.h"

VendeMaisMais::VendeMaisMais(string nomeloja, string fichClients, string fichProducts, string fichTransactions) {

	loja = nomeloja;

	ifstream in;
	string line;
	stringstream ss;

	in.open(fichClients);

	if (in.is_open())
	{
		getline(in, line);
		ss << line;
		ss >> nClientes;
		ss.clear();
		ss.str("");

		if (line != "0")
		{
			while (!in.eof())
			{
				clientes.push_back(Cliente(in));
			}
			maxClientesId = clientes[clientes.size() - 1].getId();
		}
		else
		{
			nClientes = 0;
			cout << "Warning! No clients registered in the clients file." << endl;
		}
		in.close();
	}

	in.open(fichProducts);

	if (in.is_open())
	{
		getline(in, line);
		ss << line;
		ss >> nProds;
		ss.clear();
		ss.str("");

		if (line != "0")
		{
			while (!in.eof())
			{
				produtos.push_back(Produto(in));
			}
		}
		else
		{
			nProds = 0;
			cout << "Warning! No products registered in the products file." << endl;
		}
		in.close();
	}


	in.open(fichTransactions);

	if (in.is_open())
	{
		getline(in, line);
		ss << line;
		ss >> nTrans;
		ss.clear();
		ss.str("");

		if (line != "0")
		{
			while (!in.eof())
			{
				transacoes.push_back(Transacao(in));
			}
		}
		else
		{
			nTrans = 0;
			cout << "Warning! No transactions registered in the transactions file." << endl;
		}
	}

	fichClientes = fichClients;
	fichProdutos = fichProducts;
	fichTransacoes = fichTransactions;
}

int VendeMaisMais::CheckClient(string nome) //checks if the client exists in the files
{
	vector <int> temp;

	if (checkString(nome)) //checks if the client name exists
	{
		int cont = 1;
		for (unsigned int i = 0; i < clientes.size(); i++) //places the found client position in a vector. If the client's name is unique, the vector should have only one element
		{
			if (nome == clientes[i].getNome())
			{
				cont++;
				temp.push_back(i+1);
			}
			
		}
		temp.push_back(cont);
		if (cont == 1)
		{
			cout << "Error! The client named " << nome << " was not found." << endl;
			return -1;
		}
		else if (cont == 2)
		{
			cout << "The client named " << nome << " was found." << endl;
			return temp[0];
		}
		else //if there are different clients with the same names
		{
		
			int idclient = -2;

			int check = 0;
			while (true)
			{
				
				for (unsigned int i = 0; i < temp.size() - 1; i++)
				{
					if (idclient == temp[i])
					{
						return temp[i];
					}
				}

				if (check != 0)
				{
					cout << "Error! Please only insert an id from the ones shown below: " << endl;
				}
				else {
					cout << "Multiple clients with the name " << nome << " have been found." << endl;
					cout << "Please choose one from these ids: " << endl;
					check++;
				}
			
				for (unsigned int i = 0; i < temp.size() - 1; i++)
				{
					cout << temp[i] << endl;
				}
				cout << "Please write here: ";
				string clientid;
				stringstream ss;
				getline(cin, clientid);
				if (clientid == "0")
				{
					return 0;
				}


				while (!checkNumber(clientid))
				{
					cout << "Error! Please insert a valid number." << endl;
					getline(cin, clientid);
					if (clientid == "0")
					{
						return 0;
					}

				}

				ss << clientid;
				ss >> idclient;
				ss.clear();
				ss.str("");

			}
			
		}
		
	}
	
	else if (checkNumber(nome)) //checks if the client ID exists
	{
		stringstream ss;
		int id;

		ss << nome;
		ss >> id;

		for (unsigned int i = 0; i < clientes.size(); i++)
		{
			if (id == clientes[i].getId())
			{
				cout << "The client with the id " << id << " was found." << endl;
				return id;
			}
		}
		cout << "Error! The client with the ID of " << id << " was not found." << endl;
		return -1;
	}
	else
	{
		cout << "Please only insert either the client ID or the client name!" << endl;
		return -1;
	}
}


/*********************************
 * Gestao de Clientes
 ********************************/  

// lista os clients por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{ //sorts and shows all clients

	vector <Cliente> temp = clientes;

	sort(temp.begin(), temp.end(), operadorClie);

	cout << endl;
	cout << setw(4) << "ID" << setw(20) << "NAME" << setw(18) << "DATE" << setw(14) << "VOLUME" << endl;
	for (unsigned int i = 0; i < temp.size(); i++) //after the clients vector is sorted, displays it one by one
	{
		cout << temp[i] << endl; 
	}
	system("pause");

}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome) const{ //shows client info

	cout << endl;

	if (checkString(nome))
	{
		vector <int> clientspos; //vector to place clients amount with the name inserted. If there's a unique client, the vector should only have one element.
		for (unsigned int i = 0; i < clientes.size(); i++)
		{
			if (nome == clientes[i].getNome())
			{
				clientspos.push_back(i);
			}
		}

		if (clientspos.size() == 0)
		{
			cout << "No client with the name of " << nome << " registered on our system." << endl;
		}
		else if (clientspos.size() == 1)
		{
			int k = 0;
			cout << clientes[clientspos[0]] << endl;
			cout << "Here are every transactions made by the client:" << endl << endl;

			cout << setw(4) << "ID" << setw(20) << "NAME" << setw(18) << "DATE" << setw(14) << "VOLUME" << endl;

			for (unsigned int i = 0; i < transacoes.size(); i++) //checks the transaction vector for the client ID and displays all transactions made by him
			{
				if (transacoes[i].getIdCliente() == clientes[clientspos[0]].getId())
				{
					k = 1;
					cout << transacoes[i] << endl; //transaction display one by one
				}
			}

			if (k == 0)
			{
				cout << "No transactions have been made by this client." << endl;
			}
		}
		else
		{
			cout <<"Multiple clients with that name registered in the system:" << endl;
			for (unsigned int i = 0; i < clientspos.size(); i++)
			{
				cout << clientes[clientspos[i]] << endl;
			}
			cout << "Please try again with the client ID." << endl;
		}


	}
	else if (checkNumber(nome))
	{
		stringstream ss;
		int id;

		ss << nome;
		ss >> id;

		int k = 0, l = 0;
		for (unsigned int i = 0; i < clientes.size(); i++)
		{
			if (id == clientes[i].getId())
			{
				k = 1;
				cout << clientes[i] << endl;
				cout << "Here are every transactions made by the client:" << endl << endl;

				for (unsigned int i = 0; i < transacoes.size(); i++)
				{
					if (transacoes[i].getIdCliente() == id)
					{
						l = 1;
						cout << transacoes[i] << endl; //transaction display one by one
					}
				}

				if (l != 1)
				{
					cout << "No transactions have been made by this client." << endl;
				}

			}
		}

		if (k != 1)
		{
			cout << "No client registered with that ID." << endl;
		}
	}
	else
	{
		cout << "Please only insert either the client ID or the client name!" << endl;
	}
	system("pause");
	return;
}

void VendeMaisMais::createClient() //creates client
{
	clientesAlterados = true; //flag used for the SaveChanges function
	time_t now = time(0);
	tm *ltm = localtime(&now); //used to get current date
	
	//Variables
	string name,dataf="", day,month,year;
	int newid;
	stringstream ss;
	Data currentDate;

	cout << endl << "Please write here the name of the new client: ";

	getline(cin, name);

	if (name == "0")
	{
		return;
	}

	for (unsigned int i = 0; i < name.size(); i++)
	{
		if (i == 0)
		{
			name[i]=toupper(name[i]);
		}
		else if (isspace(name[i - 1]))
		{
			name[i]=toupper(name[i]);
		}
	}
	
	newid = clientes[clientes.size() - 1].getId() + 1;

	

	currentDate.setDia(ltm->tm_mday); //getting current day
	currentDate.setMes(ltm->tm_mon+1); //getting current month
	currentDate.setAno(ltm->tm_year+1900); //getting current year
	
	
	cout << endl << "Success!" << endl;
	clientes.push_back(Cliente(newid, name,currentDate, 0));
	nClientes++;

	system("pause");
	return;
}

void VendeMaisMais::editClientName()
{
	if (nClientes <= 0)
	{
		cout << "Error! No clients detected." << endl;
		system("pause");
		return;
	}
	clientesAlterados = true; //flag used for the SaveChanges function
	string nome;
	int pos;

	listarClientesOrdemAlfa(); //sorts and shows all clients

	cout << endl << "Please insert the name or ID of the client you wish to edit: ";
	getline(cin, nome);
	if (nome == "0")
	{
		return ;
	}

	if ((pos = CheckClient(nome)) != -1) //looks for the client name/ID
	{
		pos = pos - 1;
		string name;
		cout << "Client found, please insert the new name: ";
		getline(cin, name);
		if (name == "0")
		{
			return;
		}
		clientes[pos].setNome(name);
		cout << endl << "Success!" << endl;
	}

	system("pause");
	return;
}

void VendeMaisMais::editClientDate()
{
	if (nClientes <= 0)
	{
		cout << "Error! No clients detected." << endl;
		system("pause");
		return;
	}
	clientesAlterados = true; //flag used for the SaveChanges function
	string nome;
	int pos;

	listarClientesOrdemAlfa(); //sorts and shows all clients

	cout << endl << "Please insert the name or ID of the client you wish to edit: ";
	getline(cin, nome);

	if (nome == "0")
	{
		return;
	}

	if ((pos = (CheckClient(nome))) != -1) //if client is found
	{
		pos = pos - 1;
		string name;
		cout << "Client found, please insert the new Date: ";
		
		getline(cin, name);
		if (name == "0")
		{
			return;
		}

		while ((name = checkDate(name)) == "false") //if the new date entered is not written correctly
		{ 
			cout << "Error! Please insert a valid date (DD/MM/YYYY): ";
			getline(cin, name);
			if (name == "0")
			{
				return;
			}

		} 
		clientes[pos].setData(name);
		cout << endl << "Success!" << endl;
	}

				
			
	system("pause");
	return;
}

void VendeMaisMais::editClientVol() //edits client money spent
{
	if (nClientes <= 0)
	{
		cout << "Error! No clients detected." << endl;
		system("pause");
		return;
	}
	clientesAlterados = true; //flag used for the SaveChanges function
	string nome;
	int pos;

	listarClientesOrdemAlfa(); //sorts and shows all clients

	cout << endl <<"Please insert the name or ID of the client you wish to edit: ";
	getline(cin, nome);
	if (nome == "0")
	{
		return;
	}


	if ((pos = (CheckClient(nome))) != -1) //if client is found
	{
		pos = pos - 1;
		string name;
		float vol;
		stringstream ss;

		cout << "Client found, please insert the new volume: ";
		do
		{
			getline(cin, name);
			if (name == "0")
			{
				return;
			}

		} while (!checkFloat(name)); //checks if input is a float

		ss << name;
		ss >> vol;
		ss.clear();
		ss.str("");
		clientes[pos].setVol(vol);
		cout << endl << "Success!" << endl;
	}

	system("pause");
	return;
}

void VendeMaisMais::removeClient() { //removes client

	if (nClientes <= 0)
	{
		cout << "Error! No clients detected." << endl;
		system("pause");
		return;
	}
	clientesAlterados = true; //flag used for the SaveChanges function
	string nome;
	int pos;

	listarClientesOrdemAlfa(); //sorts and shows all clients


	cout << endl << "Please insert the name or ID of the client you wish to delete: ";
	getline(cin, nome);
	if (nome == "0")
	{
		return;
	}


	if ((pos = (CheckClient(nome))) != -1) //if the client exists
	{
		pos = pos - 1;
		clientes.erase(clientes.begin() + pos);
		cout << "The client named " << nome << " was successfully deleted!" << endl;
	}

	system("pause");
	return;
}


/*********************************
 * Gestao de Produtos
 ********************************/  

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutosOrdemAlfa() const{ //sorts and shows all products
	vector <Produto> temp = produtos;

	cout << "       " << "Name" << "     " << "        " << " Cost" << endl;

	sort(temp.begin(), temp.end(),operadorProd);

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		cout << left << setw(15) << temp[i].getNome() << " -> " << right << fixed << setprecision(2) << setw(8) << temp[i].getCusto() << endl; //formats the output
	}
	system("pause");
}

void VendeMaisMais::createProduct() //creates new product
{
	produtosAlterados = true; //flag used for the SaveChanges function
	string newproduct, newprice;
	stringstream ss;
	float nprice;
	int x;

	cout << endl << "Please write here the name of the new product: ";
	getline(cin, newproduct);
	if (newproduct == "0")
	{
		return;
	}
	
	
	do { //reads the input
		cout << endl << "Please write here the price of that new product: ";
		x = leInteiro(0, 99999);
	} while (x == -1);

	if (x==0)
	{
		return;
	}


	nprice = x;

	produtos.push_back(Produto(newproduct, nprice));

	nProds++;
	cout << endl << "Success!" << endl;

	system("pause");
	return;
}

void VendeMaisMais::editProduct() //edits existing product
{

	if (nProds <= 0)
	{
		cout << "Error! No products detected." << endl;
		system("pause");
		return;
	}

	produtosAlterados = true; //flag used for the SaveChanges function
	cout << endl;
	string product;
	int k = 1, x = 0;

	for (unsigned int i = 0; i < produtos.size(); i++) //shows all products
	{
		cout << k << " - " << produtos[i] << endl;
		k++;
	}
	

	do { //reads the input
		cout << endl << "Please write here the number of the product you want to edit: ";
		x = leInteiro(1, nProds);
	} while (x == -1);

	cout << "Would you like to rename your product?" << endl;
	if (YesNo()) //"Are you sure... "?
	{
		cout << "Please write here the new name of the product " << produtos[x-1].getNome() << ": ";

		getline(cin, product);
		if (product == "0")
		{
			return;
		}

		produtos[x-1].setNome(product); //new product name
		cout << endl << "Success!" << endl;
	}
		cout << "Would you like to reprice your product?" << endl;
		if (YesNo()) //"Are you sure... "?
		{
			cout << "Please write here the new price of the product " << produtos[x-1].getNome() << ": ";

			do {
				getline(cin, product);
				if (product == "0")
				{
					return;
				}

			} while (!checkNumber(product)); //checks if the input is a number

			produtos[x-1].setCusto(product); //new price
			cout << endl << "Success!" << endl;
		}
	
	return;
}

void VendeMaisMais::removeProduct() //removes a product
{

	if (nProds <= 0)
	{
		cout << "Error! No products detected." << endl;
		system("pause");
		return;
	}

	produtosAlterados = true; //flag used for the SaveChanges function
	cout << endl;
	string product;
	int k = 1, x = 0;

	for (unsigned int i = 0; i < produtos.size(); i++) //shows all products with indexes
	{
		cout << k << " - " << produtos[i] << endl;
		k++;
	}
	

	do {
		cout << endl << "Please write here the number of the product you want to remove: ";
		x = leInteiro(1, nProds);
	} while (x == -1);

	cout << "Do you really want to remove " << produtos[x - 1].getNome() << " from the database?" << endl;
	if (YesNo())
	{
		produtos.erase(produtos.begin() + x - 1);
		cout << endl << "Product successfully removed" << endl;
		system("pause");
	}
}


/*********************************
* Gestao de Transacoes
********************************/


void VendeMaisMais::listarTransacoesOrdemID_Data() const //lists transactions sorted by ID and date
{
	vector <Transacao> temp = transacoes;

	sort(temp.begin(), temp.end(), operadorTrans);

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		cout << temp[i] << endl;
	}
	system("pause");
}

void VendeMaisMais::listarTransacoesClient() //lists transactions from a client
{
	string nome;
	int pos;

	cout << "Please insert the client ID or name: ";

	getline(cin, nome);
	if (nome == "0")
	{
		return;
	}

	
	if ((pos = (CheckClient(nome))) != -1) //checks if client exists
	{
		pos = pos - 1;
		vector <Transacao> temp;
		for (unsigned int i = 0; i < transacoes.size(); i++) //places all checked client transactions in a new vector of transactions
		{
			if (transacoes[i].getIdCliente() == pos+1)
				temp.push_back(transacoes[i]);
		}
		for (unsigned int i = 0; i < temp.size(); i++) //displays the new vector of transactions
		{
			cout << temp[i] << endl;
		}

	}
	system("pause");
}

void VendeMaisMais::listarTransacoesData() const //lists transactions of a specific date
{
	string data;
	vector <Transacao> temp;

	cout << "Please insert the target date: ";
	getline(cin, data);
	if (data == "0")
	{
		return;
	}


	while ((data = checkDate(data)) == "false")
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY): ";
		getline(cin, data);
		if (data == "0")
		{
			return;
		}

	}

	for (unsigned int i = 0; i < transacoes.size(); i++) //new vector of transactions with only transactions of one date
	{
		if (sameData(transacoes[i].getDataTrans(), Data(data)))
		{
			temp.push_back(transacoes[i]);
		}
	}

	sort(temp.begin(), temp.end(), operadorTrans); //sorts transactions vector

	for (unsigned int i = 0; i < temp.size(); i++) //displays vector
	{
		cout << temp[i] << endl;
	}
	system("pause");
}

void VendeMaisMais::listarTransacoesDuasDatas() const //lists all transactions between two dates
{
	string data1;

	cout << "Please insert the minimum date: "; //first date
	getline(cin, data1);
	if (data1 == "0")
	{
		return;
	}


	while ((data1 = checkDate(data1)) == "false") //checks first input until a valid one
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY): ";
		getline(cin, data1);
		if (data1 == "0")
		{
			return;
		}

	}

	string data2;

	cout << "Please insert the maximum date: "; //second date
	getline(cin, data2);
	if (data2 == "0")
	{
		return;
	}


	while ((data2 = checkDate(data2)) == "false") //checks second input until a valid one
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY): ";
		getline(cin, data2);
		if (data2 == "0")
		{
			return;
		}

	}


	if (biggerData(data1, data2)) //checks if the dates are in chronological order
	{
		cout << "Error! The second data is bigger than the first inputted one." << endl;
	}
	else
	{
		vector <Transacao> temp;
		for (unsigned int i = 0; i < transacoes.size(); i++) //places the transactions in a new vector of transactions
		{
			if ((biggerData(transacoes[i].getDataTrans(), data1)) || (sameData(transacoes[i].getDataTrans(), data1))  && ((operadorData(transacoes[i].getDataTrans(), data2)) || (sameData(transacoes[i].getDataTrans(), data2))))
			{
				temp.push_back(transacoes[i]);
			}
		}

		sort(temp.begin(), temp.end(), operadorTransData); //sorts the new vector

		for (unsigned int i = 0; i < temp.size(); i++) //outputs the new vector
		{
			cout << temp[i] << endl;
		}
	}
	system("pause");
}

void VendeMaisMais::createTransaction() //creates transaction
{

	if (nClientes <= 0)
	{
		cout << "Error! No clients detected." << endl;
		system("pause");
		return;
	}

	if (nProds <= 0)
	{
		cout << "Error! No products detected." << endl;
		system("pause");
		return;
	}

	transacoesAlterdas = true; //flag used for the SaveChanges function
	time_t now = time(0);
	tm *ltm = localtime(&now); //way to get current system date
	string nome, dataf = "", day, month, year,produtoesc="-1";
	int pos;
	Data currentDate;
	vector <string> prods;
	stringstream ss;
	pair<string, string> producttest;
	bool accept = false;


	cout << endl;
		for (unsigned int i = 0; i < clientes.size(); i++) //outputs client vector
	{
		cout << clientes[i] << endl;
	}
	cout << endl << endl;

	cout << "Please insert the name or ID of the client: ";
	
	getline(cin, nome);
	if (nome == "0")
	{
		return;
	}


	if ((pos = (CheckClient(nome))) != -1) //check if the client exists
	{
		pos = pos - 1;
		cout << endl << "What has " << clientes[pos].getNome() << " bought?" << endl;

		while (true) //infinite loop until specific input is entered
		{			
			cout << endl << endl << "If multiple items have been bought please write it in the form of \"item\"\"number\" (example: laranjas2 means 2 \"laranjas\" have been bought)" << endl;
			cout << endl << "If you prefer to use numbers use a \".\" to separate the item identification and the number of purchases (example: 1.2 means 2 of " << produtos[0] << " have been bought." << endl;
			cout << endl << "If at any time you wish to view the product list write the character L" << endl;
			system("pause");
			cout << endl;
			for (unsigned int j = 0; j < produtos.size(); j++)//prints the product list for an easier overview of what to input
			{
				cout << fixed << setw(5) << left << j + 1 << " - " << setw(22) << right << produtos[j] << endl; //formats the products list
			}
			//beginning of user input
		
			while (produtoesc != "0") //checks if input is "0"
			{
				cout << endl << "Please write here (0 to exit): ";
				getline(cin, produtoesc);
				
				if (produtoesc == "0" && prods.size() > 0) //checks if input is "0" after conditions for creation of a new transaction are met
				{

					currentDate.setDia(ltm->tm_mday); //current day
					currentDate.setMes(ltm->tm_mon + 1); //current month
					currentDate.setAno(ltm->tm_year + 1900); //current year

					transacoes.push_back(Transacao(pos+1, currentDate, prods)); //creates new transaction
					nTrans++;
					return;
				}

				else if (produtoesc == "0")
				{
					cout << "Error! No items have been selected, can not register purchase without items." << endl;
					system("pause");
					return;
				}

				else if (produtoesc == "l" || produtoesc == "L") //checks if user wants the product list
				{
					for (unsigned int j = 0; j < produtos.size(); j++)//prints the product list for an easier overview of what to input
					{
						cout << fixed << setw(5) << left << j + 1 << " - " << setw(22) << right << produtos[j] << endl;
					}
				}
				else 
				{
					int posdot;
					bool l = false;
					for (unsigned int j = 0; j < produtoesc.size(); j++) 
					{
						if (produtoesc[j] == '.' && l==false) //checks if the user finished inputing product id and wants to start inputing product amount bought
						{
							l = true;
							posdot = j;
						}
	
					}
					if (l)
					{
						producttest.first = produtoesc.substr(0, posdot);
						producttest.second = produtoesc.substr(posdot + 1, produtoesc.size() - posdot - 1);
						if (checkNumber(producttest.second)) //if all input is correctly written, sets accept flag to true
						{
							accept = true;
						}
						else
						{
							cout << "Invalid quantity input." << endl;
						}
					}
					else
					{
						producttest.first = produtoesc;
						producttest.second = 1;
						accept = true;
					}
				}
				if (accept)
				{


					if (checkString(producttest.first))
					{
						pair <string, int> product;
						product.first = producttest.first;
						ss << producttest.second;
						ss >> product.second;
						ss.clear();
						ss.str("");

						//if input is correctly written, it is added to the transaction and add 1 to the counter
						bool k = true;
						for (unsigned int i = 0; i < produtos.size(); i++)
						{
							if (produtos[i].getNome() == product.first)
							{
								if (find(prods.begin(), prods.end(), product.first) == prods.end())
								{
									prods.push_back(product.first);
									cout << "Product(s) saved." << endl;
								}
								else
								{
									cout << "Product(s) already listed." << endl;
								}
								clientes[pos].setVol(clientes[pos].getVolCompras() + ((produtos[i].getCusto())*product.second));
								cout << "Client purchases volume updated." << endl;
								k = false;
								break;
							}
						}

						if (k)//prints error and goes back to the while cycle
						{
							cout << "Error! Please submit a valid product." << endl;
							system("pause");
							cout << endl;
						}
					}
					else if (checkNumber(producttest.first))
					{
						pair <int, int> product;

						ss << producttest.first;
						ss >> product.first;
						ss.clear();
						ss.str("");

						ss << producttest.second;
						ss >> product.second;
						ss.clear();
						ss.str("");

						if (product.first != 0)
						{

							if (product.first > 0 && product.first <= produtos.size())
							{
								bool z = find(prods.begin(), prods.end(),produtos[product.first-1].getNome() ) == prods.end();
								if (1)
								{
								prods.push_back(produtos[product.first - 1].getNome());
								cout << "Product(s) saved." << endl;
								}
								else
								{
									cout << "Product(s) already listed." << endl;
								}
								clientes[pos].setVol(clientes[pos].getVolCompras() + ((produtos[product.first-1].getCusto()) * product.second));
								cout << "Client purchases volume updated." << endl;
								
							}
							else
							{
								cout << "Error! Please submit a valid product id." << endl;
							}
						}
						else
							return;
					}
					else
					{
						cout << "Error! Invalid input." << endl;
						system("pause");
						cout << endl;
					}
				}
				else
				{
					cout << endl << "Error! Please insert the following type of input: product.quantity OR product" << endl;
					cout << endl << "If you want to stop registering products, press 0" << endl;
				}
			}
		}

	}
	else
	{
		void;
	}
	system("pause");
	return;
}

void VendeMaisMais::removeTransaction() //removes transactions
{

	if (nTrans <= 0)
	{
		cout << "Error! No transactions detected." << endl;
		system("pause");
		return;
	}

	transacoesAlterdas = true;
	string name_string, name;
	stringstream ss;
	int id, transid, k = 1, x = 0;
	vector <int> transacoes_id;


	cout << "Insert the ID or the name of the client you wish to delete transactions: ";
	getline(cin, name_string);
	if (name_string == "0")
	{
		return;
	}

	
	if ((id = CheckClient(name_string)) >= 0)
	{
		int z;
		do
		{
			z=removeTransaction2(id);
		} while (z == 1);

	}

	else {
		cout << "Error! Invalid id/name." << endl;
		system("pause");
	}

	
}

int VendeMaisMais::removeTransaction2(int id)
{
	stringstream ss;
	int transid, k = 1, x = 0;
	vector <int> transacoes_id;

	cout << endl << "Here is the list of the transactions made by that client (the first number is a specific id of the transaction):" << endl << endl;
	for (unsigned int j = 0; j < transacoes.size(); j++) { //compares client's id with client's id in the transaction vector
		if (id == transacoes[j].getIdCliente()) {
			transacoes_id.push_back(j); //stores positions on the transaction vector
			cout << endl << k << " --- " << transacoes[j]; //lists all transactions made by the client user input
			k++;
		}
	}

	
		string temp;
		cout << endl << endl << "Please write here the number of the transaction you want to remove or the word \"ALL\" to remove every transaction on this list" << endl;
		cout << "To stop removing transactions please insert 0." << endl;
		cout << "Please write here: ";

		getline(cin, temp);
		if (temp == "0")
		{
			return 0;
		}
		else if (temp == "ALL" || temp == "all" || temp == "All")
		{
			if (transacoes.size() > 1)
			{
				for (unsigned int i = transacoes_id.size() - 1; i >= 0; i--) //erases all transactions
				{
					transid = transacoes_id[i];
					transacoes.erase(transacoes.begin() + transid);
					if (i == 0)
						break;
				}
				cout << "Success!" << endl;
				system("pause");
				return 0;
			}
			else
			{
				transacoes.erase(transacoes.begin());
				cout << "Success!" << endl;
				system("pause");
			}

		}

		else if (checkNumber(temp))
		{


			ss << temp;
			ss >> transid;
			ss.clear();
			ss.str("");


			if (transid <= transacoes_id.size() && transid != 0)
			{

				transid = transacoes_id[transid - 1] ;


				cout << "Do you really want to remove '" << transacoes[transid] << "' from the database?" << endl;
				if (YesNo()) {
					transacoes.erase(transacoes.begin() + transid); //erases specific transaction
					cout << "Success!" << endl;
					system("pause");
				}
			}
			else
			{
				cout << "Please insert a valid input." << endl;
			}

			//vai buscar a posicao no vector das transacoes correspondente ao numero que foi colocado


		}
		else
		{
			cout << "Please insert a valid input." << endl;
		}
		return 1;
}

/*********************************
* PUBLICIDADE
********************************/


void VendeMaisMais::publicity() //"normal" publicity
{
	int pos, max = 0;
	string temp;
	multimap<int, int> trans;
	map <int, string> products = indiceProds();
	int contador = 0;
	
	listarClientesOrdemAlfa();
	
	do
	{
		cout << "Please insert the ID or the name of a client: ";
		getline(cin, temp);
		if (temp == "0")
		{
			return;
		}

	} while ((pos = CheckClient(temp)) < 0);


	//Check the maximum id's to make a matrix with every data found (even removed clients that have made purchases)
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getId() > max)
			max = clientes[i].getId();
	}
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getIdCliente() > max)
			max = transacoes[i].getIdCliente();
	}


	//Initialize matrix
	vector < vector <bool>  > matriz(max, vector < bool >(produtos.size(), 0));


	//Fills the matrix (all start with false)
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		for (unsigned int k = 0; k < transacoes[i].getprods().size(); k++)
		{
			for (unsigned int l = 0; l < produtos.size(); l++)
			{
				if (produtos[l].getNome() == transacoes[i].getprods()[k])
				{
					matriz[transacoes[i].getIdCliente() - 1][l] = true;
					break;
				}
			}
		}
	}

	//Print matrix (ALL COMMENTED, IF NEEDED, REMOVE THE "/* */" SYMBOLS!)

	/*
	cout << endl;
	for (unsigned int i = 0; i < matriz.size(); i++)
	{
	for (unsigned int j = 0; j < matriz[i].size(); j++)
	{
	cout << matriz[i][j];
	}
	cout << endl;
	}
	cout << endl << endl;
	
	system("pause");
	*/

	for (unsigned int i = 0; i < matriz.size(); i++)
	{
		for (unsigned int j = 0; j < matriz[i].size(); j++)
		{
			if (matriz[i][j] == true)
			{
				trans.insert(pair<int, int>(i, j));
			}
		}
	}

	multimap<int, int>::iterator it, it2, it3, mapit;
	multimap <int, int> bestClients;
	vector<int> bestProducts;
	
	int cont = 0;
	int contfin = 0;
	int x =trans.begin()->first;
	pos = pos - 1;

	//Register the max number of similar items bought + best clients

	for (it = trans.begin(); it != trans.end(); it++) 
	{
		if (x != it->first)
		{
			cont = 0;
			x = it->first;
		}
		
		if (it->first == (pos))
		{
			void;
		}
		else
		{
			for (auto it2 = trans.lower_bound(pos); it2 != trans.upper_bound(pos); it2++)
			{
				if (it2->second == it->second)
				{
					cont++;
					break;
				}
			}
		}
		if (cont > contfin)
		{
			contfin = cont;
			bestClients.clear();
			for (auto it3 = trans.lower_bound(it->first); it3 != trans.upper_bound(it->first); it3++)
			{
				bestClients.insert(pair<int, int>(it->first, it3->second));
			}
		}
		else if (cont == contfin)
		{
			for (auto it3 = trans.lower_bound(it->first); it3 != trans.upper_bound(it->first); it3++)
			{
				bestClients.insert(pair<int, int>(it->first, it3->second));
			}
		}

	}
	

	int test = -1;
	cont = -1;
	int tempor = 0;
	//checks if there are multiple good clients
	for (mapit = bestClients.begin(); mapit != bestClients.end(); mapit++)
	{
		if (test != mapit->first)
		{
			cont++;
			test = mapit->first;
		}
	}

	if (cont > 0)
	{
		x = bestClients.begin()->first;
		cont = 0;
		contfin = 0;

		for (it = bestClients.begin(); it != bestClients.end(); it++)
		{
			if (matriz[pos][it->second] == false) 
			{


				if (tempor == bestClients.size())
				{
					break;
				}
				else
					tempor++;

				for (it2 = bestClients.begin(); it2 != bestClients.end(); it2++)
				{
					if (it->second == it2->second)
					{
						cont++;
					}
				}

				if (cont > contfin)
				{
					contfin = cont;
					bestProducts.clear();
					bestProducts.push_back(it->second);
				}
				else if (cont == contfin)
				{
					bestProducts.push_back(it->second);
				}
			}
		}

		cout << "The victim should buy: " << endl;
		for (unsigned int i = 0; i<bestProducts.size();i++)
		{
			if (matriz[pos][bestProducts[i]] == false)
			{
				cout << TAB_BIG << produtos[bestProducts[i]] << endl;
				contador++;
			}
			
		}
		if (contador == 0)
		{
			cout << "Impossible to compare, client probably hasn't got any viable comparison." << endl;
		}
	}
	else if (cont==0)
	{

		cout << "The victim should buy: " << endl;
		for (mapit = bestClients.begin(); mapit != bestClients.end(); mapit++)
		{
			if (matriz[pos][mapit->second] == false)
			{
				cout << TAB_BIG << products[mapit->second] << endl;
				contador++;
			}
			
		}
		if (contador == 0)
		{
			cout << "Impossible to compare, client probably hasn't got any viable comparison." << endl;
		}
	}
	else
	{
		cout << "No similar items appear to have been bought by any other client!" << endl;
	}
	
	system("pause");

	string temporary;
	cout << endl << endl << "To view the clients/products matrix press L, press any other key to return to the previous menu: ";
	getline(cin, temporary);

	if (temporary == "l" || temporary == "L")
	{
		cout << endl;
		for (unsigned int i = 0; i < matriz.size(); i++)
		{
			cout << "CLIENT" << i + 1 << ": " << setw(30);
			for (unsigned int j = 0; j < matriz[i].size(); j++)
			{
				cout << right <<matriz[i][j];

			}
			cout << endl;
		}
		cout << endl << endl;

		system("pause");
		return;
	}

	system("pause");

}

void VendeMaisMais::publicityBottom10() //publicity for the 10 worst clients
{
	int max = 0;
	multimap<int, int> trans;
	multimap<int, float> clientes_id_vol;
	map <int, string> products = indiceProds();


	clientes_id_vol = bottom10();

	if (clientes_id_vol.size() < 10)
	{
		cout << "Error! Not enough clients to use this function." << endl;
		system("pause");
		return;
	}


	//Check the maximum id's to make a matrix with every data found (even removed clients that have made purchases)
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getId() > max)
			max = clientes[i].getId();
	}
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getIdCliente() > max)
			max = transacoes[i].getIdCliente();
	}


	//Initialize matrix
	vector < vector <bool>  > matriz(max, vector < bool >(produtos.size(), 0));


	//Fills the matrix (all start with false)
	for (unsigned int i = 0; i < transacoes.size(); i++)
	{
		for (unsigned int k = 0; k < transacoes[i].getprods().size(); k++)
		{
			for (unsigned int l = 0; l < produtos.size(); l++)
			{
				if (produtos[l].getNome() == transacoes[i].getprods()[k])
				{
					matriz[transacoes[i].getIdCliente() - 1][l] = true;
					break;
				}
			}
		}
	}

	//Print matrix (ALL COMMENTED, IF NEEDED, REMOVE THE "/* */" SYMBOLS!)

	/*
	cout << endl;
	for (unsigned int i = 0; i < matriz.size(); i++)
	{
	for (unsigned int j = 0; j < matriz[i].size(); j++)
	{
	cout << matriz[i][j];
	}
	cout << endl;
	}
	cout << endl << endl;

	system("pause");
	*/

	//Every transaction made by Bottom10
	for (unsigned int i = 0; i < matriz.size(); i++)
	{
		if ((clientes_id_vol.count(i)) > 0)
		{
			for (unsigned int j = 0; j < matriz[i].size(); j++)
			{
				if (matriz[i][j] == true)
				{
					trans.insert(pair<int, int>(i, j));
				}
			}
		}
	}


	//products common to ALL of the bottom10 clients
	vector<int> bottom10products;
	multimap<int, int>::iterator it, it2;
	int cont = 0;

	for (it = trans.begin(); it != trans.end(); it++)
	{
		for (it2 = trans.begin(); it2 != trans.end(); it2++)
		{
			if (it->second == it2->second)
			{
				cont++;
			}
		}
		if (cont == 10)
		{
			bottom10products.push_back(it->second);
		}
	}

	//Clients that bought all of the common bottom10 products +1

	vector <int> interestingClients;
	bool z;

	for (unsigned int i = 0; i < matriz.size(); i++)
	{
		z = false;
		cont = 0;
		if ((clientes_id_vol.count(i)) > 0)
		{
			void;
		}
		else
		{
			for (unsigned int j = 0; j < matriz[i].size(); j++)
			{
				if (matriz[i][j] == true && find(bottom10products.begin(), bottom10products.end(), j) != bottom10products.end())
				{
					cont++;
				}
				else if (matriz[i][j] == true)
				{
					z = true;
				}
			}
			if (cont == bottom10products.size() && z)
			{
				interestingClients.push_back(i);
			}
		}
	}

	//histogram (in multimap form) (ordered by client) for the quantity of interesting bought products by the interesting clients (products that are not on bottom10products and are bought by interesting clients)
	multimap <int, int> histogram;
	multimap <int, int>::iterator histit;

	for (unsigned int i = 0; i < interestingClients.size(); i++)
	{
		for (unsigned int j = 0; j < matriz[i].size(); j++)
		{
			if (matriz[i][j] == true && find(bottom10products.begin(), bottom10products.end(), j) == bottom10products.end())
			{
				histogram.insert(pair <int, int>(i, j));
			}
		}
	}


	//reversed histogram (key is now the products bought);

	multimap<int, int> histogramrev;
	for (histit = histogram.begin(); histit != histogram.end(); histit++)
	{
		histogramrev.insert(pair<int, int>(histit->second, histit->first));
	}


	//number of products ordered by histogramrev index
	vector <int> numberProds;
	int x = -1;
	cont = -1;
	int contt = 0;

	for (histit = histogramrev.begin(); histit != histogramrev.end(); histit++)
	{
		if (histit->first != x)
		{
			cont++;
			x = histit->first;
			if (cont > 0)
			{
				numberProds.push_back(contt);
				contt = 0;
			}
		}
		contt++;
	}

	//create sorted vector (leave other intact)
	vector <int> numberProdsSorted;

	numberProdsSorted = numberProds;


	sort(numberProdsSorted.rbegin(), numberProdsSorted.rend());

	//run through histogram:

	vector<int> test;
	vector <int> RecommendedItems;

	for (unsigned int i = 0; i < numberProdsSorted.size(); i++)
	{
		int prodpos;
		prodpos = distance(numberProds.begin(), find(numberProds.begin(), numberProds.end(), numberProdsSorted[i]));

		while ((find(test.begin(), test.end(), prodpos) != test.end()))
		{
			prodpos++;
		}

		test.push_back(prodpos);

		cont = -1;
		x = -1;
		for (histit = histogramrev.begin(); histit != histogramrev.end(); histit++)
		{
			if (x != histit->first)
			{
				cont++;
				x = histit->first;
			}
			if (prodpos == cont)
			{
				RecommendedItems.push_back(histit->first);
			}
		}
	}

	//getting the best item, checking for products that have not been purhcased by anyone on the bottom10 vector



	for (unsigned int i = 0; i < RecommendedItems.size(); i++)
	{
		bool n = true;
		for (histit = trans.begin(); histit != trans.end(); histit++)
		{

			if (RecommendedItems[i] == histit->second)
			{
				n = false;
			}

		}
		if (n)
		{
			cout << TAB_BIG << "O produto sugerido para publicitar aos 10 clientes com menos compras e: " << products[RecommendedItems[i]] << endl;
			system("pause");
			return;
		}
	}


	//getting items quantities
	multimap<int, int> itemsquantities;

	int testing = -1;
	for (unsigned int i = 0; i < RecommendedItems.size(); i++)
	{
		if (testing != RecommendedItems[i])
		{
			testing = RecommendedItems[i];
			itemsquantities.insert(pair<int, int>(RecommendedItems[i], count(RecommendedItems.begin(), RecommendedItems.end(), RecommendedItems[i])));
		}
	}

	vector<int>quantities;

	for (it = itemsquantities.begin(); it != itemsquantities.end(); it++)
	{
		cont = 0;
		for (it2 = trans.begin(); it2 != trans.end(); it2++)
		{
			if (it->first == it2->second)
				cont++;
		}
		quantities.push_back(it->second - cont);
	}

	//best item
	 int h=*max_element(quantities.begin(), quantities.end());


	 //find and print best item
	 for (it = itemsquantities.begin(); it != itemsquantities.end(); it++)
	 {
		 if (it->second == h)
		 {
			 cout << TAB_BIG << "O produto sugerido para publicitar aos 10 clientes com menos compras e: " << products[it->first] << endl;
			 system("pause");
			 return;
		 }
	 }

}

multimap<int,float> VendeMaisMais::bottom10()
{
	multimap <int, float> bottom10map;
	vector <float> bottom10test;
	vector<float> bottom10;

	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		bottom10test.push_back(clientes[i].getVolCompras());
	}

	sort(bottom10test.begin(), bottom10test.end());

	for (unsigned int i = 0; i < bottom10test.size(); i++)
	{
		if (i < 10)
		{
			bottom10.push_back(bottom10test[i]);
		}
		else
		{
			break;
		}
	}

		for (unsigned int j = 0; j < clientes.size(); j++)
		{
			if (bottom10map.size() <= 10)
			{
				if (((find(bottom10.begin(), bottom10.end(), clientes[j].getVolCompras())) != bottom10.end()))
				{
					bottom10map.insert(pair<int, float>(clientes[j].getId(), clientes[j].getVolCompras()));
				}
			}
			else
				break;
		}


		return bottom10map;
}

map<int, string> VendeMaisMais::indiceProds()
{
	map<int,string> temp;
	for (unsigned int i = 0;i< produtos.size(); i++)
	{
		temp[i] = produtos[i].getNome();
	}
	return temp;
}

/*********************************
 * Preservar Informacao
 ********************************/  

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{

	ofstream of;
	if (clientesAlterados) //have clients been changed?
	{
		of.open(fichClientes, ios::trunc);
		if (of.is_open())
		{
			of << nClientes;
			for (unsigned int i = 0; i < clientes.size(); i++)
			{
				of << endl;
				clientes[i].save(of);
			}
			of.close();
		}
		else
		{
			cout << "Error! Clients changes have not been saved!" << endl;
		}
	}
	if (produtosAlterados) //have products been changed?
	{
		of.open(fichProdutos, ios::trunc);
		if (of.is_open())
		{
			of << nProds;
			for (unsigned int i = 0; i < produtos.size(); i++)
			{
				of << endl;
				produtos[i].save(of);
			}
			of.close();
		}
		else
		{
			cout << "Error! Products changes have not been saved!" << endl;
		}
	}

	if (transacoesAlterdas) //have transactions been changed?
	{
		of.open(fichTransacoes, ios::trunc);
		if (of.is_open())
		{
			of << nTrans;
			for (unsigned int i = 0; i < transacoes.size(); i++)
			{
				of << endl;
				transacoes[i].save(of);
			}
			of.close();
		}
		else
		{
			cout << "Error! Products changes have not been saved!" << endl;
		}
	}
	

}

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){

	return out << "You are using the \"Vende++\" Supermarket Software coded and designed by Mario Fernandes and Sergio Salgado, thank you for using our software." << endl << endl << "Currently you are working in " << supermercado.loja << " which has " << supermercado.nClientes << " clients, " << supermercado.nProds << " products and " << supermercado.nTrans << " transactions." << endl;
}
