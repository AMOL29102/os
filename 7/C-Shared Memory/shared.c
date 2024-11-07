
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 

  
int main() 
{ 
    // ftok to generate unique key 
    //key_t key = ftok("/homes/oslab/shmfile.txt",65); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget((key_t)65,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("Write Data : "); 
    gets(str); 
  
    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
    while(1);
  
    return 0; 
} 