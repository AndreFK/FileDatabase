#pragma once


const int x = 90;

struct database{
	/*
	char nombre[70];
	int tam;
	int blocksize;
	int primera_tab = -1;
	int cant_blocks;
	*/
};

struct tabla {
	/* Aqui se guarda que tipo de datos guarda la tabla
	char nombre[70];	
	char colcant;
	char deleted;
	int primer_reg = -1;
	int primera_col = -1;
	*/
};

struct col {
	/*
	char nombre[40];
	char dataype[7];
	*/
};

struct  bloc
{
	char data[x];
	int * next;
	//constant cast
};

class Block
{
public:
	//reinterpret_cast
	Block();
	~Block();
};

