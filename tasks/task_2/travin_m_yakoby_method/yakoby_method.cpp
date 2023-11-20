// Copyright 2023 Travin Maksim
#include <algorithm>
#include <random>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "task_2/travin_m_yakoby_method/yakoby_method.h"

std::vector<std::vector<double>> get_rand_matrix(int size, int min, int max) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distrib(min, max);
    std::vector<std::vector<double>> vec =
    std::vector<std::vector<double>>(size, std::vector<double>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            vec[i][j] = distrib(gen);
            if ((vec[i][j] == 0) && (i == j))
                vec[i][j]++;
        }
    }
    return vec;
}

std::vector<double> get_rand_vector(int size, int  min, int max) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distrib(min, max);
    std::vector<double> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = distrib(gen);
    }
    return vec;
}

std::vector<double> Yakobi(const std::vector<std::vector<double>>& A,
    const std::vector<double>& b, std::vector<double> x, int num_iterations) {
    int numProc;
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    int rankProc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);

    if (A[1].size() != b.size())
        throw std::exception();

    for (int i = 0; i < b.size(); i++) {
        if (A[i][i] == 0)
            throw std::exception();
    }

    for (int i = 0; i < b.size(); ++i) {
        MPI_Bcast(const_cast<double*>(A[i].data()),
        b.size(),
        MPI_DOUBLE,
        0,
        MPI_COMM_WORLD);
    }
    MPI_Bcast(const_cast<double*>(b.data()),
             b.size(),
             MPI_DOUBLE,
             0,
             MPI_COMM_WORLD);

    std::vector<double> new_x(b.size());

    for (int k = 0; k < num_iterations; k++) {
        for (int i = rankProc; i < b.size(); i += numProc) {
            new_x[i] = b[i];
            for (int j = 0; j < b.size(); j++) {
                if (i != j)
                new_x[i] -= A[i][j] * x[j];
            }
            new_x[i] /= A[i][i];
        }

        MPI_Allgather(new_x.data() + rankProc * (b.size() / numProc),
            b.size() / numProc,
            MPI_DOUBLE,
            x.data(),
            b.size() / numProc,
            MPI_DOUBLE,
            MPI_COMM_WORLD);
    }
    return x;
}
