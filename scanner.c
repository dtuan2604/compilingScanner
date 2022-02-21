#include <stdio.h>
#include "lex.h"
#include "scanner.h"
#include <string.h>
#include <ctype.h>

extern char comp_oprs[];
extern char single_oprs[];

int new_line_flag = 0; 

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
		if(character == '\n')
			new_line_flag = 1;
		else
			new_line_flag = 0;
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
	
	return -1; //No character matches with lexical definition

}

void FSADriver(FILE* fp)
{
	int test = charToFSAIndex(nextChar);
	switch(test)
	{
		case LETTER: printf("%c is a letter\n",nextChar);
				break;
		case DIGIT: printf("%c is a digit\n",nextChar);break;
		case WHITESPACE: if(new_line_flag != 1) printf("skip white space now\n");
				else printf("Next line\n"); break;
		case COMP_OPR:
		case SINGLE_OPR:
		case ASSIGN_OPR:
		case COLON_OPR: printf("%c is a operator\n",nextChar);break;
		case HASHTAG: printf("%c is a hashtag\n", nextChar);break;
		case EOFILE: printf("End of file\n");break;
		default: printf("%c is not allowed!\n");
	}
	return;
}
