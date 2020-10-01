#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int a = 0;

void *func(void *var)
{
    int *id=(int *)var;
    static int b=0;
    b=7;
    printf("the id of the thread is: %d\n", *id);
    printf("the value if a is: %d\n", a);
    printf("the value of b is: %d\n", b);
}

int main()
{
    pthread_t th_id;
    for(int i=0; i<9; i++)
    {
        pthread_create(&th_id, NULL, func, (void*)&th_id);
        pthread_join(th_id,NULL);
    }
    pthread_exit(NULL);
    return 0;
}
