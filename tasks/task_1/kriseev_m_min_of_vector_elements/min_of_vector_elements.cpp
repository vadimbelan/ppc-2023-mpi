// Copyright 2023 Kriseev Mikhail
#include "task_1/kriseev_m_min_of_vector_elements/min_of_vector_elements.h"
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>

int MinOfArray(const int arr[], int size) {
    int min = INT32_MAX;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int MinElementsInVectorSequential(const std::vector<int>& vec) {
    return MinOfArray(vec.data(), vec.size());
}

int MinElementsInVectorParallel(const std::vector<int>& vec) {
    boost::mpi::communicator world;
    int rank = world.rank();
    int commSize = world.size();
    std::vector<int> sizes(commSize, vec.size() / commSize);
    if (vec.size() % commSize) {
        sizes.back() = vec.size() % commSize;
    }
    int localSize = sizes[rank - 0];
    int *localData = new int[localSize];
    boost::mpi::scatterv(world, vec, sizes, localData, 0);

    int localMin = MinOfArray(localData, sizes[rank]);
    int globalMin = 0;

    boost::mpi::reduce(
            world,
            localMin,
            globalMin,
            boost::mpi::minimum<int>(), 0);

    delete [] localData;

    return globalMin;
}
