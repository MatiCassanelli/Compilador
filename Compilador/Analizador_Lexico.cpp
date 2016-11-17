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

void Analizador_Lexico::leer_archivo()
{
	int contador = 0;
	while (!fe.eof())
	{
		if (comprobar_token(fe.get()) != ' ' || comprobar_token(fe.get()) != '\n')
		{
			cadena.push_back(fe.get());
			cout << "OK";
		}
		else
			cerr << "Error";	//error
		contador++;
	}
	fe.close();
}

char Analizador_Lexico::comprobar_token(char caracter)
{
	int i = 0;
	caracter_leido = caracter;
	if (caracter_leido == ' '||caracter_leido=='\n')
		return caracter_leido;
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
	return caracter_leido;
	}
	
	for (char i = 'a'; i <= 'z'; i++)
		if (i == caracter_leido)
			return caracter_leido;
	for (int i = 0; i < 10; i++)
		if (i == caracter_leido)
			return caracter_leido;
}
