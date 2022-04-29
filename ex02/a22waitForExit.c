#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argCount, char **args) {
	int parentId = getpid();
	printf("First args %s. Process-ID from parent: %d\n", args[1], parentId);

	int firstChild = fork();

	int secondChild = 1;
	if (getpid() == parentId) {
		secondChild = fork();
	}
	
	int thirdChild = 1;
	if (getpid() == parentId) {
		thirdChild = fork();
	}

	if (getpid() == parentId) {
		sleep(2);
		kill(firstChild, 15);
		kill(secondChild, 9);
		kill(thirdChild, 9);
		for (int i = 0; i < 3; i++) {
			int status;
			int pid = wait(&status);
			printf("%d exited with %d\n", pid, status);
		}
		return 0;
	}

	if (firstChild == 0) {
		printf("Second arg: %s. Process-ID is %d\n", args[2], getpid());
		while (1) {
			sleep(0.1);
		}
	} else if (secondChild == 0) {
		printf("Third arg: %s. Process-ID is %d\n", args[3], getpid());
		while (1) {
			sleep(0.1);
		}
	} else if (thirdChild == 0) {
		printf("Fourth arg: %s. Process-ID is %d\n", args[4], getpid());
		sleep(1);
		return 2;
	}

	return 0;
}
