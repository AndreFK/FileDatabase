// FileDatabase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Database.h"

using namespace std;

int main()
{
	Database db;
	db.createDB("Yay", 4, 8000);
	db.createDB("Si", 4, 600);
	db.createDB("Funciona", 4, 3000);
	
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
	switch (opc) {
	case 1:
		cout << "Nombre de la base de datos: ";
		string dbname;
		cin >> dbname;
		cout << "" << endl;
		cout << "Tamano de la Base de Datos (en megas): ";
		int dbsize;
		cin >> dbsize;
		cout << "" << endl;
		cout << "Tamano de los bloques: ";
		int blocksize;
		cin >> blocksize;
		cout << "" << endl;
		db.createDB(dbname, dbsize, blocksize);
		cout << "Base de datos creada" << endl;
		break;
	}
	system("PAUSE");
    return 0;
}

