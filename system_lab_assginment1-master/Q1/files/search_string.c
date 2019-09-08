#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define PATH_SIZE 1000
#define SEARCH_STRING_SIZE 500

int tolower(int argument);

//IT FINDS SEARCH STRING CASE INSENSITIVELY AND DISPLAYS LINE IN WHICH IT IS FOUND
void search_string_in_file(char filename[],char *search_string){

    int last_index=0;
    int line_count=0,i,j,flag=0;
    int occurence_count=0;
    int count=0;
    char line[PATH_SIZE],line1[PATH_SIZE];
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
		printf("\n\033[1;32m%d\033[0m:\033[1;34m%s\033[0m: ",line_count,filename);
	    flag=1;	    

	    int len1 = strlen(search_string);	
	    int count=0;	
	  
            //COLORING THE FOUND WORD APPROPRIATELY
	    for(j=last_index;j<len;j++){

		//COLOR ONLY THE MATCHED PART
		if((word[count]==line[j]) && count<len1 && (&word[count]==&line[j])){
			printf("\033[1;31m%c\033[0m",line1[j]);
			count++;
			
		}
		//PRINT THE LINE BEFORE MATCHED STRING IN NORMAL COLOR
		else{
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
    
     //PRINT NO. OF OCCURENCE FOUND FOR EACH FILE
     if(occurence_count!=0){
	    printf("\nOccurence Found:%d\n",occurence_count);
     }

    fclose(fp);
}

//TO RECURSIVELY OPEN DIRECTORY AND FILES ONE AFTER THE OTHER IN PATH PASSED AS ARGUMENT
void walk_in_dirs(char basePath[],char *search_string,int option){

    char path[PATH_SIZE];
    char *word,*ext;
    struct dirent *dp;
    DIR *dir = opendir(basePath);

	//CHECK IF THE PATH IS VALID
        if (dir != 0){
		
		//READ CONTENTS OF DIRECTORY
		while ((dp = readdir(dir)) != NULL)
		{

             	    //FOR EACH FILE IN DIRECTORY		   
		    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
		    {

			//MAKE NEW PATH BY ADDING CURRENT FILE OR DIRECTORY NAME TO BASEPATH FOR RECURSION
		        strcpy(path, basePath);
		        strcat(path, "/");
		        strcat(path, dp->d_name);
		        ext = strtok(dp->d_name,".");
			word = ext;
			while( (ext = strtok(NULL,".")) != NULL )
				word=ext;

			//CHECK FOR READABLE FILES 
		        if( word!=NULL && (strcmp(word,"txt")==0 || strcmp(word,"sh")==0 || strcmp(word,"c")==0)){
			       search_string_in_file(path,search_string);
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

//DRIVER FUNCTION FOR CALLING DIRECTORIES RECURSIVELY
void grep(char *search_string,char path[]){

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

	//EXTRACT THE EXTENSION FROM THE PATH
    	ext_prev = strtok(temp,".");    
	ext=ext_prev;
	while((	ext_prev = strtok(NULL,".")) !=NULL)
		ext=ext_prev;

	//CHECK FOR READABLE FILES AND FIND THE SEARCH STRING INSIDE IT
	 if( ext!=NULL && (strcmp(ext,"txt")==0 || strcmp(ext,"sh")==0 || strcmp(ext,"c")==0)){
          search_string_in_file(path,search_string);
	}

	//IF PATH IS TO SOME DIRECTORY
	else{

          //IF NO SUCH DIRECTORY EXIST
	  if((dir = opendir(path)) == NULL){
		printf("No such directory or file found\n");
		return;
	  }

	  //CALLING THE SEARCH FUNCTION 
          walk_in_dirs(path,search_string,3);
	}
    }
    //IF NO PATH IS SPECIFIED THEN SEARCH IN CURRENT DIRECTORY
    else{
	if((dir = opendir(path)) == NULL){
		printf("No such directory or file found\n");
		return;
    	}
	walk_in_dirs(path,search_string,3);
    }
}


int main(int argc, char *argv[])
{
    int i;
    char path[PATH_SIZE]=".";
    char search_string[SEARCH_STRING_SIZE],option[3];
    char *temp,*temp1;
    
    //CHECK IF THERE ARE LESS NO OF ARGUMENTS
    if(argc < 2){
	printf("\nPlease Enter search string \n");
	return 0;
    }

    //EXTRACT OPTION AND PATH FROM COMMANDLINE ARGUMENT AND CALL THE DRIVER FUNCTION
    if(argc >= 2){
	strcpy(search_string,argv[1]);
	temp=search_string;
	if(argc==3){	    
	    strcpy(path,argv[2]);
	}

	//CALLING THE MAIN DRIVER FUNCTION
        grep(temp,path);
    }
    
    return 0;
}

