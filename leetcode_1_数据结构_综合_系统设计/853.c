#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Car {
    int position;
    int speed;
    int index;
    float time;
} Car;

/* 根据起始位置进行排序 */
int cmp(const void *a, const void *b) {
    return ((Car*)b)->position - ((Car*)a)->position;
}

/**
 * 位置排序后看是否能追上
 */
int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    // 如参检查
    if (positionSize <= 1) {
        return positionSize;
    }

    
    int carFleetNum = 0;
    Car *carArray = (Car *)malloc(sizeof(Car) * positionSize);
    memset((void *)carArray, 0 , sizeof(Car) * positionSize);

    // 初始化车队
    for (int i = 0; i < positionSize; i++) {
        carArray[i].position = position[i];
        carArray[i].speed = speed[i];
        carArray[i].time = (target - position[i]) / speed[i];
    };

    // 根据位置对车队排序, 也可以不排序，将index表示为位置的序号
    qsort(carArray, positionSize, sizeof(Car), cmp);

    carFleetNum = 1;
    for (int i = 1; i < positionSize; i++) {
        if (carArray[i].time <= carArray[i - 1].time) {
            carArray[i].time = carArray[i - 1].time;
            continue;
        } else {
            carFleetNum++; 
        }
    };

    return carFleetNum;
}

// *(Car(*)[5])carArray

int main()
{
	int result = 0;

    // int target = 12;
    // int position[] = { 10,8,0,5,3 };
    // int positionSize = sizeof(position) / sizeof(int);
    // int speed[] = { 2,4,1,1,3 };
    // int speedSize = sizeof(speed) / sizeof(int);

    int target = 10;
    int position[] = { 6,8 };
    int positionSize = sizeof(position) / sizeof(int);
    int speed[] = { 3, 2 };
    int speedSize = sizeof(speed) / sizeof(int);

	result = carFleet(target, position, positionSize, speed, speedSize);
	printf("%d", result);

    system("pause");
    return 0;
}
