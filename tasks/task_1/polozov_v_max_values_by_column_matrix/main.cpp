// Copyright 2023 Polozov Vladislav

#include <gtest/gtest.h>
#include <mpi.h>
#include "./max_values_by_column_matrix.h"

TEST(MPI_TESTS, Test_random1) {
    int rankProc = 0;
    int numProc = 0;
    int n = 5;
    int m = 5;
    std::vector<int>matr;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if (rankProc == 0) {
        matr = getRandomMatrix(n, m);
    }
    std::vector<int>parallelAns = getParallelMax(matr, n, m);
    if (rankProc == 0) {
        std::vector<int> sequentialAns = getSequentialMax(matr, n, m);
        ASSERT_EQ(sequentialAns, parallelAns);
    }
}

TEST(MPI_TESTS, Test_random2) {
    int rankProc = 0;
    int numProc = 0;
    int n = 7;
    int m = 9;
    std::vector<int>matr;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if (rankProc == 0) {
        matr = getRandomMatrix(n, m);
    }
    std::vector<int>parallelAns = getParallelMax(matr, n, m);
    if (rankProc == 0) {
        std::vector<int> sequentialAns = getSequentialMax(matr, n, m);
        ASSERT_EQ(sequentialAns, parallelAns);
    }
}

TEST(MPI_TESTS, Test_random3) {
    int rankProc = 0;
    int numProc = 0;
    int n = 20;
    int m = 9;
    std::vector<int>matr;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if (rankProc == 0) {
        matr = getRandomMatrix(n, m);
    }
    std::vector<int>parallelAns = getParallelMax(matr, n, m);
    if (rankProc == 0) {
        std::vector<int> sequentialAns = getSequentialMax(matr, n, m);
        ASSERT_EQ(sequentialAns, parallelAns);
    }
}

TEST(MPI_TESTS, Test_all_zero) {
    int rankProc = 0;
    int numProc = 0;
    int n = 6;
    int m = 6;
    std::vector<int>matr;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if (rankProc == 0) {
        matr.assign(n*m, 0);
    }
    std::vector<int>parallelAns = getParallelMax(matr, n, m);
    if (rankProc == 0) {
        std::vector<int> sequentialAns = getSequentialMax(matr, n, m);
        ASSERT_EQ(sequentialAns, parallelAns);
    }
}

TEST(MPI_TESTS, Test_all_neg) {
    int rankProc = 0;
    int numProc = 0;
    int n = 6;
    int m = 6;
    std::vector<int>matr;
    MPI_Comm_rank(MPI_COMM_WORLD, &rankProc);
    MPI_Comm_size(MPI_COMM_WORLD, &numProc);
    if (rankProc == 0) {
        matr = getRandomMatrix(n, m);
        for (int i = 0; i < n ; i++) {
            for (int j = 0; j < m ; j++) {
                if (matr[i*m + j] > 0)
                    matr[i * m + j] *= -1;
            }
        }
    }
    std::vector<int>parallelAns = getParallelMax(matr, n, m);
    if (rankProc == 0) {
        std::vector<int> sequentialAns = getSequentialMax(matr, n, m);
        ASSERT_EQ(sequentialAns, parallelAns);
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

