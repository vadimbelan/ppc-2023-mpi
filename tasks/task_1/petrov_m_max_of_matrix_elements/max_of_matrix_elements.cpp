// Copyright 2023 Petrov Maksim
#include <random>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include"task_1/petrov_m_max_of_matrix_elements/max_of_matrix_elements.h"

std::vector<int> init_matrix(const int rows, const int cols) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distrib(-50, 50);

    std::vector<int> matrix(rows * cols);
    for (int i = 0; i < matrix.size(); i++) {
        matrix[i] = distrib(gen);
    }
    return matrix;
}

int getSequentialOperations(std::vector<int>_matrix) {
    int globalMax = 0;

    for (int i = 0; i < _matrix.size(); i++) {
        if (_matrix[i] > globalMax)
            globalMax = _matrix[i];
    }

    std::cout << "The maximum element in the matrix is: " << globalMax << std::endl;

    return globalMax;
}

int getParallelOperations(std::vector<int> _matrix, const int rows, const int cols) {
    boost::mpi::communicator world;
    const int delta = rows * cols / world.size();
    int delta_2 = delta;
    if ((rows * cols) % world.size() != 0)
        delta_2 += ceil((rows * cols) % world.size());

    std::cout << world.size() << "size\n";
    if (world.rank() == 0) {
        for (int proc = 1; proc < world.size(); proc++) {
            world.send(proc, 0, _matrix.data() + delta_2 + (proc - 1) * delta, delta);
        }
    }

    std::vector<int> local_row(delta);
    if (world.rank() == 0) {
        local_row = std::vector<int>(_matrix.begin(),
            _matrix.begin() + delta_2);
    } else {
        world.recv(0, 0, local_row.data(), delta);
    }

    int global_max = 0;
    int local_max = getSequentialOperations(local_row);
    std::cout << world.rank() << " rank\n";
    std::cout << local_max << " Lmax\n";

    reduce(world, local_max, global_max, boost::mpi::maximum<int>(), 0);

    return global_max;
}
