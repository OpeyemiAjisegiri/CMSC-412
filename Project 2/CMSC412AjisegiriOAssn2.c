#include <stdio.h>
int main()
{
  int pid, status, a;
  pid = fork();
  if(pid == 0){
    a = getppid();
    pid = fork();
    if (pid == 0){
      printf("I am the child process C, and my pid is %d, my parent's process id is %d. My grandparent pid is %d\n\n", getpid(), getppid(), a);
    }
    else{
      wait(&status);
      printf("I am the parent process P, and my pid is %d. My parent G has pid %d.\n\n", getpid(), getppid());
    }
  }
  else{
    //sleep(2);
    wait(&status);
    printf("I am the grandparent G, and my process id is  %d.\n", getpid());
  }
}