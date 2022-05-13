#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//可以看到滑窗过程
#define CHANGEFALG 5

int longestOnes(int* A, int ASize, int K){
    int longestOne = 0;
    int temp = 0;

    int kCount = 0;
    int lowPointer = 0;
    int highPointer = 0;
    while (highPointer < ASize) {
        if (A[highPointer] == 0) {
            A[highPointer] = CHANGEFALG;
            kCount++;
        }
        highPointer++;

        while (kCount > K) {
            if ((A[lowPointer] == 0) || (A[lowPointer] == CHANGEFALG)) {
                A[lowPointer] = 0;
                kCount--;
            }
            
            lowPointer++;
        }
        
        temp = highPointer - lowPointer;
        
        if (temp > longestOne) {
            longestOne = temp;
        }

        for (int i = 0; i < ASize; i++) {
            printf("%d-[%d] ", i, A[i]);
        }
        printf("-- %d  ~  %d \n" ,lowPointer, highPointer);
        
    }

    return longestOne;
}

int main()
{
	int result = 0;

    int A[19] = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    int ASize = 19;
    int K = 3;

    // int A[7] = {0,0,1,1,1,0,0};
    // int ASize = 7;
    // int K = 0;

	result = longestOnes(A, ASize, K);
	printf("%d", result);

    system("pause");
    return 0;
}
