#pragma once
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
class Analizador_Lexico
{
private:
	char caracter_leido;
	int traza;
	ifstream fe;
	vector<char> cadena;	//para hacer mas simple el manejo de lo q leamos del txt
public:
	Analizador_Lexico();
	//Analizador_Lexico(char[100]);
	~Analizador_Lexico();
	bool abrir_archivo();
	bool leer_archivo();
	int comprobar_token(char);
	char get_token(int);	//entero para la posicion dentro de la cadena
	bool comprobar_cadena();
};

