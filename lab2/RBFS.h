#ifndef UNTITLED_RBFS_H
#define UNTITLED_RBFS_H
#include "LDFS.h"
#include <iostream>
#include <queue>

struct LessThanByF
{
    bool operator()(NodeWithPrice*& lhs, NodeWithPrice*& rhs) const
    {
        return lhs->getF() > rhs->getF();
    }
};

void RBFS(NodeWithPrice * start, bool &failure, NodeWithPrice *&res);

void RecBFS(NodeWithPrice  *cur, int& f_limit, bool &failure, NodeWithPrice *& res);

bool isPossible(int x, int y, Node* per);

void clearQueue( std::priority_queue<NodeWithPrice*, std::vector<NodeWithPrice*>, LessThanByF>& tmp);

void clearQueue_for_statistics( std::priority_queue<NodeWithPrice*, std::vector<NodeWithPrice*>, LessThanByF> &tmp, int& inMem);

void RBFS_for_statistics(NodeWithPrice * start, bool &failure, NodeWithPrice *&res,
                         long long unsigned memory_limit, long long unsigned time_limit,
                         int& iterations, int& angles, int& nodeOverall, int& nodeInMem);

void RecRBFS_for_statistics(NodeWithPrice  *cur, int& f_limit, bool &failure, NodeWithPrice *& res,
                            uint64_t memory_limit, PROCESS_MEMORY_COUNTERS& info, uint64_t startUsedRAM,
                            long long unsigned time_limit, time_point<std::chrono::high_resolution_clock> clockStart,
                            int& iterations, int& angles, int& nodeOverall, int& nodeInMem);

void RBFS_test();

#endif //UNTITLED_RBFS_H
