#include <stdio.h>
#include "testScanner.h"

char* testScanner = "testScanner";

int isfileEmpty(FILE * fp, char* caller)
{
        if(fp != NULL)
        {
                fseek(fp, 0, SEEK_END);//set the pointer to the end of the file
                int test = ftell(fp);

                if(test == 0)
                {
                        fprintf(stderr, "ERROR: %s: Input is empty\n", caller);
                        return 1;
                }


        }
        else
        {
                fprintf(stderr, "ERROR: %s: Cannot open file\n", caller);
                return 1;
        }

        fseek(fp, 0, SEEK_SET); //reset the pointer back to the beginning of the file

        return 0;
}

int runtestScanner(char* fileName)
{
	FILE * fp = fopen(fileName, "r");
	if(isfileEmpty(fp,testScanner) == 1)
		return 0;

	//Call scanner here
	printf("Hello from testScanner");

	fclose(fp);
	return 1;
}
