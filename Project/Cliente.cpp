#include "Cliente.h"


Cliente::Cliente(ifstream & in){
	
	string line,test;
	stringstream ss;

	getline(in, line);

	int cont = 0;
	int x;
	for (unsigned int i = 0; i < line.size(); i++) //checks the client file line for separations between client parameters
	{
		if (line[i] == ';') //checks if the char that's getting checked is a ";". After that checks if it is the first, second or third ";"
		{
			if (cont == 0)
			{
				ss << line.substr(0, i - 1);
				ss >> id;
				ss.clear();
				ss.str("");
				cont++;
				x = i;
			}
			else if (cont == 1)
			{
				nome = line.substr(x + 2, i - x - 3);
				cont++;
				x = i;
			}
			else if (cont == 2)
			{
				if ((test = checkDate(line.substr(x + 2, i - x - 3))) != "false")
				{
					if (test == line.substr(x + 2, i - x - 3))
					{
						cartaoCliente = Data(line.substr(x + 2, i - x - 3));
					}
					else
					{
						cartaoCliente = Data(test);
					}
				}
				else
				{
					cartaoCliente = Data(line.substr(x + 2, i - x - 3));
					cout << "!WARNING! THIS DATE IS EITHER WRITTEN WRONG OR IS NOT A REAL DATE! -> " << line << endl << "CHANGE IT ASAP OR ELSE SOME FUNCTIONS WILL NOT WORK!" << endl;
				}
				cont++;
				x = i;
			}
		}
			if (cont == 3)
			{
				ss << line.substr(x + 2, line.size()-x-2);
				ss >> volCompras;
				ss.clear();
				ss.str("");
			}
			
			
		}
	}

	


Cliente::Cliente(int id1, string name, Data date, float volc)
{
	id = id1;
	nome = name;
	cartaoCliente = date;
	volCompras = volc;
}



string Cliente::getNome() const{
  return nome;
}

unsigned int Cliente::getId() const{
  return id;
}

Data Cliente::getData() const{
	return cartaoCliente;
}

float Cliente::getVolCompras() const{
  return volCompras;
}

void Cliente::setNome(string name)
{
	nome = name;
}

void Cliente::setData(Data date)
{
	cartaoCliente = date;
}

void Cliente::setVol(float vol)
{
	volCompras = vol;
}

void Cliente::save(ofstream & out) const{

	out << id << " ; " << nome << " ; " << cartaoCliente << " ; " << volCompras;

}

ostream& operator<<(ostream& out, const Cliente & cli){
	return out << setw(4) << cli.id << " - " << setw(25) << cli.nome << " - " << setw(10) << cli.cartaoCliente << " - " << setw(10) <<cli.volCompras;
}


bool operadorClie(const Cliente &cli1, const Cliente &cli2){
  
	return cli1.getNome() < cli2.getNome();
}
