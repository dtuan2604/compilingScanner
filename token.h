#ifndef _TOKEN_H
#define _TOKEN_H

#define keySize 17

char* keywords[] = {"start", "stop", "repeat","until","whole","label","quit","listen",
		    "yell","main","portal","if","then","pick","declare","assign","proc"};

//ASCII code for operators
char comp_oprs[] = {60,62,33};
char single_oprs[] = {37,40,41,42,43,44,45,46,47,59,91,93,123,125};

//Token ID used to print to the output
enum tokenID
{
	IDENT = 0,
	NUMBER,
	KEYWORD,
	OPERATOR,
	EndOfFile,
	COMMENT
};

char* tokenNames[] = {"Identifier","Number","Keyword","Operator","EOF"};

//A token will include token id, instance of that token under string value
//along with line number and the starting position of that token on the line
struct token
{
	int tokenID;
	char* tokenIns;
	int line;
	int charN;
};

int isKeyword(char* identifier);

#endif
