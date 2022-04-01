#include <stdio.h>

int main(int argCount, char **args) {
	for (int i = 0; i < argCount; i++) {
		printf("[%d]: %s\n", i, *args);
		args++;
	}
	return 0;
}

