#include <stdio.h>
#include "lex.h"
#include "helper.h"
#include "scanner.h"
#include <string.h>
#include <ctype.h>
#include "token.h"
#include <stdlib.h>

extern char nextChar;
static int countChar = 1;
static int countLine = 1;

int new_line_flag = 0;
int whitespace_flag = 0; 
int comment_flag = 0;
char* FSAFile = "FSADriver";

void printError(struct token * tok)
{
        int errorCode = ERROR - tok->tokenID - 1;
        printf("\033[1;31m");
        printf("SCANNER ERROR: ");
        printf("\033[1;33m");
        printf("%s ",errorString[errorCode]);
        printf("(string: \'%s\', line: %d, starting char: %d)\n",tok->tokenIns, tok->line, tok->charN);
        printf("\033[0m");
}
void printToken(struct token * tok)
{
        if(tok->tokenID == COMMENT)
                return;
        printf("String: \'%s\',",tok->tokenIns);
        printf(" token type: \'%s\',",tokenNames[tok->tokenID]);
        printf(" line: %d,",tok->line);
        printf(" starting char: %d.\n",tok->charN);

}

int isKeyword(char* identifier)
{
        int i = 0;
        int res;
	if(identifier[0] >= 65 && identifier[0] <= 90)
		return -1; //Error no identifier start with uppercase letter
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
		new_line_flag = (character == '\n') ? 1 : 0;
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
	int startChar = countChar;

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

	while(state < FINAL)
	{
		if(countChar - startChar >= MAX_LENGTH - 1 && comment_flag == 0){
			tok->tokenID = OVERBOUND;
                        strcpy(tok->tokenIns, stringIns);
                        tok->line = countLine;
                        tok->charN = startChar;
			break;	
		}
		nextState = FSATable[state][index];
		
		if(nextState < ERROR || nextState > FINAL)
		{
			tok->tokenID = nextState < ERROR ? nextState : nextState - (FINAL + 1);
			if(stringIns[0] == '\0')
				strncat(tok->tokenIns, &nextChar, 1);
			else
				strcpy(tok->tokenIns, stringIns);
			tok->line = countLine;
			tok->charN = startChar;
			
			if(tok->tokenID == IDENT)
			{
				int test = isKeyword(tok->tokenIns);
				switch(test){
					case 1: tok->tokenID = KEYWORD;
						break;
					case -1: tok->tokenID = NO_ID_STARTWITH; 
						break;
				}
			}else if(tok->tokenID == COMMENT)
				comment_flag = 0;
					
			break;			
		}else{
			if(nextState == S12)
				comment_flag = 1;
			if(index == WHITESPACE && new_line_flag == 1)
                        {
                                countLine++;
                                countChar = comment_flag == 0 ? 1 : 0;
				startChar = 1;
                        }
			if(index != WHITESPACE && comment_flag == 0)
				strncat(stringIns, &nextChar, 1);
			state = nextState;
			nextChar = fgetc(fp);
			countChar++;
			index = charToFSAIndex(nextChar);
		}	
				

	}
	free(stringIns);
	return tok;
}









