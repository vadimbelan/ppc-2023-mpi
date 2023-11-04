// Copyright 2023 Kuznetsov Artem
#include "task_3/kuznetsov_a_contrast_enhancement/contrast_enhancement.h"

std::vector<uint8_t> create_random_image(size_t m, size_t n, uint8_t min,
                                         uint8_t max) {
  if (m * n == 0) return std::vector<uint8_t>();

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min, max);

  size_t size = m * n;
  std::vector<uint8_t> arr(size);
  for (auto& elem : arr) elem = dist(gen);

  return arr;
}

void seq_increase_contrast(std::vector<uint8_t>* image, uint8_t old_min,
                           uint8_t old_max, uint8_t new_min, uint8_t new_max) {
  if (old_min == old_max || image->size() == 0) return;
  for (auto& pix : *image) {
    pix = (pix - old_min) * (new_max - new_min) / (old_max - old_min) + new_min;
  }
}

void par_increase_contrast(std::vector<uint8_t>* image, size_t m, size_t n,
                           uint8_t new_min, uint8_t new_max, MPI_Comm comm) {
  int rank = 0;
  int size_world = 0;
  size_t count_pix = image->size();

  if (count_pix < m * n || count_pix == 0) return;

  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size_world);

  const int chunk = static_cast<int>(count_pix / size_world);
  const int tail = static_cast<int>(count_pix % size_world);

  std::vector<int> send_counts(size_world, 0);
  std::vector<int> displs(size_world, 0);

  if (chunk != 0) {
    for (int i = 0; i < size_world - 1; ++i) {
      send_counts[i] = chunk;
      displs[i] = i * chunk;
    }
    send_counts[size_world - 1] = static_cast<int>(
        (tail == 0) ? chunk : count_pix - (size_world - 1) * chunk);
    displs[size_world - 1] = (size_world - 1) * chunk;
  } else {
    for (int i = 0; i < count_pix; ++i) {
      send_counts[i] = 1;
      displs[i] = i;
    }
  }

  uint8_t global_min = 255;
  uint8_t global_max = 0;

  std::vector<uint8_t> local_img(send_counts[rank]);

  // FIND MAX MIN VALUES IN IMAGE
  MPI_Scatterv(image->data(), send_counts.data(), displs.data(), MPI_UINT8_T,
               local_img.data(), send_counts[rank], MPI_UINT8_T, 0, comm);

  uint8_t local_min = 255;
  uint8_t local_max = 0;

  if (rank < count_pix) {
    local_min = *std::min_element(local_img.begin(), local_img.end());
    local_max = *std::max_element(local_img.begin(), local_img.end());
  }

  // REDUCE RESULTS
  MPI_Allreduce(&local_min, &global_min, 1, MPI_UINT8_T, MPI_MIN, comm);
  MPI_Allreduce(&local_max, &global_max, 1, MPI_UINT8_T, MPI_MAX, comm);

  // RUN SEQ
  seq_increase_contrast(&local_img, global_min, global_max, new_min, new_max);

  // GATHER RESULTS
  if (rank < count_pix) {
    MPI_Gatherv(local_img.data(), send_counts[rank], MPI_UINT8_T, image->data(),
                send_counts.data(), displs.data(), MPI_UINT8_T, 0, comm);
  }
}
