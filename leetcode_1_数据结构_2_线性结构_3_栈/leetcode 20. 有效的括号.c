/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <uthash.h>
// 如需使用华为安全函数，请加上 #include "securec.h"
#include "diyiti.h"
#include <math.h>
#include <assert.h>

/* leetcode 20. 有效的括号：https://leetcode-cn.com/problems/valid-parentheses/
 */

// ---------------------------解法 ---------------------------------------------------
bool isValid(char * s){
    char *stack = (char *)malloc(sizeof(char) * (10000 + 1));
    memset((void*)stack, 0, sizeof(char) * (10000 + 1));
    int topPointer = 0;
    for (int i = 0; i < strlen(s); i++) {
        switch (s[i]) {
            case '(':
                stack[topPointer] = '(';
                topPointer++;
                break;
            case ')':
                topPointer--;
                if (topPointer < 0) { free(stack); return false; }
                if (stack[topPointer] != '(') { free(stack); return false; }
                break;

            case '[':
                stack[topPointer] = '[';
                topPointer++;
                break;
            case ']':
                topPointer--;
                if (topPointer < 0) { free(stack); return false; }
                if (stack[topPointer] != '[') { free(stack); return false; }
                break;

            case '{':
                stack[topPointer] = '{';
                topPointer++;
                break;
            case '}':
                topPointer--;
                if (topPointer < 0) { free(stack); return false; }
                if (stack[topPointer] != '{') { free(stack); return false; }
                break;
            
            default:
                free(stack);
                return false;
        }
    }

    free(stack);
    return (topPointer == 0) ? true: false;
}
// ---------------------------解法 结束--------------------------------------------------------
int main() {
    char string_1[] = "()";
    int result_1 = isValid(string_1);
    assert(result_1 == true);

    char string_2[] = "()[]{}";
    int result_2 = isValid(string_2);
    assert(result_2 == true);

    char string_3[] = "(]";
    int result_3 = isValid(string_3);
    assert(result_3 == false);

    char string_4[] = "([)]";
    int result_4 = isValid(string_4);
    assert(result_4 == false);

    char string_5[] = "[";
    int result_5 = isValid(string_5);
    assert(result_5 == false);

    char string_6[] = "]";
    int result_6 = isValid(string_6);
    assert(result_6 == false);

    return 0;
}
