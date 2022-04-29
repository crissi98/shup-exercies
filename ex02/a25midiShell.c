#include <stdio.h> 
#include <signal.h> 
#include <string.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

char** splitString(char *toSplit, char *delimiter) {
    int partCount = 1;
    char **result = (char**) malloc(partCount * sizeof(char*));
    char *part = strtok(toSplit, delimiter);
    *result = part;
    while (part != NULL) {
        partCount++;
        part = strtok(NULL, delimiter);
        result = realloc(result, partCount * sizeof(char*));
        result[partCount - 1] = part;
    }
    return result;
}

int main() {
    char **paths = splitString(getenv("PATH"), ":");
    while (1) {
        char buf[1024];
        char *workingDir = getenv("PWD");
        printf("%s>\n", workingDir);
        fgets(buf, 1024, stdin);
        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "schluss") == 0) {
            return 0;
        }
        char **programArgs = splitString(buf, " ");
        char *programName = *programArgs;
        int childProcess = fork();

        if (programName[0] != '.' && programName[0] != '/') {
            int programFound = 0;
            int i = 0;
            while (paths[i] != NULL && programFound == 0) {
                char programNameAtPath[1024];
                strcpy(programNameAtPath, paths[i]);
                strcat(programNameAtPath, "/");
                strcat(programNameAtPath, programName);
                if (access(programNameAtPath, F_OK) == 0) {
                    programName = programNameAtPath;
                    programFound = 1;
                }
                i++;
            }
            
            if (programFound == 0) {
                printf("Program %s does not exist\n", programName);
                continue;
            }
        }

	    if (childProcess == 0) {
		    printf("Starting program %s\n", programName);
		    int started = execv(programName, programArgs);
		    if (started == -1) {
			    printf("Could not start program\n");
		    }
            return 1;
        }

        int status = 0;
	    int childProcessID = wait(&status);
	    printf("Child programm at process %d exited with %d\n\n", childProcessID, status);
        free(programArgs); 
    }
    
	free(paths);
    return 0;
}
