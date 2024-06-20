// Copyright 2023 Borisov Saveliy
#include <gtest/gtest.h>
#include <mpi.h>

#include <iostream>

#include "./grid_torus_topology.h"

TEST(MPI_TESTS, Test_Get_Next) {
    int rows = 3;
    int cols = 3;

    int next_1 = getNext(rows, cols, 0, 2);
    EXPECT_EQ(next_1, 2);

    int next_2 = getNext(rows, cols, 6, 3);
    EXPECT_EQ(next_2, 3);

    int next_3 = getNext(rows, cols, 2, 6);
    EXPECT_EQ(next_3, 0);
}

TEST(MPI_TESTS, Test_First_To_Last) {
    int rank, size, rows, cols;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> expected = {1, 0, 1};

    std::pair<int, int> sizeGrid = calculateGridSize(size);
    rows = sizeGrid.first;
    cols = sizeGrid.second;

    if (rows != -1) {
        std::vector<int> data = {0, 0, 0};
        if (rank == 0) {
            data = {1, 0, 1};
        }

        sendDataUsingGridTorus(data.data(), 3, MPI_INT, 0, size - 1, rows, cols, 0, MPI_COMM_WORLD);

        if (rank == size - 1) {
            EXPECT_EQ(data, expected);
        }
    }
}

TEST(MPI_TESTS, Test_Last_To_First) {
    int rank, size, rows, cols;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> expected = {2, 0, 2};

    std::pair<int, int> sizeGrid = calculateGridSize(size);
    rows = sizeGrid.first;
    cols = sizeGrid.second;

    if (rows != -1) {
        std::vector<int> data = {0, 0, 0};
        if (rank == size - 1) {
            data = {2, 0, 2};
        }

        sendDataUsingGridTorus(data.data(), 3, MPI_INT, size - 1, 0, rows, cols, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            ASSERT_EQ(data, expected);
        }
    }
}

TEST(MPI_TESTS, Test_First_To_Neighbour) {
    int rank, size, rows, cols;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> expected = {3, 0, 3};

    std::pair<int, int> sizeGrid = calculateGridSize(size);
    rows = sizeGrid.first;
    cols = sizeGrid.second;

    if (rows != -1) {
        std::vector<int> data = {0, 0, 0};
        if (rank == 0) {
            data = {3, 0, 3};
        }

        sendDataUsingGridTorus(data.data(), 3, MPI_INT, 0, 1, rows, cols, 0, MPI_COMM_WORLD);

        if (rank == 1) {
            ASSERT_EQ(data, expected);
        }
    }
}

TEST(MPI_TESTS, Test_Neighbour_To_First) {
    int rank, size, rows, cols;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> expected = {4, 0, 4};

    std::pair<int, int> sizeGrid = calculateGridSize(size);
    rows = sizeGrid.first;
    cols = sizeGrid.second;

    if (rows != -1) {
        std::vector<int> data = {0, 0, 0};
        if (rank == 1) {
            data = {4, 0, 4};
        }

        sendDataUsingGridTorus(data.data(), 3, MPI_INT, 1, 0, rows, cols, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            ASSERT_EQ(data, expected);
        }
    }
}


int main(int argc, char** argv) {
  int result_code = 0;

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::TestEventListeners& listeners =
      ::testing::UnitTest::GetInstance()->listeners();

  if (MPI_Init(&argc, &argv) != MPI_SUCCESS) MPI_Abort(MPI_COMM_WORLD, -1);
  result_code = RUN_ALL_TESTS();
  MPI_Finalize();

  return result_code;
}
