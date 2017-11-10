#include "client.h"
#include "queue.h"
#include "tcp.h"

#include <messages.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

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

static void help()
{
	printf("./client <ip> <port>\n");
	printf("	<ip>   : Client IP Adress.\n");
	printf("	<port> : Client Port.\n");
}


int main(int argc, char* argv [])
{
	printf("Client Started\n");

	/*
	 * Check number of arguments passed by user.
	 */
	if(argc < 3)
	{
		help();
		return -1;
	}

	/*
	* Create the client object
	*/
	struct Client client;

	/*
	 * Open TCP Socket
	 */
	client.m_tcp.m_ip = argv[1];
	sscanf(argv[2], "%d", &client.m_tcp.m_port);

	if(tcpOpen(&client.m_tcp) != 0)
	{
		return -1;
	}

	/*
	 * Create Two Queues for the childs
	 */
	int queueSize = 16;
	client.m_queue[0] = queueCreate(queueSize);
	client.m_queue[1] = queueCreate(queueSize);

	/*
	 * Get Client Message
	 */
	if(getClientMessage(&client.m_clientMessage) != 0)
	{
		releaseResources(&client);
		return -1;
	}

	/*
	* Send client messsage to server
	*/
	tcpSend(&client.m_tcp, &client.m_clientMessage);

	/*
	* Receive server message
	*/
	while(tcpReceive(&client.m_tcp, &client.m_serverMessage))
	{
		/*
		* Get Job Type
		*/
		char jobType = getJobType(client.m_serverMessage.JobInfo);
		printf("jobType: %c\n", jobType);
		printf("%s\n", client.m_serverMessage.JobTekst);
		switch(jobType)
		{
			case 'O':
			  /*
			   * Enqueue message for child 1
			   */
				enqueue(client.m_queue[0], &client.m_serverMessage);
				break;
			case 'E':
			  /*
			   * Enqueue message for child 2
			   */
				enqueue(client.m_queue[1], &client.m_serverMessage);
				break;
			case 'Q':
			 /*
			  * Enqueue message for both childs
			  */
				enqueue(client.m_queue[0], &client.m_serverMessage);
				enqueue(client.m_queue[1], &client.m_serverMessage);
				break;
			default:
				printf("Wrong Job Type: %c\n", jobType);
				releaseResources(&client);
				return -1;
		}
	}

	/*
	* Release resources
	*/
	releaseResources(&client);
	
	  char option;
	  int numJobs;
	  printf("1 - Get one Job from server.\n");
	  printf("2 - Get X number of jobs from the server\n");
	  printf("3 - Get all jobs from the server\n");
	  printf("4 - Quit Program\n\n");
	  
	  scanf("%c", &option);
	  
	  switch(option)
	    {
	    case'1':
	      printf("Getting one job from the server has been selected.\n");
	      break;
	    case'2':
	      printf("Enter number of jobs to get from the server:\n");
	      scanf("%d", &numJobs);
	      //void message();
	      break;
	    case'3':
	      printf("Getting all jobs from the server has been selected.\n");
	      break;
	    case'4':
	      printf("Quiting program.\n");
	      break;
	    default:
	      printf("Invald choice  %d\n", option);
	      return -1;
	    }
	  
	  /*
	   * Fork section
	   */
	  
	  
	  int p;
	  
	  int pipeClientToChildA[2];   
	  int pipeClientToChildB[2];
	  
	  ServerMessagePtr msgServ = (ServerMessagePtr) malloc( sizeof(ServerMessagePtr) );
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

    while(1); //fixme:remove when you code is complete
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
