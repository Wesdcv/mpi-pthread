#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t *static_pointer = NULL;
int data;
int number = 0;


void *mythread (void *dummy)
{

    pthread_t mainthid;
    int num  = *(int*)dummy;
    while (num != number) {}

    mainthid = pthread_self();
    printf ("Hello from thread %i\n", number);

    printf ("Calculation result = %i\n\n", data);
    data *= 2;
    number++;

    return NULL;
}

int main (int argc, char *argv[], char *envp[])
{

    if (argv[1] == NULL)
    {
        printf ("Enter thread amount\n\n");
        exit (0);
    }

    int thread_amount = atoi (argv[1]);

    if (thread_amount < 1)
    {
        printf ("Thread amount must be >= 3\n");
        exit (0);
    }

    printf ("\nEntered thread amount = %i\n\n", thread_amount);

    pthread_t mainthid;
    data = 1;


    if (thread_amount > 2)
    {
        pthread_t *thid = (pthread_t *) malloc (sizeof (pthread_t) * (thread_amount) );
        static_pointer = thid;
        int *result = (int *) malloc (sizeof (int) * (thread_amount) );

        for (int i = 0; i < thread_amount; i++)
        {
            //printf("CREAT STAT!\n");
            result = pthread_create (thid + i, (pthread_attr_t *) NULL, mythread, &i);
            //printf("CREAT COMPLETED!\n");
            if (result != 0)
            {
                printf ("Error on thread create, return value = %d\n", result[i]);
                exit (-1);
            }

            //printf("JOIN START\n");
            pthread_join (static_pointer[i], (void **) NULL);
            //printf("JOIN END\n");
        }
    }

    free (static_pointer);

    return 0;
}
