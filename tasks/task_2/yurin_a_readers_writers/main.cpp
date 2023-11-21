// Copyright 2023 Yurin Andrey
#include <gtest/gtest.h>
#include "task_2/yurin_a_readers_writers/readers_writers.h"

TEST(Parallel_Operations_MPI, T1) {
}

TEST(Parallel_Operations_MPI, T2) {
}

TEST(Parallel_Operations_MPI,  T3) {
}

TEST(Parallel_Operations_MPI, T4) {
}

TEST(Parallel_Operations_MPI, T5) {
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
