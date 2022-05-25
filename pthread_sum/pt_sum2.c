#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int step = 1;

pthread_t *static_pointer = NULL;
long double data = 0;
long double start_number = 1;

void *mythread(void *dummy)
{
    printf("start position is %Lf\n", start_number);
    if (start_number > atoi(dummy))
    {
	return NULL;
    }

    for (long double i = start_number; i < start_number + step; i++)
    {
        data = data + 1.0 / i;
    }

    start_number = start_number + step;

    printf("Now calculation result = %Lf\n\n", data);
    return NULL;
}

int main(int argc, char *argv[], char *envp[])
{

    if (argv[1] == NULL)
    {
        printf("Enter thread amount\n");
        exit(0);
    }

    if (argv[2] == NULL)
    {
        printf("Enter limit number\n");
        exit(0);
    }


    int thread_amount = atoi(argv[1]);
    step = atoi(argv[2])/atoi(argv[1]);

    if (thread_amount < 1)
    {
        printf("Thread amount must be >= 3\n");
        exit(0);
    }

    printf("\nEntered thread amount = %i\n\n", thread_amount);

    pthread_t mainthid;

    if (thread_amount > 2)
    {
        pthread_t *thid = (pthread_t *)malloc(sizeof(pthread_t) * (thread_amount - 1));
        static_pointer = thid;
        int *result = (int *)malloc(sizeof(int) * (thread_amount - 1));

        for (int i = 0; i < thread_amount; i++)
        {
            //printf("CREAT STAT!\n");
            result = pthread_create(thid + i, (pthread_attr_t *)NULL, mythread, argv[2]);
            //printf("CREAT COMPLETED!\n");
            if (result != 0)
            {
                printf("Error on thread create, return value = %d\n", result[i]);
                exit(-1);
            }
            result++;
            //printf("JOIN START\n");
            pthread_join(static_pointer[i], (void **)NULL);
            //printf("JOIN END\n");
        }
    }

    mainthid = pthread_self();

    //printf("Hello from thread (!MAIN_THRAD!)  %lu\n", mainthid);
    printf("Final result is %Lf\n\n", data);

    free(static_pointer);

    return 0;
}