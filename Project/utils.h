#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "defs.h"



using namespace std;


void clearScreen();

unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int max);
int leInteiro(int min, int max);

string checkDate(string date);
bool leapYear(int year); //Checks if year is a leap year and returns 1 if it is, 0 if it isn't

void elemSpaces(string & temp);

bool checkFile(string filename);

bool YesNo();

bool checkString(string temp);

bool checkNumber(string temp);

bool checkFloat(string temp);
