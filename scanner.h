#ifndef _SCANNER_H
#define _SCANNER_H

extern char nextChar;
char* stringInstance;

int isOperator(char character);
int charToFSAIndex(char character);
//struct token FSADriver(FILE* fp);
void FSADriver(FILE * fp);

#endif
