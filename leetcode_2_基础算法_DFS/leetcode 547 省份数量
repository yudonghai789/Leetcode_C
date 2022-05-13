#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printGrid(int **M, int MSize) {
  	for (int i = 0; i < MSize; i++) {
    	for (int j = 0; j < MSize; j++) {
     	 	printf("%-5d", M[i][j]);
   		}
    	printf("\n");
 	}
  	printf("------------------------\n");
}

void dfs(int **M, int i, int size, int *rearchFlag) {
	if (i < 0 || i > size - 1 || rearchFlag[i] == 1) {
		return;
	}

	rearchFlag[i] = 1;

	for (int j = 0; j < size; j++) {
		if ((M[i][j] == 1) && (rearchFlag[j] == 0)) {
			dfs(M, j, size, rearchFlag);
		}
	}
}

int findCircleNum(int **M, int MSize, int *MColSize) {
	int result = 0;

	// 这个题目的数组是对称的，只需要对遍历一半
	int *rearchFlag = (int *)malloc(sizeof(int) * MSize);
	memset((void *)rearchFlag, 0, sizeof(int) * MSize);

	for (int i = 0; i < MSize; i++) {
		if (rearchFlag[i] == 0) {
			dfs(M, i, MSize, rearchFlag);
			result++;
			printGrid(M, MSize);
		}
	}

	return result;
}

int main() {
	int result = 0;

	// 这道题二维数组是对称的
	// int gradCharData[3][3] = {
	// 	{1, 1, 0},
	// 	{1, 1, 0},
	// 	{0, 0, 1},
	// };
	// int row = 3;
	// int cloum = 3;

	// int gradCharData[3][3] = {
	// 	{1, 1, 0},
	// 	{1, 1, 1},
	// 	{0, 1, 1},
	// };
	// int row = 3;
	// int cloum = 3;

	int gradCharData[4][4] = {
		{1, 0, 0, 1},
		{0, 1, 1, 0},
		{0, 1, 1, 1},
		{1, 0, 1, 1}
	};
	int row = 4;
	int cloum = 4;

	int *gradRowPointer[row];
	for (int i = 0; i < row; i++) {
		gradRowPointer[i] = &gradCharData[i][0];
	}

	result = findCircleNum(gradRowPointer, row, &cloum);

	printf("%d", result);

	system("pause");
	return 0;
}
