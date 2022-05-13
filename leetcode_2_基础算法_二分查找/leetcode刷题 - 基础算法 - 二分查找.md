

## 简单的二分查找入门
  https://leetcode-cn.com/leetbook/detail/binary-search/
  
 ## 关于二分查找的一些归纳
  https://leetcode-cn.com/problems/search-insert-position/solution/te-bie-hao-yong-de-er-fen-cha-fa-fa-mo-ban-python-/
  按照这个题解归纳的刷题


## 1.  阶段一、二分查找,
leetcode 704:  https://leetcode-cn.com/problems/binary-search/
```
int search(int* nums, int numsSize, int target) {
    int index = -1;

    int high = numsSize - 1;
    int low = 0;

    while (high >= low) {
        int nextMid = (high - low)/2 + low;
        if (target == nums[nextMid]) {
            index = nextMid;
            return index;
        } else if (target > nums[nextMid]) {
            low = nextMid + 1;
        } else {
            high = nextMid - 1;
        }
    }

    return index;
}

int main() {
    int nums_1[] = {-1,0,3,5,9,12};
    int numsSize_1 = sizeof(nums_1)/sizeof(int);
    int result = search(nums_1, numsSize_1, 9);
    assert(result == 4);

    return 0;
}
```




leetcode278. 第一个错误的版本：https://leetcode-cn.com/problems/first-bad-version/
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

/* leetcode 278. 第一个错误的版本：https://leetcode-cn.com/problems/first-bad-version/
 */

// ---------------------------解法 ---------------------------------------------------
# define TGARGTBDVRSION 1

bool isBadVersion(int version)
{
    return (version >= TGARGTBDVRSION) ? true : false;
}

int firstBadVersion(int n)
{
    if (n == 0) { return -1; }
    if (n == 1) { return (isBadVersion(1) == true) ? 1 : -1; }
    // 第一个版本就是坏版本是特殊情况，因为第0个版本一定是坏版本
    if (isBadVersion(1) == true) { return 1; }

    int high = n;
    int low = 1;
    while(low < high) {
        if (high == low + 1) { return ((isBadVersion(low) == false) && (isBadVersion(high) == true))? high : -1; }
        int mid = (high - low) / 2 + low;
        if (isBadVersion(mid) == false) {
            if (isBadVersion(mid + 1) == true) {
                return mid + 1;
            } else {
                low = mid + 1;
            }
        } else {
            high = mid;
        }
    }

    return -1;
}

int main() {
    int result_1 = firstBadVersion(2);
    assert(result_1 == 1);


    return 0;
}
```


leetcode 162. 寻找峰值：https://leetcode-cn.com/problems/find-peak-element/
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

/* leetcode 162. 寻找峰值：https://leetcode-cn.com/problems/find-peak-element/
 */

// ---------------------------解法 ---------------------------------------------------
int findPeakElement(int* nums, int numsSize){
    if (numsSize == 1) {return 0;}
    
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        if (left == right - 1) { return (nums[right] > nums[left])? right : left; } // base 两个值不会相等

        int mid = (right - left) / 2 + left;
        if (nums[mid] < nums[mid - 1]) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return -1;
}

int main() {
    int nums_1[] = {1,2,3,1};
    int numSize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int result_1 = findPeakElement(nums_1, numSize_1);
    assert(result_1 == 2);


    return 0;
}
```
leetcode 33. 搜索旋转排序数组：https://leetcode-cn.com/problems/search-in-rotated-sorted-array/

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

/* leetcode 33. 搜索旋转排序数组：https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
 */

// ---------------------------解法 ---------------------------------------------------
int search(int* nums, int numsSize, int target)
{
    if (numsSize == 0) { return -1; }
    if (numsSize == 1) { return (nums[0] == target)? 0 : -1; }
    
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = (right - left) / 2 + left;
   
        if (nums[mid] == target) {
            return mid;
        } 

        // 二分其实也是递归，到最后有一些base case
        if (right == left) { return -1; }
        if (left == mid) { return (nums[right] == target)? right : -1; }

        if (nums[left] < nums[mid]) {
            // 左边是一个完整的升序数组 
            if ((nums[left] <= target) && (target < nums[mid])) {
                // 在左边的升序数组中
                right = mid - 1;
            } else {
                // 去右边分析
                left = mid + 1;
            }
            continue;
        }

        if (nums[mid] < nums[right]) {
            // 右边是一个完整的升序数组
            if ((nums[mid] < target) && (target <= nums[right])) {
                // 在右边的升序数组中
                left = mid + 1;
            } else {
                // 去左边分析
                right = mid - 1;
            }
            continue;
        }
    }

    return -1;
}


int main() {
    int nums_1[] = { 4,5,6,7,0,1,2 };
    int numssize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int result_1 = search(nums_1, numssize_1, 3);
    assert(result_1 == -1);

    int nums_2[] = { 4,5,6,7,0,1,2 };
    int numssize_2 = sizeof(nums_2) / sizeof(nums_2[0]);
    int result_2 = search(nums_2, numssize_2, 0);
    assert(result_2 == 4);

    int nums_3[] = { 1,3 };
    int numssize_3 = sizeof(nums_3) / sizeof(nums_3[0]);
    int result_3 = search(nums_3, numssize_3, 3);
    assert(result_3 == 1);

    int nums_4[] = { 3,1 };
    int numssize_4 = sizeof(nums_4) / sizeof(nums_4[0]);
    int result_4 = search(nums_4, numssize_4, 0);
    assert(result_4 == -1);

    return 0;
}
```

153. 寻找旋转排序数组中的最小值：https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
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

/* leetcode 153. 寻找旋转排序数组中的最小值：https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
 */

// ---------------------------解法 ---------------------------------------------------
int findMin(int* nums, int numsSize)
{
    if (numsSize == 1) { return nums[0]; } 

    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        if (left == right - 1) { return (nums[left] > nums[right]) ? nums[right]: nums[left]; }  // base case 只有两个数的时候

        int mid = (right - left) / 2 + left;
        if (nums[mid] > nums[right]) {
            // 说明左侧是一个完整的升序数组且右侧存在最小值
            left = mid;
        } else if (nums[mid] < nums[right]) {
            // 说明右侧是一个完整的升序数组且左侧包括mid存在最小值
            right = mid;
        }
    }
    
    return -1;
}
```




## 阶段二、二分答案

剑指 Offer II 072. 求平方根：https://leetcode-cn.com/problems/jJ0w9p/
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include "diyiti.h"
#include <math.h>
#include <assert.h>

/* 剑指 Offer II 072. 求平方根：https://leetcode-cn.com/problems/jJ0w9p/
 */

// ---------------------------解法 ---------------------------------------------------
int mySqrt(int x){
    
    long long high = x / 2;
    long long low = 0;
    while (high >= low) {
        long long mid = (high - low) / 2 + low;
        long long midpow = mid * mid;
        long long midredu = (mid -1) * (mid - 1);
        long long midplus = (mid + 1) * (mid + 1);
        if (midpow == x) {
            return mid;
        } else if (midplus == x) {
            return mid + 1;
        } else if (midredu == x) {
            return mid - 1;
        } else if ((midpow < x) && (midplus > x)) {
            return mid;
        } else if ((midpow > x) && (midredu < x)) {
            return mid - 1;
        } else if (midredu > x) {
            high = mid - 1;
        } else if (midplus < x) {
            low = mid + 1;
        }
    }

    return 0;
}
// ---------------------------解法 结束--------------------------------------------------------
int main() {
    int nums_1 = 2147395599;
    int result = mySqrt(nums_1);
    assert(result == 2);

    return 0;
}
```

374. 猜数字大小： https://leetcode-cn.com/problems/guess-number-higher-or-lower/
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
#include "disanti.h"
#include <math.h>
#include <assert.h>


/* 374. 猜数字大小. https://leetcode-cn.com/problems/guess-number-higher-or-lower/
 */

int guess(int num) {
    int pick = 6;

    if (num == pick) {
        return 0;
    } else if (num > pick) {
        return -1;
    } else if (num < pick) {
        return 1;
    }
    return 0xff;
}

/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 */
int guessNumber(int n)
{
    if (n == 1) {
        return 1;
    }

    int high = n;
    int low = 1;
    while (n > 1) {
        int mid = (high - low) / 2 + low;
        switch (guess(mid)) {
            case 0:
                return mid;
                break;
            case -1:
                high = mid - 1;
                break;
            case 1:
                low = mid + 1;
                break;
            default:
                return -1;
        }
    }

    return 1;
}



int main(int argc, const char *argv[])
{
    int res = guessNumber(10);
    assert(res == 6);
    return 0;
}
```



leetcode 287. 寻找重复数 https://leetcode-cn.com/problems/find-the-duplicate-number/
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

/* leetcode 287. 寻找重复数 https://leetcode-cn.com/problems/find-the-duplicate-number/
 */
// ---------------------------解法 暴力 超时---------------------------------------------------
// bool IsDuplicated(int* nums, int numsSize, int traget)
// {
//     int count = 0;
//     for (int n = 0; n <= numsSize - 1; n++) {
//         if (nums[n] == traget) {
//             count = count + 1;
//             if (count >= 2) { return true; } 
//         }
//     }
//     return false;
// }


// int findDuplicate(int* nums, int numsSize)
// {
//     if (numsSize == 1) { return -1; }
//     if (numsSize == 2) { return (nums[0] == nums[1]) ? nums[0] : -1; }

//     for (int i = 1; i <= numsSize - 1; i ++) {
//         if (IsDuplicated(nums, numsSize, i) == true) {
//             return i;
//         } 
//     }

//     return -1;
// }
// ---------------------------解法 暴力 ---------------------------------------------------
// ---------------------------解法 二分---------------------------------------------------
int CountSub(int* nums, int numsSize, int traget)
{
    int count = 0;
    for (int n = 0; n <= numsSize - 1; n++) {
        if (nums[n] <= traget) {
            count = count + 1;
        }
    }
    return count;
}

int findDuplicate(int* nums, int numsSize)
{
    if (numsSize == 1) { return -1; }
    if (numsSize == 2) { return (nums[0] == nums[1]) ? nums[0] : -1; }

    int low = 1;
    int high = numsSize - 1;
    while (low <= high) {
        if (low == high) { return low; }  // base case 题目保证
        
        int mid = (high - low) / 2 + low;
        if (CountSub(nums, numsSize, mid) > mid) {
            high = mid;
        } else {
            // mid也不是答案，mid要 + 1，不然收敛不了
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int nums_1[] = {1,3,4,2,2};
    int numSize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int result_1 = findDuplicate(nums_1, numSize_1);
    assert(result_1 == 2);


    return 0;
}
```




leetcode 875  https://leetcode-cn.com/problems/koko-eating-bananas/comments/
```

```

https://leetcode-cn.com/problems/split-array-largest-sum/
https://leetcode-cn.com/problems/magnetic-force-between-two-balls/

https://leetcode-cn.com/problems/xiao-zhang-shua-ti-ji-hua/


## 阶段三、最大值极小化 
###### 数组连续切割问题
leetcode 410. 分割数组的最大值 https://leetcode-cn.com/problems/split-array-largest-sum/
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

/* leetcode 410. 分割数组的最大值 https://leetcode-cn.com/problems/split-array-largest-sum/
 */
// ---------------------------解法 暴力 超时---------------------------------------------------




// ---------------------------解法 暴力 ---------------------------------------------------
// ---------------------------解法 二分---------------------------------------------------
int FindMaxInArray(int* nums, int numsSize)
{
    if ((nums == NULL) || (numsSize == 0)) { return -1; }

    int maxTmp = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > maxTmp) {
            maxTmp = nums[i];
        }
    }

    return maxTmp;
}

int CalSumOfArray(int* nums, int numsSize)
{
    if ((nums == NULL) || (numsSize == 0)) { return -1; }

    int maxSum = 0;
    for (int i = 0; i < numsSize; i++) {
        maxSum = maxSum + nums[i];
    }

    return maxSum;
}

int CalSplitCount(int* nums, int numsSize, int splitSum)
{
    if ((nums == NULL) || (numsSize == 0)) { return -1; }

    int spliteCount = 1;
    int spliteTempSum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (spliteTempSum  + nums[i] > splitSum) {
            spliteCount = spliteCount + 1;
            spliteTempSum = 0;
        } 
        spliteTempSum = spliteTempSum + nums[i];
    }

    return spliteCount;
}



int splitArray(int* nums, int numsSize, int m)
{
    if ((nums == NULL) || (numsSize == 0)) { return -1; }

    if (numsSize == 1) { return nums[0];}

    int low = FindMaxInArray(nums, numsSize);
    int high = CalSumOfArray(nums, numsSize);

    while (low <= high ) {
        if (low == high) { return low; }

        int mid = (high - low) / 2 + low;
        if (CalSplitCount(nums, numsSize, mid) <= m) {
            // 满足条件，可以减小，但是mid值可能是解
            high = mid;
        } else {
            // 不满足条件，需要增加， mid值不满足条件
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int nums_1[] = { 7,2,5,10,8 };
    int numSize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int result_1 = splitArray(nums_1, numSize_1, 2);
    assert(result_1 == 2);


    return 0;
}
```


leetcode 875. 爱吃香蕉的珂珂 https://leetcode-cn.com/problems/koko-eating-bananas/
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

/* leetcode 875. 爱吃香蕉的珂珂 https://leetcode-cn.com/problems/koko-eating-bananas/
 */
// ---------------------------解法 二分---------------------------------------------------
long SumOfArray(int* piles, int pilesSize)
{
    if ((piles == NULL) && (pilesSize == 1)) { return -1; }
    
    long maxItmeVal = 0;
    for (long i = 0; i < pilesSize; i++) {
        maxItmeVal = maxItmeVal + piles[i];
    }

    return maxItmeVal;
}

int CalHoursEatAllInlimatdSpeed(int* piles, int pilesSize, int speedPerHour)
{
    long hourCount = 0;
    for (long i = 0; i < pilesSize; i++) {
        hourCount = hourCount + ((piles[i] % speedPerHour == 0) ? (piles[i] / speedPerHour) : (piles[i] / speedPerHour + 1));
    }

    return hourCount;
}

int minEatingSpeed(int* piles, int pilesSize, int h){
    if ((piles == NULL) && (pilesSize == 1)) { return -1; }

    long low = 1;
    long high = SumOfArray(piles, pilesSize);

    while (low <= high) {
        if (low == high) { return low; }

        long mid = (high - low) / 2 + low;
        if (CalHoursEatAllInlimatdSpeed(piles, pilesSize, mid) <= h) {
            // 满足条件，可以减少， mid是可能解
            high = mid;
        } else {
            // 不满足条件，需要增加， mid不是解
            low = mid + 1;
        }
    }

    return -1;
}
```


















###### 带条件的数组连续切割问题
LCP 12. 小张刷题计划 https://leetcode-cn.com/problems/xiao-zhang-shua-ti-ji-hua/
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

/* LCP 12. 小张刷题计划 https://leetcode-cn.com/problems/xiao-zhang-shua-ti-ji-hua/
 */
// ---------------------------解法 二分---------------------------------------------------

int SumOfArray(int* time, int timeSize)
{
    if ((time == NULL) || (timeSize == 0)) { return -1; } 
    
    int sumTemp = 0;
    for (int i = 0; i < timeSize; i++) {
        sumTemp = sumTemp + time[i];
    }

    return sumTemp;
}

int CalMinDayInlimated(int* time, int timeSize, int timeOneDay) {
    int darsCount = 1;
    int oneDaySumTemp = 0;
    int oneDayMixItem = 0;
    for (int i = 0; i < timeSize; i++) {
        if (oneDayMixItem < time[i]) { oneDayMixItem = time[i]; }

        if (oneDaySumTemp + time[i] - oneDayMixItem > timeOneDay) {
            darsCount = darsCount + 1;
            oneDaySumTemp = 0;
            oneDayMixItem = time[i];
        }
        oneDaySumTemp = oneDaySumTemp + time[i];
    }

    return darsCount;
}

int minTime(int* time, int timeSize, int m)
{
    if ((time == NULL) || (timeSize == 0)) { return -1; } 
    // if (timeSize == 1) { return -1; }

    int low = 0;  // 可能一天一道题都不用做
    int high = SumOfArray(time, timeSize);
    while (low <= high) {
        if (low == high) { return low; }

        int mid = (high - low) / 2 + low;
        if (CalMinDayInlimated(time, timeSize, mid) <= m) {
            // 满足条件，可以减少，mid也是可能解
            high = mid;
        } else {
            // 不满足条件，需要增加，mid不是解
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int nums_1[] = { 1,2,3,3 };
    int numSize_1 = sizeof(nums_1) / sizeof(nums_1[0]);
    int result_1 = minTime(nums_1, numSize_1, 2);
    assert(result_1 == 3);

    return 0;
}
```


https://incipe-win.github.io/2020/10/02/leetcode/2020/lcp-12.xiao-zhang-shua-ti-ji-hua/




## 关于二分查找的一些归纳
  https://leetcode-cn.com/problems/search-insert-position/solution/te-bie-hao-yong-de-er-fen-cha-fa-fa-mo-ban-python-/
