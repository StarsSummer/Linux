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

char *args[100][MAXLINE];
int linenum=0;


void setup()
{
  char a;
  int i=0;
  while(1){
    args[linenum][i]=(char*)malloc(10);
    scanf("%s",args[linenum][i]);
    a=getchar();
    if(a=='\n')
      break;
    else
      ungetc(a,stdin);
    i++;
  }
  args[linenum][i+1]=NULL;
}

void handler_SIGINT(){
  linenum--;
  int begin,i;
  printf("\nHistory:\n");
  if(linenum<10)
    begin=0;
  else
    begin=linenum-9;
  while(begin<=linenum){
    for(i=0;args[begin][i]!=NULL;i++){
      printf("%s",args[begin][i]);
    }
    begin++;
    printf("\n");
  }
  int num;
  while(1){
    char order[3]={' '};
    read(STDIN_FILENO,order,3);
    if(order[0]=='r' && order[2]==' '){
      num=linenum;
      linenum++;
      int j=0;
      while(args[num][j]!=NULL){
        args[linenum][j]=(char*)malloc(MAXLINE);
        args[linenum][j]=args[num][j];
        j++;
      }
      break;
    }
    else if(order[0]='r' && order[2]>'0' && order[2]<='9'){
      num=order[2]-'0'-1;
      linenum++;
      int j=0;
      while(args[num][j]!=NULL){
        args[linenum][j]=(char*)malloc(MAXLINE);
        args[linenum][j]=args[num][j];
        j++;
      }
      break; 
    }
    else{
      printf("Wrong command");
      break;
    }
  }
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
    background=fork();  
    if(!strncasecmp(*args[linenum], "exit", 4)){
      return 0; 
    }
    else{
      if(background>0){
        wait(0);
      }
      else if(background==0){
        printf("New Process:%d \n",getpid());
        execvp(args[linenum][0],args[linenum]);
        exit(0);
      }
      linenum++;
    }
  }
}
    
    
 
