#ifndef PPC_2023_MPI_GAUSS_LENT_HORIZ_H
#define PPC_2023_MPI_GAUSS_LENT_HORIZ_H

std::vector<double> Gauss(std::vector<double> matrix, int size);

bool check_result(std::vector<double> matrix, std::vector<double> x, int size);

std::vector<double> create_random_matrix(int size);

#endif //PPC_2023_MPI_GAUSS_LENT_HORIZ_H
