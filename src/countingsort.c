/* 
 * Course: High Performance Computing 2021/2022
 * 
 * Lecturer: Francesco Moscato	fmoscato@unisa.it
 *
 * Group:
 * Salvatore Grimaldi  0622701742  s.grimaldi29@studenti.unisa.it              
 * Enrico Maria Di Mauro  0622701706  e.dimauro5@studenti.unisa.it
 * Allegra Cuzzocrea  0622701707  a.cuzzocrea2@studenti.unisa.it
 * 
 * 
 * Copyright (C) 2021 - All Rights Reserved 
 *
 * This file is part of Contest-MPI.
 *
 * Contest-MPI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Contest-MPI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Contest-MPI.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
  @file countingsort.c
  @brief This is the file .c that contains the functions that are called in the main
  @copyright Copyright (c) 2021
*/

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "countingsort.h"

/**
 * @brief This function initialize randomly the array 'full_array' distributing the computation among the processes.
 * @param n             number of array elements.
 * @param n_ranks       number of ranks.
 * @param rank          rank of the current process.
 * @param range         maximum acceptable integer.
 * @param full_array    pointer to the array.
 */
void init(int n, int n_ranks, int rank, int range, int *full_array)
{
    int *recvcounts;
    int *displ;
    int dim;
    int *piece_init_vect;
    int i;

    int quoz = n / n_ranks;

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

    MPI_Gatherv(piece_init_vect, dim, MPI_INT, full_array, recvcounts, displ, MPI_INT, 0, MPI_COMM_WORLD);

    free(recvcounts);
    free(displ);
    free(piece_init_vect);
}







/**
 * @brief This function sorts the array 'full_array' using Counting Sort Algorithm distributing the computation among the processes.
 * @param n             number of array elements.
 * @param n_ranks       number of ranks.
 * @param rank          rank of the current process.
 * @param full_array    pointer to the unsorted array.
 */
void countingSort(int n, int n_ranks, int rank, int *full_array)
{
    int local_min = INT_MAX;
    int local_max = INT_MIN;
    int min;
    int max;
    int i;
    int dim;
    int quoz;
    int *piece_of_array;
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

    piece_of_array = (int *)malloc(sendcounts[rank] * sizeof(int));

    MPI_Scatterv(full_array, sendcounts, displ, MPI_INT, piece_of_array, sendcounts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    /*-------------------------------MIN E MAX-------------------------------------------------------------*/
    for (i = 0; i < dim; i++)
    {
        if (piece_of_array[i] < local_min)
            local_min = piece_of_array[i];
        else if (piece_of_array[i] > local_max)
            local_max = piece_of_array[i];
    }

    MPI_Allreduce(&local_min, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&local_max, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    /*-----------------------------------------------------------------------------------------------------*/

    /*-------------------------------COMPUTE C-------------------------------------------------------------*/
    lenC = max - min + 1;
    c_local = (int *)malloc(lenC * sizeof(int));
    for (i = 0; i < lenC; i++)
        c_local[i] = 0;

    for (i = 0; i < dim; i++)
        c_local[piece_of_array[i] - min] += 1;

    for (i = 1; i < lenC; i++)
        c_local[i] += c_local[i - 1];

    if (rank == 0)
        c = (int *)malloc(lenC * sizeof(int));

    free(piece_of_array);
    free(sendcounts);
    free(displ);

    MPI_Reduce(c_local, c, lenC, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    free(c_local);
    /*-----------------------------------------------------------------------------------------------------*/
    
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
                full_array[x] = j + min;
            }
        }
        free(c);
    }
}
