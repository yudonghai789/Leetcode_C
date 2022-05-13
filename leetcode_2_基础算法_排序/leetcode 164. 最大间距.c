/******************************************************************************
 * 版权所有 (c)
 * 功能描述   : leetcode 164. 最大间距 https://leetcode-cn.com/problems/maximum-gap/
 * 作    者   :
 * 生成日期   :
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

// ---------------------------开始-------------基数排序-----------------------------------------------
#define MAX_NUM_LEN 100000
// #define SHOWPASS    // 加打印超时了

typedef struct Array {
    int len;
    int array[MAX_NUM_LEN]
} Array;

Array g_sortArray[10];

void print(int *a, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void radixsort(int* nums, int numsSize)
{
    int max = INT_MIN;
    for (int  i = 0; i < numsSize; i++) {
        max = fmax(max, nums[i]);
    }
    
    float doubl = 0.1;
    for (int exp = 1; exp <= 9; exp++) {
        doubl = doubl * 10;
        if (max / (int)doubl == 0) {
            break;
        }

        memset(g_sortArray, 0, sizeof(g_sortArray));

        for (int i = 0; i < numsSize; i++) {
            int val = nums[i] % (int)(doubl * 10);
            int bouttom = val / (int)(doubl);
            g_sortArray[bouttom].array[g_sortArray[bouttom].len++] = nums[i];
        }
        
        int index = 0;
        for (int  i = 0; i < 10; i++) {
             for (int j = 0; j < g_sortArray[i].len; j++) {
                 nums[index++] = g_sortArray[i].array[j];
             }
             
        }
        
        #ifdef SHOWPASS
            printf("\nPASS   : ");
            print(nums, numsSize);
        #endif
    }
}

int maximumGap(int* nums, int numsSize)
{
    if (numsSize < 2) {
        return 0;
    }

    radixsort(nums, numsSize);

    int res = INT_MIN;
    for (int  i = 1; i < numsSize; i++) {
        int temp = nums[i] - nums[i - 1];
        res = fmax(res, temp);
    }
    
    return res;
}
// ---------------------------结束--------------------------------------------------------------------


int main()
{
    int nums_1[] = {494767408,862126209,213511142,768240025,631263193,839199222,990848796,214568815,540853864,760724418,980162605,976743981,168965760,680875496,256709197,970953816,948680062,347254784,732201399,786249847,782805044,40906641,674241381,784330934,175502610,731105392,424650824,549764101,986090032,710542549,249208107,448419816,527708664,158499246,223421723,114552457,466978424,821491411,19614107,115389497,902211438,2644108,744489871,897895073,372311214,551142753,933294894,426217662,217504874,983488406,516890023,426853110,971124103};
    int numsSize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int res_1 = maximumGap(nums_1, numsSize_1);
    assert(res_1 == 3);



    return 0;
}
