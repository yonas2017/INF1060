
// CMD:./pipe 1> stdout.msg 2> stderr.msg./pipe
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/messages.h"

//
// Connects to Child pipe p,  then it reads data from pipe.
//
void childProcess(int *p, int childId, bool terminateChild);

//
// Connects to Child pipe p, and then writes to the pipe.
//
void parentProcess(int *p, ServerMessagePtr msg);

#define CHILD_ID_A 0
#define CHILD_ID_B 1

// Defines for message types.
#define  JOB_INFO_TYPE_O 'O'
#define  JOB_INFO_TYPE_E 'E'
#define  JOB_INFO_TYPE_Q 'Q'

int main(){     
  int p;

  int pipeClientToChildA[2];   
  int pipeClientToChildB[2];

  ServerMessagePtr msgServ = (ServerMessagePtr ) malloc( sizeof(ServerMessagePtr) );
  msgServ->jobInfo = JOB_INFO_TYPE_O;
  msgServ->jobTextLength = 100;
  strcpy(msgServ->jobText, "123456789.\n");    

  bool terminateChild=false;
  
  p= pipe(pipeClientToChildA);    
  if(p < 0){         
    printf("Error Creating piple for Child A.");  
    _exit(1);   
  }      

  p= pipe(pipeClientToChildB);    
  if(p < 0){         
    printf("Error Creating piple for Child B.");  
    _exit(1);   
  }      

  int fA = fork();    
  if(fA > 0){

    if(msgServ->jobInfo == JOB_INFO_TYPE_Q) {
      terminateChild = true;
    } else if(msgServ->jobInfo == JOB_INFO_TYPE_O) {
      parentProcess(pipeClientToChildA, msgServ);
    } else if(msgServ->jobInfo == JOB_INFO_TYPE_E) {
      parentProcess(pipeClientToChildB, msgServ);
    }
    
  }  
  else if(fA == 0){       
    
    int fB = fork();    
    if(fB > 0){
      childProcess(pipeClientToChildA, CHILD_ID_A, terminateChild);
    }  
    else if(fB== 0){       
      childProcess(pipeClientToChildB, CHILD_ID_B, terminateChild);
    }  
    else{      
      printf("Error creating child process B.");   
    }      
  }  
  else{      
    printf("Error creating child process A.");   
  }      

  return 0;

}


void childProcess(int *p, int childId, bool terminateChild) {

  if(terminateChild) {

    printf("Exiting.\n");   
    exit(0);

  } else {
    
    char readbuffer[1];      

    /* Child process closes up write-side of pipe because it is not used bit the child.*/
    close(p[1]);
  
    /* Child process reads from read-side of pipe, and prints to STDOUT */
    int n;  
    while((n=read(p[0], readbuffer, sizeof(readbuffer))) >= sizeof(readbuffer)) {
      if(childId == CHILD_ID_A) {
	write(STDOUT_FILENO,readbuffer,n);
      } else if(childId == CHILD_ID_B) { 
	write(STDERR_FILENO,readbuffer,n);   
      } else {
	printf("Error unknow child.");   
      }
    }

    while(1);
  }
}

void parentProcess(int *p, ServerMessagePtr msg) {

  //void parentProcess(int *p, char *msg, int msgType) {

  if(msg->jobInfo != JOB_INFO_TYPE_Q) {
    /* Parent process closes up read-side of pipe because it is not used bit the parent. */
    close(p[0]);
    
    /* Parent process writes to write-side of pipe */
    write(p[1], msg->jobText, msg->jobTextLength);   
  }
}

//    FILE *fp;
//    char ch;
//    int info_start=0,info_end=0;
//    if( (fp = fopen("job.txt", "r")) == NULL)
//      fprintf(stderr, "ERROR: job.txt does not exist.\n");
//    
//    while( fscanf(fp, "%c", &ch) == 1) {
//      // fprintf(stdout, "%c", ch);
//
//      //while(1) {
//      int  size_msgA = 1000;
//      char *msgA=(char *)malloc(size_msgA);
//      //strcpy(msgA,"ClientToChildA:STD_OUT.1\n");
//      strcpy(msgA,&ch);
//      parentProcess(pipeClientToChildA,msgA);
//      free(msgA);
//
//      //int  size_msgB = 1000;
//      //char *msgB=(char *)malloc(size_msgB);
//      //strcpy(msgB,"ClientToChildB:STD_OUT.1\n");
//      //parentProcess(pipeClientToChildB,msgB);
//      //free(msgB);
//    }
//
//    fclose(fp);

