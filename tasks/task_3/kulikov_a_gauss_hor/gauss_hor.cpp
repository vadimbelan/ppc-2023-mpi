// Copyright 2023 Kulikov Artem
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <functional>
#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>
#include "task_3/kulikov_a_gauss_hor/gauss_hor.h"

uint32_t getPxSum(const std::vector<uint8_t>& pic, int n) {
    uint32_t sum = 0;
    for (int i = 1; i < n - 1; i++)
        for (int j = 1; j < n - 1; j++)
            sum += pic[i*n + j];
    return sum;
}

inline uint8_t clamp(double v) {
    return std::min<double>(std::max<double>(v, 0), uint8_t(-1));
}

double gaussPdfExp(double x_sqruare, double sd) {
    double exponent = -x_sqruare;
    exponent /= 2 * sd * sd;
    return exp(exponent);
}

std::vector<double> get3x3GaussKernel(double sd) {
    std::vector<double> kernel(9);
    double norm = .0, pdf;
    for (int i = -1; i < 1+1; i++) {
        for (int j = -1; j < 1+1; j++) {
            pdf = gaussPdfExp(i * i + j * j, sd);
            kernel[(1+i)*3 + 1+j] = pdf;
            norm += pdf;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kernel[i * 3 + j] /= norm;
        }
    }
    return kernel;
}

std::vector<uint8_t> getExtPicture(int n) {
    int ext_sz = n + 2;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::vector<uint8_t> pic(ext_sz * ext_sz);
    for (int i = 1; i < ext_sz - 1; i++) {
        for (int j = 1; j < ext_sz - 1; j++) {
            pic[i * ext_sz + j] = gen() % uint8_t(-1);
        }
    }

    for (int i = 0; i < ext_sz-1; i++) {
        pic[1+i] = pic[1+i + ext_sz];
        pic[ext_sz * ext_sz - 1 - (1+i)] = pic[ext_sz * ext_sz - 1 - (1+i + ext_sz)];
        pic[(i + 2) * ext_sz - 1] = pic[(i + 2) * ext_sz - 1 - 1];
        pic[(ext_sz -2 - i) * ext_sz] = pic[(ext_sz -2 - i) * ext_sz + 1];
    }

    return pic;
}

std::vector<uint8_t> getParallelGauss(const std::vector<uint8_t>& orig, const std::vector<double>& kernel, int n) {
    boost::mpi::communicator world;
    int rank = world.rank(), p = world.size();
    int delta = (n - 2) / p;
    std::vector<uint8_t> row(n * (delta + 2));
    std::vector<uint8_t> result;
    std::vector<int> sizes;
    std::vector<int> displs(p);

    if (world.rank() == 0) {
        sizes = std::vector<int>(p, row.size());
        displs = std::vector<int>(p);
        int d = p;
        while (displs[d] = (--d) * n * delta) {}
    }
    boost::mpi::scatterv(world, orig, sizes, displs, row.data(), row.size(), 0);
    if (world.rank() == 0) {
        result.resize(n * n);
        std::copy(orig.begin(), orig.begin() + n, result.begin());
        std::copy(orig.rbegin(), orig.rbegin() + n, result.rbegin());
        std::copy(orig.begin(), orig.begin() + row.size(), row.begin());
        // row = std::vector<uint8_t>(orig.begin(), orig.begin() + row.size());
    }
    std::vector<uint8_t> row_cpy(row);
    int idx;
    for (int j = 0; j < delta; j++) {
        for (int i = 1; i < n-1; i++) {
            idx = n*(j+1) + i;
            row[idx] = clamp(
                kernel[0] * row_cpy[idx - n -1] +
                kernel[1] * row_cpy[idx - n] +
                kernel[2] * row_cpy[idx - n +1] +

                kernel[3] * row_cpy[idx -1] +
                kernel[4] * row_cpy[idx] +
                kernel[5] * row_cpy[idx +1] +

                kernel[6] * row_cpy[idx + n -1] +
                kernel[7] * row_cpy[idx + n] +
                kernel[8] * row_cpy[idx + n +1]);
        }
    }
    if (world.rank() == 0) {
        for (int i = 0; i < p; i++) {
            sizes[i] -= 2 * n;
            displs[i] += n;
        }
    }
    boost::mpi::gatherv(world, row.data() + n, n * delta, result.data(), sizes, displs, 0);
    return result;
}




std::vector<uint8_t> getSequentialGauss(const std::vector<uint8_t>& orig, const std::vector<double>& kernel, int n) {
    uint8_t* row;
    const uint8_t * row_cpy;
    std::vector<uint8_t> result(orig);
    for (int j = 0; j < n-2; j++) {
        row = result.data() + j * n;
        row_cpy = orig.data() + j * n;
        for (int i = 1; i < n-1; i++) {
            row[n + i] = clamp(
                kernel[0] * row_cpy[n + i - n -1] +
                kernel[1] * row_cpy[n + i - n] +
                kernel[2] * row_cpy[n + i - n +1] +

                kernel[3] * row_cpy[n + i -1] +
                kernel[4] * row_cpy[n + i] +
                kernel[5] * row_cpy[n + i +1] +

                kernel[6] * row_cpy[n + i + n -1] +
                kernel[7] * row_cpy[n + i + n] +
                kernel[8] * row_cpy[n + i + n +1]);
        }
    }
    return result;
}
