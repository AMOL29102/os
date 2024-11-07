// process2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define BUFFER_SIZE 1024
#define OUTPUT_FILE "output.txt"

// Function to count characters, words, and lines
void count_text(const char *text, int *char_count, int *word_count, int *line_count)
{
    *char_count = *word_count = *line_count = 0;
    int in_word = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        (*char_count)++;

        if (text[i] == '\n')
        {
            (*line_count)++;
        }

        if (isspace(text[i]))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            (*word_count)++;
        }
    }
    if (*char_count > 0 && text[*char_count - 1] != '\n')
    {
        (*line_count)++;
    }
}

int main()
{
    char buffer[BUFFER_SIZE];
    int char_count, word_count, line_count;

    // Ensure the output file is empty initially
    FILE *file = fopen(OUTPUT_FILE, "w");
    if (file != NULL)
    {
        fclose(file);
    }

    while (1)
    {
        // Open fifo1 in read mode to read the input sentence from process1
        int fd1 = open(FIFO1, O_RDONLY);
        read(fd1, buffer, BUFFER_SIZE);
        close(fd1);

        // Count characters, words, and lines
        count_text(buffer, &char_count, &word_count, &line_count);

        // Write the counts to the output file
        file = fopen(OUTPUT_FILE, "w");
        if (file == NULL)
        {
            perror("fopen failed");
            exit(1);
        }
        fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", char_count, word_count, line_count);
        fclose(file);

        // Read the content of the output file to send back to process1
        file = fopen(OUTPUT_FILE, "r");
        if (file == NULL)
        {
            perror("fopen failed");
            exit(1);
        }
        fread(buffer, sizeof(char), BUFFER_SIZE, file);
        fclose(file);

        // Open fifo2 in write mode and write the result to it
        int fd2 = open(FIFO2, O_WRONLY);
        write(fd2, buffer, strlen(buffer) + 1);
        close(fd2);
    }

    return 0;
}