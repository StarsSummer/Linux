#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/stat.h>
#define MAXLINE 80

char *args[100][MAXLINE+1];
char cmd[MAXLINE];
int linenum=0;

char setup(){
  memset(cmd, 0, MAXLINE);
  int i=0;
  char a='0';
  while(a!='\n'){
    a=getchar();
    cmd[i]=a; 
    i++;
  }
}

void handler_SIGINT(){
  
}

int main()
{
  int background=0;
  int i;
  struct sigaction handler;
  handler.sa_handler=handler_SIGINT;
  sigaction(SIGINT,&handler,NULL);

  while(1){
    printf("COMMAND->");
    setup();
    if(!strncasecmp(cmd, "exit",4))
      return 0;
    else if(!strncasecmp(cmd, "ls", 2)){
      system(cmd);
    }
    else if(!strncasecmp(cmd, "pwd", 3)){
      system(cmd);
    }
    else if(!strncasecmp(cmd, "fork", 4)){
      background=fork();  
      printf("New Process:%d \n",getpid());
      if(background>0){
        sleep(1);
      }
      else if(background==0){
        exit(0);
      }
    }
  }
}
    
    
 
