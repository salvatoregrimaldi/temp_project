#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "countingsort.h"

int main(int argc, char *argv[]){

    int rank, n_ranks, range;
    int *full_vector;
    double read_start_time, time_init, time_count;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);


    if(argc != 3){
        if(rank == 0) 
            printf("ERRORE! OCCORRE INSERIRE LA LUNGHEZZA DEL VETTORE ED IL MASSIMO INTERO ACCETTABILE NEL VETTORE\n");
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }


    srand(time(NULL));
    int n;
    double time, start, end;
    n = atoi(argv[1]);   //lunghezza del vettore
    range = atoi(argv[2]); //massimo intero accettabile nel vettore


    if(rank == 0){
        read_start_time = MPI_Wtime();
        //allocazione dello spazio necessario per il vettore
        full_vector = (int *)malloc(n * sizeof(int));
    }



    //inizializzazione parallelizzata del vettore
    init(n, n_ranks, rank, range, full_vector);



    if(rank==0){
        time_init = MPI_Wtime() - read_start_time;

        //Stampa vettore iniziale
        for(int i=0; i<n; i++)
            printf("%d ",full_vector[i]);
        printf("\n\n");

        read_start_time = MPI_Wtime();
    }

   //esecuzione dell'algoritmo di ordinamento
   countingSort(n, n_ranks, rank, full_vector);


    if(rank == 0){

        //Stampa vettore finale
        for (int i = 0; i < n; i++)
            printf("%d ", full_vector[i]);
        printf("\n\n");

        time_count = MPI_Wtime() - read_start_time;
        printf("%d;%f;%f\n", n_ranks, time_init, time_count);
        free(full_vector);
    }

    MPI_Finalize();

}