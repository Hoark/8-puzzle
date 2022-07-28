#ifndef SOLVE_H
#define SOLVE_H
#include "node.h"

#define N 3

Node* Solve(int Start[N][N], int row0, int col0, int goal[N][N]);

struct comp
{
    bool operator()(const Node* a, const Node* b) const
    {
        return (a->h + a->level) > (b->h + b->level); //求f=g+h
    }
};



#endif // SOLVE_H
