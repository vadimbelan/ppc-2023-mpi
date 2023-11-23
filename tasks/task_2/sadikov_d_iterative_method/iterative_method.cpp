// Copyright 2023 Sadikov Damir
#include <vector>
#include <random>
#include <numeric>
#include <cmath>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/collectives.hpp>

#include "task_2/sadikov_d_iterative_method/iterative_method.h"

std::vector<double> getRandomVector(int n) {
    std::random_device dev;
    std::mt19937_64 gen(dev());
    std::uniform_real_distribution<double> dist(-10, 10);
    std::vector<double> vec(n);
    for (auto& i : vec) {
        i = dist(gen);
    }
    return vec;
}

std::vector<double> getRandomMatrix(int n) {
    // A[i][i] == 1.0, |A[i][i]| > sum{j!=i}|A[i][j]|
    std::vector<double> ret = getRandomVector(n * n);
    for (int i = 0; i < n; i++) {
        ret[i * n + i] = 1.0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                ret[i * n + i] += std::abs(ret[i * n + j]);
            }
        }
        for (int j = 0; j < n; j++) {
            if (j != i) {
                ret[i * n + j] /= ret[i * i + i];
            }
        }
        ret[i * n + i] = 1.0;
    }
    return ret;
}

double getNormOfDifference(const std::vector<double>& a, const std::vector<double>& b) {
    double ret = 0.0;
    for (int i = 0; i < a.size(); i++) {
        ret += std::abs(a[i] - b[i]);
    }
    return ret;
}

std::vector<double> getSequentialIter(const std::vector<double>& A, const std::vector<double> b, int n) {
    // A[i][i] == 1.0, |A[i][i]| > sum{j!=i}|A[i][j]|
    double epsilon = 1e-5;
    std::vector<double> x(n, 0.0);
    std::vector<double> x_new(n, 0.0);
    do {
        std::swap(x, x_new);
        x_new = b;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    x_new[i] -= A[i * n + j] * x[j];
                }
            }
        }
    } while (getNormOfDifference(x_new, x) > epsilon);
    return x;
}

std::vector<double> getParallelIter(const std::vector<double>& A, const std::vector<double> b, int n) {
    // TODO
    return {};
}

int getSequentialDotProduct(const std::vector<int>& A, const std::vector<int>& B) {
    return std::inner_product(A.begin(), A.end(), B.begin(), 0);
}

int getParallelDotProduct(const std::vector<int>& A,
                          const std::vector<int>& B, int vector_size) {
    boost::mpi::communicator world;
    const int delta = vector_size / world.size() + (world.rank() < vector_size % world.size() ? 1 : 0);

    if (world.rank() == 0) {
        int off = delta;
        for (int proc = 1; proc < world.size(); proc++) {
            int proc_delta = vector_size / world.size() + (proc < vector_size % world.size() ? 1 : 0);
            world.send(proc, 0, A.data() + off, proc_delta);
            world.send(proc, 1, B.data() + off, proc_delta);
            off += proc_delta;
        }
    }

    std::vector<int> local_A(delta);
    std::vector<int> local_B(delta);
    if (world.rank() == 0) {
        local_A = std::vector<int>(A.begin(), A.begin() + delta);
        local_B = std::vector<int>(B.begin(), B.begin() + delta);
    } else {
        world.recv(0, 0, local_A.data(), delta);
        world.recv(0, 1, local_B.data(), delta);
    }

    int global_sum = 0;
    int local_sum = getSequentialDotProduct(local_A, local_B);
    reduce(world, local_sum, global_sum, std::plus<int>(), 0);
    return global_sum;
}
