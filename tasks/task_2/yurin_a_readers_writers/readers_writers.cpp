// Copyright 2023 Yurin Andrey
#include <algorithm>
#include "task_2/yurin_a_readers_writers/readers_writers.h"


#define DEFAULT_TAG 0
#define READER_START_TAG 1
#define WRITER_START_TAG 2
#define READER_READY_TAG 3
#define READER_END_TAG 4
#define WRITER_READY_TAG 5
#define WRITER_END_TAG 6


void StartNewReaders(const boost::mpi::communicator& world, size_t* localReaderCount) {
    boost::mpi::status status = world.recv(boost::mpi::any_source, boost::mpi::any_tag);
    world.send(status.source(), READER_START_TAG);
    (*localReaderCount)++;
}

void FinishCompletedReaders(
        const boost::mpi::communicator& world,
        size_t* localReaderCount,
        size_t* processesLeft
        ) {
    world.recv(boost::mpi::any_source, READER_END_TAG);
    (*localReaderCount)--;
    (*processesLeft)--;
}

void ExecuteWriter(const boost::mpi::communicator& world, const int& dest, size_t* processesLeft) {
    world.send(dest, WRITER_START_TAG);
    world.recv(dest, WRITER_END_TAG);
    (*processesLeft)--;
}

void Controller(const boost::mpi::communicator& world, const size_t& readerCount, const size_t& writerCount) {
    size_t processesLeft = std::min(readerCount + writerCount, static_cast<size_t>(world.size() - 1));
    while (processesLeft) {
        boost::mpi::status status;

        if ((world.iprobe(boost::mpi::any_source, WRITER_READY_TAG)).has_value()) {
            status = (world.recv(boost::mpi::any_source, WRITER_READY_TAG));
        } else {
            status = world.recv(boost::mpi::any_source, boost::mpi::any_tag);
        }

        if (status.tag() == READER_READY_TAG) {
            size_t localReaderCount = 1;
            world.send(status.source(), READER_START_TAG);

            while ((world.iprobe(boost::mpi::any_source, READER_READY_TAG)).has_value() &&
            !((world.iprobe(boost::mpi::any_source, WRITER_READY_TAG)).has_value())) {
                if (world.iprobe(boost::mpi::any_source, READER_END_TAG).has_value()) {
                    FinishCompletedReaders(world, &localReaderCount, &processesLeft);
                }
                StartNewReaders(world, &localReaderCount);
            }

            while (localReaderCount) {
                FinishCompletedReaders(world, &localReaderCount, &processesLeft);
            }

        } else if (status.tag() == WRITER_READY_TAG) {
            ExecuteWriter(world, status.source(), &processesLeft);
        }
    }
}

void Reader(const boost::mpi::communicator& world) {
    world.send(0, READER_READY_TAG);
    world.recv(0, READER_START_TAG);
    // critical section
    world.send(0, READER_END_TAG);
}

void Writer(const boost::mpi::communicator& world) {
    world.send(0, WRITER_READY_TAG);
    world.recv(0, WRITER_START_TAG);
    // critical section
    world.send(0, WRITER_END_TAG);
}

void ReadersWriters(const size_t readerCount, const size_t writerCount) {
    boost::mpi::communicator world;

    if (world.rank() == 0) {
        Controller(world, readerCount, writerCount);
    } else if (world.rank() <= readerCount) {
        Reader(world);
    } else if (world.rank() <= readerCount + writerCount) {
        Writer(world);
    }
}
