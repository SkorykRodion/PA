//
// Created by ROS on 25.10.2022.
//
using namespace std;
#include "Node.h"

Node::Node(Node *parent, int (*matrix)[3], int x, int y, int level) : parent(parent), x(x), y(y), level(level) {

    memcpy(mat, matrix, sizeof mat);
}

void Node::display() {
    cout << "step"<<level<<": "<< endl;
    for (auto & i : mat)
    {
        for (int j : i)
            cout<<j<<' ';
        cout<<endl;
    }
}

Node::Node(Node *prev, int new_x, int new_y) {
    parent = prev;
    memcpy(mat, prev->mat, sizeof mat);
    x=new_x;
    y=new_y;
    level = prev->level + 1;
    auto tmp = mat[y][x];
    mat[y][x] = mat[prev->y][prev->x];
    mat[prev->y][prev->x] = tmp;

}

Node::Node() {
    srand (time(NULL));
    std::vector<int> arr { 0, 1, 2, 3, 4, 5, 6, 7 ,8 };
    parent=nullptr;
    for (int i =0; i<=2; ++i)
        for(int j=0; j<=2; ++j){
            int it = rand()%arr.size();
            mat[i][j]=arr[it];
            if(mat[i][j] == 0){
                x=j;
                y=i;
            }
            arr.erase(arr.begin()+it);
        }
    level=1;
    arr.clear();
}

int Node::getX() const {
    return x;
}

int Node::getY() const {
    return y;
}

int Node::getLevel() const {
    return level;
}

bool isSolution(Node node) {
    int final[3][3] =
            {
                    {0, 1, 2},
                    {3, 4, 5},
                    {6, 7, 8}
            };
    bool ans = true;
    for(int i=0; i<=2 && ans; ++i)
        for(int j=0; j<=2&& ans; ++j)
            if(node.mat[i][j]!=final[i][j])
                ans = false;
    return ans;
}

void Node::showPath() {
    if(parent!= nullptr)
        parent->showPath();
    display();
}

Node *Node::getParent() const {
    return parent;
}

bool Node::isSolvable() {
    int num_of_inn = 0;
    int puzzle[9];
    for(int i =0; i<=2; ++i)
        for(int j =0; j<=2; ++j){
            puzzle[3*i+j] = mat[i][j];
        }

    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
            if (puzzle[j] && puzzle[i] &&  puzzle[i] > puzzle[j])
                num_of_inn++;

    if(num_of_inn % 2 == 0)
        return true;
    else
        return false;
}


int NodeWithPrice::getF() const {
    return f;
}

NodeWithPrice::NodeWithPrice():Node() {
    f = calcF();
}

int NodeWithPrice::calcF() {
    int h = 0;
    for(int i =0; i<=2; ++i)
        for(int j =0; j<=2; ++j){
            h += findH(i, j, mat[i][j]);;
        }

    return level + h - 1;
}

int NodeWithPrice::findH(int x0, int y0, int num) {
    int x_tmp, y_tmp;
    int final[3][3] =
            {
                    {0, 1, 2},
                    {3, 4, 5},
                    {6, 7, 8}
            };
    for(int i =0; i<3; ++i)
        for(int j =0; j<3; ++j)
            if(final[i][j]== num){
                x_tmp = i;
                y_tmp = j;
            }

    return abs(x0-x_tmp) +abs(y0-y_tmp);
}

void NodeWithPrice::setF(int f) {
    NodeWithPrice::f = f;
}

NodeWithPrice::NodeWithPrice(NodeWithPrice *prev, int new_x, int new_y) : Node(prev, new_x, new_y){
    f = calcF();
}

NodeWithPrice::NodeWithPrice(NodeWithPrice *parent, int (*matrix)[3], int x, int y, int level):  Node(parent, matrix, x, y, level){
    f = calcF();
}
