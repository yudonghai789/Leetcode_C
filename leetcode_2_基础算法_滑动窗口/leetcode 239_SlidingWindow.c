#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * 算法超时
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {

   (*returnSize) = numsSize - k + 1;
    int *result = (int *)malloc(sizeof(int) * (numsSize - k + 1));
    memset((void *)result, 0, sizeof(int) * (numsSize - k + 1));

    int leftPointer = 0;
    int rightPointer = leftPointer + k - 1;

    for (rightPointer; rightPointer < numsSize; leftPointer++, rightPointer++) {
        int tempMax = nums[leftPointer];
        for (int i = 0; i < k; i++) {
            if (tempMax < nums[leftPointer + i]) {
                tempMax = nums[leftPointer + i];
            }
        }
        result[leftPointer] = tempMax;
    }
    
    return result;
}

int main()
{
	int *result = NULL;
    int resultSize = 0;

    int nums[8] = { 1, 3, -1, -3, 5, 3, 6, 7 };
    int numsSize = 8;
    int k = 3;

    // int nums[2] = { 1, -1 };
    // int numsSize = 2;
    // int k = 1;

	result = maxSlidingWindow(&nums[0], numsSize, k, &resultSize);
    
    for (int i = 0; i < resultSize; i++) {
        if (i == 0) {
            printf("[%d,", result[i]);
        } else if (i == resultSize - 1) {
            printf("%d]", result[i]);
        } else {
            printf("%d,", result[i]);
        }
    }

	free(result);
    result = NULL;
    system("pause");
    return 0;
}
