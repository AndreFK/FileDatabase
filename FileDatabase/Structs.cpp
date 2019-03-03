#include "stdafx.h"
#include "Structs.h"

database getdb(char  * name) {
	File f(name);
	database n;
	if (f.open()) {
		memcpy(n.nombre, f.read(0, sizeof(n.nombre)), sizeof(n.nombre));
		memcpy(&n.size, f.read(50, sizeof(n.size)), sizeof(n.size));
		memcpy(&n.bitmap, f.read(54, sizeof(n.bitmap)), sizeof(n.bitmap));
		memcpy(&n.blocksize, f.read(58, sizeof(n.blocksize)), sizeof(n.blocksize));
		memcpy(&n.blockcount, f.read(62, sizeof(n.blockcount)), sizeof(n.blockcount));
		memcpy(&n.primera_tab, f.read(66, sizeof(n.primera_tab)), sizeof(n.primera_tab));
		f.close();
	}
	//66 (0 - 49, 50 - 53, 54 - 57, 58 - 61, 62 - 65, 66 - 70)
	return n;
}

col get_col(string db, table tab, int pos) {
	string dbname = db + ".db";
	string filepath = dbname;
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	File f(path);
	col c;
	if(f.open()){
		database db = getdb(path);
		int skip = sizeof(database) + db.bitmap + (tab.block_cols * db.blocksize) + (pos * sizeof(col));
		memcpy(c.name, f.read(skip, sizeof(c.name)), sizeof(c.name));
		skip += sizeof(c.name) + 1;
		memcpy(&c.tipo, f.read(skip, sizeof(c.tipo)), sizeof(c.tipo));
		skip += sizeof(c.tipo);
		memcpy(&c.tam, f.read(skip, sizeof(c.tam)), sizeof(c.tam));
		skip += sizeof(c.tam);
		memcpy(&c.sig_col, f.read(skip, sizeof(c.sig_col)), sizeof(c.sig_col));
		skip += sizeof(c.sig_col);
		memcpy(&c.tam, f.read(skip, sizeof(c.tam)), sizeof(c.tam));
	}
	f.close();
	return c;
}

table get_tabpos(string db, int pos) {
	string dbname = db + ".db";
	string filepath =  dbname;
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	File f(path);
	table n;
	if (f.open()) {
		database d = getdb(path);
		int postab = sizeof(database) + d.bitmap + (pos * sizeof(table));
		memcpy(&n.deleted, f.read(postab, sizeof(n.deleted)), sizeof(n.deleted));
		postab += sizeof(n.deleted);
		memcpy(&n.name, f.read(postab, sizeof(n.name)), sizeof(n.name));
		postab += sizeof(n.name);
		memcpy(&n.size, f.read(postab, sizeof(n.size)), sizeof(n.size));
		postab += sizeof(n.size);
		memcpy(&n.block_cols, f.read(postab, sizeof(n.block_cols)), sizeof(n.block_cols));
		postab += sizeof(n.block_cols);
		memcpy(&n.primera_col, f.read(postab, sizeof(n.primera_col)), sizeof(n.primera_col));
		postab += sizeof(n.primera_col);
		memcpy(&n.primer_reg, f.read(postab, sizeof(n.primer_reg)), sizeof(n.primer_reg));
		postab += sizeof(n.primer_reg);
		memcpy(&n.sig_tabla, f.read(postab, sizeof(n.sig_tabla)), sizeof(n.sig_tabla));
		f.close();
	}
	return n;
}

table get_tab(string db, string name) {
	string dbname = name + ".db";
	string filepath = "databases/" + dbname;
	char path[sizeof(filepath)];
	strcpy(path, filepath.c_str());
	File f(path);
	table n; 
	if (f.open()) {
		database d = getdb(path);
		int postab = sizeof(database) + d.bitmap;
		if (d.primera_tab != -1) {
			int pos = d.primera_tab;
			bool eof = f.eof(postab);
			while (!eof && postab < (sizeof(database) + d.bitmap + (2 * d.blocksize))) {
				table t = get_tabpos(db, pos);
				if (t.name == name && t.deleted != 1) {
					return t;
				}
				pos++;
				postab += sizeof(table);
				eof = f.eof(postab);
			}
		}
	}
	f.close();
	return n;
}

int tabpos(string db, string name) {
	int x = -1;
	int y = 0;
	table t;
	do {
		t = get_tabpos(db, y);
		if (t.name == name && t.deleted != 1) {
			return y;
		}
		y++;
	} while (t.sig_tabla != -1);
}

