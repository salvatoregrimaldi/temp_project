/* 
 * Course: High Performance Computing 2021/2022
 * 
 * Lecturer: Francesco Moscato	fmoscato@unisa.it
 *
 * Group:
 * Salvatore Grimaldi       0622701742      s.grimaldi29@studenti.unisa.it              
 * Enrico Maria Di Mauro    0622701706      e.dimauro5@studenti.unisa.it
 * Allegra Cuzzocrea        0622701707      a.cuzzocrea2@studenti.unisa.it
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
#include <time.h>

/**
 * @brief This is the function that writes in the file 'file_name' 'n' integers distributing the computation among the processes.
 * @param n             number of array elements.
 * @param n_ranks       number of ranks.
 * @param rank          rank of the current process.
 * @param range         maximum acceptable integer.
 * @param file_name     file name.
 */
void init(int n, int n_ranks, int rank, int range, char *file_name)
{
    int dim, i;
    MPI_File fh;
    MPI_Offset disp;
    int *piece_init_array;
    int quoz = n / n_ranks;

    if (rank >= 0 && rank < n_ranks - 1)
        dim = quoz;

    if (rank == n_ranks - 1)
        dim = quoz + n % n_ranks;

    piece_init_array = (int *)malloc(dim * sizeof(int));

    for (i = 0; i < dim; i++)
        piece_init_array[i] = rand() % (range + 1);

    // Delete, re-open file and write
    MPI_File_delete(file_name, MPI_INFO_NULL);
    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

    disp = rank * quoz * sizeof(int);
    MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    MPI_File_write(fh, piece_init_array, dim, MPI_INT, MPI_STATUS_IGNORE);

    free(piece_init_array);

    MPI_File_close(&fh);
}

/**
 * @brief This is the function that sorts the integers in 'file_name' using Counting Sort Algorithm and distributing the computation among the processes.
 * @param n             number of array elements.
 * @param n_ranks       number of ranks.
 * @param rank          rank of the current process.
 * @param file_name     file name.
 */
void countingSort(int n, int n_ranks, int rank, char *file_name)
{
    MPI_File fh;
    int dim;
    int quoz = n / n_ranks;
    int *piece_of_array;
    int disp;
    int i;
    int local_min = INT_MAX;
    int local_max = INT_MIN;
    int min;
    int max;
    int *c_local;
    int *c;
    int *full_array;
    int lenC;

    /*--------------------READING ARRAY FROM FILE------------------------------------------------------*/

    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

    disp = rank * quoz * sizeof(int);
    MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);

    if (rank >= 0 && rank < n_ranks - 1)
    {
        dim = quoz;
        piece_of_array = (int *)malloc(dim * sizeof(int));
        MPI_File_read(fh, piece_of_array, dim, MPI_INT, MPI_STATUS_IGNORE);
    }

    if (rank == n_ranks - 1)
    {
        dim = quoz + n % n_ranks;
        piece_of_array = (int *)malloc(dim * sizeof(int));
        MPI_File_read(fh, piece_of_array, dim, MPI_INT, MPI_STATUS_IGNORE);
    }
    /*----------------------------------------------------------------------------------------------------*/

    /*-------------------------------MIN E MAX-------------------------------------------------------------*/
    for (i = 0; i < dim; i++)
    {
        if (piece_of_array[i] < local_min)
            local_min = piece_of_array[i];
        if (piece_of_array[i] > local_max)
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

    MPI_Reduce(c_local, c, lenC, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    free(c_local);

    /*----------------------------------------------------------------------*/

    if (rank == 0)
    {
        full_array = (int *)malloc(n * sizeof(int));

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

        MPI_File_seek(fh, 0, MPI_SEEK_SET);
        MPI_File_write(fh, full_array, n, MPI_INT, MPI_STATUS_IGNORE);
        free(full_array);
    }

    MPI_File_close(&fh);
}

/**
 * @brief This is the function that reads the integers in 'file_name' and prints them on stdout.
 * @param n             number of array elements.
 * @param rank          rank of the current process.
 * @param file_name     file name.
 */
void readingFile(int n, int rank, char *file_name)
{
    int *full_array;
    MPI_File fh;
    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

    if (rank == 0)
    {
        full_array = (int *)malloc(n * sizeof(int));
        MPI_File_read(fh, full_array, n, MPI_INT, MPI_STATUS_IGNORE);
        for (int i = 0; i < n; i++)
            printf("%d ", full_array[i]);
        printf("\n");
    }

    MPI_File_close(&fh);
}