#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * 暴力算法，累加计算
 * Note: The returned array must be malloced, assume caller calls free().
 * 算法超时
 */
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize) {
    *returnSize = n;
    int *resultArray = (int*)malloc(sizeof(int) * (*returnSize));
    memset((void*)resultArray, 0 ,sizeof(int) * (*returnSize));
    for (int i = 0; i < bookingsSize; i++) {
        for (int j = bookings[i][0]; j <= bookings[i][1]; j++) {
            resultArray[j - 1] += bookings[i][2];
        }
    }

    return resultArray;
}

int main()
{
	int *resultArray = NULL;
	int returnSize = 0;


	int cloum = 3; //每条记录都是三个整数
	int bookingsGrad[3][3] = {
		{1,2,10},
		{2,3,20},
		{2,5,25},
	};
    int n = 5;
	int row = 3;

	int *bookingsRowPointer[row];
	for (int i = 0; i < row; i++) {
		bookingsRowPointer[i] = &bookingsGrad[i][0];
	}

	resultArray = corpFlightBookings(bookingsRowPointer, row, &cloum ,n, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        if (i == 0) {
            printf("[%d,", resultArray[i]);
        } else if (i == returnSize - 1) {
            printf("%d]", resultArray[i]);
        } else {
            printf("%d,", resultArray[i]);
        }
    }

    system("pause");
    free(resultArray);
    resultArray = NULL;
    return 0;
}