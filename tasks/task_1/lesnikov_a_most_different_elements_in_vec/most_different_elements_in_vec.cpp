// Copyright 2023 Kulikov Artem
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <functional>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include "task_1/lesnikov_a_most_different_elements_in_vec/most_different_elements_in_vec.h"


std::vector<size_t> sdfsdfsdf(std::vector<int> glob_matr, int m, int n) {
    std::vector<size_t> glob_min_indexes(m);

    boost::mpi::communicator world;
    int rank = world.rank();
    std::vector<int> local_vecs;

    boost::mpi::scatterv(world, glob_matr.data(), local_vecs, local_vecs.data(), 0);

    return glob_min_indexes;
}

std::vector<std::pair<size_t, size_t>> getSequentialMostDifferentElements(std::vector<int> v) {
    std::vector<std::pair<size_t, size_t>> most_different_elements;
    int max_different_elements_value = 0;

    for (size_t i = 0; i < v.size() - 1; i++) {
        max_different_elements_value = std::max(max_different_elements_value, std::abs(v[i] - v[i+1]));
    }

    for (size_t i = 0; i < v.size() - 1; i++) {
        if (std::abs(v[i] - v[i+1]) == max_different_elements_value) {
            most_different_elements.push_back(std::make_pair(i, i + 1));
        }
    }

    return most_different_elements;
}

std::vector<std::pair<size_t, size_t>> getParallelMostDifferentElements(std::vector<int> v) {
    boost::mpi::communicator world;
    std::vector<int> loc_v;
    std::vector<size_t> glob_most_different_elements;
    std::vector<std::pair<size_t, size_t>> glob_most_different_elements_pairs;
    std::vector<size_t> loc_most_different_elements;
    const int part_size = v.size() / world.size();
    const int remainder = v.size() % world.size();
    std::vector<int> sizes(world.size(), part_size);
    sizes[0] += remainder;

    if (part_size > 0) {
        boost::mpi::scatterv(world, v.data(), sizes, loc_v.data(), 0);
    }

    if (world.rank() == 0) {
        loc_v = v;
        loc_v.resize(sizes[0]);
    }

    int max_different_elements_value = 0;

    for (size_t i = 0; i < loc_v.size() - 1; i++) {
        max_different_elements_value = std::max(max_different_elements_value, std::abs(loc_v[i] - loc_v[i+1]));
    }

    for (size_t i = 0; i < v.size() - 1; i++) {
        if (std::abs(loc_v[i] - loc_v[i+1]) == max_different_elements_value) {
            loc_most_different_elements.push_back(i + world.rank() * part_size
            + remainder * static_cast<int>(world.size() != 0));
        }
    }

    glob_most_different_elements = std::move(loc_most_different_elements);

    if (world.rank() == 0) {
        std::vector<size_t> temp;

        for (int i = 1; i < world.size(); i++) {
            world.recv(i, 0, temp);

            if (!glob_most_different_elements.size()) {
                glob_most_different_elements = std::move(temp);
            } else if (temp.size()) {
                int glob_diff = std::abs(v[glob_most_different_elements[0]] - v[glob_most_different_elements[0] + 1]);
                int temp_diff = std::abs(v[temp[0]] - v[temp[0] + 1]);
                if (glob_diff < temp_diff) {
                    glob_most_different_elements = std::move(temp);
                }
            }
        }
    } else {
        world.send(0, 0, glob_most_different_elements);
    }

    for (const size_t& i : glob_most_different_elements) {
        glob_most_different_elements_pairs.push_back(std::make_pair(i, i + 1));
    }

    return glob_most_different_elements_pairs;
}
