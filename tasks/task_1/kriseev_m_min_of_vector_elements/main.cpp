// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>
#include <vector>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/timer.hpp>
#include "min_of_vector_elements.h"

TEST(Min_Of_Vector_Elements_MPI, one_element)
{
    boost::mpi::communicator world;
    std::vector<int> data = { 1 };

    int parallelResult = MinElementsInVectorParallel(data);

    if(world.rank() == 0)
    {
        int sequentialResult = MinElementsInVectorSequential(data);
        ASSERT_EQ(parallelResult, sequentialResult);
        ASSERT_EQ(parallelResult, 1);
    }

}

TEST(Min_Of_Vector_Elements_MPI, four_elements)
{
    boost::mpi::communicator world;
    std::vector<int> data = { 5, 3, 2, 4 };

    int parallelResult = MinElementsInVectorParallel(data);

    if(world.rank() == 0)
    {
        int sequentialResult = MinElementsInVectorSequential(data);
        ASSERT_EQ(parallelResult, sequentialResult);
        ASSERT_EQ(parallelResult, 2);
    }

}

TEST(Min_Of_Vector_Elements_MPI, random_elements)
{
    srand(time(0));
    boost::mpi::communicator world;
    std::vector<int> data (100);
    for(int i = 0; i < 100; ++i)
    {
        data.emplace_back(rand() % 100);
    }
    boost::mpi::timer timer;
    int parallelResult = MinElementsInVectorParallel(data);

    if(world.rank() == 0)
    {
        std::cout << "parallel time:\t" << timer.elapsed() << "\n";
        timer.restart();
        int sequentialResult = MinElementsInVectorSequential(data);
        std::cout << "sequential time:\t" << timer.elapsed() << "\n";

        ASSERT_EQ(parallelResult, sequentialResult);
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
