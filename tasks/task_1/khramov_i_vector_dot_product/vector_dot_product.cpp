// Copyright 2023 Khramov Ivan
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <functional>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>
#include "task_1/khramov_i_vector_dot_product/vector_dot_product.h"

std::vector<int> getRandomVector(int sz) {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<int> vec(sz);
    for (int  i = 0; i < sz; i++) { vec[i] = gen() % 100; }
    return vec;
}

int getLocalVectorDotProduct(std::vector<int> vec1,
                            std::vector<int> vec2) {
    int result = 0;
    for (int i = 0; i < vec1.size(); i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

int getVectorDotProduct(boost::mpi::communicator world,
    std::vector<int> global_vec1, std::vector<int> global_vec2) {
    if (global_vec1.size() != global_vec2.size())
        return -1;
    else if (global_vec1.size() == 0 || global_vec2.size() == 0)
        return 0;
    std::vector<int> local_vec1(global_vec1.size());
    std::vector<int> local_vec2(global_vec2.size());

    boost::mpi::scatter(
        world,
        global_vec1,
        local_vec1.data(),
        global_vec1.size(),
        0);
    boost::mpi::scatter(
        world,
        global_vec2,
        local_vec2.data(),
        global_vec2.size(),
        0);

    int part_result = getLocalVectorDotProduct(local_vec1, local_vec2);

    int global_product;
    boost::mpi::reduce(world, part_result, global_product, std::plus<int>(), 0);

    return global_product;
}
