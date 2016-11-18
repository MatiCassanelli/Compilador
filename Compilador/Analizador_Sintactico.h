#pragma once
#include <vector>
#include "Analizador_Lexico.h"
class Analizador_Sintactico
{
private:
	char token;
	int c;
	Analizador_Lexico Lexico;
	ofstream of;
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
	void simbolos_juntos(char);
};

