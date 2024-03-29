#include "file_reader.h"
#include <string>
#include <fstream>

using namespace std;

void file_reader::read_in_file(string filename, unsigned char* mem) {
	ifstream prg_file(filename, ios::binary);
	int check = 1;
	int point = 0;
	while (check != EOF) {	// (file_size > memory) ? oops : fine
		mem[point++] = prg_file.get();
		check = prg_file.peek();
	}
	prg_file.close();
}