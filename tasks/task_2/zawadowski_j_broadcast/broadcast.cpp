// Copyright 2023 Zawadowski Jan
#include "task_2/zawadowski_j_broadcast/broadcast.h"

void broadcast(void* buffer,
               int count,
               MPI_Datatype datatype,
               int root,
               MPI_Comm comm) {
    int sizeWorld, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeWorld);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == root) {
        for (int i = 0; i < sizeWorld; i++)
            if (i != root)
                MPI_Send(buffer, count, datatype, i, 0, comm);
    } else {
        MPI_Status status;
        MPI_Recv(buffer, count, datatype, root, 0, comm, &status);
    }
}
