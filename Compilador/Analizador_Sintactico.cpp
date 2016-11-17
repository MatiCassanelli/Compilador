#include "stdafx.h"
#include "Analizador_Sintactico.h"


Analizador_Sintactico::Analizador_Sintactico()
{
	c = 0;
	programa();
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
			c++;
			if (bloque() == true)
				if (Lexico.get_token(c) == '}')
					ret = true;
		}
	}
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

bool Analizador_Sintactico::otrasentencia()//revisar
{
	bool ret = false;
	int g;
	if (Lexico.get_token(c) == ';')
	{
		c++;
		g = c;	//guardo c para usarlo en el camino de (;) en caso de ser necesario
		if (sentencia() == true)	//; sentencia otrasentencia
			if (otrasentencia() == true)
				ret = true;
		if (ret == false)	// ;
		{
			c = g;
			ret = true;
		}
	}
	return ret;
}

bool Analizador_Sintactico::sentencia()
{
	bool ret = false;
	if (lectura() == true)
		ret = true;
	else if(escritura() == true)
		ret = true;
	else if(asignacion() == true)
		ret = true;
	return ret;
}

bool Analizador_Sintactico::asignacion()
{
	bool ret = false;
	if(variable()==true)
		if (Lexico.get_token(c) == '=')
		{
			c++;
			if (expresion() == true)
				ret = true;
		}
	return ret;
}

bool Analizador_Sintactico::expresion()
{
	bool ret = false;
	if (termino() == true)
		if (mastermino() == true)
			ret = true;
	return ret;
}

bool Analizador_Sintactico::mastermino()
{
	bool ret = false;
	if (Lexico.get_token(c) == '+')
	{
		c++;
		if (termino() == true)
			if (mastermino() == true)
				ret = true;
	}
	else if (Lexico.get_token(c) == '-')
	{
		c++;
		if (termino() == true)
			if (mastermino() == true)
				ret = true;
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
			if (mastermino() == true)
				ret = true;
	}
	else if(Lexico.get_token(c)=='/')
	{
		c++;
		if (factor() == true)
			if (mastermino() == true)
				ret = true;
	}
	else if (Lexico.get_token(c) == '%')
	{
		c++;
		if (factor() == true)
			if (mastermino() == true)
				ret = true;
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
	}
	else if (variable() == true)
		ret = true;
	else if (constante() == true)
		ret = true;
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
	}
	return ret;
}

bool Analizador_Sintactico::variable()
{
	bool ret = false;
	if (isalpha(Lexico.get_token(c)) == true)
	{
		c++;
		ret = true;
	}
	return ret;
}

bool Analizador_Sintactico::constante()
{
	bool ret = false;
	if (isdigit(Lexico.get_token(c)) == true)
	{
		c++;
		ret = true;
	}
	return ret;
}

