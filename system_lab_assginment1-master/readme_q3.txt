
QUESTION 3: PROCESS CREATION AND INTERPROCESS COMMUNICATION

	2 Player game having players spwan in child processes and information is passed to parent using pipes.
	For each iteration "n", player A and B generates two random numbers and sends them to parent process using respective pipes. Parent process generates a 
	max_min flag randomly in every iteration. If MAX flag is set then player with maximum generated values wins if MIN flag is set then player with minimum
	generated value wins. Print the scores after every iteration and winner at the end. 

FLOW OF PROGRAM
	
	1. Pipes and semaphores are initialized. Two parent semaphores are used to wait for the child process to finish execution which are initialized to value 0.
	   Two semaphores each for child are initialized with values 1. 
	2. Two Child processes are created using fork.
	3. Each of the child process generates random number and writes to their pipes and signals the parent semaphore respectively.
	4. Parent Process waits for childs to complete and reads the values from the pipe. It generates a MAX_MIN Flag which is set to MAX(1) or MIN(0) values 
	   randomly and finds out the winner for current iteration.
	5. It displays the scores and signals child process for next iteration.
	6. Until all the iterations steps 3 to 5 are repeated.
	7. Winner of the game is displayed at the end.

REQUIREMENTS FOR RUNNING THE PROGRAM

	1. Makefile must be executed to create object (exe) files.
	2. File is stored under "../Q3/files/problem3_game.c"
	

RUNNING THE PROGRAM

	1. To compile this program seperately execute the command as "make P3_CMD"
	2. Run the .game object file from path "../Q3/obj_files/"
	3. Enter no of iterations as the commandline argument while running.

OUTPUT DISPLAYED ON SCREEN

	Numbers selected by both the child, Winner Flag and scores for each iteration is printed.
	Winner is displayed at the end.




