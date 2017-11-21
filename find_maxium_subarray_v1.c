
#include "stdio.h"
#include "limits.h"

typedef struct
{
    int leftMax;
    int rightMax;
    int subarraySum;

} MaxSubArray;

MaxSubArray find_maxium_crossing_subarray(int *pArray, int low, int high)
{
    int sum, left_sum = INT_MIN, right_sum = INT_MIN;
    int mid = (low + high) / 2;
    MaxSubArray maxsubarray;

    // low...mid
    sum = 0;
    for (int i = mid; i >= low; i--)
    {
        sum += *(pArray + i);

        if (sum > left_sum)
        {
            left_sum = sum;
            maxsubarray.leftMax = i;
        }
    }

    // mid + 1...high
    sum = 0;
    for (int i = mid + 1; i <= high; i++)
    {
        sum += *(pArray + i);

        if (sum > right_sum)
        {
            right_sum = sum;
            maxsubarray.rightMax = i;
        }
    }

    maxsubarray.subarraySum = left_sum + right_sum;

    return maxsubarray;
}

MaxSubArray find_maxium_subarray(int *pArray, int low, int high)
{
    if (low == high)
    {
        MaxSubArray maxsubarray;

        maxsubarray.leftMax = low;
        maxsubarray.rightMax = high;
        maxsubarray.subarraySum = *(pArray + low);

        return maxsubarray;
    }
    else
    {
        int mid = (low + high) / 2;

        MaxSubArray left_maxsubarray = find_maxium_subarray(pArray, low, mid);   
        MaxSubArray right_maxsubarray = find_maxium_subarray(pArray, mid + 1, high);
        MaxSubArray cross_maxsubarray = find_maxium_crossing_subarray(pArray, low, high);

        if (left_maxsubarray.subarraySum >= right_maxsubarray.subarraySum && left_maxsubarray.subarraySum >= cross_maxsubarray.subarraySum)
        {
            return left_maxsubarray;
        }
        else if (right_maxsubarray.subarraySum >= left_maxsubarray.subarraySum && right_maxsubarray.subarraySum >= cross_maxsubarray.subarraySum)
        {
            return right_maxsubarray;
        }   
        else
        {
            return cross_maxsubarray;
        }
    }
}


int main(int argc, char *argv[])
{
    int Array[] = {12, -1, 4, -2, 0, -3, -2};

    MaxSubArray maxsubarray = find_maxium_subarray(Array, 0, sizeof(Array) / sizeof(int) - 1);
    printf("%d, %d, %d...\r\n", maxsubarray.leftMax, maxsubarray.rightMax, maxsubarray.subarraySum);

    return 0;
}
