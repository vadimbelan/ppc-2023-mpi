#ifndef TASKS_TASK_1_DURANDIN_V_MAX_OF_VECTOR_ELEMENTS_H_
#define TASKS_TASK_1_DURANDIN_V_MAX_OF_VECTOR_ELEMENTS_H_

#include <mpi.h>

#include <limits>
#include <random>
#include <vector>

int64_t sub_get_max_element_of_vector(const std::vector<int64_t>& _vector);
int64_t par_get_max_element_of_vector(const std::vector<int64_t>& _vector);
void create_random_vector(std::vector<int64_t>& _vector, const size_t size,
                          const int64_t min, const int64_t max);

#endif  // !TASKS_TASK_1_DURANDIN_V_MAX_OF_VECTOR_ELEMENTS_H_
