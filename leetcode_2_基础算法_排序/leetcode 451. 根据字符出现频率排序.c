/******************************************************************************
* 版权所有 (c) 
* 功能描述   : leetcode 451. 根据字符出现频率排序 https://leetcode-cn.com/problems/sort-characters-by-frequency/
* 作    者   : 
* 生成日期   : 
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>



/* ----------------------------------------------------------------------------------------------------------------------------------------------------- *
 * 解法一 开始
 * ----------------------------------------------------------------------------------------------------------------------------------------------------- */
#define MAX_ASCII_NUM 256
int frequence[MAX_ASCII_NUM];

int GenASCIIIndex(char charter)
{
    return (charter - ' ');
}

int GetFre(char charter)
{
    int index = GenASCIIIndex(charter);
    return frequence[index];
}

void AddFre(char charter)
{
    int index = GenASCIIIndex(charter);
    frequence[index]++;
}

int CompareChar(const void *a, const void* b)
{
    char charA = *(char *)a;
    char charB = *(char *)b;

    int res = GetFre(charB) - GetFre(charA);
    if (res != 0) {
        return res;
    } else {
        return GenASCIIIndex(charB) - GenASCIIIndex(charA);
    }
}

char* frequencySort(char* s){
    int length = strlen(s);

    char* temp = (char*)malloc(sizeof(char) * (length + 1));
    strcpy(temp, s);

    memset(frequence, 0, sizeof(int) * MAX_ASCII_NUM);
    for (int i = 0; i < length; i++)
    {
        AddFre(temp[i]);
    }
    
    qsort(temp, length, sizeof(char), CompareChar);

    return temp;
}


// ---------------------------解法一 结束--------------------------------------------------------
int main() {

    char string_1[] =  "tree";
    char* result_1 = frequencySort(string_1);
    printf("%s", result_1); 
    free(result_1);


    char string_2[] =  "Aabb";
    char* result_2 = frequencySort(string_2);
    printf("%s", result_2); 
    free(result_2);




    return 0;
}