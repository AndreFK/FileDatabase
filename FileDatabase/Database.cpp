#include "stdafx.h"
#include "Database.h"
#include <iostream>
#include <string>

Database::Database()
{
}

void Database::createDB(string name, int size, int block) {
	database n;
	memcpy(n.nombre, name.c_str(), sizeof(name));
	int bytes = size * 1000000; //1 mega =  1000000 bytes
	int size_blocks = bytes - 70 - block;
	int cant_bl = size_blocks / block;
	int bitmap = cant_bl / 8;
	n.size = size;
	n.bitmap = bitmap;
	n.blockcount = cant_bl;
	n.blocksize = block;
	n.primera_tab = -1;
	string filepath = name + ".db";
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	this->file = File(path);
	file.open();
	file.write(reinterpret_cast<char *>(&n), 0, sizeof(n));
	int i = 0;
	char idx = '0';
	while (i < bitmap) {
		file.write(&idx, sizeof(n) + i, 1);
		i++;
	}
	if (file.verify(path)) {
		cout << "DB creada" << endl;
	}
	else {
		cout << "Error" << endl;
	}
	file.close();
}

void Database::dropDB(string name) {
	string filepath = name + ".db";
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	if (!file.verify(path)) {
		cout << "Esta base de datos no existe" << endl;
	}
	if (remove(path) == 0) {
		cout << "Base de datos ha sido borrada" << endl;
	}
	else {
		cout << "No se pudo borrar esta base de datos" << endl;
	}
}

void Database::createCol(database db, table tab, string name, char type, int size) {
	col c;
	strcpy(c.name, name.c_str());
	c.tipo = type;
	c.tam = size;
	string filepath = db.nombre;
	filepath += ".db";
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	if (tab.primera_col == -1) {
		int poscol = sizeof(database) + db.bitmap + (tab.block_cols * db.blocksize);
		this->file = File(path);
		if (this->file.open()) {
			this->file.write(reinterpret_cast<char *>(&c), poscol, sizeof(c));
			tab.primera_col = 0;
			poscol = sizeof(database) + db.bitmap + (sizeof(table) * tabpos(db.nombre, tab.name));
			file.write(reinterpret_cast<char*>(&tab), poscol, sizeof(table));
			file.close();
		}
	}
	else {
		int lastcol = tab.primera_col;
		col temp = get_col(db.nombre, tab, lastcol);
		while (temp.sig_col > -1) {
			lastcol = temp.sig_col;
			temp = get_col(db.nombre, tab, temp.sig_col);
		}
		file = File(path);
		if (this->file.open()) {
			int poscol = sizeof(database) + db.bitmap + (tab.block_cols * db.blocksize) + ((lastcol + 1) * sizeof(col));
			this->file.write(reinterpret_cast<char *>(&temp), poscol, sizeof(col));
			this->file.close();
		}
	}
}

void Database::set_col_size(int size, col c ){
	c.tam = size;
}

Database::~Database()
{
}
