#pragma once
#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "File.h"
#include "Structs.h"
#include <string.h>
#include <vector>

using namespace std;

class Database
{
public:
	Database();
	void createDB(string name, int dbsize, int blocksize);
	void dropDB(string name);
	void createTab(string db, string name, vector<pair<string,int>>columnas);
	void dropTab(string db, string name);
	void createCol(database db, table tab, string name, char type, int size);
	int sizereg(vector<pair<string, int>> cols);
	void showtab(string db);
	void set_col_size(int size, col c);
	File file;
	string dbname;
	~Database();
};

#endif // !DATABASE_H_INCLUDED
