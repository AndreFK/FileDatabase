#include "stdafx.h"
#include "File.h"


File::File()
{
	this->file = nullptr;
	this->dir = nullptr;
}

File::File(char * dir) {
	this->dir = dir;
	file = new fstream();
}

bool File::verify(char * file) {
	ifstream f(file);
	return f.good();
}

bool File::open() {
	if (this->file == nullptr) {
		return false;
	}
	else {
		if(!verify(this->dir)) {
			this->file->open(dir, ios::trunc | ios::in | ios::out | ios::binary);
			if (!this->file->good()) {
				return false;
			}
		}
		else {
			this->file->open(dir, fstream::in | fstream::out | fstream::binary);
			if (!this->file->good()) {
				return false;
			}
		}
		return true;
	}
}

void File::close() {
	if (this->file == nullptr) {
		cout << "Archivo que trata de cerrar no existe" << endl;
	}
	else {
		if (this->file->is_open()) {
			this->file->close();
		}
		else {
			cout << "Este archivo no está abierto" << endl;
		}
	}
}

void File::write(char * data,unsigned int pos,unsigned int tam) {
	this->file->seekp(pos, ios::beg);
	this->file->write(data, tam);
}

char * File::read(unsigned int pos,unsigned int tam) {
	char * data = new char[tam];
	this->file->seekg(pos);
	this->file->read(data, tam);
	return data;
}

bool File::eof(int pos) {
	this->file->seekg(0, ios::end);
	int end = file->tellg();
	if (pos < end) {
		return false;
	}
	else {
		return true;
	}
}

File::~File()
{
}
