#!/bin/bash

#FLAG TO CHECK IF STRING IS NOT FOUND IN ANY FILE
flag=0

#SEARCH THE STRING IN PARTICULAR FILE
search_in_file () {

	str=$1
	file=$2
	strlen=${#str}  
	line_no=0
	occurence_count=0

	#FOR EACH LINE IN FILE
	while read -r line; do
		str1=$line
		line_no=`expr $line_no + 1`

		#FOR EACH POSSIBLE SUBSTRING OF THE LINE
		for (( i=0; i<${#str1}; i++ )); do
		    temp=${str1:$i:$strlen}
		    str=${str,,}
		    temp=${temp,,}
		
		    #IF THE SUBTRING MATCHES THE SEARCH STRING
		    if [[ $temp == $str ]]; then			
			occurence_count=`expr $occurence_count + 1`
		    	printf "\nLine No : $line_no Filename:$file"
		    fi

		done
	done < $file

	#IF ANY OCCURENCE IS FOUND IN FILE THEN PRINT THE COUNT 
	if [ $occurence_count -ne 0 ]; then
		flag=1
		printf "\nOccurence Count : $occurence_count\n"
	fi
}

#RECURSIVE FUNCTION TO ITERATE OVER THE DIRECTORIES AND FILES 
walk_in_dirs(){
	path=$1

	#IF THE PATH IS A DIRECTORY
	if [ -d $path ];then

	#FOR EACH DIRECTORY IN PATH
	for directory in $path; do
		
	    #FOR EACH FILE IN DIRECTORY
	    for file in $directory/*; do		

		#IF A DIRECTORY IS FOUND THE CALL ITSELF
		if [ -d $file ]; then
		   walk_in_dirs $file

		#IF IT IS FILE
		elif [ -f $file ]; then       		    
		    extension="${file##*.}"
			
		    #CHECK FOR READABLE FILE TYPES AND SEARCH THE STRING IF APPROPRIATE
		    if [ $extension == "txt" -o $extension == "sh" -o $extension == "c" ]; then
			   search_in_file $str $file		    
		    fi
		else
		  echo "No such File : $path"
		fi		
	    done
	done

	#IF THE PATH IS FOR SOME FILE
	elif [ -f $path ];then
		    extension="${path##*.}"
		    #echo "Extension:     "$extension
		    if [ $extension == "txt" -o $extension == "sh" -o $extension == "c" ]; then
			   search_in_file $str $path		    
		    fi
	else
	  echo "No such File or Directory : $path"
	  flag=1
	fi
}

#CHECK FOR NUMBER OF ARGUMENTS AND EXTRACT THE SEARCH STRING AND THE PATH
if [[ $1 != "" ]];then
	str=$1
	if [[ $2 != "" ]];then
		path=$2
	else 
		path="./"
	fi
	walk_in_dirs $path
else
	echo "Please Enter Search String as 1st argument" 
	flag=1
fi

#IF THE STRING IS NOT FOUND IN ANY FILE
if [ $flag -eq 0 ];then
	echo "String Not found"
fi












