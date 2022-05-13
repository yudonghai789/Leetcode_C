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
#include <math.h>
#include <assert.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include "graph.h"

/* --------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                  -- 宏定义 --                *
 * ---------------------------------------------------------------------------------------------------------------------------------------------------- */
#define isLetter(a)     ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)       (sizeof(a)/sizeof(a[0]))


/* ----------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 数据结构的基本定义-- *
 * ----------------------------------------------------------------------------------------------------------------------------------------------------- */
// 边的定义
typedef struct EdgeNode {
    int toAdjVex;                               // 这条边指向的顶点
    float weight;                               // 边的权值
    struct EdgeNode *next;                      // 该顶点的下一条边, note that it only means the next edge also links to the vertex which this edge links to.
} EdgeNode;

// 顶点的定义
typedef struct VertexNode {
    struct VERTEX_DATA_TYPE {
        int intVal;
        char carVal;
    } info;                     // 顶点的数据类型定义.
    struct EdgeNode* firstEdge;                 // The first edge which the vertex points to.
} VertexNode;

# define VERTEX_NUM 100   // 图顶点的最大数量
// 图的定义
typedef struct {
    VertexNode adjList[VERTEX_NUM];             // 顶点的列表.
    int vertextNum;                             // 顶点的数量
    int edgeNum;                                // 边的数量.
} AdjListGraph;
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 对外函数接口 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 工具小函数 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*
 * 根据顶点的值，返回该顶点在图中顶点列表的位置
 */
int GetPosition(AdjListGraph *g, char ch)
{
    for (int i=0; i < g->vertextNum; i++) {
        if(g->adjList[i].info.carVal == ch) {
            return i;
        }
    }
    return -1;
}

/*
 * 将node链接到list的末尾
 */
void linkLast(EdgeNode *list, EdgeNode *node)
{
    EdgeNode *p = list;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = node;
}

/*
 * 打印邻接表图
 */
void printGraph(AdjListGraph *G)
{
    printf("== List Graph:\n");
    for (int i = 0; i < G->vertextNum; i++) {
        printf("%d(%c): ", i, G->adjList[i].info.carVal);
        EdgeNode * node = G->adjList[i].firstEdge;
        while (node != NULL) {
            printf("%d(%c) ", node->toAdjVex, G->adjList[node->toAdjVex].info.carVal);
            node = node->next;
        }
        printf("\n");
    }
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 图的基本算法 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */



/*****************************************************************************
 * 描  述: 创建邻接表对应的图(自己输入)
*****************************************************************************/



/*****************************************************************************
 * 描  述: 创建邻接表对应的图(用已提供的数据)
*****************************************************************************/
AdjListGraph* createGraph()
{
    char adjList[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'G'}, 
        {'B', 'A'}, 
        {'B', 'D'}, 
        {'C', 'F'}, 
        {'C', 'G'}, 
        {'D', 'E'}, 
        {'D', 'F'}}; 
    int vlen = LENGTH(adjList);
    int elen = LENGTH(edges);

    AdjListGraph* pG = (AdjListGraph*)malloc(sizeof(AdjListGraph));
    assert(pG != NULL);
    memset(pG, 0, sizeof(AdjListGraph));

    // 初始化"顶点数"和"边数"
    pG->vertextNum = vlen;
    pG->edgeNum = elen;
    // 初始化"邻接表"的顶点
    for(int i = 0; i < pG->vertextNum; i++) {
        pG->adjList[i].info.carVal = adjList[i];
        pG->adjList[i].info.intVal = 0;
        pG->adjList[i].firstEdge = NULL;
    }

    // 初始化"邻接表"的边
    for(int i = 0; i < pG->edgeNum; i++) {
        // 读取边的起始顶点和结束顶点
        char c1 = edges[i][0];
        char c2 = edges[i][1];
        int p1 = GetPosition(pG, c1);
        int p2 = GetPosition(pG, c2);

        // 初始化node1
        EdgeNode *node1 = (EdgeNode *)malloc(sizeof(EdgeNode));
        memset(node1, 0, sizeof(EdgeNode));
        node1->toAdjVex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if (pG->adjList[p1].firstEdge == NULL) {
            pG->adjList[p1].firstEdge = node1;
        } else {
            linkLast(pG->adjList[p1].firstEdge, node1);
        }
    }

    return pG;
}



/*****************************************************************************
 * 描  述: 深度优先搜索遍历图的递归实现   DFS用栈， BFS用队列
 * 递归就是函数维护了隐式的栈
*****************************************************************************/
void DFS(AdjListGraph *G, int i, int *visited)
{
    EdgeNode *node = NULL;

    visited[i] = 1;
    printf("%c ", G->adjList[i].info.carVal);
    node = G->adjList[i].firstEdge;
    while (node != NULL) {
        if (!visited[node->toAdjVex]) {
            DFS(G, node->toAdjVex, visited);
        }
        node = node->next;
    }
}

void DFS_traverse(AdjListGraph *G)
{
    int *visited = (int *)malloc(G->vertextNum * sizeof(int));  // 顶点访问标记
    assert(visited != NULL);
    memset(visited, 0, G->vertextNum * sizeof(int));      // 初始化所有顶点都没有被访问

    printf("== DFS: ");
    for (int i = 0; i < G->vertextNum; i++) {
        if (!visited[i]) {
            DFS(G, i, visited);
        }
    }
    printf("\n");

    free(visited);
}
/*****************************************************************************
 * 描  述: 深度优先搜索遍历图非递归    DFS用栈， BFS用队列
 * 借用了额外的数据结构——栈。  递归就是函数维护了隐式的栈
*****************************************************************************/
void DfsNonRecursion(AdjListGraph* G, int startVertextIndex, bool *visited)
{
    int *stack = (int *)malloc(G->vertextNum * sizeof(int));     // 辅组队列
    memset(stack, -1, G->vertextNum * sizeof(int));
    int stackTop = -1;

    stack[++stackTop] = startVertextIndex;  // 先将第一个入栈， 出栈时表示被访问

    while (stackTop != -1) {
        int top = stack[stackTop];   // 出栈，被访问
        stack[stackTop] = -1;         // 出栈，被访问
        stackTop--;                // 出栈，被访问

        visited[top] = true;   // 出栈，被访问
        printf("%c ", (G ->adjList[top]).info.carVal);   // 出栈，被访问

        EdgeNode *edgeNode = G->adjList[top].firstEdge;
        while (edgeNode != NULL) {
            if (!visited[edgeNode->toAdjVex]) {
                stack[++stackTop] = edgeNode ->toAdjVex;
            }
            edgeNode = edgeNode->next;
        }
    }
}


void Dfs_Notra(AdjListGraph *G)
{
    bool *visited = (bool *)malloc(G->vertextNum * sizeof(bool));   // 顶点访问标记
    memset(visited, false, G->vertextNum * sizeof(bool));
    printf("== DFS: ");

    for (int i = 0; i < G->vertextNum; i++) {
        if (!visited[i]) {
            DfsNonRecursion(G, i, visited);
        }
    }
    printf("\n");
    free(visited);
}


/*****************************************************************************
 * 描  述: 广度优先搜索     DFS用栈， BFS用队列
*****************************************************************************/
void BFS(AdjListGraph *G)
{
    int *queue = (int *)malloc(G->vertextNum * sizeof(int));     // 辅组队列
    int head = 0;
    int rear = 0;
    int *visited = (int *)malloc(G->vertextNum * sizeof(int));   // 顶点访问标记
    assert(queue!=NULL && visited!=NULL);
    memset(queue, 0, G->vertextNum * sizeof(int));
    memset(visited, 0, G->vertextNum * sizeof(int));

    printf("== BFS: ");
    for (int i = 0; i < G->vertextNum; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            printf("%c ", G->adjList[i].info.carVal);
            queue[rear++] = i;  // 入队列
        }
        while (head != rear) {
            int j = queue[head++];  // 出队列
            EdgeNode *node = G->adjList[j].firstEdge;
            while (node != NULL) {
                int k = node->toAdjVex;
                if (!visited[k]) {
                    visited[k] = 1;
                    printf("%c ", G->adjList[k].info.carVal);
                    queue[rear++] = k;
                }
                node = node->next;
            }
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}



/*****************************************************************************
 * 描  述: 拓扑排序
 * 参数说明：
 *     G -- 邻接表表示的有向图
 * 返回值：
 *     -1 -- 失败(由于内存不足等原因导致)
 *      0 -- 成功排序，并输入结果
 *      1 -- 失败(该有向图是有环的)
*****************************************************************************/
int topologicalSort(AdjListGraph *G)
{
    int num = G->vertextNum;  // 图中顶点个数

    int *ins = (int *)malloc(num * sizeof(int));   // 入度数组
    memset(ins, 0, num * sizeof(int));

    char *tops = (char *)malloc(num * sizeof(char));  // 拓扑排序结果数组，记录每个节点的排序后的序号。
    memset(tops, 0, num * sizeof(char));

    int *queue = (int *)malloc(num * sizeof(int)); // 辅助队列
    memset(queue, 0, num * sizeof(int));
    int head = 0;           // 辅助队列的头
    int rear = 0;           // 辅助队列的尾

    // 统计每个顶点的入度数
    for(int i = 0; i < num; i++) {
        EdgeNode *node = G->adjList[i].firstEdge;
        while (node != NULL) {
            ins[node->toAdjVex]++;
            node = node->next;
        }
    }

    // 将所有入度为0的顶点入队列
    for(int i = 0; i < num; i ++) {
        if(ins[i] == 0) {
            queue[rear++] = i;          // 入队列
        }
    }

    int index = 0;
    while (head != rear) {                // 队列非空
        int j = queue[head++];              // 出队列。j是顶点的序号
        tops[index++] = G->adjList[j].info.carVal; // 将该顶点添加到tops中，tops是排序结果
        EdgeNode *node = G->adjList[j].firstEdge;    // 获取以该顶点为起点的出边队列

        // 将与"node"关联的节点的入度减1；
        // 若减1之后，该节点的入度为0；则将该节点添加到队列中。
        while(node != NULL) {
            // 将节点(序号为node->toAdjVex)的入度减1。
            ins[node->toAdjVex]--;
            // 若节点的入度为0，则将其"入队列"
            if( ins[node->toAdjVex] == 0) {
                queue[rear++] = node->toAdjVex;  // 入队列
            }
                
            node = node->next;
        }
    }

    if(index != G->vertextNum) {
        printf("Graph has a cycle\n");
        free(queue);
        free(ins);
        free(tops);
        return 1;
    }

    // 打印拓扑排序结果
    printf("== TopSort: ");
    for(int i = 0; i < num; i ++) {
        printf("%c ", tops[i]);
    }
    printf("\n");

    free(queue);
    free(ins);
    free(tops);
    return 0;
}


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


// ---------------------------解法一 开始--------------------------------------------------------



// ---------------------------解法一 结束--------------------------------------------------------
int main() 
{
    AdjListGraph* pG = createGraph();
    printGraph(pG);

    BFS(pG);

    Dfs_Notra((pG));

    topologicalSort(pG);

    return 0;
}
