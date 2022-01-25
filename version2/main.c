#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char **argv)
{
    int i, n, rank, n_ranks, quoz, dim, range;
    int *piece_init_array, *full_array;
    //double buf[n];
    char *file_name;
    MPI_File fh;
    MPI_Offset disp;

    // Initialize the MPI execution environment
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

    n = atoi(argv[1]);     //array length
    range = atoi(argv[2]); //maximum acceptable integer
    file_name = argv[3];
    quoz = n / n_ranks;

    if (rank == 0)
        printf("\n\n%s\n\n", file_name);

    srand(time(NULL));
    if (rank >= 0 && rank < n_ranks - 1)
        dim = quoz;

    if (rank == n_ranks - 1)
        dim = quoz + n % n_ranks;

    piece_init_array = (int *)malloc(dim * sizeof(int));
    full_array = (int *)malloc(n * sizeof(int));

    for (i = 0; i < dim; i++)
        piece_init_array[i] = rand() % range;

    for (i = 0; i < dim; i++)
        printf("%d ", piece_init_array[i]);

    printf("\n");

    // Delete, re-open file and write
    MPI_File_delete(file_name, MPI_INFO_NULL);
    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

    disp = rank * dim * sizeof(int);
    MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    MPI_File_write(fh, piece_init_array, dim, MPI_INT, MPI_STATUS_IGNORE);
MPI_File_close(&fh);
   MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
    if(rank == 0)
        MPI_File_read(fh, full_array, n, MPI_INT, MPI_STATUS_IGNORE);

    if (rank == 0)
        for (i = 0; i < n; i++)
            printf("%d ", full_array[i]);

    MPI_File_close(&fh);
    MPI_Finalize();
    return 0;
}