#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <assert.h>
#include "pdp-11.h"
#include "debug.h"


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("usage: pdp-11 <filename>.hex\n");
		return (1);
	}
	loadFile(argv[1]);
	
	memDump(010, 10);
	return (0);
}

