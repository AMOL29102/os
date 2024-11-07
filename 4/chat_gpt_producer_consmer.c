  #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0; // Indices for producers and consumers

sem_t empty;           // Semaphore to track empty slots
sem_t full;            // Semaphore to track filled slots
pthread_mutex_t mutex; // Mutex to protect critical section

// Function for the producer
void *producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100; // Produce an item (a random number)

        // Wait if buffer is full
        sem_wait(&empty);

        // Lock to enter critical section
        pthread_mutex_lock(&mutex);

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Update index for next producer

        // Unlock after exiting critical section
        pthread_mutex_unlock(&mutex);

        // Signal that buffer is not empty
        sem_post(&full);

        sleep(1); // Simulate time taken to produce
    }
}

// Function for the consumer
void *consumer(void *arg)
{
    int item;
    while (1)
    {
        // Wait if buffer is empty
        sem_wait(&full);

        // Lock to enter critical section
        pthread_mutex_lock(&mutex);

        // Remove an item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Update index for next consumer

        // Unlock after exiting critical section
        pthread_mutex_unlock(&mutex);

        // Signal that buffer has an empty slot
        sem_post(&empty);

        sleep(1); // Simulate time taken to consume
    }
}

int main()
{
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // All buffer slots are empty initially
    sem_init(&full, 0, 0);            // No slots are full initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}