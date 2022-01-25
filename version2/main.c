#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>

void readingFile(char *, int *, int, int, int);

int main(int argc, char **argv)
{
    int i, n, rank, n_ranks, quoz, dim, range;
    int *piece_init_array, *full_array;
    // double buf[n];
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

    n = atoi(argv[1]);     // array length
    range = atoi(argv[2]); // maximum acceptable integer
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

    for (i = 0; i < dim; i++)
        piece_init_array[i] = rand() % range;

    for (i = 0; i < dim; i++)
        printf("%d ", piece_init_array[i]);

    printf("\n");

    // Delete, re-open file and write
    MPI_File_delete(file_name, MPI_INFO_NULL);
    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

    disp = rank * quoz * sizeof(int);
    MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    MPI_File_write(fh, piece_init_array, dim, MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_close(&fh);

    if (rank == 0)
        printf("\nLETTURA\n");

    readingFile(file_name, full_array, n, rank, n_ranks);

    MPI_Finalize();
    return 0;
}

void readingFile(char *file_name, int *full_array, int n, int rank, int n_ranks)
{
    MPI_File fh;
    int dim;
    int quoz = n / n_ranks;
    int *piece;
    int disp;
    MPI_File_open(MPI_COMM_WORLD, file_name, MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

    disp = rank * quoz * sizeof(int);
    MPI_File_set_view(fh, disp, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);

    if (rank >= 0 && rank < n_ranks - 1)
    {
        dim = quoz;
        piece = (int *)malloc(dim * sizeof(int));
        MPI_File_read(fh, piece, dim, MPI_INT, MPI_STATUS_IGNORE);

        for (int i = 0; i < dim; i++)
        {
            printf("%d ", piece[i]);
        }
        printf("\n");
    }

    if (rank == n_ranks - 1)
    {
        dim = quoz + n % n_ranks;
        piece = (int *)malloc(dim * sizeof(int));
        MPI_File_read(fh, piece, dim, MPI_INT, MPI_STATUS_IGNORE);

        for (int i = 0; i < dim; i++)
        {
            printf("%d ", piece[i]);
        }
        printf("\n");
    }

    MPI_File_close(&fh);
}