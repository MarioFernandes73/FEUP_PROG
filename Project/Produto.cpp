#include "Produto.h"


Produto::Produto(ifstream & in){// nome ; custo
	string line;
	stringstream ss;
	getline(in, line);

	int pos1 = -1;

	for (unsigned int i = 0; i < line.size(); i++)
	{
		if (line[i] == ';')
		{
			pos1 = i;
			break;
		}
	}

	nome = line.substr(0, pos1 - 1);
	elemSpaces(nome);

	ss << line.substr(pos1 + 2, line.size() - pos1 - 2);
	ss >> custo;
}

Produto::Produto(string name, float cost)
{
	nome = name;
	custo = cost;
}

string Produto::getNome() const {
  return nome;
}

float Produto::getCusto() const {
  return custo;
}

void Produto::setNome(string name)
{
	nome = name;
}

void Produto::setCusto(float cost)
{
	custo = cost;
}

void Produto::setCusto(string cost)
{
	stringstream ss;
	ss << cost;
	ss >> custo;
	ss.clear();
	ss.str("");
}

ostream& operator<<(ostream& out, const Produto & prod){


	return out << prod.nome << " - " << fixed << setprecision(2) << prod.custo;
	
}


bool operadorProd(const Produto &prod1, const Produto &prod2){
 
	return prod1.getNome() < prod2.getNome();
}

void Produto::save(ofstream & out) const {

	out << nome << " ; " << custo;

}

