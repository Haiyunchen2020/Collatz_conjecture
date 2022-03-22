#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


void collatz (int number);

int main (int argc, char* argv[]) {
	int wstatus;
	pid_t pid;    // process identifier
	int number;

	printf("argc = %d \n", argc);        
	for (int i=0; i < argc; i++) {
		printf("argv[%d]=%s\n", i , argv[i]);
	}
	
	if (argc <= 1) {
		printf("Usage: %s positive integer\n",argv[0]);
		exit (EXIT_SUCCESS);
	}

	number = atoi (argv[1]);
	printf("number = %d\n", number);
	
	// do the following in the child process
	//collatz(number);

	pid = fork ();

	if (pid > 0) {           // in the parent process
		wait (&wstatus);
		printf ("In the parent\n");
		sleep (10);
	}
	else  if  (pid ==0) {        // in the child process
		collatz(number);
		printf ("In the child\n");
		sleep (10);
	}
	else {          // error 
		perror ("fork()");
		exit (EXIT_FAILURE);
	}
	exit (EXIT_SUCCESS);
}



void collatz (int number) {
	long n = number; 
	while (n !=1) {
		printf ("%ld    ",n);
		if (n %2 ==0) {
			n=n/2;
		}
		else {
			n=3*n+1;
		}
	}
	printf("%ld\n",n);

}

