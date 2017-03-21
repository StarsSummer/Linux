#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
void hanshu(){
  FILE *f;
  f=fopen("system","a");
  fclose(f);
}

int main(){
  struct timeval start1,end1;
  gettimeofday(&start1,NULL);
  int i=1;
  while(i<10000)
  {
    i++;
    hanshu();
  } 
  printf("\nNot system completed!");
  gettimeofday(&end1,NULL);
  int time1=end1.tv_usec-start1.tv_usec;

  struct timeval start2,end2;
  gettimeofday(&start2,NULL);
  int j=1;
  while(j<100000)
  {
    j++;
    getpid();
  } 
  printf("\nSystem completed!");
  gettimeofday(&end2,NULL);
  int time2=end2.tv_usec-start2.tv_usec;
  printf("\nthe time1 is %d\n",time1*1000);
  printf("the time2 is %d\n",time2*1000);
  int k=time1/time2;
  printf("the k id %d\n",k);
  return 0;
}
