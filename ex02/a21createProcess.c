#include <unistd.h>
#include <stdio.h>

int main() {
	fork();
	
	printf("Process-ID: %d; Parent Process-ID: %d\n", getpid(), getppid());

	while (1) {}

	return 0;
}
