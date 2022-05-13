>由于C语言本身不存在哈希，但是当需要使用哈希表的时候自己构建哈希会异常复杂。因此，我们可以调用开源的第三方头文件，这只是一个头文件：uthash.h。我们需要做的就是将头文件复制到您的项目中，然后：#include "uthash.h"。由于uthash仅是头文件，因此没有可链接的库代码。    
 使用uthash添加，查找和删除通常是常数时间的操作，此哈希的目标是简约高效。它大约有1000行C。它会自动内联，因为它是作为宏实现的。    
 uthash还包括三个额外的头文件，主要提供链表，动态数组和字符串。utlist.h为C结构提供了链接列表宏。utarray.h使用宏实现动态数组。utstring.h实现基本的动态字符串。
 
 
 
 ## 注意
  将hash表作为函数参数传递时
 
 ## 键类型
 整型 
 字符数组
 字符串
 指针
 结构体
 
 
 
 
 ## 使用实例 整型
 ```
/******************************************************************************
 * 版权所有 (c)
 * 功能描述   : leetcode 1. 两数之和 https://leetcode-cn.com/problems/two-sum/
 * 作    者   :
 * 生成日期   :
 * 从前往后递归不能使用备忘录，因为前面的结果先计算，后面的结果后计算，但是前面的结果是依赖后面数据，所以不能使用备忘录
 * 递推只能是后面根据前面的结果递推
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




typedef struct UthashTableInt {
    int key;
    int val;
    UT_hash_handle hh;
} UthashTableInt;


/*****************************************************************************
 * 描  述: uthash 遍历uthash
*****************************************************************************/
void TuhashFindAll(UthashTableInt** hashtableHead) {
    UthashTableInt *current_user, *tmp;

    HASH_ITER(hh, *hashtableHead, current_user, tmp) {
        printf("key = %d  ->  value = %d ;", current_user->key, current_user->val);
    }

    printf("\n");
}

/*****************************************************************************
 * 描  述: uthash 通过键值查找该键值对，未找到时返回NULL
*****************************************************************************/
UthashTableInt* TuhashFindByKey(UthashTableInt** hashtableHead, int ikey) {
    UthashTableInt* tmp;
    HASH_FIND_INT(*hashtableHead, &ikey, tmp);
    return tmp;
}

/*****************************************************************************
 * 描  述: uthash 通过键值对添加
*****************************************************************************/
void TuhashAdd(UthashTableInt** hashtableHead, int ikey, int ival) {
    UthashTableInt* it = TuhashFindByKey(hashtableHead, ikey);
    if (it == NULL) {
        UthashTableInt* tmp = (UthashTableInt*)malloc(sizeof(UthashTableInt));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(*hashtableHead, key, tmp);
    } else {
        it->val = ival;
    }
}


/*****************************************************************************
 * 描  述: uthash 通过键值对删除
*****************************************************************************/
void TuhashDelete(UthashTableInt** hashtableHead, UthashTableInt* hashtable) {
    HASH_DEL(*hashtableHead, hashtable);  /* 从键值表中删除这个键值，但是不刽释放内存 */
    free(hashtable);   // 释放这个键值对的内存，删除时的可选操作
}


/*****************************************************************************
 * 描  述: uthash 通过键值删除
*****************************************************************************/
void TuhashDeleteByKey(UthashTableInt** hashtableHead, int ikey) {
    UthashTableInt* it = TuhashFindByKey(hashtableHead, ikey);
    if (it != NULL) {
        HASH_DEL(*hashtableHead, it);  /* 从键值表中删除这个键值，但是不刽释放内存 */
        free(it);   // 释放这个键值对的内存，删除时的可选操作
    }
}

/*****************************************************************************
 * 描  述: uthash 遍历删除所有
*****************************************************************************/
void TuhashDeleteAll(UthashTableInt** hashtableHead) {
    UthashTableInt *current_user, *tmp;

    HASH_ITER(hh, *hashtableHead, current_user, tmp) {
        HASH_DEL(*hashtableHead, current_user);  /* delete it (users advances to next) */
        free(current_user);             /* free it */
    }
}


/*****************************************************************************
 * 描  述: uthash通过键值排序
*****************************************************************************/
int SortByKey(UthashTableInt* a, UthashTableInt* b) {
    return (a->key - b->key);   // 字符串使用 strcmp(a->key, b->key)
}

void TuhashSortByKey(UthashTableInt** hashtableHead) {
    HASH_SORT(*hashtableHead, SortByKey);
}

/*****************************************************************************
 * 描  述: uthash通过 Value 排序
*****************************************************************************/
int SortByValue(UthashTableInt* a, UthashTableInt* b) {
    return (a->val - b->val);   // 字符串使用 strcmp(a->val, b->val)
}

void TuhashSortByValue(UthashTableInt** hashtableHead) {
    HASH_SORT(*hashtableHead, SortByValue);
}









int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    UthashTableInt* hashtableHead = NULL;
    for (int i = 0; i < numsSize; i++) {
        int count = HASH_COUNT(hashtableHead);
        TuhashSortByKey(&hashtableHead);
        TuhashFindAll(&hashtableHead);
        UthashTableInt* it = TuhashFindByKey(&hashtableHead, target - nums[i]);
        if (it != NULL) {
            // TuhashDelete(&hashtableHead, it);
            // int* ret = (int *)malloc(sizeof(int) * 2);
            // ret[0] = it->val, ret[1] = i;
            // *returnSize = 2;
            // return ret;
        }
        TuhashAdd(&hashtableHead, nums[i], i);
        TuhashSortByValue(&hashtableHead);
        TuhashFindAll(&hashtableHead);
    }
    *returnSize = 0;
    return NULL;
}


int main() {
    int nums_1[] = {7,2,15,11};
    int numsSize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int target_1 = 9;
    int returnSize_1 = 45645641;
    int* result = twoSum(nums_1, numsSize_1, target_1, &returnSize_1);
    for (int i = 0; i < returnSize_1; i++) {
        printf("%d", result[i]);
    }

    return 0;
}
```
 
 
 
 
## 使用实例 字符数组
```
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include <math.h>
#include <assert.h>

/* leetcode 771. 宝石与石头. https://leetcode-cn.com/problems/jewels-and-stones/
 * uthash 
 */
typedef struct UthshCharArray {
    char key[2];
    int val;  // 这道题其实也可以不需要Value
    UT_hash_handle hh;
} UthshCharArray;

UthshCharArray* UthshFindByKey(UthshCharArray **UthshHead, char ikey[2])
{
    UthshCharArray *temp = NULL;
    HASH_FIND_STR(*UthshHead, ikey, temp);
    return temp;
}

UthshCharArray* UthshAddByKey(UthshCharArray **UthshHead, char ikey[2], int value)
{
    UthshCharArray *temp = UthshFindByKey(UthshHead, ikey);
    if (temp == NULL) {
        temp = (UthshCharArray *)malloc(sizeof(UthshCharArray));
        memset(temp, 0, sizeof(UthshCharArray));
        strcpy(temp->key, ikey), temp->val = value;
        HASH_ADD_STR(*UthshHead, key, temp);
        return temp;
    } else {
        printf("linr 38 error");
        return NULL;
    }
}


int numJewelsInStones(char *jewels, char *stones)
{
    UthshCharArray *UthshHead = NULL;
    for (int i = 0; i < strlen(jewels); i++) {
        char key[2] = { 0 };
        key[0] = jewels[i];
        UthshAddByKey(&UthshHead, key, 0);
    }
    
    int resultCount = 0;
    for (int i = 0; i < strlen(stones); i++) {
        char key[2] = { 0 };
        key[0] = stones[i];
        if (UthshFindByKey(&UthshHead, key) != NULL) {
            resultCount++;
        }
    }

    return resultCount;
}

int main() {
    char stones_1[] = "aAAbbbb";
    char jewels_1[] = "aA";
    int result_1 = numJewelsInStones(jewels_1, stones_1);
    assert(result_1 == 3);



    return 0;
}
```

## 使用实例 字符串指针
```
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include <math.h>
#include <assert.h>

typedef struct UthashString {
    char *key;          /* key */
    int val;
    UT_hash_handle hh;         /* makes this structure hashable */
} UthashString;

UthashString* UthashFind(UthashString **UthashHead, char* key)
{
    UthashString *tmp = NULL;
    HASH_FIND_STR(*UthashHead, key, tmp);
    return tmp;
}

UthashString* UthashAdd(UthashString **UthashHead, char* key, int value)
{
    UthashString *tmp = UthashFind(UthashHead, key);
    if (tmp == NULL) {
        tmp = (UthashString *)malloc(sizeof(UthashString));
        memset(tmp, 0, sizeof(UthashString));
        tmp->key = key, tmp->val = value;   // 这个tmp->key只是指针，没有内存
        HASH_ADD_KEYPTR(hh, *UthashHead, tmp->key, strlen(tmp->key), tmp);
        return tmp;
    } else {
        printf("Add error already exit");
        return NULL;
    }
}

void UthashAddValueByKey(UthashString **UthashHead, char* key, int addValue)
{
    UthashString *tmp = UthashFind(UthashHead, key);
    if (tmp == NULL) {
        printf("Addvalue error not exit");
        return;
    } else {
        tmp->val = tmp->val + addValue;
    }
}


void UthashPrintAll(UthashString **UthashHead)
{
    UthashString *current_user, *tmp;

    HASH_ITER(hh, *UthashHead, current_user, tmp) {
        printf("key = %s  ->  value = %d ;", current_user->key, current_user->val);
    }

    printf("\n");
}

void TestUthashString(char **names, int namesSize)
{
    UthashString *UthashHead = NULL;
    for (int i = 0; i < namesSize; i++) {
        UthashString *find = UthashFind(&UthashHead, names[i]);
        if (find == NULL) {
            UthashAdd(&UthashHead, names[i], 1);
        } else {
            UthashAddValueByKey(&UthashHead, names[i], 1);
        }
        UthashPrintAll(&UthashHead);
    }
}


int main(int argc, char *argv[]) {
    char *names[5] = { "joe", "bob", "betty", "betty" , "bob"};
    int namesSize = 5; 
    TestUthashString(names, namesSize);

    return 0;
}
```


## 使用实例 指针



## 使用实例 结构体
```
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include <math.h>
#include <assert.h>

typedef struct StructKey {
  char keyA[30];
  int KeyB;
} StructKey;

typedef struct UthashStruct {
    StructKey key;          /* key */
    int val;
    UT_hash_handle hh;         /* makes this structure hashable */
} UthashStruct;

UthashStruct* UthashFind(UthashStruct **UthashHead, StructKey* key)
{
    UthashStruct *tmp = NULL;
    HASH_FIND(hh, *UthashHead, key, sizeof(StructKey), tmp);
    return tmp;
}

UthashStruct* UthashAdd(UthashStruct **UthashHead, StructKey* key, int value)
{
    UthashStruct *tmp = UthashFind(UthashHead, key);
    if (tmp == NULL) {
        tmp = (UthashStruct *)malloc(sizeof(UthashStruct));
        memset(tmp, 0, sizeof(UthashStruct));
        strcpy(tmp->key.keyA, key->keyA); 
        tmp->key.KeyB = key->KeyB;
        tmp->val = value;
        HASH_ADD(hh, *UthashHead, key, sizeof(StructKey), tmp);
        return tmp;
    } else {
        printf("Add error already exit");
        return NULL;
    }
}

void UthashAddValueByKey(UthashStruct **UthashHead, StructKey* key, int addValue)
{
    UthashStruct *tmp = UthashFind(UthashHead, key);
    if (tmp == NULL) {
        printf("Addvalue error not exit");
        return;
    } else {
        tmp->val = tmp->val + addValue;
    }
}


void UthashPrintAll(UthashStruct **UthashHead)
{
    UthashStruct *current_user, *tmp;

    HASH_ITER(hh, *UthashHead, current_user, tmp) {
        printf("key = %s %d  ->  value = %d ;", current_user->key.keyA, current_user->key.KeyB, current_user->val);
    }

    printf("\n");
}

void TestUthashStruct(StructKey *names, int namesSize)
{
    UthashStruct *UthashHead = NULL;
    for (int i = 0; i < namesSize; i++) {
        UthashStruct *find = UthashFind(&UthashHead, &names[i]);
        if (find == NULL) {
            UthashAdd(&UthashHead, &names[i], 1);
        } else {
            UthashAddValueByKey(&UthashHead, &names[i], 1);
        }
        UthashPrintAll(&UthashHead);
    }
}


int main(int argc, char *argv[]) {
    StructKey names[10] = { {"joe", 15},
                            {"bob", 6},
                            {"diel", 5},
                            {"joe", 25},
                            {"joe", 15},
                            {"joe", 15},
                            {"joe", 5},
                            {"joe", 5},
                            {"joe", 5},
                            {"joe", 5},
                          };
    int namesSize = 10; 
    TestUthashStruct(names, namesSize);

    return 0;
}
```




 
## 参考文章
    https://blog.csdn.net/houjixin/article/details/15809825
    https://blog.csdn.net/m0_62935482/article/details/120773948
    
    
    
