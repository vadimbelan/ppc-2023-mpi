// Copyright 2023 Polozov Vladislav

#include <gtest/gtest.h>
#include <mpi.h>
#include "./gauss_jordan_method.h"

TEST(MPI_TESTS, Test1) {
    int n = 3;
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    std::vector<double> matr;
    if (rank == 0) {
        matr = {3, -2, 4, 12, 3, 4, -2, 6, 2, -1, -1, -9};
    }
    std::vector<double>parallel_ans = getParallelGaussJordan(matr, n);
    if (rank == 0) {
        std::vector<double>ans = getSequentialGaussJordan(matr, n);
        ASSERT_EQ(ans, parallel_ans);
    }
}


TEST(MPI_TESTS, Test2) {
    int n = 5;
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    std::vector<double> matr;
    if (rank == 0) {
        matr = getRandomMatrix(n, n+1);
    }
    std::vector<double>parallel_ans = getParallelGaussJordan(matr, n);
    if (rank == 0) {
        std::vector<double>ans = getSequentialGaussJordan(matr, n);
        ASSERT_EQ(ans, parallel_ans);
    }
}


TEST(MPI_TESTS, Test_all_neg) {
    int n = 7;
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    std::vector<double> matr;
    if (rank == 0) {
        matr = getRandomMatrix(n, n+1);
        for (auto& x : matr) {
            if (x > 0) {
                x*=-1.0;
            }
        }
    }
    std::vector<double>parallel_ans = getParallelGaussJordan(matr, n);
    if (rank == 0) {
        std::vector<double>ans = getSequentialGaussJordan(matr, n);
        ASSERT_EQ(ans, parallel_ans);
    }
}

TEST(MPI_TESTS, Test_small_size) {
    int n = 1;
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    std::vector<double> matr;
    if (rank == 0) {
        matr = getRandomMatrix(n, n+1);
    }
    std::vector<double>parallel_ans = getParallelGaussJordan(matr, n);
    if (rank == 0) {
        std::vector<double>ans = getSequentialGaussJordan(matr, n);
        ASSERT_EQ(ans, parallel_ans);
    }
}

TEST(MPI_TESTS, Test_big_size) {
    int n = 20;
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    std::vector<double> matr;
    if (rank == 0) {
        matr = getRandomMatrix(n, n+1);
    }
    std::vector<double>parallel_ans = getParallelGaussJordan(matr, n);
    if (rank == 0) {
        std::vector<double>ans = getSequentialGaussJordan(matr, n);
        ASSERT_EQ(ans, parallel_ans);
    }
}


int main(int argc, char** argv) {
    int result = 0;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, -1);
    int rankProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    if (rankProc != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }
    result = RUN_ALL_TESTS();
    MPI_Finalize();
    return result;
}

