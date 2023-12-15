// Copyright 2023 Polozov Vladislav

#include "task_1/polozov_v_max_values_by_column_matrix/max_values_by_column_matrix.h"

std::vector<int> getRandomMatrix(int n, int m) {
    std::random_device device;
    std::mt19937 generator(device());
    constexpr int mod = 1000;
    std::vector<int> ans(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[i * m + j] = generator() % mod - mod / 2;
        }
    }
    return ans;
}

std::vector<int> getParallelMax(const std::vector<int> &A, int n, int m) {
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    int delta = m / countProc;
    int remain = m % countProc;
    std::vector<int> answer;
    std::vector<int> sendcounts;
    std::vector<int> displs;
    std::vector<int> mydata(delta * n);
    if (rank == 0) {
        answer.resize(m, -1e9);
        sendcounts.resize(countProc, delta);
        sendcounts[0] += remain;
        displs.resize(countProc, 0);
        for (int i = 1; i < countProc; i++) {
            displs[i] = displs[i - 1] + sendcounts[i - 1];
        }
        mydata.resize((delta + remain) * n);
    }
    MPI_Datatype mytype, column;
    MPI_Type_vector(n, 1, m, MPI_INT, &mytype);
    MPI_Type_commit(&mytype);
    MPI_Type_create_resized(mytype, 0, sizeof(int) * 1, &column);
    MPI_Type_commit(&column);
    MPI_Scatterv(A.data(), sendcounts.data(), displs.data(), column, mydata.data(),
                 static_cast<int>(mydata.size()), MPI_INT, 0, MPI_COMM_WORLD);
    std::vector<int> anst;
    int sizemx = mydata.size() / n;
    for (int i = 0; i < sizemx; i++) {
        int mx = INT_MIN;
        for (int j = 0; j < n; j++) {
            mx = std::max(mx, mydata[i * n + j]);
        }
        anst.push_back(mx);
    }
    MPI_Gatherv(anst.data(), anst.size(), MPI_INT, answer.data(), sendcounts.data(), displs.data(), MPI_INT, 0,
                MPI_COMM_WORLD);
    return answer;
}

std::vector<int> getSequentialMax(const std::vector<int> &A, int n, int m) {
    std::vector<int> ans(m);
    for (int i = 0; i < m; i++) {
        int mx = -1e9;
        for (int j = 0; j < n; j++) {
            // A[j][i] = A[j * m + i]
            mx = std::max(mx, A[j * m + i]);
        }
        ans[i] = mx;
    }
    return ans;
}
