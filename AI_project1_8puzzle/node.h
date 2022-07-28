#ifndef NODE_H
#define NODE_H

#define N 3

struct Node
{
    Node* parent;
    int matrix[N][N];
    int h; //启发函数
    int level; //该节点的深度
    int row0,col0; //空格子的位置

};

Node* newNode(int matrix[N][N], int goal[N][N], int row0, int col0, int newRow0, int newCol0, int level, Node* parent);
int evaluateH(int matrix[N][N], int final[N][N]);
void copyMatrix(int mat1[N][N], int mat2[N][N]);
void getArray(int matrix[N][N], int array[N*N-1]);
bool identicalMatrix(int mat1[N][N], int mat2[N][N]);
bool isSafe(int x, int y);
void getZero(int& row0, int& col0 ,int matrix[N][N]);
bool getGoal(int start[N][N]);

#endif // NODE_H
