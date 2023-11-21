// Copyright 2023 Yurin Andrey
#ifndef TASKS_TASK_2_YURIN_A_READERS_WRITERS_READERS_WRITERS_H_
#define TASKS_TASK_2_YURIN_A_READERS_WRITERS_READERS_WRITERS_H_

#include <utility>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>


void Controller(const boost::mpi::communicator& world, const size_t& readerCount, const size_t& writerCount);
void Writer(const boost::mpi::communicator& world);
void Reader(const boost::mpi::communicator& world);
void ReadersWriters(const std::size_t readerCount, const std::size_t writerCount);

#endif  // TASKS_TASK_2_YURIN_A_READERS_WRITERS_READERS_WRITERS_H_
