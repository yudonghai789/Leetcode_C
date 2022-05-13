## 自己实现Hash表

leetcode 609. 在系统中查找重复文件 https://leetcode-cn.com/problems/find-duplicate-file-in-system/

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
#include "dierti.h"
#include <math.h>
#include <assert.h>


/**
 * leetcode 609. 在系统中查找重复文件 https://leetcode-cn.com/problems/find-duplicate-file-in-system/
 * 在文件内容较长时超时，因为我是通过字典树实现的hash, 真正的hash应该根据键值直接计算出地址。
 */
# define MAX_FILE_PATH 20010
# define MAX_PATH_LEN 3010

typedef struct CharNode {
    char allPath[MAX_PATH_LEN];
    char key[MAX_PATH_LEN];
    char path[MAX_PATH_LEN];
} CharNode;

typedef struct CharNodeArray {
    int count;
    CharNode charNode[MAX_FILE_PATH];
} CharNodeArray;

void SpliteKeyAndValue(char *allPath, CharNode* charNode)
{
    char *path = strtok(allPath, "(");
    strcat(charNode->path, path);
    path = strtok(NULL, "(");
    
    char *key = strtok(path, ")");
    strcat(charNode->key, key);
    // printf("key = %s --> value = %s \n", charNode->key, charNode->path);
}

typedef struct StringListNode {
    char *path;
    struct StringListNode* next;
} StringListNode;

typedef struct CharLinkHashMap {
    struct CharLinkHashMap *linkNext[52];
    int count;
    StringListNode *Vluelist;
    int indexOne;
    int indexTwo;
} CharLinkHashMap;

int IndexOfChar(char charter)
{
    return (((charter - 'a') > 0) && ((charter - 'a') < 26)) ? (charter - 'a') : (charter - 'A');
}

CharLinkHashMap* HashMapTreeAddNode(CharLinkHashMap *charArrayKeyMap, int linkIndex)
{
    CharLinkHashMap *newNode = (CharLinkHashMap*)malloc(sizeof(CharLinkHashMap));
    memset((void*)newNode, 0, sizeof(CharLinkHashMap));
    charArrayKeyMap->linkNext[linkIndex] = newNode;
    return newNode;
}

CharLinkHashMap *HashMapTreeGetNodeByAddKey(CharLinkHashMap *root, char* key, char *path)
{
    CharLinkHashMap *TreeRoot = root;
    for (int i = 0; i < strlen(key); i++) {
        if (TreeRoot->linkNext[IndexOfChar(key[i])] == NULL) {
            TreeRoot = HashMapTreeAddNode(TreeRoot, IndexOfChar(key[i]));
        } else {
            TreeRoot = TreeRoot->linkNext[IndexOfChar(key[i])];
        }
        
    }

    if (TreeRoot->Vluelist == NULL) {
        StringListNode *newPathListNode = (StringListNode*)malloc(sizeof(StringListNode));
        memset((void*)newPathListNode, 0, sizeof(StringListNode));
        newPathListNode->path = path;
        TreeRoot->Vluelist = newPathListNode;
    } else {
        StringListNode *pathList = TreeRoot->Vluelist;
        while (pathList->next != NULL) {
            pathList = pathList->next;
        }
        StringListNode *newPathListNode = (StringListNode*)malloc(sizeof(StringListNode));
        memset((void*)newPathListNode, 0, sizeof(StringListNode));
        newPathListNode->path = path;
        pathList->next = newPathListNode;
    }
    
    TreeRoot->count++;

    return TreeRoot;
}


void ListFree(StringListNode *Vluelist)
{
    if (Vluelist->next != NULL) {
        ListFree(Vluelist->next);
    }

    free(Vluelist);
}

void HashMapTreeFree(CharLinkHashMap *charArrayKeyMap)
{
    for (int i = 0; i < 26; i++) {
        if (charArrayKeyMap->linkNext[i] != NULL) {
            HashMapTreeFree(charArrayKeyMap->linkNext[i]);
        }
    }

    if (charArrayKeyMap->Vluelist != NULL) {
        ListFree(charArrayKeyMap->Vluelist);
    }

    free(charArrayKeyMap);
}

char*** findDuplicate(char ** paths, int pathsSize, int* returnSize, int** returnColumnSizes)
{
    CharNodeArray *charNodeArray = (CharNodeArray *)malloc(sizeof(CharNodeArray));
    memset(charNodeArray, 0, sizeof(CharNodeArray));
    charNodeArray->count = 0;

    for (int i = 0; i < pathsSize; i++) {
        // printf("%s \n", paths[i]);
        char tempValue[MAX_PATH_LEN] = { 0 };
        char *token = strtok(paths[i], " ");
        strcat(tempValue, token);
        // printf("%s \n", token);
        while (token != NULL) {
            token = strtok(NULL, " ");
            // printf("%s \n", token);
            if (token != NULL) {
                if (charNodeArray->count >= MAX_FILE_PATH) { printf("line 143 error"); return NULL; }
                CharNode* charNode = &charNodeArray->charNode[charNodeArray->count];
                charNodeArray->count++;
                memset((void *)charNode, 0, sizeof(CharNode));
                strcat(charNode->allPath, tempValue);
                strcat(charNode->allPath, "/");
                strcat(charNode->allPath, token);
                // printf("%s \n", charNode->allPath);
            }
        }
    }

    for (int i = 0; i < charNodeArray->count; i++) {
        CharNode* charNode = &charNodeArray->charNode[i];
        SpliteKeyAndValue(charNode->allPath, charNode);
    }

    (*returnSize) = 0;
    char ***result = (char ***)malloc(sizeof(char**) * charNodeArray->count);
    memset(result, 0, sizeof(char**) * charNodeArray->count);
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * charNodeArray->count);   // (*returnColumnSizes) 就是一维数组的指针
    memset((*returnColumnSizes), 0, sizeof(int) * charNodeArray->count);
    CharLinkHashMap *charArrayKeyMapRoot = (CharLinkHashMap *)malloc(sizeof(CharLinkHashMap));
    memset(charArrayKeyMapRoot, 0, sizeof(CharLinkHashMap));
    for (int pathIndex = 0; pathIndex < charNodeArray->count; pathIndex++) {
        CharNode* charNode = &charNodeArray->charNode[pathIndex];
        CharLinkHashMap *node = HashMapTreeGetNodeByAddKey(charArrayKeyMapRoot, charNode->key, charNode->path);
        if (node->count == 2) {
            if ((charNodeArray->count <= (*returnSize)) || ((*returnSize) < 0)) { printf("line 170 error %d", (*returnSize)); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }

            result[(*returnSize)] = (char**)malloc(sizeof(char*) * charNodeArray->count);
            memset(result[(*returnSize)], 0, sizeof(char*) * charNodeArray->count);

            if ((charNodeArray->count <= (*returnSize)) || ((*returnSize) < 0)) { printf("line 175  error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }
            if ((charNodeArray->count <= ((*returnColumnSizes)[(*returnSize)])) || (((*returnColumnSizes)[(*returnSize)]) < 0)) { printf("error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }

            result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])] = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
            memset(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], 0, sizeof(char) * MAX_PATH_LEN);
            strcpy(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], node->Vluelist->path);
            (*returnColumnSizes)[(*returnSize)]++;

            if ((charNodeArray->count <= (*returnSize)) || ((*returnSize) < 0)) { printf("line 183  error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }
            if ((charNodeArray->count <= ((*returnColumnSizes)[(*returnSize)])) || (((*returnColumnSizes)[(*returnSize)]) < 0)) { printf("error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }

            result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])] = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
            memset(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], 0, sizeof(char) * MAX_PATH_LEN);
            strcpy(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], charNode->path);
            (*returnColumnSizes)[(*returnSize)]++;
 
            node->indexOne = (*returnSize);
            node->indexTwo = ((*returnColumnSizes)[(*returnSize)]);

            (*returnSize)++;


            if ((charNodeArray->count < node->indexOne) || (node->indexOne < 0)) { printf("line 197 error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }
            if ((charNodeArray->count < node->indexTwo) || (node->indexTwo < 0)) { printf("line 198 error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }
        } else if (node->count > 2) {
            if ((charNodeArray->count <= node->indexOne) || (node->indexOne < 0)) { printf("line 200 error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }
            if ((charNodeArray->count <= node->indexTwo) || (node->indexTwo < 0)) { printf("line 201 error"); HashMapTreeFree(charArrayKeyMapRoot); free(charNodeArray); return NULL; }


            result[node->indexOne][node->indexTwo] = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
            memset(result[node->indexOne][node->indexTwo], 0, sizeof(char) * MAX_PATH_LEN);
            strcpy(result[node->indexOne][node->indexTwo], charNode->path);
            (*returnColumnSizes)[node->indexOne]++;
            node->indexTwo++;
        }
    }

    HashMapTreeFree(charArrayKeyMapRoot);
    free(charNodeArray);

    return result;
}

// ---------------------------解法 结束--------------------------------------------------------
int main() {
    // char paths_1[4][50] = { "root/a 1.txt(abcd) 2.txt(efgh)",
    //                         "root/c 3.txt(abcd)",
    //                         "root/c/d 4.txt(efgh)",
    //                         "root 4.txt(efgh)"
    //                       };
    // int pathsSize_1 = sizeof(paths_1) / sizeof(paths_1[0]);
    // char *pathsArry_1[pathsSize_1];
    // for (int i = 0; i < pathsSize_1; i++) { pathsArry_1[i] = &paths_1[i][0]; }
    // int returnSize_1 = 4546456;
    // int *returnColumnSizes_1 = NULL;
    // char ***result_1 = findDuplicate(pathsArry_1, pathsSize_1, &returnSize_1, &returnColumnSizes_1);
    // for (int i = 0; i < returnSize_1; i++) {
    //     for (int j = 0; j < returnColumnSizes_1[i]; j++) {
    //         printf("%s, ", result_1[i][j]);
    //     }
    //     printf("\n");
    // }


    // char paths_2[1][300] = { "root/t/vsjm/jrrrsogmq/kkahnjzlp/hdtlyxwygv/ut/z ckegzyfjwc.txt(ctmgtptvblsirdqpkfuqpzsotlueetltxnwrco) nps.txt(ctmgtptvblsirdqpkfuqpzsotlueetltxnwrco)"
    //                       };
    // int pathsSize_2 = sizeof(paths_2) / sizeof(paths_2[0]);
    // char *pathsArry_2[pathsSize_2];
    // for (int i = 0; i < pathsSize_2; i++) { pathsArry_2[i] = &paths_2[i][0]; }
    // int returnSize_2 = 45642156;
    // int *returnColumnSizes_2 = NULL;
    // char ***result_2 = findDuplicate(pathsArry_2, pathsSize_2, &returnSize_2, &returnColumnSizes_2);
    // for (int i = 0; i < returnSize_2; i++) {
    //     for (int j = 0; j < returnColumnSizes_2[i]; j++) {
    //         printf("%s, ", result_2[i][j]);
    //     }
    //     printf("\n");
    // }


    char paths_3[1][3000] = { "root/jlwa/ttqlpiz/mgzsbcluaey/xjbd/loqypo/lrqgoaieipf/yqldqjbvdteih/xojqbkcro iph.txt(mm) knohpsfdmgrzbl.txt(rdixrkqwxikhzgincyfjhpvmzcmnfcmvh) jx.txt(pdaljluwbnwstblsjtvn) dqrcd.txt(ripvthuzmyujsmgmqaeypgecrcdgmcpzxctvjxhwqmpvkwrmho) yjskythkxynzc.txt(olu) axtheehicefr.txt(ripvthuzmyujsmgmqaeypgecrcdgmcpzxctvjxhwqmpvkwrmho) twilqrk.txt(pdaljluwbnwstblsjtvn) pwombqmlapqd.txt(rdixrkqwxikhzgincyfjhpvmzcmnfcmvh)"
                          };
    int pathsSize_3 = sizeof(paths_3) / sizeof(paths_3[0]);
    char *pathsArry_3[pathsSize_3];
    for (int i = 0; i < pathsSize_3; i++) { pathsArry_3[i] = &paths_3[i][0]; }
    int returnSize_3 = 45642156;
    int *returnColumnSizes_3 = NULL;
    char ***result_3 = findDuplicate(pathsArry_3, pathsSize_3, &returnSize_3, &returnColumnSizes_3);
    for (int i = 0; i < returnSize_3; i++) {
        for (int j = 0; j < returnColumnSizes_3[i]; j++) {
            printf("%s, ", result_3[i][j]);
        }
        printf("\n");
    }


    return 0;
}
```



## 使用uthash

leetcode 609. 在系统中查找重复文件 https://leetcode-cn.com/problems/find-duplicate-file-in-system/

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
#include "dierti.h"
#include <math.h>
#include <assert.h>


/**
 * leetcode 609. 在系统中查找重复文件 https://leetcode-cn.com/problems/find-duplicate-file-in-system/
 * 在文件内容较长时超时，因为我是通过字典树实现的hash, 真正的hash应该根据键值直接计算出地址。
 */
# define MAX_FILE_PATH 20010
# define MAX_PATH_LEN 3010

typedef struct PerFileNode {
    char allPath[MAX_PATH_LEN];
} PerFileNode;

typedef struct FileNodeArray {
    int count;
    PerFileNode charNode[MAX_FILE_PATH];
} FileNodeArray;

typedef struct HashValue {
    char firstPath[MAX_PATH_LEN];
    int count;
    int resultIndexOne;
    int resultIndexTwo;
} HashValue;

typedef struct UthshPath {
    char key[MAX_PATH_LEN];
    HashValue value;
    UT_hash_handle hh;
} UthshPath;

void SpliteKeyAndValue(char *allPath, UthshPath* hash)
{
    char *path = strtok(allPath, "(");
    strcat(hash->value.firstPath, path);
    path = strtok(NULL, "(");
    
    char *key = strtok(path, ")");
    strcat(hash->key, key);
    hash->value.count = 1;
    hash->value.resultIndexOne = -1;
    hash->value.resultIndexTwo = -1;
}

UthshPath* UthashFindByKey(UthshPath** uthshHead, char ikey[MAX_PATH_LEN])
{
    UthshPath* temp = NULL;
    HASH_FIND_STR(*uthshHead, ikey, temp);
    return temp;
}

void UthashAddByKeyAddValue(UthshPath** uthshHead, char ikey[MAX_PATH_LEN], HashValue* value)
{
    UthshPath* temp = UthashFindByKey(uthshHead, ikey);
    if (temp == NULL) {
        temp = (UthshPath *)malloc(sizeof(UthshPath));
        strcpy(temp->key, ikey);
        temp->value = *value;
        temp->value.count = 1;
        temp->value.resultIndexOne = -1;
        temp->value.resultIndexTwo = -1;
        HASH_ADD_STR(*uthshHead, key, temp);
    } else {
        printf("add error");
    }
}


void UthashFreeAll(UthshPath** uthshHead)
{
    UthshPath *current_user, *tmp;
    HASH_ITER(hh, *uthshHead, current_user, tmp) {
        HASH_DEL(*uthshHead, current_user);  /* delete it (users advances to next) */
        free(current_user);             /* free it */
    }
}


char*** findDuplicate(char ** paths, int pathsSize, int* returnSize, int** returnColumnSizes)
{
    FileNodeArray *fileNodeArray = (FileNodeArray *)malloc(sizeof(FileNodeArray));
    memset(fileNodeArray, 0, sizeof(FileNodeArray));
    fileNodeArray->count = 0;

    for (int i = 0; i < pathsSize; i++) {
        // printf("%s \n", paths[i]);
        char tempValue[MAX_PATH_LEN] = { 0 };
        char *token = strtok(paths[i], " ");
        strcat(tempValue, token);
        // printf("%s \n", token);
        while (token != NULL) {
            token = strtok(NULL, " ");
            // printf("%s \n", token);
            if (token != NULL) {
                if (fileNodeArray->count >= MAX_FILE_PATH) { printf("line 143 error"); return NULL; }
                PerFileNode* perFileNode = &fileNodeArray->charNode[fileNodeArray->count];
                fileNodeArray->count++;
                memset((void *)perFileNode, 0, sizeof(PerFileNode));
                strcat(perFileNode->allPath, tempValue);
                strcat(perFileNode->allPath, "/");
                strcat(perFileNode->allPath, token);
                // printf("%s \n", perFileNode->allPath);
            }
        }
    }


    (*returnSize) = 0;
    char ***result = (char ***)malloc(sizeof(char**) * fileNodeArray->count);
    memset(result, 0, sizeof(char**) * fileNodeArray->count);
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * fileNodeArray->count);   // (*returnColumnSizes) 就是一维数组的指针
    memset((*returnColumnSizes), 0, sizeof(int) * fileNodeArray->count);

    UthshPath* uthshHead = NULL;
    for (int pathIndex = 0; pathIndex < fileNodeArray->count; pathIndex++) {
        PerFileNode* perFileNode = &fileNodeArray->charNode[pathIndex];
        UthshPath tempHash = { 0 };
        SpliteKeyAndValue(perFileNode->allPath, &tempHash);
        UthshPath* find = UthashFindByKey(&uthshHead, tempHash.key);
        if (find == NULL) {
            UthashAddByKeyAddValue(&uthshHead, tempHash.key, &tempHash.value);
        } else {
            if (find->value.count == 1) {
                if ((fileNodeArray->count <= (*returnSize)) || ((*returnSize) < 0)) { printf("line 170 error %d", (*returnSize)); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }

                result[(*returnSize)] = (char**)malloc(sizeof(char*) * fileNodeArray->count);
                memset(result[(*returnSize)], 0, sizeof(char*) * fileNodeArray->count);

                if ((fileNodeArray->count <= (*returnSize)) || ((*returnSize) < 0)) { printf("line 175  error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }
                if ((fileNodeArray->count <= ((*returnColumnSizes)[(*returnSize)])) || (((*returnColumnSizes)[(*returnSize)]) < 0)) { printf("error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }

                result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])] = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
                memset(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], 0, sizeof(char) * MAX_PATH_LEN);
                strcpy(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], find->value.firstPath);
                (*returnColumnSizes)[(*returnSize)]++;

                if ((fileNodeArray->count <= (*returnSize)) || ((*returnSize) < 0)) { printf("line 183  error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }
                if ((fileNodeArray->count <= ((*returnColumnSizes)[(*returnSize)])) || (((*returnColumnSizes)[(*returnSize)]) < 0)) { printf("error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }

                result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])] = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
                memset(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], 0, sizeof(char) * MAX_PATH_LEN);
                strcpy(result[(*returnSize)][((*returnColumnSizes)[(*returnSize)])], tempHash.value.firstPath);
                (*returnColumnSizes)[(*returnSize)]++;
    
                find->value.count++;
                find->value.resultIndexOne = (*returnSize);
                find->value.resultIndexTwo = ((*returnColumnSizes)[(*returnSize)]);

                (*returnSize)++;


                if ((fileNodeArray->count < find->value.resultIndexOne) || (find->value.resultIndexOne < 0)) { printf("line 197 error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }
                if ((fileNodeArray->count < find->value.resultIndexTwo) || (find->value.resultIndexTwo < 0)) { printf("line 198 error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }
            } else if (find->value.count >= 2) {
                if ((fileNodeArray->count <= find->value.resultIndexOne) || (find->value.resultIndexOne < 0)) { printf("line 200 error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }
                if ((fileNodeArray->count <= find->value.resultIndexTwo) || (find->value.resultIndexTwo < 0)) { printf("line 201 error"); UthashFreeAll(&uthshHead); free(fileNodeArray); return NULL; }

                find->value.count++;
                result[find->value.resultIndexOne][find->value.resultIndexTwo] = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
                memset(result[find->value.resultIndexOne][find->value.resultIndexTwo], 0, sizeof(char) * MAX_PATH_LEN);
                strcpy(result[find->value.resultIndexOne][find->value.resultIndexTwo], tempHash.value.firstPath);
                (*returnColumnSizes)[find->value.resultIndexOne]++;
                find->value.resultIndexTwo++;
            }
        }
    }
    UthashFreeAll(&uthshHead); 
    free(fileNodeArray);

    return result;
}
```

leetcode 49. 字母异位词分组 https://leetcode-cn.com/problems/group-anagrams/
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
#include "dierti.h"
#include <math.h>
#include <assert.h>


/**
 * leetcode 49. 字母异位词分组 https://leetcode-cn.com/problems/group-anagrams/
 */
typedef union CharCountStructKey {
    int charCount[26];
    struct {
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        int g;
        int h;
        int i;
        int j;
        int k;
        int l;
        int m;
        int n;
        int o;
        int p;
        int q;
        int r;
        int s;
        int t;
        int u;
        int v;
        int w;
        int x;
        int y;
        int z;
    } content;
} CharCountStructKey;

typedef struct HashValue {
    // char firstPath[110];
    int resGropIdx;
    int resCntIdx;
} HashValue;


typedef struct UthashStructTable {
    CharCountStructKey key;
    HashValue value;
    UT_hash_handle hh;
} UthashStructTable;

int IndexOfChar(char charter)
{
    return (charter - 'a');
}

void GenCharCountKey(char *string, int strlenth, CharCountStructKey *key)
{
    for (int i = 0; i < strlenth; i++) {
        key->charCount[IndexOfChar(string[i])]++;
    }
}

UthashStructTable* UthashFindByKey(UthashStructTable** uthashhead, CharCountStructKey *ikey)
{
    UthashStructTable* temp = NULL;
    HASH_FIND(hh, *uthashhead, ikey, sizeof(CharCountStructKey), temp);
    return temp;
}

UthashStructTable* UthashAddByKey(UthashStructTable** uthashhead, CharCountStructKey *ikey)
{
    UthashStructTable* temp = UthashFindByKey(uthashhead, ikey);
    if (temp == NULL) {
        temp = (UthashStructTable*)malloc(sizeof(UthashStructTable));
        memset(temp, 0, sizeof(UthashStructTable));
        temp->key = *ikey;
        temp->value.resGropIdx = -1;
        temp->value.resCntIdx = -1;
        HASH_ADD(hh, *uthashhead, key, sizeof(CharCountStructKey), temp);
        return temp;
    } else {
        printf("add error already exit");
        return NULL;
    }
}

char*** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    UthashStructTable* uthashhead = NULL;
    (*returnSize) = 0;
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * strsSize);
    memset((*returnColumnSizes), 0, sizeof(int) * strsSize);
    char ***result = (char ***)malloc(sizeof(char**) * strsSize);
    memset((result), 0, sizeof(char**) * strsSize);
    for (int i = 0; i < strsSize; i++) {
        CharCountStructKey tempKey = { 0 };
        GenCharCountKey(strs[i], strlen(strs[i]), &tempKey);
        UthashStructTable* find = UthashFindByKey(&uthashhead, &tempKey);
        if (find == NULL) {
            find =UthashAddByKey(&uthashhead, &tempKey);
            find->value.resGropIdx = (*returnSize);
            find->value.resCntIdx = 0;

            result[find->value.resGropIdx] = (char**)malloc(sizeof(char*) * strsSize);
            memset(result[find->value.resGropIdx], 0, sizeof(char*) * strsSize);

            result[find->value.resGropIdx][find->value.resCntIdx] = (char*)malloc(sizeof(char) * (strlen(strs[i]) + 1));
            memset(result[find->value.resGropIdx][find->value.resCntIdx], 0, sizeof(char) * (strlen(strs[i]) + 1));
            memcpy(result[find->value.resGropIdx][find->value.resCntIdx], strs[i], sizeof(char) * (strlen(strs[i])));
            
            find->value.resCntIdx++;
            (*returnColumnSizes)[*returnSize] = find->value.resCntIdx;
            (*returnSize)++;
        } else {
            result[find->value.resGropIdx][find->value.resCntIdx] = (char*)malloc(sizeof(char) * (strlen(strs[i]) + 1));
            memset(result[find->value.resGropIdx][find->value.resCntIdx], 0, sizeof(char) * (strlen(strs[i]) + 1));
            memcpy(result[find->value.resGropIdx][find->value.resCntIdx], strs[i], sizeof(char) * (strlen(strs[i])));
            find->value.resCntIdx++;
            (*returnColumnSizes)[find->value.resGropIdx] = find->value.resCntIdx;
        } 
    }

    return result;
}

int main() {
    int strsSize_1 = 6;
    char *strs_1[] = { "eat", "tea", "tan", "ate", "nat", "bat" };
    int returnSize_1 = 45645264;
    int *returnColumnSizes = NULL;
    char*** result_1 = groupAnagrams(strs_1, strsSize_1, &returnSize_1, &returnColumnSizes);
    for (int i = 0; i < returnSize_1; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%s, ", result_1[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```


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
#include "dierti.h"
#include <math.h>
#include <assert.h>


/**
 * leetcode 49. 字母异位词分组 https://leetcode-cn.com/problems/group-anagrams/
 */

typedef struct HashValue {
    int resGropIdx;
    int resCntIdx;
} HashValue;

typedef struct UthashStructTable {
    char key[110];
    HashValue value;
    UT_hash_handle hh;
} UthashStructTable;

UthashStructTable* UthashFindByKey(UthashStructTable** uthashhead, char *ikey)
{
    UthashStructTable* temp = NULL;
    HASH_FIND_STR(*uthashhead, ikey, temp);
    return temp;
}

UthashStructTable* UthashAddByKey(UthashStructTable** uthashhead, char *ikey)
{
    UthashStructTable* temp = UthashFindByKey(uthashhead, ikey);
    if (temp == NULL) {
        temp = (UthashStructTable*)malloc(sizeof(UthashStructTable));
        memset(temp, 0, sizeof(UthashStructTable));
        strcpy(temp->key, ikey);
        temp->value.resGropIdx = -1;
        temp->value.resCntIdx = -1;
        HASH_ADD_STR(*uthashhead, key, temp);
        return temp;
    } else {
        printf("add error already exit");
        return NULL;
    }
}

int CompareChar(const void *a, const void *b)
{
    // return strcmp((char*)a, (char*)b);  // 字符串
    return *(char *)a - *(char *)b;     // 字符
}

char*** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    UthashStructTable* uthashhead = NULL;
    (*returnSize) = 0;
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * strsSize);
    memset((*returnColumnSizes), 0, sizeof(int) * strsSize);
    char ***result = (char ***)malloc(sizeof(char**) * strsSize);
    memset((result), 0, sizeof(char**) * strsSize);
    for (int i = 0; i < strsSize; i++) {
        char tempKey[strlen(strs[i]) + 1];
        memset(tempKey, 0, sizeof(char) * strlen(strs[i]) + 1);
        memcpy(tempKey, strs[i], sizeof(char) * strlen(strs[i]));
        qsort(tempKey, strlen(strs[i]), sizeof(char), CompareChar);
        UthashStructTable* find = UthashFindByKey(&uthashhead, tempKey);
        if (find == NULL) {
            find = UthashAddByKey(&uthashhead, tempKey);
            find->value.resGropIdx = (*returnSize);
            find->value.resCntIdx = 0;

            result[find->value.resGropIdx] = (char**)malloc(sizeof(char*) * strsSize);
            memset(result[find->value.resGropIdx], 0, sizeof(char*) * strsSize);

            result[find->value.resGropIdx][find->value.resCntIdx] = (char*)malloc(sizeof(char) * (strlen(strs[i]) + 1));
            memset(result[find->value.resGropIdx][find->value.resCntIdx], 0, sizeof(char) * (strlen(strs[i]) + 1));
            memcpy(result[find->value.resGropIdx][find->value.resCntIdx], strs[i], sizeof(char) * (strlen(strs[i])));
            
            find->value.resCntIdx++;
            (*returnColumnSizes)[*returnSize] = find->value.resCntIdx;
            (*returnSize)++;
        } else {
            result[find->value.resGropIdx][find->value.resCntIdx] = (char*)malloc(sizeof(char) * (strlen(strs[i]) + 1));
            memset(result[find->value.resGropIdx][find->value.resCntIdx], 0, sizeof(char) * (strlen(strs[i]) + 1));
            memcpy(result[find->value.resGropIdx][find->value.resCntIdx], strs[i], sizeof(char) * (strlen(strs[i])));
            find->value.resCntIdx++;
            (*returnColumnSizes)[find->value.resGropIdx] = find->value.resCntIdx;
        } 
    }

    return result;
}

int main() {
    int strsSize_1 = 6;
    char *strs_1[] = { "eat", "tea", "tan", "ate", "nat", "bat" };
    int returnSize_1 = 45645264;
    int *returnColumnSizes = NULL;
    char*** result_1 = groupAnagrams(strs_1, strsSize_1, &returnSize_1, &returnColumnSizes);
    for (int i = 0; i < returnSize_1; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%s, ", result_1[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```



leetcode 1. 两数之和 https://leetcode-cn.com/problems/two-sum/
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

/* leetcode 1. 两数之和 https://leetcode-cn.com/problems/two-sum/
 * 
 */
typedef struct hashTable {
    int key;
    int val;
    UT_hash_handle hh;
} hashTable;

hashTable* hashtable;

hashTable* find(int ikey) {
    hashTable* tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

void insert(int ikey, int ival) {
    hashTable* it = find(ikey);
    if (it == NULL) {
        hashTable* tmp = (hashTable*)malloc(sizeof(hashTable));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(hashtable, key, tmp);
    } else {
        it->val = ival;
    }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    hashtable = NULL;
    for (int i = 0; i < numsSize; i++) {
        hashTable* it = find(target - nums[i]);
        if (it != NULL) {
            int* ret = (int *)malloc(sizeof(int) * 2);
            ret[0] = it->val, ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        insert(nums[i], i);
    }
    *returnSize = 0;
    return NULL;
}


int main() {
    int nums_1[] = {2,7,11,15};
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

/* leetcode 1. 两数之和 https://leetcode-cn.com/problems/two-sum/
 * 
 */

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



leetcode 771. 宝石与石头. https://leetcode-cn.com/problems/jewels-and-stones/
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

/* 771. 宝石与石头. https://leetcode-cn.com/problems/jewels-and-stones/
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


