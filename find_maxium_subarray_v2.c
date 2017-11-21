
#include "stdio.h"

typedef struct
{
    int leftMax;
    int rightMax;
    int subarraySum;

} MaxSubArray;

MaxSubArray find_maxium_subarray(int *pArray, int low, int high)
{
    if (low == high)
    {
        MaxSubArray maxsubarray;

        maxsubarray.leftMax = low;
        maxsubarray.rightMax = high;
        maxsubarray.subarraySum =  *(pArray + high);

        return maxsubarray;
    }
    {
        high--;

        MaxSubArray left_maxsubarray = find_maxium_subarray(pArray, low, high);

        int crossing_sum = 0;
        for ( int i = high + 1; i > left_maxsubarray.rightMax; i--)
        {
            crossing_sum += *(pArray + i);
        }
        crossing_sum += left_maxsubarray.subarraySum;

        if (left_maxsubarray.subarraySum >= crossing_sum && left_maxsubarray.subarraySum >= *(pArray + high + 1))
        {
            return left_maxsubarray;
        }
        else if (*(pArray + high + 1) >= crossing_sum && *(pArray + high + 1) >= left_maxsubarray.subarraySum)
        {
            MaxSubArray right_maxsubarray = {high + 1, high + 1, *(pArray + high + 1)};

            return right_maxsubarray;
        }
        else
        {
            MaxSubArray crossing_maxsubarray = {left_maxsubarray.leftMax, high + 1, crossing_sum};

            return crossing_maxsubarray;
        }
    }
}

int main(int argc, char *argv[])
{
    int Array[] = {-12, -1, 12, 2, -12, 15, -2};

    MaxSubArray maxsubarray = find_maxium_subarray(Array, 0, sizeof(Array) / sizeof(int) - 1);
    printf("%d, %d, %d...\r\n", maxsubarray.leftMax, maxsubarray.rightMax, maxsubarray.subarraySum);
    
    return 0;
}
