// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main()
{
    // Generate the same unique key as in the writer
    key_t key = ftok("shmfile", 65);

    // Access the shared memory segment created by the writer
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment to the reader's address space
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    // Read and display data from shared memory
    printf("Reader: Reading data from shared memory: \"%s\"\n", shared_memory);

    // Detach from shared memory
    shmdt(shared_memory);

    // Remove the shared memory segment after reading
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}