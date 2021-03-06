/******************************************************************************
* 版权所有 (c) 
* 功能描述   : 有向图的基本算法
* 作    者   : 
* 生成日期   : 
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include <math.h>
#include <assert.h>



/* --------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                  -- 宏定义 --                *
 * ---------------------------------------------------------------------------------------------------------------------------------------------------- */



/* ----------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 数据结构的基本定义-- *
 * ----------------------------------------------------------------------------------------------------------------------------------------------------- */
typedef struct {
    int number;                   // 在图中的位置，也就是邻接矩阵的索引
    struct VERTEX_DATA_TYPE {
        int intVal;
        char carVal;
    } info;                     // 顶点的数据类型定义.
} Vertex;

# define VERTEX_NUM 100   // 图顶点的最大数量

typedef struct
{
    int vertextNum;                             // 顶点的数量
    int edgeNum;                                // 边的数量.
    Vertex vex[VERTEX_NUM];                     // 顶点的列表.
    float edges[VERTEX_NUM][VERTEX_NUM];        // 边的列表（邻接矩阵，大小表示边的权值）.
} MGraph;



/* ------------------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 对外函数接口 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 工具小函数 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */



/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 图的基本算法 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*****************************************************************************
 * 描  述: 创建的图(自己输入)
*****************************************************************************/



/*****************************************************************************
 * 描  述: 创建图(用已提供的数据)
*****************************************************************************/




/*****************************************************************************
 * 描  述: 深度优先搜索遍历图的递归实现
*****************************************************************************/



/*****************************************************************************
 * 描  述: 深度优先搜索遍历图非递归
*****************************************************************************/



/*****************************************************************************
 * 描  述: 广度优先搜索
*****************************************************************************/


/*****************************************************************************
 * 描  述: 拓扑排序
*****************************************************************************/


/*****************************************************************************
 * 描  述: 最小生成树 （Minimum Spanning Tree）
*****************************************************************************/



/*****************************************************************************
 * 描  述: 并查集 （Union Find Set）
*****************************************************************************/


/*****************************************************************************
 * 描  述: 最短路径算法   -- 单源最短路径算法——迪杰斯特拉算法（Dijkstra Algorithm）
*****************************************************************************/






/*****************************************************************************
 * 描  述: 最短路径算法   -- 多源最短路径算法——弗洛伊德算法（Floyd Algorithm）
*****************************************************************************/











int main() {



    return 0;
}
