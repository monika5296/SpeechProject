#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define GEN_SIZE 1000
#define BUFF_SIZE 100

//TO UNLINK THE USED SEMAPHORES
void unlink_semaphores(){
	sem_unlink("/sema1");
	sem_unlink("/sema2");
	sem_unlink("/sema3");
	sem_unlink("/sema4");	
}

//CLOSE ALL THE USED PIPES
void close_pipe(int fd[2]){
	close(fd[0]);
	close(fd[1]);
}

//IT EVALUATES THE WINNER FOR CURRENT ITERATION BY GENERATING THE MAX OR MIN FLAG 
int make_decision(int num1,int num2){

	int max_min_flag = rand()%2;
	static int score_1=0;
	static int score_2=0; 

	//IF WINNER IS MAXIMUM FLAG FOR CURRENT ITERATION
	if(max_min_flag == 1){
		printf("Winner is Maximum Number\n");
		if(num1>num2){
			score_1++;
		}else{
			score_2++;
		}
	}

	//IF WINNER IS MINIMUM FLAG FOR CURRENT ITERATION	
	else{
		printf("Winner is Minimum Number\n");
		if(num1<num2){
			score_1++;
		}else{
			score_2++;
		}
	}

	//PRINT THE SCORE AND RETURN THE WINNER TILL CURRENT ITERATION
	printf("Score : %d %d\n\n",score_1,score_2);
	if(score_1==score_2)
		return 0;
	else if(score_1>score_2)
		return 1;
	else 
		return 2;
}

//DRIVER FUNCTION TO CREATE AND MANAGE PLAYERS AND GETTING VALUES USING PIPES 
void game(int n){

	int len1,len2,i,val=-1,winner=0;
	int temp;
	long time_long;
	time_t time_var;
	char temp1[BUFF_SIZE];
	int pipe1[2],pipe2[2];
	char player1_data[BUFF_SIZE];
	char player2_data[BUFF_SIZE];

	pid_t player1_pid,player2_pid;
	sem_t *sem_player1,*sem_player2,*sem1_parent,*sem2_parent;

	//UNLINK THE SEMAPHORES BEFORE USE	
	unlink_semaphores();
	
	//INITIALIZE SEMAPHORES WITH APPROPRIATE VALUES
	sem_player1 = sem_open("/sema1", O_CREAT,  0644, 1);
	sem_player2 = sem_open("/sema2", O_CREAT,  0644, 1);
	sem1_parent = sem_open("/sema3", O_CREAT,  0644, 0);
	sem2_parent = sem_open("/sema4", O_CREAT,  0644, 0);

	//PIPE 1 IS FOR PLAYER1 AND PIPE 2 IS FOR PLAYER2
	pipe(pipe1);
	pipe(pipe2);
	
	//CREATE TWO CHILD PROCESSES
	player1_pid = fork();
	if(player1_pid<0)
		printf("Failed to create Child for Player 1\n");

	if(player1_pid>0){
		player2_pid = fork();
		if(player2_pid<0)	
			printf("Failed to create child for Player 2\n");
	}
		
	//FIRST CHILD PROCESS: FOR PLAYER 1		
	if(player1_pid == 0 ){
		srand((unsigned) time(&time_var));
		for(i=0;i<n;i++){

			sem_wait(sem_player1);	

			temp = rand()%GEN_SIZE;
			printf("Player 1 selected : %d\n",temp);
			sprintf(temp1,"%d",temp);
			close(pipe1[0]);
			len1=strlen(temp1);
			write(pipe1[1],temp1,BUFF_SIZE);					

			sem_post(sem1_parent);				
		}
		printf("**** Player 1 leaving game: Ending Child Process ****\n");
	}
	//SECOND CHILD PROCESS: FOR PLAYER 2	
	else if(player2_pid == 0){
		
		for(i=0;i<n;i++){
			sem_wait(sem_player2);
		
			temp = rand()%GEN_SIZE;
			printf("Player 2 selected : %d\n",temp);		
			sprintf(temp1,"%d",temp);
			close(pipe2[0]);
			len2=strlen(temp1);
			write(pipe2[1],temp1,BUFF_SIZE);

			sem_post(sem2_parent);
			
		}
		printf("**** Player 2 leaving game: Ending Child Process ****\n");
	}
	//PARENT PROCESS: MAIN BLOCK TO HANDLE CHILD PROCESSES
	else{
		
		for(i=0;i<n;i++){		
		
		//WAIT FOR PLAYERS TO SELECT NUMBERS
		sem_wait(sem1_parent);
		sem_wait(sem2_parent);

		//READ DATA FROM PIPES
		close(pipe1[1]);
		read(pipe1[0],player1_data,BUFF_SIZE);
		close(pipe2[1]);
		read(pipe2[0],player2_data,BUFF_SIZE);			
		
		//printf("In parent - Player 1: %d\n",atoi(player1_data));	
		//printf("In parent - Player 2: %d\n\n",atoi(player2_data));	

		//MAKE DECISION OF WINNER FOR CURRENT ITERATION BASED ON NUMBERS
		winner = make_decision(atoi(player1_data),atoi(player2_data));
		
		//CHECK FOR THE RETURN FLAG FROM DECISION FUNCTION 
		if(i==n-1){
			if(winner == 0){
				printf("Game is a Tie\n");
			}else if(winner == 1){
				printf("Winner is Player 1\n");
			}else{
				printf("Winner is Player 2\n");
			}
		}		
		sem_post(sem_player1);	
		sem_post(sem_player2);	

		}				
		printf("**** Ending Parent Process ****\n");
	}

	//CLOSE AND UNLINK THE PIPES AND SEMAPHORES
	sem_close(sem_player1);
        sem_close(sem_player2);
        sem_close(sem1_parent);
        sem_close(sem2_parent);

	unlink_semaphores();

	close_pipe(pipe1);
	close_pipe(pipe2);
}

int main(int argc,char *args[]){
	int n;

	//CHECK FOR ENOUGH NUMBER OF ARGUMENTS
	if(argc>=2){
		printf("\n************* 2 Player Game **************");
		n = atoi(args[1]);
		printf("\nNo. of Iterations : %d\n\n",n);
		game(n);
	}else
		printf("Please enter no of iterations in argument\n");
	return 0;
}
