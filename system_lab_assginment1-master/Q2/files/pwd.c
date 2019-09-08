#include <unistd.h>
#include <stdio.h>
#include<string.h>
#define SIZE 1024
#define COMMAND_SIZE 256

//UTILITY FUNCTION FOR PRINTING HELP
void help()
{
	FILE *fp = fopen("pwdHelp.txt","r"); 
	if (fp == NULL)
		return;

	char c = fgetc(fp);
	printf("%c", c); 

	//WRITE THE HELP FILE
	while(!feof(fp))
    	{
       		char c = fgetc(fp);
        	if(c != EOF)
        		printf("%c", c); 
    	}  
    	fclose(fp); 
}

//MAIN PROGRAM
int main( int argc, char *argv[] )  {

	//CHECK FOR APPROPRIATE NUMBER OF ARGUMENTS
	if( argc == 2 ) {
		char command[COMMAND_SIZE];
		strcpy(command,argv[1]);
     		if(strcmp(command,"--help")==0)
				help();//CALLING HELP
		else
				printf("invalid command\n");
   	}
   	else if( argc > 2 ) {
      		printf("Too many arguments supplied.\n");
   	}
   	else {
		char cwd[SIZE];
	    	getcwd(cwd, sizeof(cwd));//GETTING CURRENT WORKING DIRECTORY
	    	printf("%s\n",cwd);
   	}
}
