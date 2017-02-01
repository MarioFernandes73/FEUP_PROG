# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "utils.h"

using namespace std;


class Data {
 private:
  int day;
  int month;
  int year;

 public:
  Data(){};
  Data(int dia, int mes, int ano);
  Data(string dataStr); // data na forma DD/MM/AAA -> receives a date string and sets day, month, year
  int getDia() const;
  int getMes() const;
  int getAno() const;
  void setDia(int dia); //Checks if the day actually exists in the year/month defined
  void setMes(int mes);
  void setAno(int ano);
  void save(ofstream & out) const;
  friend ostream& operator<<(ostream& out, const Data & data); //prints class Data
  friend bool sameData(const Data &data1, const Data &data2);
  friend bool biggerData(const Data &data1, const Data &data2);
  friend bool operadorData(const Data &data1, const Data &data2);
};