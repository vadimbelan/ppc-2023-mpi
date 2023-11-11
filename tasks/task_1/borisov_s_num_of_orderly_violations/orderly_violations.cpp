// Copyright 2023 Borisov Saveliy
#include <random>
#include <algorithm>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "task_1/borisov_s_num_of_orderly_violations/orderly_violations.h"

std::vector<int> getRandomVector(int size) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vector(size);

    for (int  i = 0; i < size; i++) { 
        vector[i] = gen() % 100; 
    }
    return vector;
}

int getViolationsSequentially(std::vector<int> vector) {
    const int  vector_size = vector.size();
    int violations_number = 0;

    for (int index = 1; index < vector_size; index++) {
        if (vector[index] < vector[index - 1]) {
            violations_number++;
        }
    }

    return violations_number;
}

int getViolationsInParallel(std::vector<int> vector) {
    boost::mpi::communicator world;
    const int delta = vector.size() / world.size();

    if (world.rank() == 0) {
        for (int process = 1; process < world.size(); process++) {
            world.send(process, 0, vector.data() + process * delta, delta);
        }
    }

    std::vector<int> local_vector(delta);
    if (world.rank() == 0) {
        local_vector = std::vector<int>(vector.begin(), vector.begin() + delta);
    } else {
        world.recv(0, 0, local_vector.data(), delta);
    }

    int global_violations_number = 0;
    int local_violations_number = getViolationsSequentially(local_vector);
    reduce(world, local_violations_number, global_violations_number, std::plus<int>(), 0);

    return global_violations_number;
}
