/******************************************************************************
* 版权所有 (c) 
* 功能描述   : 
* 作    者   : 
* 生成日期   : 
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


// ---------------------------解法 开始---Floyd算法-----------------------------------------------------


#define MAX_LEN 10

struct RouterDelayInfo {
    int router1;
    int router2;
    int delay;
};

# define VERTEX_NUM MAX_LEN   // 图顶点的最大数量
#define INF 0xffff // 没有路径时，将权值置位无效
typedef struct {
    int number;                   // 在图中的位置，也就是邻接矩阵的索引
    struct VERTEX_DATA_TYPE {
        int intVal;
        // char carVal;
    } info;                     // 顶点的数据类型定义.
} Vertex;
typedef struct {
    int vertextNum;                             // 顶点的数量
    int edgeNum;                                // 边的数量.
    Vertex vex[VERTEX_NUM];                     // 顶点的列表.
    unsigned short edges[VERTEX_NUM][VERTEX_NUM];        // 边的列表（邻接矩阵，大小表示边的权值）.
} MGraph;
MGraph g_mG;


void GenGraph(int routerNum, struct RouterDelayInfo* info, int infoCnt)
{
    g_mG.vertextNum = routerNum;
    g_mG.edgeNum = infoCnt;
    for (int i = 0; i < g_mG.vertextNum; i++) {
        for (int j = 0; j < g_mG.vertextNum; j++) {
            g_mG.edges[i][j] = INF;
        }
        g_mG.edges[i][i] = 0;
        g_mG.vex[i].number = i;
        g_mG.vex[i].info.intVal = i + 1;
    }

    for (int i = 0; i < infoCnt; i++) {
        g_mG.edges[info[i].router1 - 1][info[i].router2 - 1] = info[i].delay;
    }
}

typedef struct Matrix {
    unsigned short val[VERTEX_NUM][VERTEX_NUM];        // 边的列表（邻接矩阵，大小表示边的权值）.
} Matrix;


/*
 * Floyd 最短路径。
 *
 * 参数说明：
 *        g_mG -- 图
 *     disDp --  各个顶点之间距离的dp数组，一个一个顶点添加时更新
 *     linkVex -- 记录过程中中转节点，要得到完成路径时，迭代即可
 */
void Floyd(Matrix *disDp, Matrix *linkVex)
{
    // 初始化D, P数组
    for (int v = 0; v < g_mG.vertextNum; v++) {
        for (int w = 0; w < g_mG.vertextNum; w++) {
            disDp->val[v][w] = g_mG.edges[v][w];
            linkVex->val[v][w] = w;
        }
    }

    /* 开始循环查找最短路径，更新D P数组
       k为中转顶点，用于比对是否v经过k到w的开销比D数组中当前更小
       如果更小，则说明k更有可能存在于v到w最短路径上，更新disDp，及preVex
    */
    for (int k = 0; k < g_mG.vertextNum; k++) {
        // v行
        for (int v = 0; v < g_mG.vertextNum; v++) {
            // v行所有w列 
            for (int w = 0; w < g_mG.vertextNum; w++) {
                // 判断k是否有可能在v和w的最短路径上
                if (disDp->val[v][w] > disDp->val[v][k] + disDp->val[k][w]) {
                    // 更新两点间的距离和
                    disDp->val[v][w] = disDp->val[v][k] + disDp->val[k][w]; 
                    //因为k存在于v到w的路径上，所以v想要到w需要先经过 v到k要经过的顶点
                    linkVex->val[v][w] = linkVex->val[v][k]; 
                }
            }
        }
    }
}


// 待实现函数，在此函数中填入答题代码
void GetMinDelay(int routerNum, struct RouterDelayInfo* info, int infoCnt)
{
    memset_s(&g_mG, (size_t)sizeof(g_mG), 0, (size_t)sizeof(g_mG));
    GenGraph(routerNum, info, infoCnt);

    Matrix disDp = { 0 };
    Matrix linkVex = { 0 };
    Floyd(&disDp, &linkVex);

    printf("D数组(任意顶点间的最短路径开销或者叫距离)\n");
    for (int i = 0; i < g_mG.vertextNum; i++) {
        for (int j = 0; j < g_mG.vertextNum; j++) {
            printf("%d->%d = %d      ", i, j, disDp.val[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("任意顶点间的最短路径:\n");
    for (int i = 0; i < g_mG.vertextNum; i++) {
        for (int j = i + 1; j < g_mG.vertextNum; j++) {
            printf("%d -> %d distance: %3d, path:", i, j, disDp.val[i][j]);
            printf("%d->", i); // 先打印源点
            int k = linkVex.val[i][j];
            while (k != j) {
                printf("%d->", k);
                k = linkVex.val[k][j]; // 相当于递归查找
            }
            printf("%d\n", k);
        }
    }
}



int main(void)
{
    int routerNum = 0;
    if (scanf_s("%d", &routerNum) != 1) { return -1; }
    int infoCnt = 0;
    if (scanf_s("%d\n", &infoCnt) != 1) { return -1; }
    static struct RouterDelayInfo infos[MAX_LEN];
    int i;
    for (i = 0; i < infoCnt; i++) {
        if (scanf_s("%d %d %d\n",
                    &infos[i].router1,
                    &infos[i].router2,
                    &infos[i].delay) != 3) { return -1; }
    }

    GetMinDelay(routerNum, infos, infoCnt);
    

    return 0;
}

// ---------------------------解法 结束---------------------------------------------------------------------
/*
4 8
1 2 2
1 3 7
1 4 4
2 3 3
3 4 1
3 1 7
4 1 5
4 3 12

0 2 5 4 
9 0 3 4 
6 8 0 1
5 7 10 0

*/
