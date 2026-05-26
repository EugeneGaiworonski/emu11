#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include "debug.h"
#include "pdp-11.h"

LogLevel loglevel = LogLevel::ERROR;

void testMem(){ 
  address addr;
  byte byte0, byte1, byteres;
  word word0, wordres;

  // read byte/write byte
  fprintf(stderr, "Write and read a byte at an even address\n");
  addr = 0;
  byte0 = 0xAA;
  byteWrite(addr, byte0);
  byteres = byteRead(addr);
  fprintf(stderr, "addr=%06o byte0=%hhX byteres=%hhX\n", addr, byte0, byteres);
  assert(byte0 == byteres);
  
  fprintf(stderr, "Write and read a byte at an odd address\n");
  addr = 1;
  byte0 = 0xBB;
  byteWrite(addr, byte0);
  byteres = byteRead(addr);
  fprintf(stderr, "addr=%06o byte0=%hhX byteres=%hhX\n", addr, byte0, byteres);
  assert(byte0 == byteres);

  // read word/write word
  fprintf(stderr, "Write and read a word at an even address\n");
  addr = 2;       
  word0 = 0xFACE;
  wordWrite(addr, word0);
  wordres = wordRead(addr);
  fprintf(stderr, "addr=%06o word0=%04X wordres=%04X\n", addr, word0, wordres);
  assert(word0 == wordres);

  // write 2 bytes/read 1 word
  fprintf(stderr, "Write 2 bytes, read a word at an even address\n");
  addr = 4;        
  word0 = 0xCAFE;
  // little-endian
  byte0 = 0xFE;
  byte1 = 0xCA;
  byteWrite(addr, byte0);
  byteWrite(addr + 1, byte1);
  wordres = wordRead(addr);
  fprintf(stderr, "addr=%06o byte1=%02hhX byte0=%02hhX wordres=%04X\n", addr, byte1, byte0, wordres);
  assert(word0 == wordres);
}

void loadFile(const char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    perror(filename);
    exit(errno);
  };
  address addr;
  word n;
  byte b;

  while (fscanf(file, "%hx %hx", &addr, &n) == 2) {
    for (word i = 0; i < n; i++) {
      if (fscanf(file, "%hhx", &b) != 1) {
        fclose(file);
        return;
      }
      byteWrite(addr + i, b);
    }
  }
  fclose(file);
}

void loadData() {
  address addr;
  word n;
  byte b;

  while (scanf("%hx %hx", &addr, &n) == 2) {
    for (word i = 0; i < n; i++) {
      if (scanf("%hhx", &b) != 1) {
        return;
      }
      byteWrite(addr + i, b);
    }
  }
}

void memDump(address addr, int size) {
  int idx;
  for (idx = 0; idx < size; idx++) {
    printf("%06o: %06o %04X\n", addr, wordRead(addr), wordRead(addr));
    addr++;
    addr++;
  }
}

void membDump(address addr, int size) {
  int idx;
  for (idx = 0; idx < size; idx++) {
    printf("%06o: %03o %02X\n", addr, byteRead(addr), byteRead(addr));
    addr++;
  }
}

LogLevel set_log_level(LogLevel level) {
  LogLevel oldlevel = loglevel;
  loglevel = level;
  return (oldlevel);
}

void trace(LogLevel level, const char* message) {
  if (level >= loglevel) printf("%s", message);
}