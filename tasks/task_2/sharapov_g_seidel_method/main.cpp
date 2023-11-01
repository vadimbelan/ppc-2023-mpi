// Copyright 2023 Sharapov Georgiy
#include <mpi.h>
#include <gtest/gtest.h>
#include "task_2/sharapov_g_seidel_method/seidel_method.h"

TEST(Seidel_Method_MPI, Test_5) {
    int size = 5;

    bool test = seidelMethod(size, 0.000001);

    ASSERT_TRUE(test);
}

TEST(Seidel_Method_MPI, Test_25) {
    int size = 25;

    bool test = seidelMethod(size, 0.000001);

    ASSERT_TRUE(test);
}

TEST(Seidel_Method_MPI, Test_50) {
    int size = 50;

    bool test = seidelMethod(size, 0.000001);

    ASSERT_TRUE(test);
}

TEST(Seidel_Method_MPI, Test_75) {
    int size = 75;

    bool test = seidelMethod(size, 0.000001);

    ASSERT_TRUE(test);
}

TEST(Seidel_Method_MPI, Test_100) {
    int size = 100;

    bool test = seidelMethod(size, 0.000001);

    ASSERT_TRUE(test);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    int ProcRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    if (ProcRank != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }

    int result = RUN_ALL_TESTS();
    MPI_Finalize();

    return result;
}

