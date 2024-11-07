#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0;         // Shared data
int reader_count = 0; // Number of active readers

pthread_mutex_t mutex; // Mutex for reader count
sem_t rw_mutex;        // Semaphore for read-write lock

// Function for readers
void *reader(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        // Lock to modify reader_count
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1)
        {
            // First reader locks the rw_mutex for writers
            sem_wait(&rw_mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Reading data
        printf("Reader %d: read data = %d\n", id, data);
        sleep(1); // Simulate time taken to read

        // Lock to modify reader_count
        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0)
        {
            // Last reader releases the rw_mutex
            sem_post(&rw_mutex);
        }
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate time before next read
    }
}

// Function for writers
void *writer(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        // Writer waits for exclusive access
        sem_wait(&rw_mutex);

        // Writing data
        data++;
        printf("Writer %d: wrote data = %d\n", id, data);
        sleep(1); // Simulate time taken to write

        // Release exclusive access for other writers or readers
        sem_post(&rw_mutex);

        sleep(1); // Simulate time before next write
    }
}

int main()
{
    pthread_t readers[5], writers[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    // Initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++)
    {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for threads to finish (though in this example, they run infinitely)
    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}