/******************************************************************************
* 版权所有 (c) 
* 功能描述   : 优先队列的基本算法(二叉堆实现)
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
// #include "securec.h"


/*
二叉堆（Binary Heap）没什么神秘，性质比二叉搜索树 BST 还简单。其主要操作就两个，sink（下沉）和 swim（上浮），用以维护二叉堆的性质。其主要应用有两个，首先是一种排序方法「堆排序」，第二是一种很有用的数据结构「优先级队列」
首先，二叉堆和二叉树有啥关系呢，为什么人们总是把二叉堆画成一棵二叉树？
因为，二叉堆在逻辑上其实是一种特殊的二叉树（完全二叉树），只不过存储在数组里。一般的链表二叉树，我们操作节点的指针，而在数组里，我们把数组索引作为指针

*/



/* --------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                  -- 宏定义 --                *
 * ---------------------------------------------------------------------------------------------------------------------------------------------------- */



/* ----------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 数据结构的基本定义-- *
 * ----------------------------------------------------------------------------------------------------------------------------------------------------- */
#define MINPQSize (10)
// #define MAXPQSize (1000)    // 做题的时候就不用动态申请，直接写死最大值就好了

#define MinDATA (-32767)


typedef struct EelememtType {
    int intVal;
    char charVal;
} EelememtType;

typedef struct HeapStruct {
    int capacity;
    int size;
    EelememtType *elems;   // 做题的时候就不用动态申请，直接写死最大值就好了
} HeapStruct, PriorityQueue;


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 对外函数接口 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------- */


void EnQueue(PriorityQueue* H ,EelememtType elem);
EelememtType DeQueue(PriorityQueue* H);
EelememtType FindTop(PriorityQueue* H);


PriorityQueue* Initialize(int initMaxElem);
void Destroy(PriorityQueue* H);
bool IsEmpty(PriorityQueue* H);
bool IsFull(PriorityQueue* H);
void MakeEmpty(PriorityQueue* H);




/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 工具小函数 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*
 * 
 */
void Swap(PriorityQueue* H, int IndexA, int indexB)
{
    EelememtType tmp = H->elems[IndexA];
    H->elems[IndexA] = H->elems[indexB];
    H->elems[indexB] = tmp;
}




/*
 * 
 */
int Compare(PriorityQueue* H, int IndexA, int indexB)
{
    return H->elems[IndexA].intVal < H->elems[indexB].intVal;
}


/*
 * 
 */
// 注意： 这里我们的计算是基于根节点在数组中的下标为1
// 计算下标为index的节点的父节点下标
int get_parent_index(int index)
{
    return (index) / 2;
}

// 计算下标为index的节点的左孩子下标
int get_left_child_index(int root)
{
    return 2 * root;
}

// 计算下标为index的节点的右孩子下标
int get_right_child_index(int root)
{
    return 2 * root + 1;
}


/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 顺序栈的基本算法 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/*****************************************************************************
 * 描  述: 创建优先级队列(控制台输入)
 * 参数说明：
 * 返回值：
*****************************************************************************/



/*****************************************************************************
 * 描  述: 创建(用已提供的数据)
 * 参数说明：
 * 返回值：
*****************************************************************************/
PriorityQueue* Initialize(int initMaxElem)
{
    if (initMaxElem < MINPQSize) {
        printf("size error \n");
    }

    PriorityQueue* H = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (H == NULL) {
        printf("maloc error \n");
    }
    memset(H, 0, sizeof(PriorityQueue));


    H->elems = (EelememtType *)malloc(sizeof(EelememtType) * (initMaxElem + 1));
    if (H->elems == NULL) {
        printf("maloc error \n");
    }
    memset(H->elems, 0, sizeof(EelememtType) * (initMaxElem + 1));

    
    H->capacity = initMaxElem;
    H->size = 0;
    H->elems[0].intVal = MinDATA;

    return H;
}






/*****************************************************************************
 * 描  述: 上浮
 * 参数说明：
 * 返回值：
*****************************************************************************/
void Swim(PriorityQueue* H, int IndexK)
{
    // indexK >1 判断是否已经到了顶，
    while ((IndexK > 1) && Compare(H, get_parent_index(IndexK), IndexK)) {
        Swap(H, get_parent_index(IndexK), IndexK);
        IndexK = get_parent_index(IndexK);
    }
}



/*****************************************************************************
 * 描  述: 下沉
 * 参数说明：
 * 返回值：
*****************************************************************************/
void Sink(PriorityQueue* H, int IndexK)
{
    // 如果已经沉到了堆低，就沉不下去了
    while (get_left_child_index(IndexK) <= H->size) {

        // 先比左右节点,假设左子节点大
        int order = get_left_child_index(IndexK);
        if (get_right_child_index(IndexK) <= H->size && Compare(H, order, get_right_child_index(IndexK))) { // 如果右子节点存在且右子节点比左子节点大
            order = get_right_child_index(IndexK);
        }

        if (Compare(H, order, IndexK)) { // 左右子节点都没有当前节点大
            break;
        }

        Swap(H, IndexK, order);
        IndexK = order;
    }
}




/*****************************************************************************
 * 描  述: 入队列，将新元素加最后，让它上浮到正确的位置
 * 参数说明：
 * 返回值：
*****************************************************************************/
void EnQueue(PriorityQueue* H, EelememtType elem)
{
    if (IsFull(H)) {
        printf("full \n");
        return;
    }

    H->elems[++H->size] = elem;

    Swim(H, H->size);
}


/*****************************************************************************
 * 描  述: 出队列，将对顶元素Top和堆底元素B对调，然后删除Top，最后让元素B下沉到正确的位置
 * 参数说明：
 * 返回值：
*****************************************************************************/
EelememtType DeQueue(PriorityQueue* H)
{
    if (IsEmpty(H)) {
        printf("empty \n");
        return H->elems[0];
    }

    EelememtType max = H->elems[1];
    Swap(H, 1, H->size);

    H->elems[H->size].intVal = 0;
    H->elems[H->size].charVal = 0;
    H->size--;


    Sink(H, 1);
    return max;
}




/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/
EelememtType FindTop(PriorityQueue* H)
{
    if (IsEmpty(H) == false) {
        return H->elems[1];
    } 

    printf("enpty \n ");

    return H->elems[0];
}



/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/
bool IsEmpty(PriorityQueue* H)
{
    return H->size == 0;
}

bool IsFull(PriorityQueue* H)
{
    return H->size == H->capacity;
}

void Destroy(PriorityQueue* H)
{
    free(H->elems);
    free(H);
}


void MakeEmpty(PriorityQueue* H) {
    H->size = 0;

    memset(H->elems, 0, sizeof(EelememtType) * (H->capacity + 1));
}


void PrintfQue(PriorityQueue* H)
{
    // 依次出队
    printf("riority_queue: ");
    for (int i = 1; i <= H->size; i++) {
        printf("{ %d, %c} --> ", H->elems[i].intVal, H->elems[i].charVal);
    }
    printf("\n");
}



/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/

/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/




/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/


/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/

/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/


// ---------------------------解法一 开始--------------------------------------------------------



// ---------------------------解法一 结束--------------------------------------------------------








int main(int argc, const char *argv[])
{
    PriorityQueue* H = Initialize(20);

    // 入队元素
    EelememtType ele = { 0 };
    
    ele.intVal = 2;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 45;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 65;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 75;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 1;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = 20;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    DeQueue(H);
    PrintfQue(H);

    DeQueue(H);
    PrintfQue(H);

    DeQueue(H);
    PrintfQue(H);

    DeQueue(H);
    PrintfQue(H);

    return 0;
}
