#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return idCliente;
}

Data Transacao::getDataTrans() const
{
	return data;
}

vector <string>  Transacao::getprods() const
{
	return produtos;
}

void Transacao::setProds(vector<string> newproducts)
{
	produtos = newproducts;
}

Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos

	string line,dataTemp,prods;
	stringstream ss;
	int pos1 = -1;
	int pos2 = -1;
	
	getline(in, line);

	for (unsigned int i = 0; i < line.size(); i++)
	{
		if (line[i] == ';')
		{
			if (pos1 == -1)
			{
				pos1 = i;
			}
			else if (pos2 == -1)
			{
				pos2 = i;
				break;
			}
		}
	}

	ss << line.substr(0, pos1 - 1);
	ss >> idCliente;
	ss.clear();
	ss.str("");

	dataTemp = checkDate(line.substr(pos1 + 1, pos2 - 2 - pos1));

	data = Data(dataTemp);

	prods = line.substr(pos2 + 2, line.size() - pos2 - 1);
	unsigned int j;

	for (unsigned int i = 0; i < prods.size(); i++)
	{
		for (j = i+1; j < prods.size(); j++)
		{
			if (prods[j] == ',')
			{
				produtos.push_back(prods.substr(i, j - i));
				break;
			}
			else if (j == prods.size() - 1)
			{
				produtos.push_back(prods.substr(i, prods.size() - i));
				break;
			}
		}
		i = j+1;
	}

}

Transacao::Transacao(int id, Data date, vector <string> prods)
{
	idCliente = id;
	data = date;
	produtos = prods;
}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
  
	out << idCliente << " ; " << data << " ;";
	for (unsigned int i = 0; i < produtos.size(); i++)
	{
		if (i == produtos.size() - 1)
		{
			out << produtos[i];
		}
		else
		{
			out << produtos[i] << ",";
		}
	}
}


ostream& operator<<(ostream& out, const Transacao & trans){

	out << trans.idCliente << " ; " << trans.data << " ; ";
	for (unsigned int i = 0; i < trans.produtos.size(); i++)
	{
		if (i == trans.produtos.size() - 1)
			out << trans.produtos[i];
		else
		out << trans.produtos[i] << ",";
	}
	return out;
}


bool operadorTrans(const Transacao &trans1, const Transacao &trans2) {

	return ((trans1.idCliente < trans2.idCliente) || ((trans1.idCliente == trans2.idCliente) && (operadorData(trans1.data, trans2.data))));
}

bool operadorTransData(const Transacao &trans1, const Transacao &trans2) {

	return ((operadorData(trans1.data, trans2.data) || (sameData(trans1.data, trans2.data)) && (trans1.idCliente < trans2.idCliente)));
}
