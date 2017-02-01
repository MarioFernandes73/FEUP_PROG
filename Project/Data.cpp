#include "Data.h"

Data::Data(int dia, int mes, int ano)
{
	day = dia;
	month = mes;
	year = ano;
}

// gets date in DD/MM/AAAA fprm (before it receives, run checkDate)
Data::Data(string dataStr) { 
	
	stringstream ss;
	int tempYear, tempMonth, tempDay;

	ss << dataStr.substr(6, 4);
	ss >> tempYear;
	ss.clear();
	ss.str("");

	setAno(tempYear);

	ss << dataStr.substr(3, 2);
	ss >> tempMonth;
	ss.clear();
	ss.str("");

	setMes(tempMonth);

	ss << dataStr.substr(0, 2);
	ss >> tempDay;
	ss.clear();
	ss.str("");

	setDia(tempDay);

}

int Data::getDia() const{
  return day;
}

int Data::getMes() const{
  return month;
}

int Data::getAno() const{
  return year;
}

void Data::setDia(int dia){
	day = dia;
} 

void Data::setMes(int mes) {
	month = mes;
}

void Data::setAno(int ano){
	year = ano;
}


void Data::save(ofstream & out) const{
  // A IMPLEMENTAR
}

//prints Class Data
ostream& operator<<(ostream& out, const Data & data){
	stringstream ss;
	string temp;
	ss << data.day << "/" << data.month << "/" << data.year;
	ss >> temp;
	ss.clear();
	ss.str("");
	temp = checkDate(temp);
	
	return out << temp;
}


bool sameData(const Data &data1, const Data &data2)
{
	return ((data1.year == data2.year) && (data1.month == data2.month) && (data1.day == data2.day));
}

bool operadorData(const Data &data1, const Data &data2)
{
	return ((data1.year < data2.year) || ((data1.year == data2.year) && (data1.month < data2.month)) || ((data1.year == data2.year) && (data1.month == data2.month) && (data1.day < data2.day)));
}

bool biggerData(const Data &data1, const Data &data2)
{
	return ((data1.year > data2.year) || ((data1.year == data2.year) && (data1.month > data2.month)) || ((data1.year == data2.year) && (data1.month == data2.month) && (data1.day > data2.day)));
}