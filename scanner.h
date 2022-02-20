#ifndef _SCANNER_H
#define _SCANNER_H

#include "token.h"

extern char nextChar;
char* stringInstance;

enum FSAIndex
{
	LETTER = 0,
	DIGIT,
	COMP_OPR, //operator with "=" only
	ASSIGN_OPR, //operator "="
	SINGLE_OPR, //operator without "=" only
	COLON_OPR, //operator ":"
	WHITESPACE,
	EOFILE
}

//state of the FSA table
enum state
{
	S1 = 0,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	S8,
	S9,
	S10
}

enum finalState
{
	EOFTK = 999,
	IDTK,
	NUMBTK,
	KEYWTK,
	OPRTK
}

enum ErrorState
{
	NO_OPR_EXIST = -3
	NO_ID_STARTWITH,
	ERROR
}
int FSATable[][] = 
{
	{S2,S3,S4,S6,S8,S9,S1,EOFTK},
	{S2,S2,IDTK,IDTK,IDTK,IDTK,IDTK,IDTK},
	{NUMBTK,S3,NUMBTK,NUMBTK,NUMBTK,NUMBTK,NUMBTK,NUMBTK},
	{NO_OPR_EXIST,NO_OPR_EXIST,NO_OPR_EXIST,S5,NO_OPR_EXIST,NO_OPR_EXIST,NO_OPR_EXIST,NO_OPR_EXIST},
	{OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK},
	{OPRTK,OPRTK,OPRTK,S7,OPRTK,OPRTK,OPRTK,OPRTK},
	{OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK},
	{OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK},
	{OPRTK,OPRTK,OPRTK,S10,OPRTK,OPRTK,OPRTK,OPRTK},
	{OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK,OPRTK}
}

char scanFilter(FILE * fp); //filter out white space and comments
int charToFSAIndex(char character);
struct token FSADriver();


#endif
