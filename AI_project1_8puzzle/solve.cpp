#include "solve.h"
#include <vector>
#include<queue>

//分别让空格向上、下、左、右移动
int movementRow[4]={-1,1,0,0};
int movementCol[4]={0,0,-1,1};

Node* Solve(int Start[N][N], int row0, int col0, int goal[N][N])
{
    std::priority_queue<Node*, std::vector<Node*>, comp> open;
    std::vector<Node*> closed;

    //根节点
    Node* start = newNode(Start,goal, row0, col0, row0, col0,0,NULL);
    open.push(start);

    while (!open.empty())
    {
        Node* min;
        bool flag;
        do
        {
            flag = false;
            min = open.top();
            for (unsigned i = 0; i < closed.size(); i++)
            {
                if (identicalMatrix(min->matrix, closed[i]->matrix)) //Check of je deze matrix al gehad hebt
                {
                    if ((min->h+min->level)<(closed[i]->h+closed[i]->level))
                    {
                        closed.erase(closed.begin()+i);
                    }else
                    {
                        flag = true;
                        open.pop();
                        break;
                    }
                }
            }
        } while (flag);
        closed.push_back(min);
        open.pop();

        //检查节点m是否是目标节点
        if (min->h == 0)
        {
            //printPath(min);
            return min;
        }

        //扩展
        for (int i = 0; i < 4; i++)
        {
            if (isSafe((min->row0+movementRow[i]), (min->col0 + movementCol[i])))
            {
                Node* child = newNode(min->matrix, goal, min->row0, min->col0, min->row0+movementRow[i], min->col0+movementCol[i], min->level +1, min);

                open.push(child);
            }
        }

    }
    return NULL;
}

