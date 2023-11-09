// Copyright 2023 Polozov Vladislav
#include <gtest/gtest.h>

#include "./most_different.h"

TEST(MPI_TESTS, Test_small) {

}

TEST(MPI_TESTS, Test_all_zero) {

}

TEST(MPI_TESTS, Test_less_two) {

}

TEST(MPI_TESTS, Test_end) {

}

TEST(MPI_TESTS, Test_random) {

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
