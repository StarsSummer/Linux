#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>
class Node
{
    public:
        int num;
        Node* next;
};
Node* head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

class Mm
{
    public:
        Mm(){
            pthread_t pro;
            pthread_t con;
            head=NULL;
            int err;
            err = pthread_create(&pro, NULL, mallocos,NULL);
            err = pthread_create(&con, NULL, freeos,NULL);
            pthread_join(pro, NULL);
            pthread_join(con, NULL);
        };
        void *mallocos(){
            while(1)
            {
                avail=(Node*)malloc(sizeof(Node));
                avail->num=rand()%100+1;
                printf("produce %d\n",avail->num);
                pthread_mutex_lock(&mutex);
                avail->next=head;
                head=avail;
                pthread_mutex_unlock(&mutex);
                pthread_cond_signal(&cond);
                sleep(1);
            }
        };
        void *freeos(){
            while(1)
            {
                pthread_mutex_lock(&mutex);
                if (NULL == head)
                    pthread_cond_wait(&cond, &mutex);
                avail = head;
                if (avail->next)
                {
                    while (avail->next)
                    {
                        alloc = avail;
                        avail = avail->next;
                    }
                printf("Consume %d\n", avail->num);
                free(avail);
                alloc->next = avail = NULL;
                }
                else
                {
                    printf("Consume %d\n", avail->num);
                    free(avail);
                    head = avail = NULL; /// < 必须的，且注意head！
                }
                pthread_mutex_unlock(&mutex);
                sleep(1);
            }
        };
    private:
        char* memory;
        Node* avail;
        Node* alloc;
};

int main(){
    Mm model;
    return 0;
}
