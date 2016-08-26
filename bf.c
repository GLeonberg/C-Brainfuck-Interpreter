#include <stdio.h>
#define MAXSIZE 30000

void interpret(char program[MAXSIZE], int len);

/*--------------------------------------------
--------------------------------------------*/

int main(int argc, char* argv[])
{	
	FILE* input = NULL;
	char program[MAXSIZE] = {'\0'}, val = '\0';
	int fileLen = 0;
	
	/* commence argument processing */
	if(strcmp(argv[1], "help") == 0) 
	{
		printf("Enter the file name as a command line argument\n\n");
		return 0;
	}
	
	/* open file for reading */
	if( ( input = fopen(argv[1], "r") ) == '\0') 
	{
    		perror("Error");
    		printf("\n");
    		return 0;
    	}
	
	/* store contents of file */
	while (((val = fgetc(input)) != EOF) && (fileLen < MAXSIZE)) 
	{
		program[fileLen] = val;
		fileLen++;
	}
	
	fclose(input);
	interpret(program, fileLen);
	printf("\n\n\n");
	return 0;
} 

/*--------------------------------------------
--------------------------------------------*/

void interpret(char program[MAXSIZE], int len)
{	
	char tape[MAXSIZE] = {'\0'};
	int ipointer = 0, dpointer = 0, numLoops = 0;
	
	for(ipointer = 0; ipointer < len; ipointer++)
	{
		switch(program[ipointer])
		{
			case '<':
				if(dpointer > 0) dpointer--;
				else dpointer = 0;
				break;
			
			case '>':
				if(dpointer < MAXSIZE) dpointer++;
				else dpointer = 0;
				break;
				
			case '+':
				if(tape[dpointer] < 255) tape[dpointer] += 1;
				else tape[dpointer] = 0;
				break;
				
			case '-':
				if(tape[dpointer] > 0) tape[dpointer] -= 1;
				else tape[dpointer] = 0;
				break;
			
			case '.':
				printf("%c", tape[dpointer]);
				break;
				
			case ',':
				printf("\n");
				scanf("%c", &tape[dpointer]);
				printf("\n");
				break;
			
			case '[':
			
				numLoops = 1;
				
				/* if data at pointer is 0, skip to matching closing bracket */
      				if (tape[dpointer] == 0) 
      				{
        				do
        				{
         					ipointer++;
          				
          					if(program[ipointer] == '[')
          					{ numLoops++; }
          				
          					else 
          					{
          						if(program[ipointer] == ']')
          						{ numLoops--; }
          					}
       			 		} 
     			 	
       			 		while(numLoops != 0);
      				}
				
				break;
				
			case ']':
			
				/* skip to matching opening bracket */
				numLoops = 0;
				
      				do 
      				{
        				if(program[ipointer] == '[')
        				{ numLoops++; }
       				
       					else
       					{
       						if(program[ipointer] == ']')
       						{ numLoops--; }
       					}
        			
        				ipointer--;
      				} 
      			
      				while(numLoops != 0);
				
				break;
		}
	}
}
