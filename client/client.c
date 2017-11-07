#include "client.h"
#include <stdio.h>
#include <unistd.h>


int main (){
int pipeends[2];
int pipeends1[2];

pipe(pipeends);
pipe(pipeends1);

pid_t child_a, child_b;

child_a = fork();


if (child_a == 0) {
    /* Child A code */
void chilld_A();

} else {
    child_b = fork();

    if (child_b == 0) {
        /* Child B code */
void chilld_B();
    } else {
        /* Parent Code */
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
