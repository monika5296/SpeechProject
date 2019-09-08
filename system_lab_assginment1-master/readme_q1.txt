
QUESTION 1: INTRODUCTION TO BASIC SHELL SCRIPTING

	A). A shell script that searches for particular string(case insensitive) in a directory containing multiple files(recursively).
	    Print: Line number and filename where the string is found.
		   Print Total occurence of strings in that file.

	B). Implement above question (part A) in C.Using in-built system command is prohibited in this
	    question.Question-2: Create a Shell of your own.

FLOW OF PROGRAM
	
	1. Commandline arguments are fetched and search string and path are extracted from it.
	2. If the path is a path to a file then respective function to search in file is called and results are displayed on screen.
	3. If the path is some directory then recusive function "walk_in_dirs" is called to recursively open every files and folders in the heirarchy.
	4. For every path containing a file function to search is called and results are displayed.
	5. For both case mentioned in step 2 and 4 strings are converted to lowercase to search case insensitively in files.
	6. For files not supported or path which does not exist appropriate error messages are shown on screen.

REQUIREMENTS FOR RUNNING THE PROGRAM

	1. Makefile must be executed to create object (exe) files.
	2. File are stored under "../Q1/files/" (both sh and C file)

	NOTE: ** files of type ".sh" , ".c" and ".txt" are considered while searching strings as of now, more extensions can be added if found 
	      appropriate to read using program **.
	

RUNNING THE PROGRAM

	1. To compile C program seperately execute the command "make P1_C_CMD"
	2. Run the .search_string object file from path "../Q3/obj_files/search_string" (For Part A)
	   Run the .search_string object file from path "../Q3/files/search_string.sh" (For Part B)
	3. Enter search string followed by path or filename as commandline arguments.
	
	For example:
	1) ./search_string "Hello" /home/jay
	2) bash search_string.sh "hello" /home/jay

OUTPUT DISPLAYED ON SCREEN

	Line number:filename:line in which string is found

.

