#pragma once
#include <vector>
#include "Analizador_Lexico.h"
class Analizador_Sintactico
{
private:
	//vector<char> alfabeto = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n' };
	char token;
	int c;
	Analizador_Lexico Lexico;
public:
	Analizador_Sintactico();
	~Analizador_Sintactico();

	bool programa();
	bool bloque();
	bool otrasentencia();
	bool sentencia();
	bool asignacion();
	bool expresion();
	bool mastermino();
	bool termino();
	bool masfactor();
	bool factor();
	bool lectura();
	bool escritura();
	bool variable();
	bool constante();
};

