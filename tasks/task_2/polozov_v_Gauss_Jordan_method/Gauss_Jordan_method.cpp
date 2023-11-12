// Copyright 2023 Polozov Vladislav

#include "task_2/polozov_v_Gauss_Jordan_method/Gauss_Jordan_method.h"

std::vector<double> getRandomMatrix(int n, int m) {
    std::random_device device;
    std::mt19937 generator(device());
    constexpr int mod = 1000;
    std::vector<double> ans(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[i * m + j] = generator() % mod - mod / 2;
        }
    }
    return ans;
}

std::vector<double> getParallelGaussJordan(std::vector<double> A, int n) {
    return {};
}

std::vector<double> getSequentialGaussJordan(std::vector<double> A, int n) {
    std::vector<double> ans(n);
    int m = n + 1;
    for(int i = 0;i<n;i++){
        //A[i][i] - центральный элемент
        double val = A[i * m + i];
        for(int j = 0;j<m;j++){
            // нормирую свою строку
            A[i * m + j] /= val;
        }
        for(int j = 0;j<n;j++){
            if(j == i) continue;
            //val = A[j][i]
            val = A[j * m + i];
            for(int k = 0;k<m;k++){
                //A[j][k] -= val * A[i][k]
                A[j * m + k] -= val * A[i * m + k];
            }
        }
    }
    constexpr double eps = 0.00000001;
    for(int i = 0;i<n;i++){
        ans[i] = A[i * m + n];
        if(abs(ans[i]) < eps)
            ans[i] = 0;
    }
    return ans;
}
