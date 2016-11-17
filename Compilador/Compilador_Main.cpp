// Compilador.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "Analizador_Lexico.h"
#include <vector>

using namespace std;

int main()
{
	//char cadena[100] = { "asd.txt" };
	Analizador_Lexico al;
	if (al.leer_archivo())
		cout << "Cadena bien";
	else
		cout << "Cadena mal";
	//ifstream archivo("asd.txt");
	//char linea[128];
	//int contador = 0;
	//vector<char> aux, aux2;
	//if (archivo.fail())
	//	cerr << "Error al abrir el archivo"<< endl;
	//else
	//	while (!archivo.eof())
	//	{
	//		//linea[contador]=archivo.get();
	//		aux.push_back(archivo.get());
	//		aux2.push_back(archivo.get());
	//		//contador++;
	//	}
	////cout << linea[2] << endl;
	//archivo.close();

	//aux.shrink_to_fit();
	//for (int i = 0; i < aux.size(); i++)
	//{
	//	cout << aux[i];
	//}
	
	system("Pause");
	return 0;
}
