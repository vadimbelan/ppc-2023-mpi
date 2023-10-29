#include <vector>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "gauss_lent_horiz.h"

int get_slice(int size, int proc_count, int rank){
    int q = size / proc_count;
    if (size % proc_count)
        q++;
    int r = proc_count * q - size;

    int slice = q;
    if (rank >= proc_count - r)
        slice = q - 1;
    return slice;
}

std::vector<double> Gauss(std::vector<double> matrix, int size){
    boost::mpi::communicator world;
    int rank = world.rank();
    int comm_size = world.size();

    std::vector<double> Xi(size);
    int nrows = get_slice(size, comm_size, rank);

    std::vector<int> rows(nrows);
    std::vector<double> tmp(size + 1);

    for (int i = 0; i < nrows; i++)
        rows[i] = rank + comm_size * i;

    // прямой проход
    int row = 0;
    for (int i = 0; i < size - 1; i++) {
        if (i == rows[row]){  // если эта строка текущего процесса
            boost::mpi::broadcast(world, &matrix.data()[rows[row] * (size + 1)], size + 1, rank);
            for (int j = 0; j <= size; j++) {
                tmp[j] = matrix[rows[row] * (size + 1) + j];
            }
            row++;
        } else {
            boost::mpi::broadcast(world, tmp.data(), size + 1, i % comm_size);
        }

        for (int j = row; j < nrows; j++) {
            int row_id = rows[j];
            double scaling = matrix[row_id * (size + 1) + i] / tmp[i];
            for (int k = i; k < size + 1; k++) {
                matrix[row_id * (size + 1) + k] -= scaling * tmp[k];
            }
        }
    }

    // Инициализируем X
    row = 0;
    for (int i = 0; i < size; i++) {
        Xi[i] = 0;
        if (i == rows[row]) {
            Xi[i] = matrix[i * (size + 1) + size];
            row++;
        }
    }

    // Обратный ход
    row = nrows - 1;
    for (int i = size - 1; i > 0; i--) {
        if (row >= 0){
            if (i == rows[row]) {
                Xi[i] /= matrix[i * (size + 1) + i];
                std::cout << "Xi = " << Xi[i] << " proc_id = " << rank  << " /= " << matrix[i * (size + 1) + i] << std::endl;
                boost::mpi::broadcast(world, &(Xi.data())[i], 1, rank);
                row--;
            } else {
                boost::mpi::broadcast(world, &(Xi.data())[i], 1, i % comm_size);
            }
        } else {
            boost::mpi::broadcast(world, &(Xi.data())[i], 1, i % comm_size);
        }

        for (int j = 0; j <= row; j++) {
            Xi[rows[j]] -= matrix[rows[j] * (size + 1) + i] * Xi[i];
        }
    }

    if (rank == 0)
        Xi[0] /= matrix[rows[row] * (size + 1)];

    boost::mpi::broadcast(world, Xi.data(), 1, 0);

    return Xi;
}
