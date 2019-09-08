#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define LINESIZE 1000
#define PATH_SIZE 1000
#define SEARCH_STRING_SIZE 500

int tolower(int argument);

//UTILITY FUNCTION TO DISPLAY HELP
void help()
{
	FILE *fp = fopen("grep_help.txt","r"); 
	if (fp == NULL)
		return;
	char c = fgetc(fp);
	while(!feof(fp))
    	{
       		char c = fgetc(fp);
		if(c!=EOF)
	        	printf("%c", c); 
    	}  
    fclose(fp); 
}

//IMPLEMENTATION OF -N OPTION FOR GREP COMMAND: IT DISPLAYS LINE NUMBER AND LINE WHICH IS MATCHED 
void option_n(char filename[],char *search_string){

    int last_index=0;
    int line_count=0,i,j,flag=0;
    int occurence_count=0;
    int count=0;
    char line[LINESIZE],line1[LINESIZE];
    char *word;
    char delimeter[] = " \n";
    FILE *fp=fopen(filename,"r");

	
    //ITERATING LINE BY LINE IN A FILE	
    while( fgets ( line, sizeof line, fp ) != NULL ){
	last_index=0;
	flag=0;
	line_count++;
       	strcpy(line1,line);

	//CONVERTING CURRENT LINE INTO LOWERCASE
	/*for( i = 0; line[i]; i++){
	  line[i] = tolower(line[i]);
  	 }*/
	word = line;
	
	//FINDING ALL THE SUBSTRINGS WHICH MATCH THE SEARCH STRING IN PARTICULAR LINE
	int len = strlen(line);	
	while(word = strstr(word,search_string)){
	    if(flag==0)
		printf("\n\033[1;34m%s\033[0m:\033[1;32m%d\033[0m:",filename,line_count);
	    flag=1;	    

	    int len1 = strlen(search_string);	
	    int count=0;	
  		
	    //COLORING THE FOUND WORD APPROPRIATELY
	    for(j=last_index;j<len;j++){
		if((word[count]==line[j]) && count<len1 && (&word[count]==&line[j])){
			printf("\033[1;31m%c\033[0m",line[j]);
			count++;
			
		}else{
			if(count<len1){
				printf("%c",line[j]);
			}else{
				last_index=j;
				break;
			}
		}
		
	    }
	    occurence_count++;
	    word++;
	}
	
	//WRITE THE REMAINING PART OF THE LINE
	while(j<len-1 && flag==1)
		printf("%c",line[j++]);
	
    }
    if(occurence_count!=0)
    printf("\n");
    fclose(fp);
}

//IMPLEMENTATION OF -C OPTION FOR GREP COMMAND: IT DISPLAYS COUNT OF OCCURENCE AND CORRESPONDING FILE
void option_c(char filename[],char *search_string){

    int line_count=0,i;
    int occurrence_count=0;
    int count=0;
    char line[LINESIZE];
    char *word;
    char delimeter[] = " \n";
    FILE *fp=fopen(filename,"r");

    //ITERATING LINE BY LINE IN A FILE
    while( fgets ( line, sizeof line, fp ) != NULL ){
        line_count++;
        word = line;

	//FINDING ALL THE SUBSTRINGS WHICH MATCH THE SEARCH STRING IN PARTICULAR LINE	
        while(word = strstr(word,search_string)){
	    occurrence_count++;
	    word++;
        }
    }
  
    //PRINT FILENAME ONLY IF ANY OCCURENCE IS FOUND 
    if(occurrence_count!=0)
    	printf("\033[1;34m%s\033[0m:\033[1;32m%d\033[0m\n",filename,occurrence_count);

    fclose(fp);
}

//IMPLEMENTATION OF -L OPTION FOR GREP COMMAND: IT DISPLAYS FILENAME IN WHICH SEARCH STRING IS FOUND
void option_l(char filename[],char *search_string){

    int line_count=0,i;
    int occurence_count=0;
    int count=0;
    char line[LINESIZE];
    char *word;
    char delimeter[] = " \n";
    FILE *fp=fopen(filename,"r");

    //ITERATING LINE BY LINE IN A FILE
    while( fgets ( line, sizeof line, fp ) != NULL ){
        line_count++;
        word = line;

	//FINDING ALL THE SUBSTRINGS WHICH MATCH THE SEARCH STRING IN PARTICULAR LINE	
        if(word = strstr(word,search_string)){
		occurence_count++;
		break;
        }
    }
	
    //PRINT FILENAME ONLY IF ANY OCCURENCE IS FOUND 	
    if(occurence_count!=0)
	    printf("\033[1;34m%s\033[0m\n",filename);   
    fclose(fp);
}

//IMPLEMENTATION OF -I OPTION FOR GREP COMMAND: IT FINDS SEARCH STRING CASE INSENSITIVELY AND DISPLAYS LINE IN WHICH IT IS FOUND
void option_i(char filename[],char *search_string){

    int last_index=0;
    int line_count=0,i,j,flag=0;
    int occurence_count=0;
    int count=0;
    char line[LINESIZE],line1[LINESIZE];
    char *word;
    char delimeter[] = " \n";
    FILE *fp=fopen(filename,"r");

    //CONVERTING SEARCH STRING INTO LOWERCASE FOR COMPARISON
    for( i = 0; search_string[i]; i++){
	search_string[i] = tolower(search_string[i]);
    }
	
    //ITERATING LINE BY LINE IN A FILE	
    while( fgets ( line, sizeof line, fp ) != NULL ){
	last_index=0;
	flag=0;
	line_count++;
       	strcpy(line1,line);

	//CONVERTING CURRENT LINE INTO LOWERCASE
	for( i = 0; line[i]; i++){
	  line[i] = tolower(line[i]);
  	 }
	word = line;
	
	//FINDING ALL THE SUBSTRINGS WHICH MATCH THE SEARCH STRING IN PARTICULAR LINE
	int len = strlen(line);	
	while(word = strstr(word,search_string)){
	    if(flag==0)
		printf("\n\033[1;34m%s\033[0m: ",filename);
	    flag=1;	    

	    int len1 = strlen(search_string);	
	    int count=0;	
	  
            //COLORING THE FOUND WORD APPROPRIATELY
	    for(j=last_index;j<len;j++){
		if((word[count]==line[j]) && count<len1 && (&word[count]==&line[j])){
			printf("\033[1;31m%c\033[0m",line1[j]);
			count++;
			
		}else{
			if(count<len1){
				printf("%c",line1[j]);
			}else{
				last_index=j;
				break;
			}
		}
		
	    }
	    occurence_count++;
	    word++;
	}
	
	//WRITE THE REMAINING PART OF THE LINE
	while(j<len-1 && flag==1)
		printf("%c",line1[j++]);
	
    }
    if(occurence_count!=0)
    printf("\n");
    fclose(fp);
}

//TO RECURSIVELY OPEN DIRECTORY AND FILES ONE AFTER THE OTHER IN PATH PASSED AS ARGUMENT
void walk_in_dirs(char basePath[],char *search_string,int option){

    char path[PATH_SIZE];
    char *word,*ext;
    struct dirent *dp;    
    DIR *dir = opendir(basePath);

    //IF CURRENT PATH IS DIRECTORY
    if (dir != 0){

	    //READ CONTENTS OF DIRECTORY		
	    while ((dp = readdir(dir)) != NULL){

		//FOR EACH FILE IN DIRECTORY
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		{
			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			ext = strtok(dp->d_name,".");
			word = ext;
			while( (ext = strtok(NULL,".")) != NULL )
				word=ext;


			//CHECK FOR READABLE FILES 
			if( word!=NULL && (strcmp(word,"txt")==0 || strcmp(word,"sh")==0 || strcmp(word,"c")==0)){
			    if(option == 0){		     	
			        option_n(path,search_string);
			    }else if(option == 1){
			        option_c(path,search_string);
			    }else if(option == 2){
			        option_l(path,search_string);
			    }else if(option == 3){
			       option_i(path,search_string);
			    }
			}
			
			//RECURSIVELY CALL ITSELF IF A DIRECTORY IS FOUND
			walk_in_dirs(path,search_string,option);
		}
	    }
    }else{		
	return;
    }	

    closedir(dir);
}

//DRIVER FUNCTION FOR CALLING FUNCTION BASED ON OPTIONS : PERFORMS DECISION MAKING FOR FILES AND DIRECTORY
void grep(char* search_string,char *option,char path[]){

    //printf("\nSTRING TO SEARCH: %s",search_string);
    //printf("\nOPTION: %s",option);
    //printf("\nPATH: %s\n\n",path);

    char *temp,*ext,*ext_prev;
    char path_copy[PATH_SIZE];
    strcpy(path_copy,path);
    temp=path_copy;   
    DIR *dir;
    struct dirent *dp;

    //IF THE PATH SUPPLIED IS A FILE THEN DIRECTLY PERFORM THE STRING SEARCH
    if(strcmp(path,".")!=0){	
	FILE *fp=fopen(path,"r");

	//IF NO SUCH FILE EXIST
	if(fp==NULL){
		printf("No such  file found\n");
		return;
	}	

    	ext_prev = strtok(temp,".");    
	ext=ext_prev;
	while((	ext_prev = strtok(NULL,".")) !=NULL)
		ext=ext_prev;

	//CHECK FOR READABLE FILES AND FIND THE SEARCH STRING INSIDE IT
	 if( ext!=NULL && (strcmp(ext,"txt")==0 || strcmp(ext,"sh")==0 || strcmp(ext,"c")==0)){
	    if(strcmp(option,"-n")==0){		     	
	          option_n(path,search_string);
	    }else if(strcmp(option,"-c")==0){
		
	          option_c(path,search_string);
	    }else if(strcmp(option,"-l")==0){
	          option_l(path,search_string);
	    }else if(strcmp(option,"-i")==0){
	          option_i(path,search_string);
	    }else{
		printf("Please enter valid option\n");
	    }
	
	//IF PATH IS A PATH TO SOME DIRECTORY
	}else{
	    
            //IF NO SUCH DIRECTORY EXIST
	    if((dir = opendir(path)) == NULL){
		printf("No such directory or file found\n");
		return;
    	     }

	    //WALK IN DIRECTORY RECURSIVELY 
	    if(strcmp(option,"-n")==0)
	    	walk_in_dirs(path,search_string,0);
	    if(strcmp(option,"-c")==0)
	    	walk_in_dirs(path,search_string,1);
	    if(strcmp(option,"-l")==0)
	    	walk_in_dirs(path,search_string,2);
	    if(strcmp(option,"-i")==0)
	    	walk_in_dirs(path,search_string,3);
	}

    //IF NO PATH IS SPECIFIED THEN SEARCH IN CURRENT DIRECTORY
    }else{
	    
	    if((dir = opendir(path)) == NULL){
		printf("No such directory or file found\n");
		return;
    	    }
	    if(strcmp(option,"-n")==0)
	    	walk_in_dirs(path,search_string,0);
	    else if(strcmp(option,"-c")==0)
	    	walk_in_dirs(path,search_string,1);
	    else if(strcmp(option,"-l")==0)
	    	walk_in_dirs(path,search_string,2);
	    else if(strcmp(option,"-i")==0)
	    	walk_in_dirs(path,search_string,3);
	    else
		printf("Please enter valid option\n");
    }
}

int main(int argc, char *argv[])
{
    int i;
    char path[PATH_SIZE]=".";
    char search_string[SEARCH_STRING_SIZE],option[3];
    char *temp,*temp1;
    
    //CHECK IF THERE ARE LESS NO OF ARGUMENTS
    if(argc < 3){
	if(argc==2){
	if(strcmp(argv[1],"--help")==0){
		help();
		return 0;
	}}
	printf("Please Enter option and search string \n");
	return 0;
    }

    //EXTRACT OPTION AND PATH FROM COMMANDLINE ARGUMENT AND CALL THE DRIVER FUNCTION
    if(argc >= 3 && argc<5 ){
	strcpy(option,argv[1]);	
	strcpy(search_string,argv[2]);
	temp=search_string;
	temp1=option;
	if(argc==4){	    
	    strcpy(path,argv[3]);
	}	

	//CALLING THE MAIN DRIVER FUNCTION
        grep(temp,temp1,path);
    }else{
	printf("Too many arguments\n");
    }
    
    return 0;
}

