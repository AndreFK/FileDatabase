#pragma once
#include <string.h>
#include "File.h"

using namespace std;

//60 bytes
struct database {
	char nombre[40];
	int size;
	int bitmap;
	int blockcount;
	int blocksize;
	int primera_tab = -1;
};

struct table {
	char name[40];
	char deleted = '0'; //0 = false ; 1 = true
	int size;
	int block_cols;
	int primera_col = -1;
	int primer_reg = -1;
	int sig_tabla = -1;

};

struct col {
	char name[40];
	char tipo; //i = int ; d = double ; c = char
	int tam; //i = 4, d = 8, c = variable
	int sig_col = -1;
};

struct block {
	char  * data;
	int usado = 0;
	int next = -1;
};

struct reg {
	char * data;
};

database getdb(char * nombre);
table get_tab(string db, string nombre);
table get_tabpos(string db, int pos);
col get_col(string db,table tab, int pos);
int tabpos(string db, string name);

//52 (0 - 29, 30 - 33, 34 - 37, 38 - 41, 42 - 45, 46
