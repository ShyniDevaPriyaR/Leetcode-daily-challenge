int missingNumber(int* nums, int numsSize) {
    int excepted = numsSize*(numsSize + 1)/2;
    int actualSum = 0;

    for ( int i=0; i<numsSize; i++)
    {
          actualSum = actualSum + nums[i];
    }
    int missingNum = excepted - actualSum;

    return missingNum;
    
}