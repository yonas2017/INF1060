#include "client.h"
#include <stdio.h>
#include <stdint.h>

int getClientMessage(ClientMessagePtr p_message)
{
  /*
	 * Get input from User
	 */
	 char option, numJobs;
   printf("Choose 1 - 4 from the list below:\n\n");
   printf("1 - Get one Job from server.\n");
   printf("2 - Get X number of jobs from server\n");
   printf("3 - Get all jobs from server\n");
   printf("4 - Quit Program\n\n");

   scanf("%c", &option);

   switch(option)
	 {
		 case'1':
		 	printf("Getting one job from the server has been selected.\n");
			p_message->msg_type = GET_JOB;
			p_message->all_jobs = 0;
			p_message->num_jobs = 1;
      break;
     case'2':
			 printf("Enter number of jobs to get from the server:\n");
			 scanf("%c", &numJobs);
       printf("Getting %c job from the server has been selected.\n", numJobs);
			 p_message->msg_type = GET_JOB;
			 p_message->all_jobs = 0;
			 sscanf(&numJobs, "%d", &p_message->num_jobs);
       break;
     case'3':
			 printf("Getting all jobs from the server has been selected.\n");
			 p_message->msg_type = GET_JOB;
			 p_message->all_jobs = 1;
			 p_message->num_jobs = 0;
       break;
     case'4':
       printf("Quiting program.\n");
			 p_message->msg_type = QUIT_PROGRAM;
			 p_message->all_jobs = 0;
			 p_message->num_jobs = 0;
       break;
 		 default:
			 printf("Invald choice  %c\n", option);
			 return -1;
		 }

     return 0;
}

char getJobType(char jobInfo)
{
  uint8_t jobType = (jobInfo >> 5) & 0x07;
  switch(jobType)
  {
    case 0:
      return 'O';
    case 1:
      return 'E';
    case 7:
      return 'Q';
    default:
      return 'X';
  }
}

void releaseResources(ClientPtr p_client)
{
  /*
	* Close Queues
	*/
  queueDestroy(p_client->m_queue[0]);
  queueDestroy(p_client->m_queue[1]);

  /*
  * Close TCP Sockets
  */
  tcpClose(&p_client->m_tcp);

  printf("Resources deallocated properly.\n");
}

/*
int main (){
int pipeends[2];
int pipeends1[2];

pipe(pipeends);
pipe(pipeends1);

pid_t child_a, child_b;

child_a = fork();


if (child_a == 0) {
    // Child A code
void chilld_A();

} else {
    child_b = fork();

    if (child_b == 0) {
        // Child B code
void chilld_B();
    } else {
        // Parent Code
    }
}
void chilld_A(){
	printf("here");
dup2(pipeends[1], 1);
close(pipeends[1]);
close(pipeends[0]);
dup2(pipeends1[0], 0);
}

void chilld_B(){
	printf("hear 2");
dup2(pipeends[1], 1);
close(pipeends[1]);
close(pipeends[0]);
dup2(pipeends1[0], 0);
}

}
*/
