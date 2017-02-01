#include "utils.h"


void clearScreen(){
	system("cls");
	return;
}



//return 9 -> error
unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){

	string temp;
	stringstream ss;
	unsigned short int number;
	
	getline(cin, temp);

	//Simple cycle to check if the string called harbors any unwanted characters (in this case, anything that's not a digit)
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (!isdigit(temp[i]))
		{
			cout << "Error! Please only insert one digit." << endl;
			system("pause");
			return 9;
		}
	}

	ss << temp;
	ss >> number;
	ss.clear();
	ss.str("");

	if (number < min || number > max)
	{
		cout << "Error! Please insert a number bigger than " << min << " and smaller than " << max << "." << endl;
		system("pause");
		return 9;
	}
	else
		return number;
}

//return 0 -> error
int leInteiro(int min, int max){

	string temp;
	stringstream ss;
	int number;

	getline(cin, temp);

	//Simple cycle to check if the string called harbors any unwanted characters (in this case, anything that's not a digit)
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (!isdigit(temp[i]))
		{
			cout << "Error! Please only insert digits." << endl;
			system("pause");
			return -1;
		}
	}

	ss << temp;
	ss >> number;
	ss.clear();
	ss.str("");

	if (number < min || number > max)
	{
		cout << "Error! Please insert a number bigger than " << min << " and smaller than " << max << "." << endl;
		system("pause");
		return -1;
	}
	else
		return number;

}



//usage: "while ( (string = checkDate ( string ) ) == "false" ) { getline(cin,string) } (do while)
string checkDate(string  date)
{

	elemSpaces(date);


	unsigned int pos1 = -1;
	unsigned int pos2 = -1;

	//analyze where "/" is, register it, and see if there is only 2 "/" and the rest are numbers
	for (unsigned int i = 0; i < date.size(); i++)
	{
		if (date[i] == '/')
		{
			if (pos1 == -1)
			{
				pos1 = i;
			}
			else if (pos2 == -1)
			{
				pos2 = i;
			}
			else
			{
				cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
				system("pause");
				return "false";
			}
		}
		else if (!isdigit(date[i]))
		{
			cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
			system("pause");
			return "false";
		}
	}

	//analyze if it's in the format of DD/MM/YYYY, if not, add 0's or return false
	
	int k=0;
	
	if (pos1 == 2)
		void;
	else if (pos1 > 2)
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
		system("pause");
		return "false";
	}
	else if (pos1 == 1)
	{
		k = 1;
		date.insert(0, "0");
	}
	else
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
		system("pause");
		return "false";
	}
	// "DD/" -> is guaranteed or returned false by now


	if (pos2 > 5)
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
		system("pause");
		return "false";
	}
	else if (pos2 == 5 && k == 0)
	{
		void;
	}
	else if (pos2 == 4)
	{
		if (k == 0)
		{
			date.insert(3, "0");
		}
		else if (k == 1)
		{
			void;
		}
	}
	else if (pos2 == 3 && k == 1)
	{
		date.insert(3, "0");
	}
	else
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
		system("pause");
		return "false";
	}
	// "DD/MM/" -> is guaranteed or returned false by now



	//Date string should be in the standard "DD/MM/YYYY" mode by now or has/will return false after this cycle
	if (date.size() != 10)//if year is higher than 9999 or lower than 1000
	{
		cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
		system("pause");
		return "false";
	}
	else
	{
		for (unsigned int i = 0; i < date.size(); i++)
		{
			if (i != 2 && i != 5)
			{
				if (!isdigit(date[i]))
				{
					cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
					system("pause");
					return "false";
				}
			}
			else
			{
				if (date[i] != '/')
				{
					cout << "Error! Please insert a valid date (DD/MM/YYYY)." << endl;
					system("pause");
					return "false";
				}
			}
		}
	}


	//Time to test if the date actually exists (exampls of strings that could pass: 34/20/9999)

	stringstream ss;
	int tempYear, tempMonth, tempDay;

	ss << date.substr(6, 4);
	ss >> tempYear;
	ss.clear();
	ss.str("");

	ss << date.substr(3, 2);
	ss >> tempMonth;
	ss.clear();
	ss.str("");
	
	if (tempMonth > 12 || tempMonth < 1)
	{
		cout << "Error! Please insert a valid month" << endl;
		system("pause");
		return "false";
	}

	ss << date.substr(0, 2);
	ss >> tempDay;
	ss.clear();
	ss.str("");


	if (tempMonth == 2)
	{
		if (leapYear(tempYear))
		{
			if (tempDay > 29 || tempDay < 1)
			{
				cout << "Error! Please insert a valid day." << endl;
				system("pause");
				return "false";
			}
		}
		else
		{
			if (tempDay > 28 || tempDay < 1)
			{
				cout << "Error! Please insert a valid day." << endl;
				system("pause");
				return "false";
			}
		}
	}
	else if (tempMonth == 1 || tempMonth == 3 || tempMonth == 5 || tempMonth == 7 || tempMonth == 8 || tempMonth == 10 || tempMonth == 12)
	{
		if (tempDay > 31 || tempDay < 1)
		{
			cout << "Error! Please insert a valid day." << endl;
			system("pause");
			return "false";
		}
	}
	else
	{
		if (tempDay > 30 || tempDay < 1)
		{
			cout << "Error! Please insert a valid day." << endl;
			system("pause");
			return "false";
		}
	}
	return date;
}


bool leapYear(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return false;
	else
		return true;
}

void elemSpaces(string & temp)
{
	if (temp.size() > 1)
	{
		size_t f = temp.find_first_not_of(' ');
		temp = temp.substr(f, temp.find_last_not_of(' ') - f + 1);
	}
}

bool checkFile(string filename)
{
	ifstream in;
	in.open(filename);
	if (in.is_open())
	{
		in.close();
		return true;
	}
	else
	{
		cout << filename << " can not be opened!" << endl;
		system("pause");
		return false;
	}
}

bool YesNo()
{
	string input = "erro";
	while (input != "y" || input != "Y" || input != "n" || input != "N")
	{
		cout << "Press Y for yes or N for no: ";

		getline(cin, input);

		if (input == "y" || input == "Y")
		{
			return true;
		}
		else if (input == "n" || input == "N")
		{
			return false;
		}
		else
		{
			cout << "Error! Please only write Y/N!" << endl << endl;
		}
	}
}

bool checkString(string temp)
{
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (!isalpha(temp[i]) && !isspace(temp[i]))
		{
			return false;
		}
	}

	return true;

}

bool checkNumber(string temp)
{
	
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			if (!isdigit(temp[i]))
			{
				return false;
			}
		}

		return true;
	
}

bool checkFloat(string temp)
{
	unsigned int short k = 0;

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (k == 0)
		{
			if (temp[i] == '.')
			{
				k = 1;
			}
			else if (!isdigit(temp[i]))
			{
				cout << "Invalid number, please only insert a number (use '.' for the decimal point)" << endl;
				system("pause");
				return false;
			}
		}
		else if (!isdigit(temp[i]))
		{
			cout << "Invalid number, please only insert a number (use '.' for the decimal point)" << endl;
			system("pause");
			return false;
		}
		
	}

	return true;
}
