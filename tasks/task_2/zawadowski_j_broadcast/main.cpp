// Copyright 2023 Zawadowski Jan
#include <gtest/gtest.h>
#include "./broadcast.h"

TEST(Broadcast, Test_MPI_INT) {
    int sizeWorld, rank, sum = 0,
        root = 0, size = 10;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeWorld);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vector(size);

    if (rank == root) {
        for (int i = 0; i < size; i++)
            vector[i] = 0;
    }
    broadcast(vector.data(), size, MPI_INT, root, MPI_COMM_WORLD);
    vector[rank] = 1;

    MPI_Reduce(&vector[rank],
               &sum,
               1,
               MPI_INT,
               MPI_SUM,
               root,
               MPI_COMM_WORLD);

    if (rank == root)
        ASSERT_EQ(sum, sizeWorld);
}

TEST(Broadcast, Test_MPI_FLOAT) {
    int sizeWorld, rank,
        root = 0, size = 15;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeWorld);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    float sum = 0.0;
    std::vector<float> vector(size);

    if (rank == root) {
        for (int i = 0; i < size; i++)
            vector[i] = 0.0;
    }
    broadcast(vector.data(), size, MPI_FLOAT, root, MPI_COMM_WORLD);
    vector[rank] = 1.0;

    MPI_Reduce(&vector[rank],
               &sum,
               1,
               MPI_FLOAT,
               MPI_SUM,
               root,
               MPI_COMM_WORLD);

    if (rank == root)
        ASSERT_EQ(sum, sizeWorld);
}

TEST(Broadcast, Test_MPI_DOUBLE) {
    int sizeWorld, rank,
        root = 0, size = 20;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeWorld);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double sum = 0.0;
    std::vector<double> vector(size);

    if (rank == root) {
        for (int i = 0; i < size; i++)
            vector[i] = 0.0;
    }
    broadcast(vector.data(), size, MPI_DOUBLE, root, MPI_COMM_WORLD);
    vector[rank] = 1.0;

    MPI_Reduce(&vector[rank],
               &sum,
               1,
               MPI_DOUBLE,
               MPI_SUM,
               root,
               MPI_COMM_WORLD);

    if (rank == root)
        ASSERT_EQ(sum, sizeWorld);
}

TEST(Broadcast, Test_time) {
    int sizeWorld, rank, sum = 0,
        root = 0, size = 10;
    double t1, t2, t3, t4;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeWorld);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vector(size);

    if (rank == root) {
        for (int i = 0; i < size; i++)
            vector[i] = 1;
    }
    t1 = MPI_Wtime();
    broadcast(vector.data(), size, MPI_INT, root, MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    if (rank == 0) {
        for (int i = 0; i < size; i++)
            sum += vector[i];
    }
    t3 = MPI_Wtime();
    MPI_Bcast(vector.data(), size, MPI_INT, root, MPI_COMM_WORLD);
    t4 = MPI_Wtime();
    if (rank == root) {
        std::cout << "My Broadcast time: " << t2 - t1 <<
            '\n' << "MPI_Bcast time: " << t4 - t3 << '\n';
        ASSERT_EQ(sum, size);
    }
}

TEST(Broadcast, Test_sum) {
    int sizeWorld, rank, sum = 0,
        root = 0, size = 15;
    MPI_Comm_size(MPI_COMM_WORLD, &sizeWorld);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::vector<int> vector(size);

    if (rank == root) {
        for (int i = 0; i < size; i++)
            vector[i] = 1;
    }
    broadcast(vector.data(), size, MPI_INT, root, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size; i++)
            sum += vector[i];
    }
    if (rank == root)
        ASSERT_EQ(sum, size);
}

int main(int argc, char** argv) {
    int resultCode = 0;
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        MPI_Abort(MPI_COMM_WORLD, -1);
    resultCode = RUN_ALL_TESTS();
    MPI_Finalize();

    return resultCode;
}
