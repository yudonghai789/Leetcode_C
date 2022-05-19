/******************************************************************************
 * 版权所有 (c)
 * 功能描述   : 
 * 作    者   :
 * 生成日期   :

 * 动态规划 
      --- 
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
#include <math.h>
#include <assert.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include "securec.h"



#define MAX_SLIDELEN_NUM 51
#define MAX_BLOCK_NUM 20
#define TWO 2

bool g_grid[MAX_SLIDELEN_NUM][MAX_SLIDELEN_NUM];

bool g_visit[MAX_SLIDELEN_NUM][MAX_SLIDELEN_NUM];

typedef enum DIRECTION {
    DOWN = 0,
    UP = 1,
    RIGHT = 2,
    LEFT = 3,
    DIR_BUTT = 4
} DIRECTION;

int g_direct[DIR_BUTT][TWO] = {
    { 1, 0 },
    { -1, 0 },
    { 0, 1 },
    { 0, -1 }
};

bool IsRowInv(int gridSize, int dirNextRow)
{
    bool isRowInv = (dirNextRow < 0 || dirNextRow >= gridSize);
    return isRowInv;
}

bool IsColInv(int gridSize, int dirNextCol)
{
    bool isColInv = (dirNextCol < 0 || dirNextCol >= gridSize);
    return isColInv;
}

bool IsDirChangeOk(int gridSize, int dirNextRow, int dirNextCol)
{
    if (IsRowInv(gridSize, dirNextRow) || IsColInv(gridSize, dirNextCol)) {
        return true;
    }
    bool isDirChangeOk = (g_visit[dirNextRow][dirNextCol] == true ||
                          g_grid[dirNextRow][dirNextCol] == true);
    return isDirChangeOk;
}

bool IsNextCanMove(int gridSize, int nextRow, int nextCol)
{
    if (IsRowInv(gridSize, nextRow) || IsColInv(gridSize, nextCol)) {
        return false;
    }

    bool isNextCanMove = ((g_visit[nextRow][nextCol] == false) &&
                          (g_grid[nextRow][nextCol] == false));
    return isNextCanMove;
}

void GetMoveDir(int gridSize, int row, int col, int dirction, bool dirCanGo[DIR_BUTT])
{
    dirCanGo[dirction] = true;
    int dirNextRow = row + g_direct[dirction][0];
    int dirNextCol = col + g_direct[dirction][1];

    if (IsDirChangeOk(gridSize, dirNextRow, dirNextCol) == true) {
        dirCanGo[DOWN] = true;
        dirCanGo[UP] = true;
        dirCanGo[RIGHT] = true;
        dirCanGo[LEFT] = true;
        dirCanGo[dirction] = false;
    }
}


void DfsRecursive(int gridSize, int row, int col, int dirction, int *outRes)
{
    bool dirCanGo[DIR_BUTT] = { 0 };
    GetMoveDir(gridSize, row, col, dirction, dirCanGo);

    int maxPath = 0;
    for (int dir = 0; dir < (int)DIR_BUTT; dir++) {
        if (dirCanGo[dir] == false) {
            continue;
        }

        int nextRow = row + g_direct[dir][0];
        int nextCol = col + g_direct[dir][1];

        if (IsNextCanMove(gridSize, nextRow, nextCol) == true) {
            g_visit[nextRow][nextCol] = true;
            int temp = 0;
            DfsRecursive(gridSize, nextRow, nextCol, dir, &temp);

            g_visit[nextRow][nextCol] = false;
            maxPath = fmax(maxPath, 1 + temp);
        }
    }
    *outRes = maxPath;
}



int GetMaxArea(int gridSize)
{
    int res = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (g_grid[i][j] == 1) {
                continue;
            }
            for (int dir = 0; dir < (int)DIR_BUTT; dir++) {
                memset_s(g_visit, (size_t)sizeof(g_visit), 0, (size_t)sizeof(g_visit));
                g_visit[i][j] = true;
                int temp = 0;
                DfsRecursive(gridSize, i, j, dir, &temp);
                res = fmax(res, 1 + temp);
            }
        }
    }

    return res;
}

void InitGrad(int blockNum, int **blocks)
{
    memset_s(g_grid, (size_t)sizeof(g_grid), 0, (size_t)sizeof(g_grid));
    for (int i = 0; i < blockNum; i++) {
        g_grid[blocks[i][0]][blocks[i][1]] = true;
    }
}


// 待实现函数，在此函数中填入答题代码
static int GetOptimalSolution(int sideLen, int blockNum, int **blocks)
{
    InitGrad(blockNum, blocks);
    int res = GetMaxArea(sideLen);
    return res;
}

int main(void)
{
    int sideLen, blockNum;
    if (scanf_s("%d %d", &sideLen, &blockNum) != TWO) { return -1; }

    static int buf[MAX_BLOCK_NUM][TWO];
    static int *blocks[MAX_BLOCK_NUM];
    for (int i = 0; i < blockNum; i++) {
        if (scanf_s("%d %d", &buf[i][0], &buf[i][1]) != TWO) { return -1; }
        blocks[i] = buf[i];
    }

    int result = GetOptimalSolution(sideLen, blockNum, blocks);
    printf("%d", result);

    return 0;
}
