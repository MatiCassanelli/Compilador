#include "stdafx.h"
#include "Analizador_Sintactico.h"
using namespace std;

Analizador_Sintactico::Analizador_Sintactico()
{
	c = 0;
	if (Lexico.hay_error() == false)
	{
		of.open("Codigo.txt");
		programa();
		of.close();
	}
	else
		cout << "Se cancelo la compilacion" << endl;
}

Analizador_Sintactico::~Analizador_Sintactico()
{
}

bool Analizador_Sintactico::programa()
{
	bool ret = false;
	if (Lexico.get_token(c) == 'M')
	{
		c++;
		if (Lexico.get_token(c) == '{')
		{
			of << ".CODE\n";
			c++;
			if (bloque() == true)
			{
				if (Lexico.get_token(c) == '}')
				{
					of << "END";
					ret = true;
					cout << "Compilacion y codificacion correcta!"<<endl;
				}
			}
			else cout << "Falta }" << endl;
		}
		else cout << "Falta {" << endl;
	}
	else cout << "Falta simbolo de inicio M"<<endl;
	
	return ret;
}

bool Analizador_Sintactico::bloque()
{
	bool ret = false;
	if (sentencia() == true)
		if (otrasentencia() == true)
			ret = true;
	return ret;
}

bool Analizador_Sintactico::otrasentencia()
{
	bool ret = false;
	if (Lexico.get_token(c) == ';')
	{
		c++;
		if (Lexico.get_token(c) == '}')
			ret = true;
		//if (Lexico.get_token(c) == -1)
		//	ret = false;
		else if (sentencia() == true)	//; sentencia otrasentencia
		{
			if (otrasentencia() == true)
				ret = true;
		}
		//else cout << "Falta }"<<endl;	//esto imprime falta } cada vez q la sentencia este mal
	}
	else
		cout << "Falta ;" << endl;
	return ret;
}

bool Analizador_Sintactico::sentencia()
{
	bool ret = false;
	if (lectura() == true)
	{
		of << "INPUT "<<Lexico.get_token(c-1)<<"\n";
		ret = true;
	}
	else if (escritura() == true)
	{
		of << "OUTPUT " << Lexico.get_token(c-1) << "\n";
		ret = true;
	}
	else if (asignacion() == true)
	{
		ret = true;
	}
	return ret;
}

bool Analizador_Sintactico::asignacion()
{
	bool ret = false;
	if (variable() == true)
	{
		of << "PUSHA "<<Lexico.get_token(c-1)<<"\n";
		if (Lexico.get_token(c) == '=')
		{
			c++;
			if (expresion() == true)
			{
				of << "STORE\n";
				ret = true;
			}
		}
	}
	return ret;
}

bool Analizador_Sintactico::expresion()
{
	bool ret = false;
	if (termino() == true)
	{
		if (mastermino() == true)
			ret = true;
	}
	return ret;
}

bool Analizador_Sintactico::mastermino()
{
	bool ret = false;
	if (Lexico.get_token(c) == '+')
	{
		c++;
		if (termino() == true)
		{
			of << "ADD\n";
			if (mastermino() == true)
				ret = true;
		}
		else
			simbolos_juntos(c);
		
	}
	else if (Lexico.get_token(c) == '-')
	{
		c++;
		if (termino() == true)
		{
			of << "NEG\nADD\n";
			if (mastermino() == true)
				ret = true;
			
		}
		else
			simbolos_juntos(c);
	}
	else
		ret = true;	/////////VACIOOO???
	return ret;
}

bool Analizador_Sintactico::termino()
{
	bool ret = false;
	if (factor() == true)
		if (masfactor() == true)
			ret = true;
	return ret;
}

bool Analizador_Sintactico::masfactor()
{
	bool ret = false;
	if (Lexico.get_token(c) == '*')
	{
		c++;
		if (factor() == true)
		{
			of << "MUL\n";
			if (mastermino() == true)
				ret = true;
		}
		else
			simbolos_juntos(c);
	}
	else if(Lexico.get_token(c)=='/')
	{
		c++;
		if (factor() == true)
		{
			of << "DIV\n";
			if (mastermino() == true)
				ret = true;
		}
		else
			simbolos_juntos(c);
	}
	else if (Lexico.get_token(c) == '%')
	{
		c++;
		if (factor() == true)
		{
			of << "MOD\n";
			if (mastermino() == true)
				ret = true;
		}
		else
			simbolos_juntos(c);
	}
	else
		ret = true;	//VACIOO?
	return ret;
}

bool Analizador_Sintactico::factor()
{
	bool ret = false;
	if (Lexico.get_token(c) == '(')
	{
		c++;
		if (expresion() == true)
			if (Lexico.get_token(c) == ')')
			{
				c++;
				ret = true;
			}
			else
				cout << "Debe escribir )" << endl;
	}

	else if (variable() == true)
	{
		of << "PUSHA " << Lexico.get_token(c - 1) << "\n" << "LOAD\n";
		ret = true;
	}
	else if (constante() == true)
	{
		of << "PUSHC " << Lexico.get_token(c - 1) << "\n";
		ret = true;
	}
	return ret;
}

bool Analizador_Sintactico::lectura()
{
	bool ret = false;
	if (Lexico.get_token(c) == 'R')
	{
		c++;
		if (variable() == true)
			ret = true;
		else
			cout << "Despues de R debe ir una variable" << endl;
	}
	return ret;
}

bool Analizador_Sintactico::escritura()
{
	bool ret = false;
	if (Lexico.get_token(c) == 'W')
	{
		c++;
		if (variable() == true)
			ret = true;
		else
			cout << "Despues de W debe ir una variable" << endl;
	}
	return ret;
}

bool Analizador_Sintactico::variable()
{
	bool ret = false;
	if (Lexico.get_token(c)>='a'&&Lexico.get_token(c)<='z')
	{
		c++;
		ret = true;
	}
	return ret;
}

bool Analizador_Sintactico::constante()
{
	bool ret = false;
	if (isdigit(Lexico.get_token(c)))
	{
		c++;
		ret = true;
	}
	return ret;
}

void Analizador_Sintactico::simbolos_juntos(char c)
{
	char aux = Lexico.get_token(c);
	if (aux == '+'|| aux == '-' || aux == '*' || aux == '/' || aux == '%')
		cout << "No pueden haber dos simbolos juntos"<<endl;
}

