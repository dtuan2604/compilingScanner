#include "token.h"
#include <string.h>

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
