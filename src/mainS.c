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
  @file mainS.c
  @brief This is the file mainS.c, which contains the sequential main function and the function 'init' that calls the other functions
  @copyright Copyright (c) 2021
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <limits.h>

void init(int n, int range, int *full_array);
void countingSort(int n, int *full_array);

#define STARTTIME(id)                             \
    clock_t start_time_42_##id, end_time_42_##id; \
    start_time_42_##id = clock()

#define ENDTIME(id, x)          \
    end_time_42_##id = clock(); \
    x = ((double)(end_time_42_##id - start_time_42_##id)) / CLOCKS_PER_SEC

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("ERROR! YOU MUST INSERT ARRAY LENGTH AND THE MAXIMUM ACCEPTABLE INTEGER\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int n, range;
    int *full_array;
    double time_init = 0, time_count = 0;
    n = atoi(argv[1]);     //array length
    range = atoi(argv[2]); //maximum acceptable integer

    /*
    for(int i=0; i<n; i++)
        printf("%d ",full_array[i]);
    printf("\n");*/

    STARTTIME(0);

    full_array = (int *)malloc(n * sizeof(int)); //allocation of space needed for the array

    init(n, range, full_array);

    ENDTIME(0, time_init);

    /*
    for(int i=0; i<n; i++)
        printf("%d ",full_array[i]);
    printf("\n");*/

    STARTTIME(1);

    countingSort(n, full_array);

    ENDTIME(1, time_count);

    printf("1;%f;%f\n", time_init, time_count);
    /*for(int i=0; i<n; i++)
        printf("%d ",full_array[i]);*/

    free(full_array);

    return 0;
}

/**
 * @brief This function initialize randomly the array 'full_array'.
 * @param n             number of array elements.
 * @param range         maximum acceptable integer.
 * @param full_array    pointer to the array.
 */
void init(int n, int range, int *full_array)
{
    for (int i = 0; i < n; i++)
        full_array[i] = rand() % range;
}

/**
 * @brief This function sorts the array 'full_array' using Counting Sort Algorithm.
 * @param n             number of array elements.
 * @param full_array    pointer to the unsorted array.
 */
void countingSort(int n, int *full_array)
{
    int min = INT_MAX;
    int max = INT_MIN;

    for (int i = 0; i < n; i++)
        if (full_array[i] > max)
            max = full_array[i];
        else if (full_array[i] < min)
            min = full_array[i];

    int *c;
    int lenC = max - min + 1;
    if ((c = malloc(lenC * sizeof(int))) == NULL)
        exit(1);

    for (int i = 0; i < lenC; i++)
        c[i] = 0;

    for (int i = 0; i < n; i++)
        c[full_array[i] - min] += 1;

    for (int i = 1; i < lenC; i++)
        c[i] += c[i - 1];

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
