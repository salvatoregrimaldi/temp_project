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
  @file main.c
  @brief This is the file main.c, which is the main function that calls the other functions
  @copyright Copyright (c) 2021
*/

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/countingsort.h"

int main(int argc, char *argv[])
{
    int rank, n_ranks, range;
    double read_start_time, time_init, time_count;
    char* file_name;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    if (argc != 4)
    {
        if (rank == 0)
            printf("ERROR! YOU MUST INSERT ARRAY LENGTH, THE MAXIMUM ACCEPTABLE INTEGER AND THE FILE NAME\n");
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int n;
    double time, start, end;
    n = atoi(argv[1]);     //array length
    range = atoi(argv[2]); //maximum acceptable integer
    file_name = argv[3];

    if (rank == 0)
        read_start_time = MPI_Wtime();

    //parallelized initialization of the array
    init(n, rank, n_ranks, range, file_name);

    if (rank == 0)
    {
        time_init = MPI_Wtime() - read_start_time;

        /*Print initial array
        for (int i = 0; i < n; i++)
            printf("%d ", full_array[i]);
        printf("\n\n");*/

        read_start_time = MPI_Wtime();
    }

    //execution of the counting sort algorithm
    countingSort(n, n_ranks, rank, file_name);

    if (rank == 0)
    {

        /*Print sorted array
        for (int i = 0; i < n; i++)
            printf("%d ", full_array[i]);
        printf("\n\n");*/

        time_count = MPI_Wtime() - read_start_time;
        printf("%d;%f;%f\n", n_ranks, time_init, time_count);
        //free(full_array);
    }

    readingFile(file_name, n, rank);

    MPI_Finalize();
}