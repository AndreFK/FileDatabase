// FileDatabase.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Database.h"
#include <vector>

using namespace std;

int main()
{
	Database db;
	vector<pair<string, int>> cols;

	string dbname;
	string tabname;
	string colname;
	int size;
	int mascols = 1;

	string file = dbname + ".db";

	File f;

	//db.createDB("z", 1, 8000);
	//db.createTab("z", "Test2", cols);
	//db.createTab("z", "Test1", cols);
	//db.dropTab("z", "Test2");
	//db.dropTab("z", "Test");
	//system("PAUSE");
	//db.showtab("z");

	

	int opc = 0;
	cout << ":::File Database:::" << endl;
	cout << "" << endl;
	cout << "1.) Crear Base de Datos" << endl;
	cout << "2.) Borrar Base de Datos" << endl;
	cout << "3.) Crear Tablas" << endl;
	cout << "4.) Borrar Tabla" << endl;
	cout << "5.) Cambiar de base de datos" << endl;
	cout << "6.) Mostrar Tablas" << endl;
	cout << "7.) Insertar datos a Tabla" << endl;
	cout << "8.) Borrar datos de Tabla" << endl;
	cout << "9.) Actualizar datos de Tabla" << endl;
	cout << "10.) Seleccionar datos de Tabla" << endl;
	cout << "Opcion: ";
	cin >> opc;
	cout << "" << endl;
	switch (opc) {
	case 1:
		cout << "Nombre de la base de datos: ";
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
		cout << "" << endl;
		break;
	case 2:
		cout << "Nombre de la base de datos: ";
		cin >> dbname;
		db.dropDB(dbname);
		cout << "" << endl;
		break;
	case 3:
		cout << "Nombre de la Tabla: ";
		cin >> tabname;
		while (mascols == 1) {
			cout << "Nombre de la columna: ";
			cin >> colname;
			cout << "Tamaño de dato: ";
			cin >> size;
			cols.push_back(make_pair(colname, size));
			cout << "Otra columna? 1 = si 0 = no" << endl;
			cin >> mascols;
		}
		mascols = 0;
		db.createTab(dbname, tabname, cols);
		cout << "" << endl;
		break;
	case 4:
		cout << "Nombre de la tabla: ";
		cin >> tabname;
		db.dropTab(dbname, tabname);
		cout << "" << endl;
		break;
	case 5:
		cout << "Nombre de base de datos: ";
		cin >> dbname;

		char path[sizeof(file)];
		strcpy(path, file.c_str());

		if (f.verify(path)) {
			cout << "Exito" << endl;
		}
		else {
			cout << "Base de datos no encontrada" << endl;
		}
		break;
	case 6:
		cout << "Nombre de base de datos: ";
		cin >> dbname;
		db.showtab(dbname);
		cout << "" << endl;
		break;
	}
	system("PAUSE");
    return 0;
}

