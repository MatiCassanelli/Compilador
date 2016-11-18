#include "stdafx.h"
#include "Analizador_Lexico.h"


Analizador_Lexico::Analizador_Lexico()
{
	if (abrir_archivo() == false)
	{
		error = true;
		cout << "Error al abrir el archivo" << endl;
	}
	else
	{
		leer_archivo();
		comprobar_cadena();
		eliminar_espacios();
	}

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
	if (pos > cadena.size()-1)
		return -1;
	else
		return cadena[pos];
}

void Analizador_Lexico::comprobar_cadena()
{
	for (int i = 0; i < cadena.size()-1; i++)
	{
		if (cadena[i] >= 'a' && cadena[i] <= 'z')
			if (cadena[i + 1] >= 'a' && cadena[i + 1] <= 'z')
			{
				cout << cadena[i] << cadena[i + 1] << ": Nombre de variable no admitido" << endl;
				error = true;
				return;
			}
			else if (isdigit(cadena[i + 1]))
			{
				cout << cadena[i]<< cadena[i + 1]<<": Nombre de variable no admitido" << endl;
				error = true;
				return;
			}
	}
	//error = false;
}

void Analizador_Lexico::eliminar_espacios()
{
	for (int i = 0; i < cadena.size(); i++)
		if (cadena[i] == ' ')
			cadena.erase(cadena.begin() + i);
}

bool Analizador_Lexico::hay_error()
{
	return error;
}

void Analizador_Lexico::leer_archivo()
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
		}
		else
			if (rta == 0 && leo != -1)	//-1 es el termino de eof
			{
				cout << "Error. " << leo << " no es un caracter valido" << endl;
				error = true;
			}
	}
	fe.close();
	//return error;
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

