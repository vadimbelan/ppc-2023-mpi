// Copyright 2023 Pivovarov Alexey

#include <mutex>
#include "task_2/pivovarov_a_producer_consumer/producer_consumer.h"


void producer_consumer_seq(int num_producers, int num_consumers, std::vector<int> results) {
    std::vector<int> buffer;
    std::mutex mutex;
    std::condition_variable cv_producer, cv_consumer;

    auto producer_thread = [&](int id) {
        for (int i = 0; i < num_producers; ++i) {
            std::unique_lock<std::mutex> lock(mutex);

            cv_producer.wait(lock, [&] { return buffer.size() < num_consumers; });

            buffer.push_back(id * 100 + i);

            cv_consumer.notify_one();
        }
    };

    auto consumer_thread = [&](int id) {
        for (int i = 0; i < num_consumers; ++i) {
            std::unique_lock<std::mutex> lock(mutex);

            cv_consumer.wait(lock, [&] { return !buffer.empty(); });

            int data = buffer.front();
            buffer.pop_back();

            cv_producer.notify_one();

            std::cout << "Consumer " << id << " consumed: " << data << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(num_producers);
    for (int i = 0; i < num_producers; ++i) {
        threads.emplace_back(producer_thread, i);
    }

    for (int i = 0; i < num_consumers; ++i) {
        threads.emplace_back(consumer_thread, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    results.push_back(1);
}

void producer_consumer_par(int num_producers, int num_consumers, std::vector<int> results) {
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int tasks_per_process = num_producers / size;
    int remainder = num_producers % size;

    int start = rank * tasks_per_process + std::min(rank, remainder);
    int end = start + tasks_per_process + (rank < remainder ? 1 : 0);

    for (int i = start; i < end; ++i) {
        int data = i;
        std::cout << "Producer " << rank << " produced: " << data << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    tasks_per_process = num_consumers / size;
    remainder = num_consumers % size;

    start = rank * tasks_per_process + std::min(rank, remainder);
    end = start + tasks_per_process + (rank < remainder ? 1 : 0);

    for (int i = start; i < end; ++i) {
        int data = i;
        std::cout << "Consumer " << rank << " consumed: " << data << ", Processed: " << data * 2 << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    results.push_back(1);
}
