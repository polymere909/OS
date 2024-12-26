#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigusr1_handler(int sig) {
    printf("Child received SIGUSR1 (signal %d).\n", sig);
}

int main() {
    pid_t pid;

    pid = fork();

    if (pid == -1) { // Error
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
            perror("signal");
            exit(EXIT_FAILURE);
        }
        printf("Child process ID: %d. Waiting for SIGUSR1...\n", getpid());
        while (1) {
            pause(); // Wait for signals
        }
    } else { // Parent process
        printf("Parent process ID: %d. Child PID: %d\n", getpid(), pid);
        sleep(3); // Sleep for 3 seconds before sending SIGUSR1
        printf("Parent sending SIGUSR1 to child.\n");
        kill(pid, SIGUSR1);
        sleep(1); // Wait for child to handle the signal
        kill(pid, SIGTERM); // Terminate the child process
        wait(NULL); // Wait for the child process to terminate
        printf("Child process terminated.\n");
    }

    return 0;
}
