// Copyright 2023 Sharapov Georgiy
#include <mpi.h>
#include <cmath>
#include <random>
#include <iostream>
#include <algorithm>
#include "task_3/sharapov_g_conv_hull_conn_comp/connected_component.h"

int* marking(int* image, size_t n, size_t k) {
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
    int *ProcElem = new int[ProcNum]();
    int *ProcElemDisp = new int[ProcNum]();
    for (int i = 0; i < ProcNum; i++) {
        ProcElem[i] = ProcSizes[i] * n;
        ProcElemDisp[i] = ProcDisp[i] * n;
    }


    int *rows = new int[ProcElem[ProcRank]]();

    //  DEBUG --------------------------------------
    int test = 0;
    //  DEBUG --------------------------------------

    //  packing and sending rows to corresponding processors
    int *PackedRows = nullptr;
    if (ProcRank == 0) {
        PackedRows = new int[n * n]();
        for (int row = 0; row < n; row++) {
            for (int elem = 0; elem < n; elem++) {
                PackedRows[(ProcElemDisp[row % ProcNum]) + ((row / ProcNum) * n) + elem] = image[(row * n) + elem];
            }
        }

        MPI_Scatterv(image, ProcElem, ProcElemDisp,
            MPI_INT, rows, ProcElem[ProcRank],
            MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        MPI_Scatterv(nullptr, nullptr, nullptr,
            MPI_INT, rows, ProcElem[ProcRank],
            MPI_INT, 0, MPI_COMM_WORLD);
    }

    //  processing image

    //  forward step
    int zero = 0;
    int* prevRow = new int[n]();
    int currentLocalRow = 0;
    int currentElemLimit = k;
    int currentProcessedElem = 0;
    int prevRowProc = (ProcRank == 0 ? (ProcNum - 1) : (ProcRank - 1));
    int nextRowProc = (ProcRank == ProcNum - 1 ? 0 : (ProcRank + 1));
    bool first = (ProcRank == 0 ? true : false);
    MPI_Status status;

    //  each processor do algorithm for each of it's rows
    while (currentLocalRow < ProcSizes[ProcRank]) {
        currentElemLimit = k;
        currentProcessedElem = 0;

        //  on first iteration each processor should get prevRow
        //  except first one, it cant get it at start
        if (!first) {
            MPI_Recv(prevRow, n, MPI_INT, prevRowProc, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }
        if (ProcRank == 0) first = false;

        //  processing elemnts in row and after send it to next processor
        //  if next processor still have unprocessed rows
        while (currentProcessedElem < n) {
            while (currentProcessedElem < currentElemLimit && currentProcessedElem < n) {
                //  marking algorithm

                //  for readability purposes
                int* current = &rows[(currentLocalRow * n) + currentProcessedElem];
                int* upper = &prevRow[currentProcessedElem];
                int* left = (currentProcessedElem == 0 ? &zero :
                    &rows[(currentLocalRow * n) + currentProcessedElem - 1]);

                if (*current == 1) {
                    if (*upper == 0 && *left == 0) {
                        // new component
                        *current = currentProcessedElem * ProcNum;
                    } else {
                        // part of alreday existing component
                        if (*upper > *left) {
                            *current = *upper;
                        } else {
                            *current = *left;
                        }
                    }
                }

                currentProcessedElem++;
            }
            if ((ProcRank + (currentLocalRow * ProcNum) + 1) < n) {
                MPI_Send(&rows[currentLocalRow * n], n, MPI_INT, nextRowProc, MPI_ANY_TAG, MPI_COMM_WORLD);
            }
            currentElemLimit += k;
        }

        currentLocalRow++;
    }

    //  backward step

    //  reciving rows from processors on root and recreating image
    int *processedImage = nullptr;
    if (ProcRank == 0) {
        processedImage = new int[n * n];
        MPI_Gatherv(rows, ProcElem[ProcRank], MPI_INT,
            processedImage, ProcElem, ProcElemDisp,
            MPI_INT, 0, MPI_COMM_WORLD);

        //  DEBUG --------------------------------------

        //  printing processed array
        for (int row = 0; row < n; row++) {
            for (int elem = 0; elem < n; elem++) {
                std::cout << processedImage[row * n + elem] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        //  DEBUG --------------------------------------

    } else {
        MPI_Gatherv(rows, ProcElem[ProcRank], MPI_INT,
            nullptr, nullptr, nullptr,
            MPI_INT, 0, MPI_COMM_WORLD);
    }

    delete[] rows;
    delete[] PackedRows;
    return nullptr;
}
