#pragma once
#ifndef DEBUG_H
#define DEBUG_H
#include "pdp-11.h"

enum LogLevel {
	ERROR,
	INFO,
	TRACE,
	DEBUG 
};

void testMem();
void loadData();
void loadFile(const char* filename);
void memDump(address addr, int size);
void membDump(address addr, int size);
#endif // !DEBUG_H

