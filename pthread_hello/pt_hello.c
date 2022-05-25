#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t *static_pointer = NULL;

void *mythread (void *dummy)

{

    pthread_t mainthid;

    mainthid = pthread_self();

    printf ("Hello from thread %lu\n", mainthid);

    return NULL;
}

int main (int argc, char *argv[], char *envp[])
{

    if (argv[1] == NULL)
    {
        printf ("Enter thread amount\n");
        exit (0);
    }

    int thread_amount = atoi (argv[1]);

    printf ("\nEntered thread amount = %i\n\n", thread_amount);

    pthread_t mainthid;

    if (thread_amount > 1)
    {
        pthread_t *thid = (pthread_t *) malloc (sizeof (pthread_t) * (thread_amount - 1) );
        static_pointer = thid;
        int *result = (int *) malloc (sizeof (int) * (thread_amount - 1) );

        for (int i = 0; i < thread_amount - 1; i++)
        {
            result = pthread_create (thid + i, (pthread_attr_t *) NULL, mythread, NULL);
            if (result != 0)
            {
                printf ("Error on thread create, return value = %d\n", result[i]);
                exit (-1);
            }
            result++;
        }
    }

    mainthid = pthread_self();

    printf ("Hello from main thread %lu\n", mainthid);

    for (int i = 0; i < thread_amount - 1; i++)
    {
        pthread_join (static_pointer[i], (void **) NULL);
    }

    free (static_pointer);

    return 0;
}