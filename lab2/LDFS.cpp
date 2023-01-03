//
// Created by ROS on 26.10.2022.
//

#include "LDFS.h"

void LDFS(Node* start, int limit, bool &failure, Node*&res) {
    bool cutoff = false;
    failure = true;
    RecDFS(start, limit, cutoff, failure, res);
    if(cutoff == true)
        std::cout<<"memory or time etention"<<std::endl;
}

void RecDFS(Node *cur, int limit, bool &cutoff, bool &failure, Node*& res) {



    int row[] = { -1, 0, 1, 0 };
    int col[] = { 0, -1, 0, 1 };

    cutoff = false;
    if(isSolution(*cur))
    {
        res= cur;
        failure = false;
    }
    else if(cur->getLevel() == limit)
        cutoff = true;
    else
        for(int i=0; i<4 && failure; ++i)
        {
            int x_tmp= cur->getX() + row[i];
            int y_tmp= cur->getY() + col[i];
            if(isPossible(x_tmp, y_tmp, cur->getParent()))
            {
                Node* next = new Node(cur, x_tmp, y_tmp);
                RecDFS(next, limit, cutoff, failure, res);
            }

        }
}

bool isPossible(int x, int y, Node* per) {
    if(per == nullptr)
        return (x>=0 && x<=2)&&(y>=0 && y<=2);
    else
        return (x>=0 && x<=2)&&(y>=0 && y<=2) && x!=per->getX() && y!=per->getY();
}




void LDFS_with_limits(Node* start, int limit, bool &failure, Node*&res,
                      long long unsigned memory_limit, long long unsigned time_limit) {
    bool cutoff = false;
    failure = true;

    uint64_t startUsedRAM(0);
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    startUsedRAM = info.WorkingSetSize;

    auto clockStart =  high_resolution_clock::now();


    RecDFSLDFS_with_limits(start, limit, cutoff, failure, res, memory_limit, info, startUsedRAM, time_limit, clockStart);
}

void RecDFSLDFS_with_limits(Node *cur, int limit, bool &cutoff, bool &failure, Node*& res, uint64_t memory_limit,
                            PROCESS_MEMORY_COUNTERS& info, uint64_t startUsedRAM,
                            long long unsigned time_limit, time_point<std::chrono::high_resolution_clock> clockStart) {

    int row[] = { -1, 0, 1, 0 };
    int col[] = { 0, -1, 0, 1 };

    uint64_t currentUsedRAM(0);
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    currentUsedRAM = info.WorkingSetSize - startUsedRAM;

    if(currentUsedRAM>memory_limit){
        cutoff = true;
        return;
    }

    auto clockCur =  high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(clockCur - clockStart);
    if(duration.count() > time_limit){
        cutoff = true;
        return;
    }

    cutoff = false;
    if(isSolution(*cur))
    {
        res= cur;
        failure = false;
    }
    else if(cur->getLevel() == limit)
        cutoff = true;
    else
        for(int i=0; i<4 && failure; ++i)
        {
            int x_tmp= cur->getX() + row[i];
            int y_tmp= cur->getY() + col[i];
            if(isPossible(x_tmp, y_tmp, cur->getParent()))
            {
                Node* next = new Node(cur, x_tmp, y_tmp);
                RecDFSLDFS_with_limits(next, limit, cutoff, failure, res, memory_limit, info, startUsedRAM, time_limit, clockStart);
            }

        }
}

void LDFS_for_statistics(Node* start, int limit, bool &failure, Node*&res,
                         long long unsigned memory_limit, long long unsigned time_limit,
                         int& iterations, int& angles, int& nodeOverall, int& nodeInMem) {
    bool cutoff = false;
    failure = true;

    uint64_t startUsedRAM(0);
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    startUsedRAM = info.WorkingSetSize;

    auto clockStart =  high_resolution_clock::now();

    iterations = 0;
    angles =0;
    nodeOverall=1;
    nodeInMem=1;


    RecDFSLDFS_for_statistics(start, limit, cutoff, failure, res,
                              memory_limit, info, startUsedRAM, time_limit, clockStart,
                              iterations, angles, nodeOverall, nodeInMem);
}

void RecDFSLDFS_for_statistics(Node *cur, int limit, bool &cutoff, bool &failure, Node*& res, uint64_t memory_limit,
                            PROCESS_MEMORY_COUNTERS& info, uint64_t startUsedRAM,
                            long long unsigned time_limit, time_point<std::chrono::high_resolution_clock> clockStart,
                               int& iterations, int& angles, int& nodeOverall, int& nodeInMem) {
    iterations++;
    int row[] = { -1, 0, 1, 0 };
    int col[] = { 0, -1, 0, 1 };

    uint64_t currentUsedRAM(0);
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    currentUsedRAM = info.WorkingSetSize - startUsedRAM;

    if(currentUsedRAM>memory_limit){
        cutoff = true;
        return;
    }

    auto clockCur =  high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(clockCur - clockStart);
    if(duration.count() > time_limit){
        cutoff = true;
        return;
    }

    cutoff = false;
    if(isSolution(*cur))
    {
        res= cur;
        failure = false;
    }
    else if(cur->getLevel() == limit){
        cutoff = true;
        angles++;
    }
    else
        for(int i=0; i<4 && failure; ++i)
        {
            int x_tmp= cur->getX() + row[i];
            int y_tmp= cur->getY() + col[i];
            if(isPossible(x_tmp, y_tmp, cur->getParent()))
            {
                nodeInMem++;
                nodeOverall++;
                Node* next = new Node(cur, x_tmp, y_tmp);
                RecDFSLDFS_for_statistics(next, limit, cutoff, failure, res,
                                          memory_limit, info, startUsedRAM, time_limit, clockStart,
                                          iterations, angles, nodeOverall, nodeInMem);
            }

        }
}

void LDFS_test(){
    Node *res;
    bool fail;
    int iterations, angles, nodeOverall,  nodeInMem;
    bool sol = false;
    Node* start;
    while (!sol){
        start = new Node();
        sol = start->isSolvable();
    }
    LDFS_for_statistics(start, 40, fail, res, (long long unsigned) 8*1024*1024*1024, 1000*60*60*30,
                        iterations, angles, nodeOverall,  nodeInMem);
    if(!fail)
        res->showPath();
    else{
        start->display();
        std::cout<<"fail";
    }
    std::cout<<"\n--------------\n";
    std::cout<<"iterations: "<<iterations<<"\n";
    std::cout<<"angles: "<<angles<<"\n";
    std::cout<<"states: "<<nodeOverall<<"\n";
    std::cout<<"states in memory:"<<nodeInMem<<"\n";
}
