// Copyright 2023 Sredneva Anastasiya
#include <vector>
#include <random>
#include "task_1/sredneva_a_sum_values_by_matrix_columns/sum_values.h"

std::vector<int> getRandomMatrix(int columns, int lines, int l, int r) {
    int size = columns * lines;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distrib(l, r);
    std::vector<int> M(size);
    for (int i = 0; i < lines; i++) { 
        for (int j = 0; j < columns; j++) {
            M[i * columns + j] = distrib(gen);
        }
    }
    return M;
}

std::vector<int> getSequentialSum(const std::vector<int>& M, int columns) {
    const int size = M.size();
    std::vector<int> Summ(columns);
    for (int j = 0; j < columns; j++) {
        int sum = 0;
        for (int i = j; i < size; i = i + columns) {
            sum += M[i];
        }
        Summ[j] = sum;
    }
    return Summ;
}

std::vector<int> getParallelSum(const std::vector<int>& M, int columns, int lines) {
    int ProcRank, ProcNum;
    int size = M.size();
    std::vector<int> Summ(columns);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    int size1 = columns / ProcNum;
    int ost = columns % ProcNum;
    std::vector<int> sendcounts(ProcNum);
    std::vector<int> recvcounts(ProcNum);
    std::vector<int> displs(ProcNum);
    std::vector<int> displs2(ProcNum);
    std::vector<int> Matr(size1 * lines);
    if (ProcRank == 0) {
        for (int i = 0; i < ProcNum; i++) {
            sendcounts[i] = size1 * lines;
            displs[i] = 0;
            recvcounts[i] = size1;
            displs2[i] = 0;
        }
        sendcounts[0] += ost * lines;
        recvcounts[0] += ost;
        for (int i = 1; i < ProcNum; i++) {
            displs[i] = displs[i - 1] + sendcounts[i - 1];
            displs2[i] = displs2[i - 1] + recvcounts[i - 1];
        }
        Matr.resize((size1 + ost) * lines);
    }
    std::vector<int> tMat = transposeMatr(M, columns, lines);
    MPI_Scatterv(tMat.data(), sendcounts.data(), displs.data(), MPI_INT, Matr.data(), Matr.size(), MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> sum;
    int k = Matr.size() / lines;
    for (int i = 0; i < k; i++) {
        int s = 0;
        for (int j = 0; j < lines; j++) {
            s += Matr[i * lines + j];
        }
        sum.push_back(s);
    }
    MPI_Gatherv(sum.data(), sum.size(), MPI_INT, Summ.data(), recvcounts.data(), displs2.data(), MPI_INT, 0, MPI_COMM_WORLD);
    return Summ;
}

std::vector<int> transposeMatr(const std::vector<int>& M, int columns, int lines) {
    std::vector<int> tMat(M.size());
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            tMat[i + j * lines] = M[i * columns + j];
        }
    }
    return tMat;
}