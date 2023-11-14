// Copyright 2023 Polozov Vladislav

#include "task_2/polozov_v_gauss_jordan_method/gauss_jordan_method.h"

int CalcRank(std::vector<double> A, int n) {
    int rank = n;
    constexpr double eps = 0.00000001;
    auto swap_row = [&](int x, int y){
        for (int i = 0; i < n; i++) {
            std::swap(A[x * n + i], A[y * n + i]);
        }
    };
    for (int row = 0; row < rank; row++) {
        if (abs(A[row * n + row]) > eps) {
            for (int col = 0; col < n; col++) {
                if (col != row) {
                    double val = A[col * n + row] / A[row * n + row];
                    for (int i = 0; i < rank; i++)
                        A[col * n + i] -= val * A[row * n + i];
                }
            }
        } else {
            bool find = false;
            for (int i = row + 1; i < n; i++) {
                if (abs(A[i * n + row]) > eps) {
                    swap_row(row, i);
                    find = true;
                    break;
                }
            }
            if (!find) {
                rank--;
                for (int i = 0; i < n; i++)
                    A[i * n + row] = A[i * n + rank];
            }
            row--;
        }
    }
    return rank;
}

std::vector<double> generateMatrix(int n) {
    std::random_device device;
    std::mt19937 generator(device());
    constexpr int mod = 1000;
    std::vector<double> A = getRandomMatrix(n, n);
    while (CalcRank(A, n) != n) {
        A = getRandomMatrix(n, n);
    }
    std::vector<double> matr;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matr.push_back(A[i * n + j]);
        }
        int val = generator();
        if (val < 0) {
            val *= -1;
        }
        val %= mod;
        val -= mod / 2;
        matr.push_back(val);
    }
    return matr;
}

std::vector<double> getRandomMatrix(int n, int m) {
    std::random_device device;
    std::mt19937 generator(device());
    constexpr int mod = 1000;
    std::vector<double> ans(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int val = generator();
            if (val < 0) {
                val *= -1;
            }
            val %= mod;
            val -= mod / 2;
            ans[i * m + j] = val;
        }
    }
    return ans;
}

std::vector<double> getParallelGaussJordan(std::vector<double> A, int n) {
    int m = n + 1;
    constexpr double eps = 0.00000001;
    int rank = 0;
    int countProc = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &countProc);
    int delta = n / countProc;
    int remain = n % countProc;
    std::vector<double> answer;
    std::vector<double> center_row;
    std::vector<double> cur_rows;
    std::vector<int> sendcounts;
    std::vector<int> displs;
    std::vector<int> who;
    cur_rows.resize(delta * m);
    center_row.resize(m);
    auto swap_row = [&](int x, int y){
        for (int i = 0; i < m; i++) {
            std::swap(A[x * m + i], A[y * m + i]);
        }
    };
    if (rank == 0) {
        sendcounts.resize(countProc, delta * m);
        sendcounts[0] += remain * m;
        displs.resize(countProc, 0);
        for (int i = 1; i < countProc; i++) {
            displs[i] = displs[i - 1] + sendcounts[i - 1];
        }
        who.resize(n);
        for (int i = 0; i < delta + remain; i++) {
            who[i] = 0;
        }
        int cur = delta + remain;
        for (int i = 1; i < countProc; i++) {
            for (int j = 0; j < delta; j++) {
                who[cur] = i;
                cur++;
            }
        }
        cur_rows.resize(sendcounts[0]);
    }

    for (int i = 0; i < n; i++) {
        int rank_block;
        int num_row_block;
        double val;
        if (rank == 0) {
            if (abs(A[i * m + i]) < eps) {
                for (int j = i + 1; j < n; j++) {
                    if (abs(A[j * m + i]) > eps) {
                        swap_row(i, j);
                        break;
                    }
                }
            }
            val = A[i * m + i];
            for (int j = 0; j < m; j++) {
                A[i * m + j] /= val;
                center_row[j] = A[i * m + j];
            }
            rank_block = who[i];
            num_row_block = 0;
            while (i - num_row_block >= 0 && who[i - num_row_block] == who[i]) {
                num_row_block++;
            }
            num_row_block--;
        }
        MPI_Scatterv(A.data(), sendcounts.data(), displs.data(), MPI_DOUBLE, cur_rows.data(), cur_rows.size(),
                     MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(center_row.data(), m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&rank_block, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&num_row_block, 1, MPI_INT, 0, MPI_COMM_WORLD);
        for (int j = 0; j < (cur_rows.size() / m); j++) {
            if (rank == rank_block && j == num_row_block) continue;
            val = cur_rows[j * m + i];
            for (int k = 0; k < m; k++) {
                cur_rows[j * m + k] -= val * center_row[k];
            }
        }
        MPI_Gatherv(cur_rows.data(), cur_rows.size(), MPI_DOUBLE, A.data(), sendcounts.data(), displs.data(),
                    MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    if (rank == 0) {
        answer.resize(n);
        for (int i = 0; i < n; i++) {
            answer[i] = A[i * m + n];
            double val = answer[i];
            if (val < 0)
                val *= -1;
            if (val < eps)
                answer[i] = 0;
        }
    }
    return answer;
}

std::vector<double> getSequentialGaussJordan(std::vector<double> A, int n) {
    std::vector<double> ans(n);
    constexpr double eps = 0.00000001;
    int m = n + 1;
    auto swap_row = [&](int x, int y){
        for (int i = 0; i < m; i++) {
            std::swap(A[x * m + i], A[y * m + i]);
        }
    };
    for (int i = 0; i < n; i++) {
        if (abs(A[i * m + i]) < eps) {
            for (int j = i + 1; j < n; j++) {
                if (abs(A[j * m + i]) > eps) {
                    swap_row(i, j);
                    break;
                }
            }
        }
        double val = A[i * m + i];
        for (int j = 0; j < m; j++) {
            A[i * m + j] /= val;
        }
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            val = A[j * m + i];
            for (int k = 0; k < m; k++) {
                A[j * m + k] -= val * A[i * m + k];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        ans[i] = A[i * m + n];
        double val = ans[i];
        if (val < 0)
            val *= -1;
        if (val < eps)
            ans[i] = 0;
    }
    return ans;
}
