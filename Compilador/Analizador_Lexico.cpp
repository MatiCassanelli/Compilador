#include "stdafx.h"
#include "Analizador_Lexico.h"


Analizador_Lexico::Analizador_Lexico()
{
	if(abrir_archivo()==false)
		cerr << "Error al abrir el archivo" << endl;
	else
		leer_archivo();
}

//Analizador_Lexico::Analizador_Lexico(char nombre_Archivo[100])
//{
//	fe = ifstream(nombre_Archivo);
//	if (fe.fail())
//		cerr << "Error al abrir el archivo" << endl;
//	leer_archivo();
//}


Analizador_Lexico::~Analizador_Lexico()
{
	fe.close();
	cout << "Archivo cerrado";
}

bool Analizador_Lexico::abrir_archivo()
{
	fe = ifstream("asd.txt");
	if (fe.fail())
		
		return false;
	else
		return true;
}

char Analizador_Lexico::get_token(int pos)
{
	return cadena[pos];
}

bool Analizador_Lexico::comprobar_cadena()
{
	for (int i = 0; i < cadena.size()-1; i++)
	{
		if (isalpha(cadena[i]))
			if (cadena[i + 1] != ' ')
				return false;
	}
	return true;
}

bool Analizador_Lexico::leer_archivo()
{
	int contador = 0;
	char leo;
	while (!fe.eof())
	{
		leo = fe.get();
		int rta = comprobar_token(leo);
		if (rta == 1)
		{
			cadena.push_back(leo);
			//cout << "OK";
		}
		else
			if (rta == 0 && leo !=-1)
				cerr << "Error. "<<leo<<"no es un caracter valido";	//error
	}
	fe.close();
	return comprobar_cadena();
}

int Analizador_Lexico::comprobar_token(char caracter)
{
	int i = 0;
	caracter_leido = caracter;
	if (caracter_leido=='\n')
		return 2;
	switch (caracter_leido)
	{
	case 'M':
	case 'R':
	case 'W':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case '(':
	case ')':
	case ';':
	case '{':
	case '}':
	case ' ':
	return 1;
	}
	
	for (char i = 'a'; i <= 'z'; i++)
		if (i == caracter_leido)
			return 1;
	for (char i = 48; i <=57; i++)
	{
		if (i == caracter_leido)
			return 1;
	}
	return 0;
}

