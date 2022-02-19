#ifndef _TOKEN_H
#define _TOKEN_H

char* keywords[] = {"start", "stop", "repeat","until","whole","label","quit","listen",
		    "yell","main","portal","if","then","pick","declare","assign","proc"};

enum tokenID
{
	IDENT = 0,
	NUM,
	KW,
	OPR
}

char* tokenNames[] = {"Identifier","Number","Keyword","Operator"};

//A token will include token id, instance of that token under string value
//along with line number and the position of that token on the line
struct token
{
	int tokenID;
	char* tokenIns;
	int line;
	int charN;

};



#endif
