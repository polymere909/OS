#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) { // Child process
            printf("Child process with PID: %d\n", getpid());
            return 0; // Prevent child from forking again
        }
    }
    // Parent process waits for all children to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("Parent process with PID: %d\n", getpid());
    return 0;
}
