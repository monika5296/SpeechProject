#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <errno.h> 
#include <unistd.h>
#include <curses.h>
#include <ncurses.h>
#include <readline/readline.h>
#include <readline/history.h>


#define MAX 		10000
#define clearScreen() 	printf("\033[H\033[J")  		//THIS WILL CLEAR THE CONTENT OF TERMINAL

char in[MAX] = "" ,*s = NULL , *words[100],*newWords[100] ;
int i = 0, flag = 0,flag1 = 0;;
pid_t pid ;

void compareString(char [], char *);				//THIS WILL COMPARE THE INPUT STRING WITH THE COMMANDS
void shellStart();						//THIS WILL CLEAR THE TERMINAL AND PRINT THE WELCOME NOTE.
int readInput();						//THIS FUNCTION WILL READ THE INPUT FROM KEYBOARD
void displayDirectory(); 					//THIS WILL DISPLAY CURRENT DIRECTORY


void shellStart() 
{ 
	clearScreen(); 						//THIS WILL CLEAR THE CONTENT OF TERMINAL
	printf("\n\n******************************************"); 
	printf("\n\n\tWelcome to your shell\t"); 
	printf("\n\n******************************************"); 
	printf("\n"); 
}

int readInput()
{
	char str[MAX] , tempString[MAX] ; 
	char * token ; 
	s = readline(in);
	strcpy(str,s);
	strcpy(tempString,str);
	char * rest = tempString;
	i = 0 ;

	//THIS WILL CHECK WHETHER INPUT STRING IS NULL OR NOT, IF NULL THEN IT WILL GO BACK TO MAIN PROGRAM WITHOUT COMPARING 
	if( strcmp(str,"") == 0 )
	{
		flag = 0;
	}
	else
	{

		//THIS WILL ADD THE COMMANDS INTO HISTORY
		add_history(s);

		//THIS LOOP WILL FIND THE WORDS FROM THE INPUTN STRING
		while ((token = strtok_r(rest, " \n", &rest))) 
		{
			words[i] = token;
			i++; 
		}

		//CALL TO COMPARE STRING FUNCTION.
		compareString(str,words[0]);
	} 
}

void displayDirectory() 
{ 
	char myPwd[1000] , hostname[1024];

	//THIS WILL GET CURRENT WORKING DIRECTORY
	getcwd(myPwd,sizeof(myPwd));

	//THIS WILL GET HOSTNAME
    	gethostname(hostname, 1024);

	//sprintf(in,"\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m$ ", getenv("USER"),hostname,myPwd); 	//EXACTLY SAME AS TERMINAL	
	sprintf(in,"\033[1;36m%s@%s\033[0m:\033[1;33m%s\033[0m$ ", getenv("USER"),hostname,myPwd);   	//ANOTHER COLORS

	//sprintf(in,"%s@%s:~%s$: ", getenv("USER"),hostname,myPwd);					//WITHOUT ANY COLORS
	
} 

void compareString(char str1[MAX], char *word1)
{
	if( strcmp(word1,"pwd") == 0 )
	{	

		//THIS WILL CREATE A CHILD PROCESS USING FORK AND THEN RUN ./MYPWD FILE
		pid = fork();
		if (pid == -1)
		{  

		      // IF PID=-1 THEN IT'S AN ERROR 
		      printf("can't fork, error occured\n"); 
		      exit(EXIT_FAILURE); 
		} 

		//CHILD PROCESS WILL EXECUTE THE ./MYPWD
		if( pid == 0 ) 
		{
			execv("./mypwd",words); 
			exit(0);
		}
	}

	else if(strcmp(word1,"mv") == 0) 
	{	

		//THIS WILL CREATE A CHILD PROCESS USING FORK AND THEN RUN ./MYMOVE FILE
		pid = fork();
		if (pid == -1)
		{  

		      // IF PID=-1 THEN IT'S AN ERROR 
		      printf("can't fork, error occured\n"); 
		      exit(EXIT_FAILURE); 
		} 
		//CHILD PROCESS WILL EXECUTE THE ./MYMOVE	
		if( pid == 0 )
		{
			execv("./mymv",words); 
			exit(0);
		}
	}

	else if(strcmp(word1,"grep") == 0 ) 
	{
		for(int z=0;z<100;z++)
			newWords[z]=NULL;
		char s1[1000],s2[1000],s3[1000];
		int a=0,b=0,c=0;
		int flag1 = 0;
		char * token1, * token3 ;
		for(int i=0;i<strlen(str1);i++)
		{
			if(str1[i] == '"')
				flag1++;
			else
			{
				if(flag1 == 0)
				{
					s1[a] = str1[i];
					a++;
				}
				else if(flag1 == 1)
				{
					s2[b] = str1[i];
					b++;
				}
				else
				{
					s3[c] = str1[i];
					c++;
				}
			}	
		}
		if(flag1 == 2)
			s3[c] ='\0';
		s1[a]=s2[b]='\0';
		char *rest1 = s1;
		char *rest3 = s3;
		int i = 0;
		while ((token1 = strtok_r(rest1, " \n", &rest1))) 
		{
			newWords[i] = token1;
			i++; 
		}
		if(flag1 >= 1)
		{		
			newWords[i] = (char*)s2;
			i++;
		}
		if(flag1 == 2)
		{	
			int start_index=0;
			for(int z=0;z<strlen(s3);z++)
			{
				if(s3[z] != ' ')
				{
					start_index = z;
					break;
				}
			}
			char *rest3 =(char *)&s3[start_index];
			while ((token3 = strtok_r(rest3, " \n", &rest3))) 
			{
				newWords[i] = token3;
				i++; 
			}
		}
		//THIS WILL CREATE A CHILD PROCESS USING FORK AND THEN RUN ./MYGREP FILE
		pid = fork();
		if (pid == -1)
		{  

		      // IF PID=-1 THEN IT'S AN ERROR 
		      printf("can't fork, error occured\n"); 
		      exit(EXIT_FAILURE); 
		} 
		//CHILD PROCESS WILL EXECUTE THE ./MYGREP
		if( pid == 0 )
		{
			execv("./mygrep",newWords); 
			exit(0);
		}
	}

	else if(strcmp(words[0],"split") == 0) 
	{

		//THIS WILL CREATE A CHILD PROCESS USING FORK AND THEN RUN ./MYSPLIT FILE
		pid = fork();

		//CHILD PROCESS WILL EXECUTE THE ./MYSPLIT
		if( pid == 0 )
		{
			execv("./mysplit",words); 
			exit(0);
		}
	} 
	else if(strcmp(word1,"help") == 0 ) 
	{

		//THIS WILL CREATE A CHILD PROCESS USING FORK AND THEN RUN ./MYHELP FILE
		pid = fork();

		//CHILD PROCESS WILL EXECUTE THE ./MYHELP
		if( pid == 0)
		{
			execv("./myhelp",NULL); 
			exit(0);
		}
	} 
	else if(strcmp(word1,"clear") == 0 ) 
	{
		flag = 0;

		//THIS WILL CLEAR THE TERMINAL SCREEN
		//clearScreen();
		shellStart();		
	}
	else if(strcmp(word1,"exit") == 0 ) 
	{
		flag = 0;
		printf("I don't have meaningful msg\n");
		
		//THIS WILL EXIT THE PROGRAM
		exit(0);
		
	}
	else
	{
		flag = 0;

		//THIS THE INPUT STRING DOESN'T MATCH WITH ANY COMMAND THEN IT WILL PRINT FOLLOWING
		printf("%s: command not found\n",str1);
	}
}

int main()
{
	int ret = 1; 
	int status;
	shellStart();

	//THIS WILL INITIALIZE THE HISTORY
	using_history();  
	while(1)
	{

			//PARENT WILL WAIT UNTIL CHILD PROCESS COMPLETES IT'S EXECUTION
			for(int z=0;z<100;z++)
				words[z]=NULL;
			if (waitpid(pid, &status, 0) > 0 || flag ==0) 
			{
				flag =1;
				displayDirectory(); 		
				readInput();
				
			} 	
	}
	return 0;
}
