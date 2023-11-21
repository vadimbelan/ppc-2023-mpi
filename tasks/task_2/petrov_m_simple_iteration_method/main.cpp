// Copyright 2023 Petrov Maksim
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <random>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "./simple_iteration_method.h"

using std::vector;

vector<double> A;
vector<double> b;
vector<double> b_check;
vector<double> x_parallel;
vector<double> x_sequential;

TEST(Simple_Iteration_Method, Simple_Iteration_Method_test_1) {
    boost::mpi::communicator world;
    int n = 6;
    double epsilon = 1e-8;
    A = get_rand_matrix(n);
    b = get_rand_vec(n);
    x_parallel = get_parallel_simple_iteration_method(A, b, n, 100, 1e-10);

    int rank = world.rank();

    if (rank == 0) {
        x_sequential = get_sequential_simple_iteration_method(A, b, n, 100, 1e-10);
        b_check = mult_for_verification_aprox(A, x_parallel, n);

        for (int i = 0; i < n; ++i)
            ASSERT_DOUBLE_EQ(x_parallel[i], x_sequential[i]);
        for (int i = 0; i < n; ++i)
            ASSERT_NEAR(b[i], b_check[i], epsilon);
    }
}

TEST(Simple_Iteration_Method, Simple_Iteration_Method_test_2) {
    boost::mpi::communicator world;
    int n = 10;
    double epsilon = 2e-9;
    A = get_rand_matrix(n);
    b = get_rand_vec(n);
    x_parallel = get_parallel_simple_iteration_method(A, b, n, 100, 1e-10);

    int rank = world.rank();

    if (rank == 0) {
        x_sequential = get_sequential_simple_iteration_method(A, b, n, 100, 1e-10);
        b_check = mult_for_verification_aprox(A, x_parallel, n);

        for (int i = 0; i < n; ++i)
            ASSERT_DOUBLE_EQ(x_parallel[i], x_sequential[i]);
        for (int i = 0; i < n; ++i)
            ASSERT_NEAR(b[i], b_check[i], epsilon);
    }
}

TEST(Simple_Iteration_Method, Simple_Iteration_Method_test_3) {
    boost::mpi::communicator world;
    int n = 50;
    double epsilon = 1e-8;
    A = get_rand_matrix(n);
    b = get_rand_vec(n);
    x_parallel = get_parallel_simple_iteration_method(A, b, n, 100, 1e-10);

    int rank = world.rank();

    if (rank == 0) {
        x_sequential = get_sequential_simple_iteration_method(A, b, n, 100, 1e-10);
        b_check = mult_for_verification_aprox(A, x_parallel, n);

        for (int i = 0; i < n; ++i)
            ASSERT_DOUBLE_EQ(x_parallel[i], x_sequential[i]);
        for (int i = 0; i < n; ++i)
            ASSERT_NEAR(b[i], b_check[i], epsilon);
    }
}

TEST(Simple_Iteration_Method, Simple_Iteration_Method_test_4) {
    boost::mpi::communicator world;
    int n = 150;
    double epsilon = 1e-7;
    A = get_rand_matrix(n);
    b = get_rand_vec(n);
    x_parallel = get_parallel_simple_iteration_method(A, b, n, 100, 1e-10);

    int rank = world.rank();

    if (rank == 0) {
        x_sequential = get_sequential_simple_iteration_method(A, b, n, 100, 1e-10);
        b_check = mult_for_verification_aprox(A, x_parallel, n);

        for (int i = 0; i < n; ++i)
            ASSERT_DOUBLE_EQ(x_parallel[i], x_sequential[i]);
        for (int i = 0; i < n; ++i)
            ASSERT_NEAR(b[i], b_check[i], epsilon);
    }
}

TEST(Simple_Iteration_Method, Simple_Iteration_Method_test_5) {
    boost::mpi::communicator world;
    int n = 300;
    double epsilon = 1e-6;
    A = get_rand_matrix(n);
    b = get_rand_vec(n);
    x_parallel = get_parallel_simple_iteration_method(A, b, n, 100, 1e-10);

    int rank = world.rank();

    if (rank == 0) {
        x_sequential = get_sequential_simple_iteration_method(A, b, n, 100, 1e-10);
        b_check = mult_for_verification_aprox(A, x_parallel, n);

        for (int i = 0; i < n; ++i)
            ASSERT_DOUBLE_EQ(x_parallel[i], x_sequential[i]);
        for (int i = 0; i < n; ++i)
            ASSERT_NEAR(b[i], b_check[i], epsilon);
    }
}

int main(int argc, char** argv) {
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    if (world.rank() != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }
    return RUN_ALL_TESTS();
}
