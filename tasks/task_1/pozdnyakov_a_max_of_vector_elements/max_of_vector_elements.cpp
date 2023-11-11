// Copyright 2023 Pozdnyakov Vasya
#include <random>
#include "task_1/pozdnyakov_a_max_of_vector_elements/max_of_vector_elements.h"

int get_max_element(const std::vector<int>& init_vec, size_t vec_size) {
    boost::mpi::communicator world;
    const size_t local_part_size = vec_size / world.size();
    const size_t remain = vec_size % world.size();
    std::vector<int> local_vec(local_part_size);
    std::vector<int> local_vec_sizes(world.size(), static_cast<int>(local_part_size));
    local_vec_sizes[0] += static_cast<int>(remain);

    if (local_part_size== 0) {
        local_vec = init_vec;
    } else {
        if (world.rank() == 0) {
            local_vec.resize(local_part_size + remain);
            boost::mpi::scatterv(world, init_vec, local_vec_sizes, local_vec.data(), 0);
        } else {
            boost::mpi::scatterv(world, local_vec.data(), local_vec_sizes[world.rank()], 0);
        }
    }

    int local_res = *std::max_element(local_vec.begin(), local_vec.end());
    int global_res = 0;
    if (local_part_size != 0) {
        boost::mpi::reduce(world, local_res, global_res, boost::mpi::maximum<int>(), 0);
    } else {
        if (world.rank() == 0) {
            global_res = local_res;
        }
    }

    return global_res;
}

std::vector<int> get_random_vector(size_t size, int min_elem, int max_elem) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distrib(min_elem, max_elem);

    std::vector<int> vec(size);
    for (int  i = 0; i < size; i++) {
        vec[i] = distrib(gen);
    }
    return vec;
}
