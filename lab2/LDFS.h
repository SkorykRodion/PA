//
// Created by ROS on 26.10.2022.
//

#include <iostream>
#include <vector>

#include <chrono>

#include "Node.h"
#include "windows.h"
#include "psapi.h"

using namespace std::chrono;

#ifndef UNTITLED_LDFS_H
#define UNTITLED_LDFS_H



void LDFS(Node*, int limit, bool &failure, Node*& res);

void RecDFS(Node* cur, int limit, bool &cutoff, bool &failure, Node*& res);

bool isPossible(int, int, Node*);

void LDFS_with_limits(Node* start, int limit, bool &failure, Node*&res,
                      long long unsigned memory_limit, long long unsigned time_limit);

void RecDFSLDFS_with_limits(Node *cur, int limit, bool &cutoff, bool &failure, Node*& res, uint64_t memory_limit,
                            PROCESS_MEMORY_COUNTERS& info, uint64_t startUsedRAM,
                            long long unsigned time_limit, time_point<std::chrono::high_resolution_clock> clockStart);

void LDFS_for_statistics(Node* start, int limit, bool &failure, Node*&res,
                         long long unsigned memory_limit, long long unsigned time_limit,
                         int& iterations, int& angles, int& nodeOverall, int& nodeInMem);

void RecDFSLDFS_for_statistics(Node *cur, int limit, bool &cutoff, bool &failure, Node*& res, uint64_t memory_limit,
                               PROCESS_MEMORY_COUNTERS& info, uint64_t startUsedRAM,
                               long long unsigned time_limit, time_point<std::chrono::high_resolution_clock> clockStart,
                               int& iterations, int& angles, int& nodeOverall, int& nodeInMem);

void LDFS_test();

#endif //UNTITLED_LDFS_H
