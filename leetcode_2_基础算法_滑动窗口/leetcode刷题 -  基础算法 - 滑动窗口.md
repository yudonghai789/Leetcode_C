
int longestSubarray(int* nums, int numsSize){
    if ((nums == NULL) || (numsSize == 0)) { return 0; }

    int resultLen = 0;
    int zeroCount = 0;
    int left  = 0;
    int right = 0;
    while (right < numsSize) {
        if (nums[right] == 0) { zeroCount = zeroCount + 1; }

        while (zeroCount > 1) {
            if (nums[left] == 0) { zeroCount = zeroCount - 1; }
            left++;
        }

        // 满足条件时
        resultLen = fmax(resultLen, right - left);

        right++;
    }

    return resultLen;
}

