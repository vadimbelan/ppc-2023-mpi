// Copyright 2023 Polozov Vladislav

#include <gtest/gtest.h>
#include <mpi.h>
#include "./double_radix_sort_simple_merge.h"

TEST(MPI_TESTS, Test1) {
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    int n = 10;
    double* inp = new double[n];

}

/*
TEST(MPI_TESTS, Test2) {

}


TEST(MPI_TESTS, Test_all_neg) {

}

TEST(MPI_TESTS, Test_small_size) {

}

TEST(MPI_TESTS, Test_big_size) {

}
*/

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
