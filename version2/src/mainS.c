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
  @brief This is the file mainS.c, which contains the sequential main function, the function 'init', 'countingSort' and 'readingFile'
  @copyright Copyright (c) 2021
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <limits.h>

void init(int n, int range, char *file_name);
void countingSort(int n, char *file_name);
void readingFile(char *file_name, int n);

#define STARTTIME(id)                             \
    clock_t start_time_42_##id, end_time_42_##id; \
    start_time_42_##id = clock()

#define ENDTIME(id, x)          \
    end_time_42_##id = clock(); \
    x = ((double)(end_time_42_##id - start_time_42_##id)) / CLOCKS_PER_SEC

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("ERROR! YOU MUST INSERT ARRAY LENGTH, THE MAXIMUM ACCEPTABLE INTEGER AND THE FILE NAME\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int n, range;
    char *file_name;

    double time_init = 0, time_count = 0;
    n = atoi(argv[1]);     // array length
    range = atoi(argv[2]); // maximum acceptable integer
    file_name = argv[3];   // file name

    STARTTIME(0);

    init(n, range, file_name);

    ENDTIME(0, time_init);



    STARTTIME(1);

    countingSort(n, file_name);

    ENDTIME(1, time_count);



    //readingFile(file_name, n);

    printf("1;%f;%f\n", time_init, time_count);

}




/**
 * @brief This function writes in the file 'file_name' 'n' integers.
 * @param n             number of array elements.
 * @param range         maximum acceptable integer.
 * @param file_name     file name.
 */
void init(int n, int range, char *file_name)
{
    FILE *fp;
    int app;

    if ((fp = fopen(file_name, "wb")) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < n; i++)
    {
        app = rand() % range;
        fwrite(&app, sizeof(int), 1, fp);
        //Print to comment
        //printf("%d ", app);
    }
    //Print to comment
    //printf("\n\n");

    fclose(fp);
}





/**
 * @brief This function sorts the integers in 'file_name' using Counting Sort Algorithm.
 * @param n             number of array elements.
 * @param file_name     file name.
 */
void countingSort(int n, char *file_name)
{
    FILE *fp;
    int *full_array;
    int min = INT_MAX;
    int max = INT_MIN;

    full_array = (int *)malloc(n * sizeof(int));

    if ((fp = fopen(file_name, "rb+")) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < n; i++)
        fread(full_array + i, sizeof(int), 1, fp);
    
    //Print to comment
    /*printf("DOPO LETTURA:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", full_array[i]);
    printf("\n\n");*/

    for (int i = 0; i < n; i++)
        if (full_array[i] > max)
            max = full_array[i];
        if (full_array[i] < min)
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

    //moving to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < n; i++)
        fwrite(full_array + i, sizeof(int), 1, fp);

    free(full_array);
    fclose(fp);
}





/**
 * @brief This function reads the integers in 'file_name' and prints them on stdout.
 * @param file_name     file name.
 * @param n             number of array elements.
 */
void readingFile(char *file_name, int n)
{
    FILE *fp;
    int* full_array;

    full_array = (int *)malloc(n * sizeof(int));    

    if ((fp = fopen(file_name, "rb")) == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < n; i++){
        fread(full_array + i, sizeof(int), 1, fp);
        printf("%d ", full_array[i]);
    }
    printf("\n");
}