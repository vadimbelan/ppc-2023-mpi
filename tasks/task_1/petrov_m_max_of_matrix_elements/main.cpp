// Copyright 2023 Petrov Maksim
#include <gtest/gtest.h>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include"./max_of_matrix_elements.h"

TEST(Max_of_matrix_elem, Test_max_of_matrix_elem_1) {

    boost::mpi::communicator world;
    const int rows = 4;
    const int cols = 4;
    std::vector<int> matrix;
    
    if (world.rank() == 0) {
        matrix = init_matrix(rows, cols);
        
    }
    int global_max = getParallelOperations(matrix,rows,cols);

    if (world.rank() == 0) {
        
        int ref_max = getSequentialOperations(matrix);
        ASSERT_EQ(ref_max, global_max);
    }
}
TEST(Max_of_matrix_elem, Test_max_of_matrix_elem_2) {

    boost::mpi::communicator world;
    const int rows = 4;
    const int cols = 5;
    std::vector<int> matrix;
    
    if (world.rank() == 0) {
        matrix = init_matrix(rows, cols);
    }
    int global_max = getParallelOperations(matrix, rows, cols);

    if (world.rank() == 0) {
        
        int ref_max = getSequentialOperations(matrix);
        ASSERT_EQ(ref_max, global_max);
    }
}
TEST(Max_of_matrix_elem, Test_max_of_matrix_elem_3) {

    boost::mpi::communicator world;
    const int rows = 7;
    const int cols = 7;
    std::vector<int> matrix;
    
    if (world.rank() == 0) {
        matrix = init_matrix(rows, cols);
        matrix[48] = 60;
    }
    int global_max = getParallelOperations(matrix, rows, cols);

    if (world.rank() == 0) {
        
        int ref_max = getSequentialOperations(matrix);
        ASSERT_EQ(ref_max, global_max);
    }
}
TEST(Max_of_matrix_elem, Test_max_of_matrix_elem_4) {

    boost::mpi::communicator world;
    const int rows = 5;
    const int cols = 5;
    std::vector<int> matrix;
    
    if (world.rank() == 0) {
        matrix = init_matrix(rows, cols);
    }
    int global_max = getParallelOperations(matrix, rows, cols);

    if (world.rank() == 0) {
        
        int ref_max = getSequentialOperations(matrix);
        ASSERT_EQ(ref_max, global_max);
    }
}
TEST(Max_of_matrix_elem, Test_max_of_matrix_elem_5) {

    boost::mpi::communicator world;
    const int rows = 5;
    const int cols = 6;
    std::vector<int> matrix;
   
    if (world.rank() == 0) {
        matrix = init_matrix(rows, cols);
    }
    int global_max = getParallelOperations(matrix, rows, cols);

    if (world.rank() == 0) {
        
        int ref_max = getSequentialOperations(matrix);
        ASSERT_EQ(ref_max, global_max);
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