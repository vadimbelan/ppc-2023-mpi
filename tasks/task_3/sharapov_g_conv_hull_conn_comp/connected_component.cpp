// Copyright 2023 Sharapov Georgiy
#include <mpi.h>
#include <cmath>
#include <random>
#include <iostream>
#include <algorithm>
#include "task_3/sharapov_g_conv_hull_conn_comp/connected_component.h"

int* marking(bool* picture, size_t n) {
    int ProcRank, ProcNum;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    //  declaration of variables
    int *ProcSizes = new int[ProcNum]();
    for (int i = 0; i < ProcNum; i++) {
        ProcSizes[i] = n / ProcNum + (i < n % ProcNum ? 1 : 0);
    }

    int *rows = new int[ProcSizes[ProcRank] * n]();

    //  sending rows to corresponding processors
    if (ProcRank == 0) {
        int *PackedRows = new int[n * n];
        for (int row = 0; row < n; row++) {
            for (int elem = 0; elem < n; elem++) {
                PackedRows[(ProcSizes[row % ProcNum] * n) + (row / ProcNum) + elem] = picture[(row * n) + elem];
            }
        }

        //  DEBUG --------------------------------------

        for (int row = 0; row < n; row++) {
            for (int elem = 0; elem < n; elem++) {
                std::cout << PackedRows[row * n + elem];
            }
            std::cout << std::endl;
        }

        //  DEBUG --------------------------------------
    } else {
        std::cout << "";
    }

    return nullptr;
}
