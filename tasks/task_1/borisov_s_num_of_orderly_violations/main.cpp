// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "./orderly_violations.h"

TEST(Violations_Numbers_MPI, Test_Random_Vector) {
    boost::mpi::communicator world;
    std::vector<int> global_vector;
    const int vector_size = 120;

    if (world.rank() == 0) {
        global_vector = getRandomVector(vector_size);
    }

    int global_violations_number = getViolationsInParallel(global_vector);

    if (world.rank() == 0) {
        int sequential_violations_number = getViolationsSequentially(global_vector);
        ASSERT_EQ(sequential_violations_number, global_violations_number);
    }
}

TEST(Violations_Numbers_MPI, Test_Random_Vector_With_One_Element) {
    boost::mpi::communicator world;
    std::vector<int> global_vector;
    const int vector_size = 1;

    if (world.rank() == 0) {
        global_vector = getRandomVector(vector_size);
    }

    int global_violations_number = getViolationsInParallel(global_vector);

    if (world.rank() == 0) {
        int sequential_violations_number = getViolationsSequentially(global_vector);
        ASSERT_EQ(sequential_violations_number, global_violations_number);
    }
}

TEST(Violations_Numbers_MPI, Test_Manual_Filled_Vector) {
    boost::mpi::communicator world;
    std::vector<int> global_vector{ 5, 4, 6, -7, 8, 9, 0 };

    int global_violations_number = getViolationsInParallel(global_vector);

    if (world.rank() == 0) {
        int sequential_violations_number = getViolationsSequentially(global_vector);
        ASSERT_EQ(sequential_violations_number, global_violations_number);
    }
}

TEST(Violations_Numbers_MPI, Test_Manual_Filled_Vector_With_One_Element) {
    boost::mpi::communicator world;
    std::vector<int> global_vector{ 1 };

    int global_violations_number = getViolationsInParallel(global_vector);

    if (world.rank() == 0) {
        int sequential_violations_number = getViolationsSequentially(global_vector);
        ASSERT_EQ(sequential_violations_number, global_violations_number);
    }
}

TEST(Violations_Numbers_MPI, Test_Vector_With_All_Same_Elements) {
    boost::mpi::communicator world;
    std::vector<int> global_vector{ 5, 5, 5, 5, 5, 5, 5 };

    int global_violations_number = getViolationsInParallel(global_vector);

    if (world.rank() == 0) {
        int sequential_violations_number = getViolationsSequentially(global_vector);
        ASSERT_EQ(sequential_violations_number, global_violations_number);
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
