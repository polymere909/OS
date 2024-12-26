#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[30];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        printf("Child process PID: %d\n", getpid());
        close(fd[1]); // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    } else { // Parent process
        printf("Parent process PID: %d, Created Child PID: %d\n", getpid(), pid);
        close(fd[0]); // Close read end
        write(fd[1], "Hello from parent", 17);
        close(fd[1]);
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
