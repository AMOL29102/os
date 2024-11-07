// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main()
{
    // Generate a unique key for the shared memory segment
    key_t key = ftok("shmfile", 65);

    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment to the writer's address space
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    // Write data to shared memory
    char *message = "Hello from the writer process!";
    printf("Writer: Writing data to shared memory: \"%s\"\n", message);
    strncpy(shared_memory, message, SHM_SIZE);

    // Detach from shared memory
    shmdt(shared_memory);

    return 0;
}