#include "RBFS.h"




void RBFS(NodeWithPrice *start, bool &failure, NodeWithPrice *&res) {
    bool cutoff = false;
    failure = true;
    int f_limit = 10000;
    RecBFS(start, f_limit, failure, res);
}

void RecBFS(NodeWithPrice *cur, int& f_limit, bool &failure, NodeWithPrice *&res) {

    int row[] = { -1, 0, 1, 0 };
    int col[] = { 0, -1, 0, 1 };

    if(isSolution(*cur))
    {
        res= cur;
        failure = false;
        return;
    }
    std::priority_queue<NodeWithPrice*, std::vector<NodeWithPrice*>, LessThanByF> successors;
    for(int i=0; i<4 && failure; ++i)
    {
        int x_tmp= cur->getX() + row[i];
        int y_tmp= cur->getY() + col[i];
        if(isPossible(x_tmp, y_tmp, cur->getParent()))
        {
            NodeWithPrice* tmp = new NodeWithPrice(cur, x_tmp, y_tmp);
            successors.push(tmp);
        }

    }
    if (successors.empty()){
        f_limit = 10000;
        return;
    }

    while (failure && !successors.empty()){
        NodeWithPrice* best = successors.top();
        if (best->getF() > f_limit){
            f_limit = best->getF();
            clearQueue(successors);
            return;
        }
        successors.pop();

        int f_lim_tmp;
        if (!successors.empty())
            f_lim_tmp =std::min(f_limit, successors.top()->getF());
        else
            f_lim_tmp =f_limit;

        RecBFS(best, f_lim_tmp, failure, res);
        best->setF(f_lim_tmp);
        successors.push(best);
    }


}

void clearQueue( std::priority_queue<NodeWithPrice*, std::vector<NodeWithPrice*>, LessThanByF> &tmp) {
    while (!tmp.empty()){
        delete tmp.top();
        tmp.pop();
    }
}

void clearQueue_for_statistics( std::priority_queue<NodeWithPrice*, std::vector<NodeWithPrice*>, LessThanByF> &tmp, int& inMem) {
    while (!tmp.empty()){
        delete tmp.top();
        tmp.pop();
        inMem--;
    }
}

bool isPossible(int x, int y, NodeWithPrice* per) {
    if(per == nullptr)
        return (x>=0 && x<=2)&&(y>=0 && y<=2);
    else
        return (x>=0 && x<=2)&&(y>=0 && y<=2) && x!=per->getX() && y!=per->getY();
}


void RBFS_for_statistics(NodeWithPrice * start, bool &failure, NodeWithPrice *&res,
                         long long unsigned memory_limit, long long unsigned time_limit,
                         int& iterations, int& angles, int& nodeOverall, int& nodeInMem){

    uint64_t startUsedRAM(0);
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    startUsedRAM = info.WorkingSetSize;

    auto clockStart =  high_resolution_clock::now();

    iterations = 0;
    angles =0;
    nodeOverall=1;
    nodeInMem=1;


    bool cutoff = false;
    failure = true;
    int f_limit = 10000;
    RecRBFS_for_statistics(start, f_limit, failure, res,
                           memory_limit, info, startUsedRAM, time_limit, clockStart,
                           iterations, angles, nodeOverall, nodeInMem);

}

void RecRBFS_for_statistics(NodeWithPrice  *cur, int& f_limit, bool &failure, NodeWithPrice *& res,
                            uint64_t memory_limit, PROCESS_MEMORY_COUNTERS& info, uint64_t startUsedRAM,
                            long long unsigned time_limit, time_point<std::chrono::high_resolution_clock> clockStart,
                            int& iterations, int& angles, int& nodeOverall, int& nodeInMem){
    iterations++;
    uint64_t currentUsedRAM(0);
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    currentUsedRAM = info.WorkingSetSize - startUsedRAM;

    if(currentUsedRAM>memory_limit)
        return;

    auto clockCur =  high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(clockCur - clockStart);

    if(duration.count() > time_limit)
        return;

    int row[] = { -1, 0, 1, 0 };
    int col[] = { 0, -1, 0, 1 };

    if(isSolution(*cur))
    {
        res= cur;
        failure = false;
        return;
    }
    std::priority_queue<NodeWithPrice*, std::vector<NodeWithPrice*>, LessThanByF> successors;
    for(int i=0; i<4 && failure; ++i)
    {
        int x_tmp= cur->getX() + row[i];
        int y_tmp= cur->getY() + col[i];
        if(isPossible(x_tmp, y_tmp, cur->getParent()))
        {
            nodeOverall++;
            nodeInMem++;
            NodeWithPrice* tmp = new NodeWithPrice(cur, x_tmp, y_tmp);
            successors.push(tmp);

        }

    }
    if (successors.empty()){
        f_limit = 10000;
        return;
    }

    while (failure && !successors.empty()){
        NodeWithPrice* best = successors.top();
        if (best->getF() > f_limit){
            f_limit = best->getF();
            clearQueue_for_statistics(successors, nodeInMem);
            angles++;//?
            return;
        }
        successors.pop();

        int f_lim_tmp;
        if (!successors.empty())
            f_lim_tmp =std::min(f_limit, successors.top()->getF());
        else
            f_lim_tmp =f_limit;

        RecRBFS_for_statistics(best, f_lim_tmp, failure, res,
                               memory_limit, info, startUsedRAM, time_limit, clockStart,
                               iterations, angles, nodeOverall, nodeInMem);
        best->setF(f_lim_tmp);
        successors.push(best);
    }

}

void RBFS_test(){
    NodeWithPrice *res;
    bool fail;
    int iterations, angles, nodeOverall,  nodeInMem;
    bool sol = false;
    NodeWithPrice* start;
    while (!sol){
        start = new NodeWithPrice();
        sol = start->isSolvable();
    }
    RBFS_for_statistics(start, fail, res, (long long unsigned) 8*1024*1024*1024, 1000*60*60*30,
                        iterations, angles, nodeOverall,  nodeInMem);
    if(!fail)
        res->showPath();
    else
        std::cout<<"fail";
    std::cout<<"\n--------------\n";
    std::cout<<"iterations: "<<iterations<<"\n";
    std::cout<<"angles: "<<angles<<"\n";
    std::cout<<"states: "<<nodeOverall<<"\n";
    std::cout<<"states in memory:"<<nodeInMem<<"\n";
}