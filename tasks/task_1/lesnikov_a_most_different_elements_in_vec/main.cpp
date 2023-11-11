// Copyright 2023 Kulikov Artem
#include <gtest/gtest.h>
#include <vector>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/serialization/vector.hpp>

#include "./most_different_elements_in_vec.h"


TEST(Parallel_Most_Different_Elements_In_Vector_MPI, Random_Test_1) {
    boost::mpi::communicator world;

    std::vector<int> random_vector;
    const size_t n = 1000;

    if (world.rank() == 0) {
        random_vector = getRandomVector(n);
    }

    std::vector<std::pair<size_t, size_t>> parallel_most_diff = getParallelMostDifferentElements(random_vector);

    if (world.rank() == 0) {
        std::vector<std::pair<size_t, size_t>> sequential_most_diff = getSequentialMostDifferentElements(random_vector);

        ASSERT_EQ(sequential_most_diff, parallel_most_diff);
    }
}

TEST(Parallel_Most_Different_Elements_In_Vector_MPI, Random_Test_2) {
    boost::mpi::communicator world;

    std::vector<int> random_vector;
    const size_t n = 1000;

    if (world.rank() == 0) {
        random_vector = getRandomVector(n);
    }

    std::vector<std::pair<size_t, size_t>> parallel_most_diff = getParallelMostDifferentElements(random_vector);

    if (world.rank() == 0) {
        std::vector<std::pair<size_t, size_t>> sequential_most_diff = getSequentialMostDifferentElements(random_vector);

        ASSERT_EQ(sequential_most_diff, parallel_most_diff);
    }
}

TEST(Parallel_Most_Different_Elements_In_Vector_MPI, Test_With_Size_Less_Than_2) {
    boost::mpi::communicator world;
    std::vector<int> vec_1;
    std::vector<int> vec_2(1);

    std::vector<std::pair<size_t, size_t>> most_dif_1 = getParallelMostDifferentElements(vec_1);
    std::vector<std::pair<size_t, size_t>> most_dif_2 = getParallelMostDifferentElements(vec_2);

    if (world.rank() == 0) {
        ASSERT_EQ(most_dif_1.size(), 0);
        ASSERT_EQ(most_dif_2.size(), 0);
    }
}

TEST(Parallel_Most_Different_Elements_In_Vector_MPI, Test_With_Size_2) {
    boost::mpi::communicator world;
    std::vector<int> vec = {1, 2};

    std::vector<std::pair<size_t, size_t>> most_dif = getParallelMostDifferentElements(vec);
    std::vector<std::pair<size_t, size_t>> expected = {{0, 1}};

    if (world.rank() == 0) {
        ASSERT_EQ(most_dif, expected);
    }
}

TEST(Parallel_Most_Different_Elements_In_Vector_MPI, manual_test) {
    boost::mpi::communicator world;

    std::vector<int> vec;

    vec = {4, 3, 10, 23, 100, 1, 100, 1};

    std::vector<std::pair<size_t, size_t>> most_dif = getParallelMostDifferentElements(vec);
    std::vector<std::pair<size_t, size_t>> expected = {{4, 5}, {6, 7}};

    if (world.rank() == 0) {
        ASSERT_EQ(most_dif, expected);
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

    /*
    std::vector<int> vec = {4, 3};

    std::vector<std::pair<size_t, size_t>> most_dif = getParallelMostDifferentElements(vec);

    std::cout << "\n\nDONE\n\n" << std::endl;

    if (world.rank() == 0) {
        std::cout << most_dif[0].first << " " << most_dif[0].second << std::endl;
    }
    */

    return 0;
}

