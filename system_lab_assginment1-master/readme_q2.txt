QUESTION 2:CREATE SHELL OF YOUR OWN.

A bash shell(“my_shell”) is implemented consisting of four commands implemented using c programs:
	1. pwd.c
	2. mv.c
	3. grep.c
	4. split.c

HIGH LEVEL FLOW OF MY SHELL
	1. On executing my_shell parent process will be created.
	2. After giving command a child process will be created accordingly.
	3. Child will call respective object file and execute.
	4. After exection it will get back to parent process.
	5. Same process is repeated until we exit the shell.

REQUIREMENT FOR RUNNING THE PROGRAM
	1. Makefile must be executed to create object (exe) files.
	2. All the executable file must be in Obj_files folder inside Q2(which will automatically created in correct location after executing Makefile).
	3. Help files (grep_help,mvHelp,pwdHelp,splitHelp) must be in Obj_files folder inside Q2.

TO RUN PROGRAM(SHELL)
	1. run ./my_shell ,you will be inside the shell.
	2. Run the command you wish(supported command given above).
	3. "clear" can be used to clear the screen.
	4. Up and down key can be used to get history.
	5. Tab can be used for suggestions.

TO RUN COMMAND SEPERATELY
	1. To compile this program seperately execute the command "make ALL"
	2. Run the obj file inside obj_files folder.

List of arguments supported:
	1.pwd:
		1. No arguments:To print current working directory.
		2. --help:To get help about the working of pwd.
		3. If any illegal argument other than above is provided prompt respective error message will be printed.
	2.mv: 
		1. Two arguments:Containing source and destination.
		2. --help:To get help about the working of mv.
		3. If any illegal argument other than above is provided prompt respective error message will be printed.
	3.grep:
		1. Two arguments:Containing option and search string.
		2. Three arguments:Containing option,search string and destination directory where the search string need to be searched.
		3. --help:To get help about working of grep.
		4. If any illegal argument other than above is provided prompt respective error message will be printed.
	4.split:
		1. One argument:Containing path of file.
		2. Two arguments:Containing path of file and option.
		3. Three arguments:Containing path of file,option and number.
		4. --help:To get help about working of split.
		5. If any illegal argument other than above is provided prompt respective error message will be printed.

OUTPUT DISPLAYED ON SCREEN
	Will be directed to next line on successfull execution of command or a message is thrown for illegal or unspported commands.







