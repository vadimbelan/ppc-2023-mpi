#include <vector>
#include <iostream>
#include <mpi.h>
#include "./average_of_vector_elements.h"

int main(int argc, char** argv) {
    size_t array_size = 5;
    int lower_bound = 1;
    int upper_bound = 11;

    std::vector<int> vector = fillVectorRandomNumbers(array_size, lower_bound, upper_bound);

    for (const auto& element : vector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    MPI_Init(&argc, &argv);

    double res = calculateAverageOfVectorElements(vector);

    std::cout << res << std::endl;

    MPI_Finalize();

    return 0;
}