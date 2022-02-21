#ifndef _SCANNER_H
#define _SCANNER_H

#define NUM_ERRORS 

char* errorString[] = {"This character is not allowed in the lexical definition.",
			"There is no such operator existed in the lexical definition.",
			"Identifier can not start with uppercase letter."};

int isKeyword(char* identifier);
int isOperator(char character);
int charToFSAIndex(char character);
struct token * FSADriver(FILE* fp);

#endif
