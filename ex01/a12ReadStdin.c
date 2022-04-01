#include <stdio.h>
#include <stdlib.h>

int main(int argCount, char **args) {
	if (argCount != 2) {
		printf("no number of names provided");
		return 1;
	}
	args++;
	int nameCount = atoi(*args);
	printf("Enter %d names\n", nameCount);
	char **buf = (char**) malloc(nameCount * sizeof(char*));

	for (int i = 0; i < nameCount; i++) {
		char *str = (char*) malloc(10);
		scanf("%9s", str);
		*buf = str;
		buf++;
		fflush(stdin);
	}

	printf("\nOutput:\n");
	for (int i = nameCount; i > 0; i--) {
		buf--;
		printf("%s\n", *buf);
		free(*buf);
	}
	free(buf);
	return 0;	
}
