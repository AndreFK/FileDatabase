// FileDatabase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int opc = 0;
	cout << ":::File Database:::" << endl;
	cout << "" << endl;
	cout << "1.) Crear Base de Datos" << endl;
	cout << "2.) Borra Base de Datos" << endl;
	cout << "3.) Crear Tablas" << endl;
	cout << "4.) Borrar Tabla" << endl;
	cout << "5.) Insertar datos a Tabla" << endl;
	cout << "6.) Borrar datos de Tabla" << endl;
	cout << "7.) Actualizar datos de Tabla" << endl;
	cout << "8.) Seleccionar datos de Tabla" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << "" << endl;
	system("PAUSE");
    return 0;
}

