#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "pdp-11.h"

#define MEMSIZE 0xFFFF

byte mem[MEMSIZE];
word reg[8];

// пишем байт b по адресу adr
void byteWrite(address addr, byte b) {
	mem[addr] = b;
};

// читаем байт по адресу adr
byte byteRead(address addr) {
	return(mem[addr]);
};

// пишем слово w по адресу adr
void wordWrite(address addr, word w) {
	assert((addr & 1) == 0);
	//if (addr % 2 == 1) return; //адрес слова всегда четный
	mem[addr] = (byte)(w);
	mem[addr + 1] = (byte)(w >> 8);
}

// читаем слово по адресу adr
word wordRead(address addr) {
	assert((addr & 1) == 0);
	//if (addr % 2 == 1) return 0xFFFF; //адрес слова всегда четный
	word buf = mem[addr + 1];
	buf = (word)buf << 8;
	buf = (word)(buf + mem[addr]);
	return (buf);
};
