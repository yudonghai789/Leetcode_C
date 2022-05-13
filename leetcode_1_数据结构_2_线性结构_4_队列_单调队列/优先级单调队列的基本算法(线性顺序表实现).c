/******************************************************************************
* 版权所有 (c) 
* 功能描述   : 优先级单调队列的基本算法(线性顺序表实现)
* 作    者   : 
* 生成日期   : 
 * 保持有序的线性表（list）和二分查找插入方法自己手工维护一个“优先队列”。
   线性链表的插入最坏时间复杂度是O(N),因为链表只能有前后节点（堆实现的优先队列是O(logN)

   线性顺序表（数组）可以直接找数组下标，折半查找，但是插入又有复杂度
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


*/



/* --------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                  -- 宏定义 --                *
 * ---------------------------------------------------------------------------------------------------------------------------------------------------- */



/* ----------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 数据结构的基本定义-- *
 * ----------------------------------------------------------------------------------------------------------------------------------------------------- */
#define MINPQSize (10)
// #define MAXPQSize (1000)    // 做题的时候就不用动态申请，直接写死最大值就好了

#define MAXDATA (0x7fffffff)


typedef struct EelememtType {
    int intVal;
    char charVal;
} EelememtType;

typedef struct ListStruct {
    int capacity;
    int size;
    EelememtType *elems;   // 做题的时候就不用动态申请，直接写死最大值就好了
    EelememtType *temp;   // 用于拷贝，做题的时候就不用动态申请，直接写死最大值就好了
} ListStruct, PriorityQueue;


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
    PriorityQueue* H = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (H == NULL) {
        printf("maloc error \n");
    }
    memset(H, 0, sizeof(PriorityQueue));

    H->elems = (EelememtType *)malloc(sizeof(EelememtType) * initMaxElem);
    if (H->elems == NULL) {
        printf("maloc error \n");
    }
    memset(H->elems, 0, sizeof(EelememtType) * initMaxElem);

    H->temp = (EelememtType *)malloc(sizeof(EelememtType) * initMaxElem);
    if (H->elems == NULL) {
        printf("maloc error \n");
    }
    memset(H->temp, 0, sizeof(EelememtType) * initMaxElem);


    H->capacity = initMaxElem;
    H->size = 0;

    return H;
}


int FindInsetPo(PriorityQueue* H, EelememtType *elem)
{
    if ( H->size == 0) {
        return 0;
    }

    int frontBig = 0;
    int tailSmall = H->size - 1;
    int mid;


    if (elem->intVal > H->elems[0].intVal) {
        return 0;
    }

    if (elem->intVal <= H->elems[H->size - 1].intVal) {
        return H->size;
    }

    while (frontBig < tailSmall) {
        mid = (tailSmall - frontBig) / 2 + frontBig;
        if ((frontBig + 1 == tailSmall) && (H->elems[frontBig].intVal >= elem->intVal) && (H->elems[tailSmall].intVal < elem->intVal)) {
            return tailSmall;
        }

        if (H->elems[mid].intVal >= elem->intVal) {  // 大于等于不是插入的位置
            frontBig = mid;
        } else {                                          // 小于有可能是插入的位置
            tailSmall = mid;
        }
    }

    return 0;
}


/*****************************************************************************
 * 描  述: 入队列，折半查找
 * 参数说明：
 * 返回值：
*****************************************************************************/
void EnQueue(PriorityQueue* H, EelememtType elem)
{
    if (IsFull(H)) {
        printf("full \n");
        return;
    }

    int insetPosition = FindInsetPo(H, &elem);

    memcpy(&H->temp[0], &H->elems[insetPosition], sizeof(EelememtType) * (H->size - insetPosition));
    H->elems[insetPosition] = elem;
    memcpy(&H->elems[insetPosition + 1], &H->temp[0], sizeof(EelememtType) * (H->size - insetPosition));
    memset(&H->temp[0], 0, sizeof(EelememtType) * (H->capacity));
    H->size++;
}


/*****************************************************************************
 * 描  述: 出队列，
 * 参数说明：
 * 返回值：
*****************************************************************************/
EelememtType DeQueue(PriorityQueue* H)
{
    if (IsEmpty(H)) {
        printf("empty \n");
        EelememtType error = { 0xffff, 'x'};
        return error;
    }

    EelememtType max = H->elems[0];

    --H->size;
    memcpy(&H->temp[0], &H->elems[1], sizeof(EelememtType) * (H->size));
    memcpy(&H->elems[0], &H->temp[0], sizeof(EelememtType) * (H->size));
    memset(&H->temp[0], 0, sizeof(EelememtType) * (H->capacity));

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
        return H->elems[0];
    } 

    printf("enpty \n ");
    EelememtType error = { 0xffff, 'x'};
    return error;
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
    free(H->temp);
    free(H);
}



void MakeEmpty(PriorityQueue* H) {
    H->size = 0;

    memset(H->elems, 0, sizeof(EelememtType) * (H->capacity));
}



void PrintfQue(PriorityQueue* H)
{
    // 依次出队
    printf("riority_queue: ");
    for (int i = 0; i < H->size; i++) {
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

    ele.intVal = 5;
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

    ele.intVal = 0;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = 19;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 102;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = 0;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 1000;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = -9;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = 0;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = 30;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);


    ele.intVal = 20;
    ele.charVal = 'd';
    EnQueue(H , ele);
    PrintfQue(H);

    ele.intVal = 1000;
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
