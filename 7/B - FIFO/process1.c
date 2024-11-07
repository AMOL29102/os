// process1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUFFER_SIZE 1024

int main()
{
    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    // Create FIFOs
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    // Prompt user for input
    printf("Enter sentences (type 'exit' to quit):\n");

    while (1)
    {
        // Accept input sentence from the user
        printf("> ");
        fgets(input, BUFFER_SIZE, stdin);

        // Exit if the user types "exit"
        if (strncmp(input, "exit", 4) == 0)
        {
            break;
        }

        // Open fifo1 in write mode and write the input sentence to it
        int fd1 = open(FIFO1, O_WRONLY);
        write(fd1, input, strlen(input) + 1);
        close(fd1);

        // Open fifo2 in read mode to receive the result from process2
        int fd2 = open(FIFO2, O_RDONLY);
        read(fd2, output, BUFFER_SIZE);
        close(fd2);

        // Display the result
        printf("Result from Process 2:\n%s\n", output);
    }

    // Remove the FIFOs after completion
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}