// Copyright 2023 Kulikov Artem
#include <gtest/gtest.h>
#include <vector>

#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/serialization/vector.hpp>

#include "./most_different_elements_in_vec.h"


TEST(dummy, dummy_test1) {
    ADD_FAILURE();
}

TEST(dummy, dummy_test2) {
    ADD_FAILURE();
}

TEST(dummy, dummy_test3) {
    ADD_FAILURE();
}

TEST(dummy, dummy_test4) {
    ADD_FAILURE();
}

TEST(dummy, dummy_test5) {
    ADD_FAILURE();
}


int main(int argc, char** argv) {
    boost::mpi::environment env(argc, argv);
    boost::mpi::communicator world;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    if (world.rank() != 0) {
        delete listeners.Release(ззlisteners.default_result_printer());
    }
    return RUN_ALL_TESTS();
}

