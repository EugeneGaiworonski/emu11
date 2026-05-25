#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <assert.h>
#include "pdp-11.h"

const int MEMSIZE = 0xFFFF;
byte mem[MEMSIZE];

// пишем байт b по адресу adr
void b_write(Address addr, byte b) {
	mem[addr] = b;
};
// читаем байт по адресу adr
byte b_read(Address addr) {
	return mem[addr];
};

// пишем слово w по адресу adr
void w_write(Address addr, word w) {
	if (addr % 2 == 1) return; //адрес слова всегда четный
	mem[addr] = (byte)(w);
	mem[addr + 1] = (byte)(w >> 8);
}

// читаем слово по адресу adr
word w_read(Address addr) {
	if (addr % 2 == 1) return 0xFFFF; //адрес слова всегда четный
	word buf = mem[addr + 1];
	buf = (word)buf << 8;
	buf = (word)(buf + mem[addr]);
	return (buf);
};

void load_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	Address addr;
	word n;
	byte b;

	while (fscanf(file, "%hx %hx", &addr, &n) == 2) {
		for (word i = 0; i < n; i++) {
			if (fscanf(file, "%hhx", &b) != 1) {
				fclose(file);
				return;
			}
			b_write(addr + i, b);
		}
	}
	fclose(file);
}

int main(int argc, char* argv[]) {
	word ww;
	if (argc < 2) {
		printf("usage: pdp-11 <filename>.hex\n");
		return 1;
	}
	load_file(argv[1]);
	w_write(0x0A, 0xABCD);
	ww = w_read(0x0A);
	
	return (0);
}

