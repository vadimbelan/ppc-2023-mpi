// Copyright 2023 Sharapov Georgiy
#include <mpi.h>
#include <gtest/gtest.h>
#include "task_2/sharapov_g_seidel_method/seidel_method.h"

TEST(Seidel_Method_MPI, Test_1) {
    ASSERT_EQ(1, 1);
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

