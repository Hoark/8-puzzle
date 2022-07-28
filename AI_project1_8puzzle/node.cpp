#include "node.h"
#include<algorithm>

Node* newNode(int matrix[N][N], int goal[N][N], int row0, int col0, int newRow0, int newCol0, int level, Node* parent)
{
    Node* newNode  = new Node;
    newNode->parent = parent;

    copyMatrix(newNode->matrix,matrix);

    std::swap(newNode->matrix[row0][col0], newNode->matrix[newRow0][newCol0]);

    newNode->level = level;

    newNode->h = evaluateH(newNode->matrix, goal);

    newNode->row0 = newRow0;
    newNode->col0 = newCol0;

    return newNode;
}

int evaluateH(int matrix[N][N], int final[N][N])
{
    int p=0, s=0;

    //求P（距离）值
    for (int n = 1; n <= 2; n++)
    {
        bool flag = false;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (matrix[i][j] == n)
                {
                    if (final[0][0] == n)
                    {
                        p+=(abs(i)+abs(j));
                    }
                    else if (final[0][1] == n)
                    {
                        p+=(abs(i)+abs(j+1-2));
                    }
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
    }

    for (int n = 3; n <= N*N-1; n++)
    {
        bool flag = false;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (matrix[i][j] == n)
                {
                    switch (n)
                    {
                    case 3:
                        p += (abs(i)+abs(j-2)); //j-2 = (j+1) -3
                        break;
                    case 4:
                        p += (abs(i-1)+abs(j-2));
                        break;
                    case 5:
                        p += (abs(i-2)+abs(j-2));
                        break;
                    case 6:
                        p += (abs(i-2)+abs(j-1));
                        break;
                    case 7:
                        p += (abs(i-2)+abs(j));
                        break;
                    case 8:
                        p += (abs(i-1)+abs(j));
                        break;
                    default:
                        break;
                    }
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
    }

    //求S值
    int array[N*N-1];
    getArray(matrix,array);

    switch (final[0][0])
    {
    case 1:
        for (int i = 0; i < N*N-2; i++)
        {
            if (array[i] == 0)
                continue;
            else
            {
                if (array[i] == N*N-1)
                {
                    if (array[i+1] != 1)
                    {
                        s+=2;
                    }
                }else
                {
                    if (array[i+1] != array[i]+1)
                    {
                        s+=2;
                    }
                }
            }
        }
        break;

    case 2:
        for (int i = 0; i < N*N-2; i++)
        {
            if (array[i] == 0)
                continue;
            else
            {
                if (array[i] == N*N-1)
                {
                    if (array[i+1] != 2)
                    {
                        s+=2;
                    }
                }else if (array[i] == 1)
                {
                    if (array[i+1] != 3)
                    {
                        s+=2;
                    }
                }else if (array[i] == 2)
                {
                    if (array[i+1] != 1)
                    {
                        s+=2;
                    }
                }else
                {
                    if (array[i+1] != array[i]+1)
                    {
                        s+=2;
                    }
                }
            }
        }
        break;

    default:
        break;
    }



    if (matrix[N/2][N/2] != 0)
        s += 1;

    return p+3*s;
}


void copyMatrix(int mat1[N][N], int mat2[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            mat1[i][j] = mat2[i][j];
        }
    }
}

void getArray(int matrix[N][N], int array[N*N-1])
{
    for (int n = 0; n < N*N-1; n++)
    {
        switch (n/(N-1))
        {
        case 0:
                array[n] = matrix[0][n%2];
                break;
            case 1:
                array[n] = matrix[n%2][2];
                break;
            case 2:
                array[n] = matrix[2][2-(n%2)];
                break;
            case 3:
                array[n] = matrix[2-(n%2)][0];
                break;
        default:
            break;
        }
    }
}

bool identicalMatrix(int mat1[N][N], int mat2[N][N])
{
    bool flag = true;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                flag = false;
                break;
            }
        }
        if(!flag) break;
    }

    return flag;
}

bool isSafe(int x, int y)
{
    return (x>=0 && x< N && y>=0 && y< N);
}

void getZero(int& row0, int& col0 ,int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] == 0)
            {
                row0 = i;
                col0 = j;
                return;
            }
        }
    }
}

bool getGoal(int start[N][N])
{
    int count = 0;
    int array[N*N];
    getArray(start,array);
    array[N*N-1] = start[1][1];

    for (int i = 0; i < N*N-1; i++)
    {
        for (int j = i+1; j < N*N; j++)
        {
            if (array[i]!=0 && array[j]!=0 && array[i]>array[j])
            {
                count++;
            }
        }
    }

    return count%2 == 0;
}
