
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 

  
int main() 
{ 
    // ftok to generate unique key 
    //key_t key = ftok("/home/oslab/shmfile1.txt",65); 
    //key_t key = ftok(".",65); correct one
  
    // shmget returns an identifier in shmid 
    int shmid = shmget((key_t)65,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("Data read from memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
    
    // destroy the shared memory 
    //shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 