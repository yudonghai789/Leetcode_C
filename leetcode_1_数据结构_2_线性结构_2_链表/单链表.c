/******************************************************************************
 * 版权所有 (c)
 * 功能描述   : leetcode 707. 设计链表. https://leetcode.cn/problems/design-linked-list/
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



#ifndef BIT_CLR
#define BIT_CLR(data, pos) ((data) &= ~(unsigned int)(0x1U << (pos)))
#endif

#ifndef BIT_TST
#define BIT_TST(data, pos) (((data) >> (pos)) & 0x1U)
#endif

#ifndef BIT_SET
#define BIT_SET(data, pos) ((data) |= (0x1U << (pos)))
#endif

// 翻转bit
#ifndef BIT_RVS
#define BIT_RVS(data, pos) ((data) ^= (0x1U << (pos)))
#endif

#ifndef BIT_CNT
#define BIT_CNT(data)                             \
do {                                              \
    int cnt = 0;                                  \
    for (int i = 0; i < 32; i++) {                \
        if (((data >> i) & 1) == 1) {             \
            cnt++;                                \
        }                                         \
    }                                             \
    return cnt;                                   \
} while (0)
#endif

int BitCnt(int bitmap)
{
    int cnt = 0;
    for (int i = 0; i < 32; i++) {
        if (((bitmap >> i) & 1) == 1) {
            cnt++;
        }
    }
    return cnt;
}





/* ----------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 数据结构的基本定义-- *
 * ----------------------------------------------------------------------------------------------------------------------------------------------------- */
#define INVALID_ELEM 0xffffffff

typedef struct Node {
    int  val;
    struct Node *next;
} Node;

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------- *
 *                -- 对外函数接口 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------- */



/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 工具小函数 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*
 * 
 */

/*
 * 
 */


/*
 * 打印单链表
 */
void ListPrint(Node *head)
{
    Node* temp = head; //将temp指针重新指向头结点
    //只要temp指针指向的结点的next不是Null，就执行输出语句。
    int index = 1;
    while (temp->next) {
        temp = temp->next;
        printf("{%d: %d} ->", index, temp->val);
        index++;
    }
    printf("\n");
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------ *
 *                -- 图的基本算法 --                *
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/*****************************************************************************
 * 描  述: 创建单链表(控制台输入)
 * 参数说明：
 * 返回值：
*****************************************************************************/



/*****************************************************************************
 * 描  述: 创建单链表(用已提供的数据)
 * 参数说明：
 * 返回值：
*****************************************************************************/
Node* ListCreate()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->val = INVALID_ELEM;
    head->next = NULL;
    return head;
}


// 根据元素数组生成链表
Node* ListInit(int *arr, int arrLen)
{
    Node *head = ListCreate();//创建一个头结点
    Node *temp = head;//声明一个指针指向头结点，用于遍历链表
    //生成链表
    for (int i = 0; i < arrLen; i++) {
        Node *a = (Node *)malloc(sizeof(Node));
        a->val = arr[i];
        a->next =NULL;

        temp->next = a;
        temp = temp->next;
    }
    return head;
}


/*****************************************************************************
 * 描  述: 插入结点
 * 参数说明：
 * 返回值：
*****************************************************************************/
// 在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点
void ListAddAtHead(Node* head, int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    if (head->next == NULL) {
        // 链表是空的，只有头结点
        head->next = node;
        return;
    } else {
        // 链表不是空的
        node->next = head->next;
        head->next = node;
        return;
    }
}

// 将值为 val 的节点追加到链表的最后一个元素。
void ListAddAtTail(Node* head, int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

// 在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
void ListAddAtIndex(Node* head, int index, int val)
{
    if (index <= 1) {
        ListAddAtHead(head, val);
        return;
    }

    Node *temp = head;
    int now = 1;
    while (temp->next != NULL) {
        if (now == index) {
            break;
        }
        temp = temp->next;
        now++;
    }

    if (index != now) {
        return;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = temp->next;
    temp->next = node;
}

/*****************************************************************************
 * 描  述: 删除结点
 * 参数说明：
 * 返回值：
*****************************************************************************/
Node* ListDelAtTail(Node * head)
{
    Node *temp = head->next;
    //遍历到被删除结点的上一个结点
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    Node *del = temp->next;//单独设置一个指针指向被删除结点，以防丢失
    temp->next = NULL;
    free(del);//手动释放该结点，防止内存泄漏
    return head;
}




// 如果索引 index 有效，则删除链表中的第 index 个节点
void ListDelAtIndex(Node* head, int index)
{
    if (index < 1 || head->next == NULL) {
        return;
    }

    Node *temp = head;
    if (index == 1) {
        Node *del = head->next;
        head->next = head->next->next;
        free(del);
        return;
    }

    temp = head->next;
    int now = 1;
    while (temp->next != NULL) {
        if (now == index - 1) {
            break;
        }
        temp = temp->next;
        now++;
    }

    if (now == index - 1 && temp->next != NULL) {
        Node *del = temp->next;
        temp->next = temp->next->next;
        free(del);
    }
}




// 如果索引 index 有效，则删除链表中的第 index 个节点
void ListDelByVal(Node* head, int val)
{
    Node *temp = head;
    while (temp->next != NULL) {
        if (temp->next->val == val) {
            Node *del = temp->next;
            temp->next = temp->next->next;
            free(del);
            return;
        }
        temp = temp->next;
    }
}

/*****************************************************************************
 * 描  述: 查找
 * 参数说明：
 * 返回值：
*****************************************************************************/
int ListFindElemIndexByVal(Node * head, int val)
{
    Node *temp = head;
    int i = 1;
    while (temp->next) {
        temp = temp->next;
        if (temp->val == val) {
            return i;
        }
        i++;
    }
    return -1;
}


// 获取链表中第 index 个节点的值。如果索引无效，则返回-1。
Node* ListFindElemByIndex(Node* head, int index)
{
    if (index < 1 || head->next == NULL) {
        return NULL;
    }

    int now = 1;
    Node *temp = head->next;
    while (now < index) {
        if (temp == NULL) {
            return NULL;
        }

        temp = temp->next;
        now++;
    }

    if (temp != NULL) {
        return temp;
    }

    return NULL;
}



/*****************************************************************************
 * 描  述: 修改
 * 参数说明：
 * 返回值：
*****************************************************************************/
void ListAmendElemByIndex(Node *head, int index, int newElemVal)
{
    Node *node = ListFindElemByIndex(head, index);
    node->val = newElemVal;
}



/*****************************************************************************
 * 描  述: 
 * 参数说明：
 * 返回值：
*****************************************************************************/
void NodeFree(Node* Node) {
    if (Node->next != NULL) {
        NodeFree(Node->next);
        Node->next = NULL;
    }
    free(Node);
    
}

void ListDestory(Node* head) {
    NodeFree(head);
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


// ---------------------------解法一 开始--------------------------------------------------------


typedef struct {
    Node *head;
} MyLinkedList;


MyLinkedList* myLinkedListCreate() {
    MyLinkedList *obj = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    obj->head = ListCreate();
    return obj;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    Node *node = ListFindElemByIndex(obj->head, index + 1);
    if (node == NULL) {
        return -1;
    } else {
        return node->val;
    }

}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    ListAddAtHead(obj->head, val);
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    ListAddAtTail(obj->head, val);
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    ListAddAtIndex(obj->head, index + 1, val);
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    ListDelAtIndex(obj->head, index + 1);
}

void myLinkedListFree(MyLinkedList* obj) {
    ListDestory(obj->head);
    free(obj);
}
// ---------------------------解法一 结束--------------------------------------------------------
int main() 
{
    MyLinkedList* obj = myLinkedListCreate();
    myLinkedListAddAtHead(obj, 2);
    ListPrint(obj->head);
    myLinkedListAddAtIndex(obj, 0, 1);
    ListPrint(obj->head);
    myLinkedListGet(obj, 1);
   
    return 0;
}
