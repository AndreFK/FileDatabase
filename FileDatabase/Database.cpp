#include "stdafx.h"
#include "Database.h"
#include <iostream>
#include <string>

Database::Database()
{
}

void Database::createDB(string name, int size, int blocks) {
	database n;
	memcpy(n.nombre, name.c_str(), sizeof(name));
	int bytes = size * 1000000; //1 mega =  1000000 bytes
	int size_blocks = bytes - 70 - blocks;
	int cant_bl = size_blocks / blocks;
	int bitmap = cant_bl / 8;
	n.size = size;
	n.bitmap = bitmap;
	n.blockcount = cant_bl;
	n.blocksize = blocks;
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

void Database::createTab(string db, string name, vector<pair<string, int>>columnas) {
	string filepath = db + ".db";
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	database d = getdb(path);
	table t;
	strcpy(t.name, name.c_str());

	if (!file.verify(path)) {
		cout << "No existe esta base de datos" << endl;
	}
	else {
		if (d.primera_tab == -1) {
			t.deleted = '0';
			t.name;
			t.size = this->sizereg(columnas);
			t.primera_col = -1;
			t.sig_tabla = -1;
			t.block_cols = 2;
			this->file = File(path);
			if (this->file.open()) {
				int pos = sizeof(database) + d.bitmap;
				this->file.write(reinterpret_cast<char*>(&t), pos, sizeof(t));
				d.primera_tab = 0;
				this->file.write(reinterpret_cast<char*>(&d), 0, sizeof(database));
				cout << "Tabla creada" << endl;
				this->file.close();

				File f = File(path);
				this->file.open();
				if (f.open()) {
					for (int i = 0; i < columnas.size(); i++) {
						string colname = columnas[i].first;
						char type;
						if (columnas[i].second == 4) {
							type = 'i';
							this->createCol(d, t, colname, type, 4);
						}
						else if (columnas[i].second == 8) {
							type = 'd';
							this->createCol(d, t, colname, type, 8);
						}
						else {
							type = ' c';
							this->createCol(d, t, colname, type, columnas[i].second);
						}
					}
				}
			}
		}
		else {
			int lastpos = d.primera_tab;
			table temp = get_tabpos(db, lastpos);
			while (temp.sig_tabla > -1) {
				lastpos = temp.sig_tabla;
				temp = get_tabpos(db, temp.sig_tabla);
			}
			temp.sig_tabla = lastpos + 1;
			t.deleted = '0';
			t.size = sizereg(columnas);
			t.sig_tabla = -1;
			t.block_cols = 2 + (lastpos + 1);
			this->file = File(path);
			if (this->file.open()) {
				int posini = sizeof(database) + d.bitmap + (lastpos * sizeof(table));
				this->file.write(reinterpret_cast<char *>(&temp), posini, sizeof(temp));
				posini = sizeof(database) + d.bitmap + ((lastpos + 1) * sizeof(table));
				this->file.write(reinterpret_cast<char*>(&t), posini, sizeof(t));
				this->file.close();
				this->file = File(path);
				this->file.open();
				if (this->file.open()) {
					for (int i = 0; i < columnas.size(); i++) {
						t = get_tab(db, name);
						string colname = columnas[i].first;
						char type;
						if (columnas[i].second == 4) {
							type = 'i';
							this->createCol(d, t, colname, type, 4);
						}
						else if (columnas[i].second == 8) {
							type = 'd';
							this->createCol(d, t, colname, type, 8);
						}
						else {
							type = ' c';
							this->createCol(d, t, colname, type, columnas[i].second);
						}
					}
				}
				this->file.close();
			}
		}
	}
}

void Database::dropTab(string db,string name) {
	string filepath = db + ".db";
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	database d = getdb(path);
	table t = get_tab(db, name);
	if (t.primera_col == -1) {
		cout << "Tabla no existe" << endl;
	}
	else {
		t.deleted = '1';
		this->file = File(path);
		if (this->file.open()) {
			int poscol = sizeof(database) + d.bitmap + (sizeof(table) * tabpos(db, name));
			this->file.write(reinterpret_cast<char*>(&t), poscol, sizeof(table));
			this->file.close();
			cout << t.deleted << endl;
		}
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
			this->file.write(reinterpret_cast<char*>(&tab), poscol, sizeof(table));
			this->file.close();
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

void Database::showtab(string db) {
	string filepath = db + ".db";
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	database d = getdb(path);
	int i = d.primera_tab;
	while (i > -1) {
		table t = get_tabpos(db, i);
		if (t.deleted != '1') {
			cout << t.name << endl;
		}
		i = t.sig_tabla;
	}
}

int Database::sizereg(vector<pair<string, int>>campos) {
	int size = 0;
	for (int i = 0; i < campos.size(); i++) {
		int s = campos[i].second;
		size += s;
	}
	return size;
}

void Database::set_col_size(int size, col c ){
	c.tam = size;
}



Database::~Database()
{
}
