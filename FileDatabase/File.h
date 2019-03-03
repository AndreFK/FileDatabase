#pragma once
#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <fstream>
#include <iostream>

using namespace std;

class File
{
private:
	fstream * file;
	char * dir;
public:
	File(char * dir);
	File();
	bool verify(char * file);
	bool open();
	void close();
	void write(char * data,unsigned int pos,unsigned int tam);
	char * read(unsigned int pos,unsigned int tam);
	bool eof(int pos);
	~File();
};

#endif // !FILE_H_INCLUDED