#include <stdio.h>
#include "lex.h"
#include <string.h>
#include <ctype.h>
#include "token.h"
#include <stdlib.h>

extern char comp_oprs[];
extern char single_oprs[];
char nextChar;
static int countChar = 0;
static int countLine = 1;

int new_line_flag = 0; 
char* FSAFile = "FSADriver";

int isKeyword(char* identifier)
{
        int i = 0;
        int res;
        while(i < keySize)
        {   
                res = strcmp(identifier, keywords[i]);
                if(res == 0)
                        return 1; //1 means the identifier is keyword
                else
                        i++;
        }   
    
        return 0; //0 means the identifier is not keyword

}
int isOperator(char character)
{
        int i = 0;
        int comp_opr_size = strlen(comp_oprs);
        int single_opr_size = strlen(single_oprs);
    
        while(i < comp_opr_size)
        {   
                if(character == comp_oprs[i])
                        return 2; //means that this is comparison operator
                else
                        i++;
        }   
    
        i = 0;
        while(i < single_opr_size)
        {   
                if(character == comp_oprs[i])
                        return 1; //means that this is single operator
                else
                        i++;
        }   
    
        return 0; //means that this is not comparison or single operator
}


int charToFSAIndex(char character)
{
	if(((character >= 65) && (character <= 90)) || 
		((character >= 97) && (character <= 122)) ||
		character == 95)
		return LETTER;
	else if((character >= 48) && (character <= 57))
		return DIGIT;
	else if(isspace(character) != 0)
	{
		new_line_flag = character == '\n' ? 1 : 0;
		return WHITESPACE;
	}	
	else if(character == EOF)
		return EOFILE;
	else //operator
	{
		int test = isOperator(character);
		if(test == 2)
			return COMP_OPR;
		else if(test == 1)
			return SINGLE_OPR;
		else if(character == 61)
			return ASSIGN_OPR;
		else if(character == 58)
			return COLON_OPR;
		else if(character == 35)
			return HASHTAG;
	}
	
	return NONEXIST; //No character matches with lexical definition

}

struct token * FSADriver(FILE* fp)
{
	nextChar = fgetc(fp);
	countChar++;

	struct token* tok = (struct token*)malloc(sizeof(struct token));
	if(tok == NULL)
	{
                printf("ERROR: %s: failed to allocate memory\n",FSAFile);
                return NULL;
        } 
	tok->tokenIns = (char*)malloc(MAX_LENGTH);
	if(tok->tokenIns == NULL)
        {   
                printf("ERROR: %s: failed to allocate memory\n",FSAFile);
                return NULL;
        }
	memset(tok->tokenIns,'\0',MAX_LENGTH);   
	
	int state = S1;
	int nextState;
	int index = charToFSAIndex(nextChar);
	char* stringIns = (char*)malloc(MAX_LENGTH);
	if(stringIns == NULL)
        {
                printf("ERROR: %s: failed to allocate memory\n",FSAFile);
                return NULL;
        }
	memset(stringIns,'\0',MAX_LENGTH);
	strncat(stringIns, &nextChar, 1);

	if(index == NONEXIST)
	{
		tok->tokenID = NO_CHAR_EXIST;
		strcpy(tok->tokenIns, stringIns);
		tok->line = countLine;
		tok->charN = countChar;
		return tok; 
	}else if(index == WHITESPACE && new_line_flag == 1)
		countLine++; 
	
	while(state < FINAL)
	{
		nextState = FSATable[state][index];
		
		if(nextState < ERROR || nextState > FINAL)
		{
			tok->tokenID = nextState < ERROR ? nextState : nextState - (FINAL + 1);
			strcpy(tok->tokenIns, stringIns);
			tok->line = countLine;
			tok->charN = countChar;
			break;			
		}else{
			state = nextState;
			nextChar = fgetc(fp);
			countChar++;
			index = charToFSAIndex(nextChar);
			if(index == WHITESPACE && new_line_flag == 1)
				countLine++;			

		}	
				

	}
	return tok;
}









