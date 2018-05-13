// BrightOne1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


int check(unsigned char buff)
{

		int suma = 0;
		while (buff > 0)
		{
			if (buff & 1 == 1)
			{
				suma++;
			}
			buff=buff>>1;
		}
		return suma;
}

int main()
{
	string tekst;
	fstream file;
	ofstream myOutFile;
	unsigned char *buff{0};
	unsigned char *parzyste{0};
	unsigned char *nieparzyste{0};

	file.open("plik.txt", ios::in);
	if (file.good())
	{
		int temp = 0;
		while (!file.eof())
		{
			getline(file, tekst);
			istringstream iss(tekst);
			buff = new unsigned char[tekst.length()]{ 0 };
			int b = 0;
			for (int i = 0; i < tekst.length(); i++)
			{

				int a =iss.get();

				if ((b%2==0)&&((a >= '0' && a <= '9')))
				{
					a = a - 48;
					buff[temp] += a<<4;
					b++;
				}
				else if((b % 2 == 0) && (a >= 'A' && a <= 'F'))
				{
					a = a - 'A' + 10;
					buff[temp] += a<<4;
					b++;
				}
				else if ((b % 2 == 1) && (a >= '0' && a <= '9'))
				{
					a = a - 48;
					buff[temp] += a;
					temp++;
					b++;
				}
				else if ((b % 2 == 1) && (a >= 'A' && a <= 'F'))
				{
					a = a - 'A' + 10;
					buff[temp] += a;
					temp++;
					b++;
				}
			}
			if (b % 2)
			{
				buff[temp] = buff[temp] >> 4;
			}
			else
			{
				temp--;
			}
		}

		parzyste = new unsigned char[temp]{ 0 };
		nieparzyste = new unsigned char[temp]{ 0 };
		int suma = 0;
		int index_n = 0;
		int inedx_p = 0;

		for (int i = 0; i <= temp; i++)
		{
			suma = check(buff[i]);
			if (suma % 2)
			{
				nieparzyste[index_n] = buff[i];
				index_n++;
			}
			else
			{
				parzyste[inedx_p] = buff[i];
				inedx_p++;
			}
		}
		
		//sortowanie rosnace
		for (int i = 0; i < index_n - 1; i++)
		{
			for (int j = 0; j < index_n - 1; j++)
			{
				if (nieparzyste[j] > nieparzyste[j + 1])
				{
					unsigned char temp = nieparzyste[j + 1];
					nieparzyste[j + 1] = nieparzyste[j];
					nieparzyste[j] = temp;
				}
			}
		}

		//sortowanie malejace
		for (int i = 0; i < inedx_p - 1; i++)
		{
			for (int j = 0; j < inedx_p - 1; j++)
			{
				if (parzyste[j] < parzyste[j + 1])
				{
					unsigned char temp = parzyste[j + 1];
					parzyste[j + 1] = parzyste[j];
					parzyste[j] = temp;
				}
			}
		}


		myOutFile.open("myFile.txt", ios::out);
		myOutFile << "Numbers containing an even number of ones sorted in ascending order:\n";
		for (int i = 0; i < index_n; i++)
		{
			if (nieparzyste[i] >= 0 && nieparzyste[i] <= 9 && nieparzyste[i] != buff[temp])
				myOutFile << hex << uppercase <<'0'<< static_cast<int>(nieparzyste[i]) << " ";
			else
				myOutFile << hex << uppercase << static_cast<int>(nieparzyste[i]) << " ";
		}
		myOutFile << "\n";
		myOutFile << "Remaining numbers sorted in descending order:\n";
		for (int i = 0; i < inedx_p; i++)
		{
			if(parzyste[i] >= 0 && parzyste[i] <= 9 && parzyste[i]!=buff[temp])
				myOutFile << hex << uppercase << '0' << static_cast<int>(parzyste[i]) << " ";
			else
				myOutFile << hex << uppercase << static_cast<int>(parzyste[i]) << " ";
		}
			
		file.close();
		myOutFile.close();
		delete[] parzyste;
		delete[] nieparzyste;
		delete[] buff;
	}
    return 0;
}

