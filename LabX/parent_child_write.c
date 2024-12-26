#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    FILE *file;

    file = fopen("pids.txt", "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) { // Error
        perror("fork");
        fclose(file);
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        fprintf(file, "Child PID: %d\n", getpid());
        fclose(file);
    } else { // Parent process
        fprintf(file, "Parent PID: %d\n", getpid());
        fclose(file);
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
