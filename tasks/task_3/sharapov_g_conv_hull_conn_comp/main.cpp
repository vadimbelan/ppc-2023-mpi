// Copyright 2023 Sharapov Georgiy
#include <mpi.h>
#include <gtest/gtest.h>
#include "task_3/sharapov_g_conv_hull_conn_comp/connected_component.h"
#include "task_3/sharapov_g_conv_hull_conn_comp/convex_hull.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    int ProcRank;
    int ProcNum;
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    //  DEBUG --------------------------------------

    int size = 8;
    int *matrix = nullptr;

    if (ProcRank == 0) {
        matrix = new int[size * size];
        int image[] = {
            1, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 1, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0,
            0, 1, 0, 0, 0, 0, 1, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 1,
        };
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[(i * size) + j] = image[(i * size) + j];
            }
        }
    }
    std::vector<point> ans;

    ans = convex_hull(matrix, size);

    // if (ProcRank == ProcNum - 1) {
    //     for (int i = 0; i < ans.size(); i++) {
    //         ans[i].print();
    //     }
    // }

    //  DEBUG --------------------------------------

    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    if (ProcRank != 0) {
        delete listeners.Release(listeners.default_result_printer());
    }

    //  int result = RUN_ALL_TESTS();
    MPI_Finalize();

    return 0;
    //  return result;
}
