#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int signalsReceived = 0;

void handleSignal(int signal) {
	signalsReceived++;
	if (signal == SIGINT) {
		printf("SIGINT received\n");
	} else if (signal == SIGTERM) {
		printf("SIGTERM received\n");
	}

	if (signalsReceived >= 3) {
		printf("Terminating since I received third signal\n");
		_exit(5);
	}
} 

int main() {
	printf("Signal reacter started with PID %d\n", getpid());
	printf("I am reacting to SIGINT and SIGTERM and logging out if I receive the signal.\n");
	printf("I am exiting with return code 5  when I received three signals\n");

	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);

	while (1) {
		sleep(1);
	}
	
	return 0;
}
