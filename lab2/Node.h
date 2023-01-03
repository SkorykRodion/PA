#include <iostream>
#include <ctime>
#include <vector>


class Node {
protected:
    Node* parent;
    int mat[3][3];
    int x;
    int y;
    int level;
public:
    bool isSolvable();

    int getX() const;

    int getY() const;

    int getLevel() const;

    Node();

    Node *getParent() const;

    Node(Node *parent, int (*matrix)[3], int x, int y, int level);

    Node (Node*, int, int);

    friend bool isSolution(Node node);

    void display();

    void showPath();
};

class NodeWithPrice: public Node {
    int f;
    int findH(int, int, int);
    int calcF();
public:
    NodeWithPrice(NodeWithPrice *parent, int (*matrix)[3], int x, int y, int level);

    NodeWithPrice();

    NodeWithPrice(Node*);

    NodeWithPrice(NodeWithPrice*, int, int);

    void setF(int f);

    int getF() const;

};
