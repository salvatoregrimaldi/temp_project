#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

int *initArray(int N, int range);
void countingSort(int *A, int n);

#define STARTTIME(id)                             \
    clock_t start_time_42_##id, end_time_42_##id; \
    start_time_42_##id = clock()

#define ENDTIME(id, x)          \
    end_time_42_##id = clock(); \
    x = ((double)(end_time_42_##id - start_time_42_##id)) / CLOCKS_PER_SEC

long val;

int main(int argc, char *argv[])
{

    // Parse parameters
    if(argc != 3){
        printf("you must insert the length of array to order and the interval\n");
        exit(EXIT_FAILURE);
    }


    srand(time(NULL));
    long n;
    double time_init=0, time_count=0;
    n = atoi(argv[1]);   //array langth
    val = atoi(argv[2]); //max value of element in array


    int *A;

    /*
    for(int i=0; i<n; i++)
        printf("%d ",A[i]);
    printf("\n");*/

    STARTTIME(0);

    A = initArray(n, val);

    ENDTIME(0, time_init);
    
    /*
    for(int i=0; i<n; i++)
        printf("%d ",A[i]);
    printf("\n");*/


    STARTTIME(1);

    countingSort(A, n);

    ENDTIME(1, time_count);


    printf("1;%f;%f\n", time_init, time_count);
    /*for(int i=0; i<n; i++)
        printf("%d ",A[i]);*/

    free(A);


    return 0;
}

/**
 * @brief initArray is a function that make it used to initialize a random array
 * 
 * @param N id the dim of array 
 * @param range is the max num of array
 * @return int* array initialized
 */
int *initArray(int N, int range){
    int *A;
    if ((A = malloc(N * sizeof(int))) == NULL)
        exit(1);


    for (int i = 0; i < N; i++)
        A[i] = rand() % range;
    
    return A;
}

/**
 * @brief countingSort is the fnction that order the array A using the counting sort algorithm
 * 
 * @param A is the array
 * @param n is the dim of array A
 */
void countingSort(int *A, int n)
{

    /*
    for(int i = 0; i < myDim; i++)
        printf("io sono %d: %d\n", rank, Rcv[i]);*/

    int local_min = A[0];
    int local_max = A[0];

    for(int i = 0; i < n; i++)
        if (A[i] > local_max)
            local_max = A[i];
        else if (A[i] < local_min)
            local_min = A[i];

    int *C_local;
    int lenC_local = local_max - local_min + 1;
    if ((C_local = malloc(lenC_local * sizeof(int))) == NULL)
        exit(1);

    for (int i = 0; i < lenC_local; i++)
        C_local[i] = 0;

    for (int i = 0; i < n; i++)
        C_local[A[i] - local_min] += 1; 

    for (int i = 1; i < lenC_local; i++)
        C_local[i] += C_local[i - 1];
    

    int p;


    for (int j = 0; j < lenC_local; j++)
    {
        if (j == 0)
            p = 0;
        else
            p = C_local[j - 1];

        for (int x = p; x < C_local[j]; x++)
        {
            A[x] = j + local_min;
        }
    }

    free(C_local);

}
