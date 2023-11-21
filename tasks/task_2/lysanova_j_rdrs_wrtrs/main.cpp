// Copyright 2023 Lysanova Julia
#include <gtest/gtest.h>
#include "./rdrs_wrtrs.h"
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>



TEST(Readers_Writers_Problem, RWT_1) {
    boost::mpi::communicator world;
}



TEST(Readers_Writers_Problem, RWT_2) {
    boost::mpi::communicator world;
}



TEST(Readers_Writers_Problem, RWT_3) {
    boost::mpi::communicator world;
}



TEST(Readers_Writers_Problem, RWT_4) {
    boost::mpi::communicator world;
}



TEST(Readers_Writers_Problem, RWT_5) {
    boost::mpi::communicator world;
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
