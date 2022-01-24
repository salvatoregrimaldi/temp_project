#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "countingsort.h"


void init(int n, int n_ranks, int rank, int range, int *full_vector){
    int *recvcounts;
    int *displ;
    int dim;
    int *piece_init_vect;
    int i;

    int quoz = n / n_ranks;

    // L'inizializzazione randomica del vettore viene equamente distribuita tra i processi

    if (rank >= 0 && rank < n_ranks - 1)
        dim = quoz;

    if (rank == n_ranks - 1)
        dim = quoz + n % n_ranks;

    recvcounts = (int *)malloc(n_ranks * sizeof(int));
    displ = (int *)malloc(n_ranks * sizeof(int));
    for (i = 0; i < n_ranks; i++)
    {
        displ[i] = i * quoz;

        if (i == n_ranks - 1)
            recvcounts[i] = quoz + n % n_ranks;
        else
            recvcounts[i] = quoz;
    }

    piece_init_vect = (int *)malloc(dim * sizeof(int));

    for (i = 0; i < dim; i++)
        piece_init_vect[i] = rand() % range;
    
    MPI_Gatherv(piece_init_vect, dim, MPI_INT, full_vector, recvcounts, displ, MPI_INT, 0, MPI_COMM_WORLD);
    
    free(recvcounts);
    free(displ);
    free(piece_init_vect);
}












void countingSort(int n, int n_ranks, int rank, int *full_vector){
    int local_min = INT_MAX;
    int local_max = INT_MIN;
    int min;
    int max;
    int i;
    int dim;
    int quoz;
    int *piece_of_vector;
    int *c_local;
    int *c;
    int *sendcounts;
    int *displ;
    int lenC;

    quoz = n / n_ranks;


    if (rank >= 0 && rank < n_ranks - 1)
        dim = quoz;

    if (rank == n_ranks - 1)
        dim = quoz + n % n_ranks;

    
    displ = (int *)malloc(n_ranks * sizeof(int));
    sendcounts = (int *)malloc(n_ranks * sizeof(int));

    for (i = 0; i < n_ranks; i++)
    {
        displ[i] = i * quoz;
        if (i == n_ranks - 1)
            sendcounts[i] = quoz + n % n_ranks;
        else
            sendcounts[i] = quoz;
    }

    piece_of_vector = (int *)malloc(sendcounts[rank] * sizeof(int));

    MPI_Scatterv(full_vector, sendcounts, displ, MPI_INT, piece_of_vector, sendcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    /*-------------------------------MIN E MAX-------------------------------------------------------------*/
    for (i = 0; i < dim; i++)
    {
        if (piece_of_vector[i] < local_min)
            local_min = piece_of_vector[i];
        else if (piece_of_vector[i] > local_max)
            local_max = piece_of_vector[i];
    }

    MPI_Allreduce(&local_min, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&local_max, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    /*----------------------------------------------------------------------------------------------------*/

    /*--------------------------COMPUTE C------------------------------------------------------------------*/
    lenC = max - min + 1;
    c_local = (int *)malloc(lenC * sizeof(int));
    for (i = 0; i < lenC; i++)
        c_local[i] = 0;

    for (i = 0; i < dim; i++)
        c_local[piece_of_vector[i] - min] += 1;

    for (i = 1; i < lenC; i++)
        c_local[i] += c_local[i - 1];

    if (rank == 0)
        c = (int *)malloc(lenC * sizeof(int));

    free(piece_of_vector);
    free(sendcounts);
    free(displ);

    MPI_Reduce(c_local, c, lenC, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    free(c_local);
    /*-----------------------------------------------------------------------------------------------------*/

    /*CAPIRE COME FUNZIONA SU CARTA IL SEGUENTE PEZZO DI ALGORITMO NON PARALLELIZZABILE*/
    /*----------------------------------------------------------------------------------------------------*/
    if (rank == 0)
    {
        int p;

        for (int j = 0; j < lenC; j++)
        {
            if (j == 0)
                p = 0;
            else
                p = c[j - 1];

            for (int x = p; x < c[j]; x++)
            {
                full_vector[x] = j + min;
            }
        }
    free(c);
    }

}
