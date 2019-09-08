CC=gcc
#SH=bash
LOC_Q1=Q1/files/
LOC_Q2=Q2/files/
LOC_Q3=Q3/files/

OP_LOC_Q1=Q1/obj_files/
OP_LOC_Q2=Q2/obj_files/
OP_LOC_Q3=Q3/obj_files/

LIB1=-lreadline
LIB2=-lpthread
LIB3=-lrt


PWD_CMD:
	$(CC) $(LOC_Q2)pwd.c -o $(OP_LOC_Q2)mypwd
MOVE_CMD:
	$(CC) $(LOC_Q2)move.c -o $(OP_LOC_Q2)mymv
GREP_CMD:
	${CC} $(LOC_Q2)grep.c -w -o $(OP_LOC_Q2)mygrep
SPLIT_CMD:
	${CC} $(LOC_Q2)split.c -w -o $(OP_LOC_Q2)mysplit
HELP_CMD:
	${CC} $(LOC_Q2)help.c -o $(OP_LOC_Q2)myhelp
SHELL_CMD:
	${CC} $(LOC_Q2)my_shell.c -w -o $(OP_LOC_Q2)myshell $(LIB1)
P1_C_CMD:
	${CC} $(LOC_Q1)search_string.c -w -o $(OP_LOC_Q1)search_string
#P1_SH_CMD:
#	${SH} $(LOC_Q1)search_string.sh -w -o $(OP_LOC_Q1)search_string_sh
P3_CMD:
	${CC} $(LOC_Q3)problem3_game.c -o $(OP_LOC_Q3)game $(LIB2) $(LIB3)

ALL:	PWD_CMD	MOVE_CMD	GREP_CMD	SPLIT_CMD	HELP_CMD	SHELL_CMD	P1_C_CMD	P3_CMD

clean: 
	rm $(OP_LOC_Q2)grep $(OP_LOC_Q2)pwd $(OP_LOC_Q2)split $(OP_LOC_Q2)mv $(OP_LOC_Q2)shell $(OP_LOC_Q2)help
	rm $(OP_LOC_Q1)search_string
	rm $(OP_LOC_Q3)game

