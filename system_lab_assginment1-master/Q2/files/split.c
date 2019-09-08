#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define k 1000
#define m 10000
#define OUTPUT_FILE_NAME 20
#define BUFFER_SIZE 1024
#define FILE_NAME 500
#define LINE_SIZE 500

char *buffer[BUFFER_SIZE];

/*UTILITY FUNCTION TO DETERMINE THE SIZE OF ENTIRE FILE*/
long sizeOfFile(char *str)
{
    FILE *fp = fopen(str, "rb"); 
    long fileSize=-1;
    if(fp)
    {
        fseek (fp, 0, SEEK_END);//RETURN POINTER TO START OF FILE
        fileSize = ftell(fp)+1;//RETURNS SIZE OF FILE
        fclose(fp);
    }
    return fileSize;
}

/*UTILITY FUNCTION TO OPEN FILE FOR SPLITTING LINE WISE WITH TWO LENGTH SUFFIX */
FILE *openFile_for_l(char c,int count) {
	char outputFileName[OUTPUT_FILE_NAME];    
	sprintf(outputFileName, "x%c%c",c, (char)(count+96));
	strcat(outputFileName, ".txt");
	return fopen(outputFileName, "w");
}

/*UTILITY FUNCTION TO OPEN FILE FOR SPLITTING LINE WISE WITH THREE LENGTH SUFFIX */
FILE *openFile_for_l_new(char ch,char c,int count) {
	char outputFileName[OUTPUT_FILE_NAME];       
	sprintf(outputFileName, "x%c%c%c",ch,c, (char)(count+96));
	strcat(outputFileName, ".txt");
	return fopen(outputFileName, "w");
}

/*UTILITY FUNCTION TO OPEN FILE FOR SPLITTING WITH SUFFIX AS DIGITS */
FILE *openFile_for_d(int count) {
	char outputFileName[OUTPUT_FILE_NAME];
	sprintf(outputFileName, "x0%d", (count-1));//APPEND SUFFIX AS DIGITS
	strcat(outputFileName, ".txt");
	return fopen(outputFileName, "w");
}

/*FUNCTION TO IMPLEMENT SPLIT WITH -b OPTION*/
void split_b(char *file, char* bytes){
	//CHECK IF SPLITTED FILE SIZE IS ZERO
	if(atoi(bytes)==0)
	{
	printf("0 is not valid size\n");
	return;
	}
	int blocksize;
	char *ext,*temp,*temp1,*ext1;
	char copy[100];
	strcpy(copy,bytes);
	temp=copy;
	ext=strtok(temp,"k");	//TOKENIZING ON K TO GET STRING WRITTEN BEFORE K
	temp1=copy;
	ext1=strtok(temp1,"m");	 //TOKENIZING ON K TO GET STRING WRITTEN BEFORE M
 	//HANDLING SIZE GIVEN IN KBs OR MBs 
	if(strstr(bytes,"k"))
	{
	blocksize=(atoi(ext))*1000;
	}
	else if(strstr(bytes,"m"))
	{

	blocksize=(atoi(ext1))*1000000;
	}
	//IF SPECIFIED IN BYTES
	else
	{
	blocksize=atoi(bytes);
	}
    	int N=0, i, len, cursor;
    	FILE *fp1, *fp2;
    	char mainFile[FILE_NAME],ch;
	strcpy(mainFile,file);
    	long sizeFile = sizeOfFile(mainFile);
    	N = sizeFile/blocksize + 1;//N IS NUMBER OF FILES TO BE CREATED OF SIZE PROVIDED 
	char filename[FILE_NAME]={"xa"};
    	char splittedFile[FILE_NAME];
    	char buffer[1080];
    	fp1 = fopen(mainFile, "r");
 	if(fp1==NULL)
		printf("file not found\n");
    	if(fp1)
    	{
        	for(i=0;i<N;i++)
        	{
            		cursor = 0;
            		sprintf(splittedFile, "%s%d.txt", filename, i);//STORE FILENAME OF SPLITTED 										//FILE IN BUFFER
            		fp2 = fopen(splittedFile, "w");//SPLIT FILE OPEN
            		if(fp2)
            		{
				/*READ THE FILE CHARACTER WISE AND WRITE UNTIL BLOCKSIZE IS REACHED */
                		while(cursor < blocksize && !(feof(fp1)) )
                		{
					ch = getc(fp1);//READ CHARACTER WISE
                    			cursor ++;
					if(!(feof(fp1)))
                    				fputc(ch, fp2);//WRITE CHARACTER WISE
                		}
                		fclose(fp2);//SPLIT FILE CLOSE
            		}
        	}
        	fclose(fp1);
    	}
   

}

/*FUNCTION TO IMPLEMENT SPLIT WITH -n OPTION*/
void split_n(char *file ,long N)
{
	//CHECK IF NUMBER OF PARTS ARE NOT 0
	if(N==0)
	{
	printf("0 is not valid part\n");
	return;
	}
	int blocksize=0;
    	long  i, len, cursor;
    	FILE *fp1, *fp2;
    	char mainFile[FILE_NAME];
	strcpy(mainFile,file);
    	long sizeFile = sizeOfFile(mainFile);
    	blocksize = sizeFile/N + 1;//DETERMINE THE SIZE OF SPLITTED FILE
    	char filename[FILE_NAME]={"xa"};
    	char splittedFile[FILE_NAME],ch;
    	char buffer[BUFFER_SIZE];
    	fp1 = fopen(mainFile, "r");
	if(fp1==NULL)
	printf("file not found\n");	
    	if(fp1)
    	{
        	for(i=0;i<N;i++)
        	{
            		cursor = 0;
            		sprintf(splittedFile, "%s%ld.txt", filename, i);//STORE FILENAME OF SPLITTED 										//FILE IN BUFFER
            		fp2 = fopen(splittedFile, "w");//SPLIT FILE OPEN
            		if(fp2)
            		{
				/*READ THE FILE CHARACTER WISE AND WRITE UNTIL CALCULATED FILE SIZE OF SPLITTED IS REACHED*/
                		while(cursor <= blocksize && !(feof(fp1)) )
                		{
                    			ch = getc(fp1);//READ CHARACTER WISE
                    			cursor ++;
					if(!(feof(fp1)))
                    				fputc(ch, fp2);//WRITE CHARACTER
                		}
                		fclose(fp2);//SPLIT FILE CLOSE
            		}
        	}
        	fclose(fp1);
    	}
    
}

/*FUNCTION TO IMPLEMENT SPLIT WITH -l OPTION*/
void split_l(char *filename, long n)
{
	//CHECK IF NUMBER OF PARTS ARE NOT 0
	if(n==0)
	{
	printf("0 lines is not valid\n");
	return;
	}
	FILE *fr;
	FILE *fw;
	char line[LINE_SIZE]; 
	int count = 1, lc = 1;
	long lineNum=n+1;
	char c='a',ch='a',c1='a';
	fr = fopen(filename, "r");
	if(fr==NULL)
	printf("file not found\n");
	else
		{	
			fw = openFile_for_l(c,count);
			/*READ THE INPUT FILE AND WRITE IN A FILE UNTIL N LINE AND THEN CREATE A NEW FILE*/
			while (fgets(line, sizeof line, fr) != NULL) {

				if (lc == lineNum) {

				fclose(fw);//CLOSE THE FILE WHEN REACHED N LINES
				if(c<='z')
				{
					lc = 1;
					count++;
					fw = openFile_for_l(c,count);//OPEN NEW FILE FOR WRITE
					if(count==26)
						{
						count=1;
						c++;
						}
					
				}
				else
				{
					lc = 1;
					
					count++;

					fw = openFile_for_l_new(ch,c1,count);//OPEN NEW FILE FOR WRITE
					
					
					if(count==26 && c1!='z')
						{
						count=1;
						c1++;
						}

					 else if(c1=='z' && count==26)
						{

							count=1;
							c1='a';
							ch++;
						}
					
				}
			}
			fprintf(fw, "%s", line);
			lc++;
		}
			fclose(fr);//FILE CLOSE
		}
}

/*FUNCTION TO IMPLEMENT SPLIT WITH -d OPTION*/
void split_d(char *filename)
{
	FILE *fr;
	FILE *fw;
	char line[LINE_SIZE]; 
	int count = 1, lc = 1;

	fr = fopen(filename, "r");
	if(fr==NULL)
		printf("file not found\n");
	else
		{
			fw = openFile_for_d(count);
			/*READ THE INPUT FILE AND WRITE IN A FILE UNTIL 1000 LINE AND THEN CREATE A NEW FILE*/
			while (fgets(line, sizeof line, fr) != NULL) {
				if (lc == 1001) {
					fclose(fw);//CLOSE THE FILE WHEN REACHED 1000 LINES
					lc = 1;
					count++;
					fw = openFile_for_d(count);//OPEN NEW FILE FOR WRITE
			
					}
				fprintf(fw, "%s", line);
				lc++;
				}
			fclose(fr);//FILE CLOSE
		}
}

/*FUNCTION TO IMPLEMENT SPLIT WITH NOT OPTION*/
void split_main(char *filename)
{
	FILE *fr;
	FILE *fw;
	char line[LINE_SIZE]; 
	int count = 1, lc = 1;
	char c='a',ch='a',c1='a';
	fr = fopen(filename, "r");//FILE OPEN FOR READING
	if(fr==NULL)
		printf("file not found\n");
	else
		{
			fw = openFile_for_l(c,count);
			/*READ THE INPUT FILE AND WRITE IN A FILE UNTIL 1000 LINE AND THEN CREATE A NEW FILE*/
			while (fgets(line, sizeof line, fr) != NULL) {

				if (lc == 1001) {

				fclose(fw);//CLOSE THE FILE WHEN REACHED N LINES
				if(c<='z')
				{
					lc = 1;
					count++;
					fw = openFile_for_l(c,count);//OPEN NEW FILE FOR WRITE
					if(count==26)
						{
						count=1;
						c++;
						}
					
				}
				else
				{
					lc = 1;
					
					count++;

					fw = openFile_for_l_new(ch,c1,count);//OPEN NEW FILE FOR WRITE
					
					
					if(count==26 && c1!='z')
						{
						count=1;
						c1++;
						}

					 else if(c1=='z' && count==26)
						{

							count=1;
							c1='a';
							ch++;
						}
					
				}
			}
			fprintf(fw, "%s", line);
			lc++;
		
			}
			fclose(fr); //FILE CLOSE
		}
}

//UTILITY FUNCTION TO DISPLAY HELP
void help()
{
	FILE *fp = fopen("splitHelp.txt","r"); //OPENING TEXT FILE IN WHICH DESCRIPTION IS WRITTEN
	if (fp == NULL)
		return;
	char c = fgetc(fp);
	printf("%c", c); 
	while(!feof(fp))
    	{
       		char c = fgetc(fp);
		if(c!=EOF)
        	printf("%c", c); 
    	}  
    fclose(fp); 
}

/*UTILITY FUNCTION TO DECIDE WHICH OPTION OF SPLIT NEED TO BE EXECUTED*/
void split(char *option, char *filename,char* n){    
    if(strcmp(filename,"--help")==0){
    	help();
	return;
    }
    if(strcmp(option,"-n")==0){
    	split_n(filename,atol(n));
    }
    else if(strcmp(option,"-d")==0){
    	split_d(filename);
    }
    else if(strcmp(option,"-l")==0){
    	split_l(filename,atol(n));
    }
    else if(strcmp(option,"-b")==0){
    	split_b(filename,n);
    }
    else if(strcmp(option,"not")==0)
    {
	
	split_main(filename);
    }
    else
	printf("invalid option\n");	
}

//MAIN PROGRAM
int main(int argc, char *argv[])
{
    int i;
    char *option,*filename;
    
    if(argc == 2)
    filename = argv[1];
    else{
	printf("Illegal number of arguments\n");
	return;
	}

    char* num;
	if(argc == 2)
	{
		
	   option = "not"; //IF NO OPTIONS ARE PROVIDED COMPARING WITH NOT
	   num=0;
	}

	if (argc == 3)
 	{
	
	   option = argv[2];
	   num=0;
	}
		
        if(argc == 4)
	{
	
	option = argv[2];
	num=argv[3];
    
        }
        //CHECK IF LESS OR MORE ARGUMENTS ARE PROVIDED
	if(argc<2 || argc >4)
	{
	printf("illegal arguments\n");
	}  
	//if(strstr(num,"-"))
	//printf("negative argument not accepted\n");
	//else
    	split(option,filename,num);//CALL FUNCTION TO DECIDE WHICH SPLIT FUNCTION TO CALL
    return 0;
}
