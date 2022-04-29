#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argCount, char **args) {
	if (argCount < 2) {
		printf("No program to exec provided\n");
		return 1;
	}

	args++;
	char *programName = *args;
	int childProcess = fork();
	
	if (childProcess == 0) {
		printf("Starting program %s\n", programName);
		int started = execv(programName, args);
		if (started == -1) {
			printf("Could not start program\n");
		}
		return 1;
	}


	int status = 0;
	int childProcessID = wait(&status);
	printf("Child programm at process %d exited with %d\n", childProcessID, status);

	return 0;
}
