#pragma once
#ifndef PDP11_H
#define PDP11_H

typedef unsigned char byte;
typedef unsigned short word;
typedef word address;

void byteWrite(address addr, byte b); // пишем байт b по адресу adr
byte byteRead(address addr); // читаем байт по адресу adr
void wordWrite(address addr, word w);	// пишем слово w по адресу adr, адрес слова всегда четный
word wordRead(address addr); // читаем слово по адресу adr, адрес слова всегда четный

#endif // !PDP11_H
