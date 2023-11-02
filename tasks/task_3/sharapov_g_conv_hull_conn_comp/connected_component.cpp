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
    int *ProcDisp = new int[ProcNum]();
    for (int i = 0; i < ProcNum; i++) {
        ProcSizes[i] = n / ProcNum + (i < n % ProcNum ? 1 : 0);
        ProcDisp[i] = i * (n / ProcNum) + std::min<int>(i, n % ProcNum);
    }

    int *rows = new int[ProcSizes[ProcRank] * n]();

    //  sending rows to corresponding processors
    int *PackedRows = nullptr;
    if (ProcRank == 0) {
        PackedRows = new int[n * n]();
        for (int row = 0; row < n; row++) {
            for (int elem = 0; elem < n; elem++) {
                PackedRows[(ProcDisp[row % ProcNum] * n) + ((row / ProcNum) * n) + elem] = picture[(row * n) + elem];
            }
        }

        //  DEBUG --------------------------------------

        for (int row = 0; row < n; row++) {
            for (int elem = 0; elem < n; elem++) {
                std::cout << PackedRows[row * n + elem] << "\t";
            }
            std::cout << std::endl;
        }

        //  DEBUG --------------------------------------
    } else {
        std::cout << "";
    }

    delete[] rows;
    delete[] PackedRows;
    return nullptr;
}
