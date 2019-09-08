#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define PATH_SIZE 1000
#define COMMAND_SIZE 256

//IT COPIES THE SOURCE FILE TO DESTINATION PATH OR FILE BY COPYING THE CONTENTS AND DELETES THE SOURCE FILE
void move_file(char source_file[PATH_SIZE],char destination_file[PATH_SIZE]){

	char ch;
	FILE *srcname, *desname;
	srcname=fopen(source_file,"r");
	desname=fopen(destination_file,"w");
	printf("Moving : %s\n",source_file);
	printf("To:%s\n",destination_file);

	//COPY CONTENT OF SOURCE TO DESTINATION FILE
	while ((ch = fgetc(srcname)) != EOF)
		fputc(ch, desname);

	fclose(srcname);
	fclose(desname);

	//DELETE THE SOURCE FILE AFTER COPYING
	remove(source_file);	
}

//MOVES FILES FROM SOURCE TO DESTINATION
void move(char source[PATH_SIZE],char destination[PATH_SIZE]){

	char source1[PATH_SIZE],source2[PATH_SIZE],destination1[PATH_SIZE],destination_path[PATH_SIZE];
	char ch;
	char *src_ptr1,*src_ptr,*des_ptr;

        DIR *dr,*dr_check;
	struct dirent *de,*de_check;
	FILE *srcname, *desname;
	char *ext ,*ext_prev,*ext1,*ext1_prev,*ext2,*ext2_prev;

	//MAKING COPIES OF SOURCE AND DESTINATION PATH 
	strcpy(source1,source);
	strcpy(source2,source);
	strcpy(destination1,destination);

	src_ptr1=source1;
	src_ptr=source2;
	des_ptr=destination1;
	
	//TOKENIZING SOURCE AND DESTINATION PATH TO CHECK FOR FILE OR DIRECTORY
	ext_prev = strtok(src_ptr1,".");    
	//ext=ext_prev;
	while((ext_prev=strtok(NULL,"."))!=NULL)
		ext=ext_prev;


	ext1_prev = strtok(des_ptr,".");    
    	//ext1 = ext1_prev;
	while((ext1_prev=strtok(NULL,"."))!=NULL)
		ext1=ext1_prev;

	//printf("Ext:%s\n",ext);
	//printf("Ext1:%s\n",ext1);

	//IF SOURCE IS A PATH TO A FILE 	
	if( ext!=NULL && ((strcmp(ext,"txt")==0) || (strcmp(ext,"sh")==0) || (strcmp(ext,"c")==0)) )
	{ 
		
		//IF NO SUCH SOURCE FILE EXIST
		FILE *fp=fopen(source,"r");		
		if(fp==NULL){
			printf("No such file exist: %s\n",source);
			return;
		}

		//CHECK IF SOURCE CONTAINS HEIRARCHICAL PATH
		ext2 = strtok(src_ptr,"/");    
		ext2 = strtok(NULL,"/");   
		
		//IF SOURCE IS OF CURRENT WORKING DIRECTORY
		if(ext2==NULL){	
			
			//IF DESTINATION IS A SINGLE FILE
			if( ext1!=NULL && ((strcmp(ext1,"txt")==0) || (strcmp(ext1,"sh")==0) || (strcmp(ext1,"c")==0)) )
			{
				
				//MOVE FILE FOR READABLE EXTENSION
				if( (strcmp(ext1,"txt")==0) || (strcmp(ext1,"sh")==0) || (strcmp(ext1,"c")==0) )
					move_file(source,destination);							
				else{
					printf("File Not supported to move\n");
					return;
				}
			}	
			
			//IF DESTINATION IS A PATH		
			else
			{
				//CHECK IS THE PATH EXIST
				dr_check = opendir(destination); 
				if(dr_check == NULL){
					printf("No such directory: %s\n",destination);	
					return;
				}
								
				strcpy(destination_path,destination);
				strcat(destination_path,"/");
				strcat(destination_path,source);

				move_file(source,destination_path);				
			}
		}
		//IF SOURCE CONTAINS HEIRARCHY OF FOLDERS BEFORE FILES
		else
		{
			
			//IF DESTINATION IS A SINGLE FILE
			if( ext1!=NULL && ((strcmp(ext1,"txt")==0) || (strcmp(ext1,"sh")==0) || (strcmp(ext1,"c")==0)) )
			{
				//MOVE FILE FOR READABLE EXTENSION
				if((strcmp(ext1,"txt")==0) || (strcmp(ext1,"sh")==0) || (strcmp(ext1,"c")==0) )
					move_file(source,destination);							
				else{
					printf("File Not supported to move\n");
					return;
				}

			}
			//IF DESTINATION IS A PATH	
			else
			{		
				
				//CHECK IS PATH EXIST
				dr_check = opendir(destination); 
				if(dr_check == NULL){
					printf("No such directory: %s\n",destination);	
					return;
				}
	
				char *ext_temp;
				ext_temp = ext2;
				
				//EXTRACT DESTINATION FILENAME FROM THE HEIRARCHY
				while((ext2 = (strtok(NULL,"/"))) != NULL ){
					ext_temp = ext2;
				}
				
				strcpy(destination_path,destination);
				strcat(destination_path,"/");
				strcat(destination_path,ext_temp);

				move_file(source,destination_path);
			}
		}
	}
	//IF SOURCE IS A PATH TO A DIRECTORY
	else
	{
		
		//CHECK IF SOURCE PATH EXIST
		dr_check = opendir(source); 
		if(dr_check == NULL){
			printf("No such directory: %s\n",source);	
			return;
		}
	
		//SINCE SOURCE IS A PATH DESTINATION CANNOT BE A SINGLE FILE
		if( ext1!=NULL && (strcmp(ext1,"txt")==0) )
		{
			printf("Destination cannot be a single file\n");
			return;
		}

		//CHECK IF DESTINATION PATH EXIST
		dr_check = opendir(destination); 
		if(dr_check == NULL){
			printf("No such directory: %s\n",destination);	
			return;
		}


		dr = opendir(source); 
		char source_path[PATH_SIZE];

		//MOVE ALL FILES FROM SOURCE PATH
		while ((de = readdir(dr)) != NULL) 
		{		
			if((strcmp(de->d_name,".")!=0) && (strcmp(de->d_name,"..")!=0))
			{
				
				char filename[250];
				strcpy(filename,de->d_name);
				ext2 = filename;
				ext1 = strtok(ext2,".");    
			    	ext1 = strtok(NULL,".");
				if(ext1 !=NULL && ((strcmp(ext1,"txt")==0) || (strcmp(ext1,"sh")==0) || (strcmp(ext1,"c")==0)) ){ 
					strcpy(destination_path,destination);				
					strcat(destination_path,"/");
					strcat(destination_path,de->d_name);

					strcpy(source_path,source);				
					strcat(source_path,"/");
					strcat(source_path,de->d_name);
					
					move_file(source_path,destination_path);					
				}else{
					printf("Is a Directory:%s\n",de->d_name);
				}	
			}
		}
	    	closedir(dr);    	
	}
         
}

//FETCHES THE HELP FILE AND PRINTS THE CONTENT ON THE CONSOLE
void help()
{
	FILE *fp = fopen("mvHelp.txt","r"); 
	if (fp == NULL)
		return;
	char c = fgetc(fp);
	printf("%c", c); 
	while(!feof(fp))
    	{
       		char c = fgetc(fp);
        	if(c != EOF)
        		printf("%c", c); 
    	}  
    fclose(fp); 
}

int main(int argc, char* argv[])
{	

	char source[PATH_SIZE];
        char destination[PATH_SIZE];
	char command[COMMAND_SIZE];

	//CHECK FOR NUMBER OF ARGUMENTS IN COMMAND
	if(argc==3){
		strcpy(source, argv[1]);
		strcpy(destination, argv[2]);
		
	 	move(source,destination);
 	}else if(argc==2){
		strcpy(command,argv[1]);
		if(strcmp(command,"--help")==0)
			help();
		else
			printf("invalid parameters\n");
	}
	else
	{
		printf("Please provide source and destination path\n");
	}
	
	return 0;
}
