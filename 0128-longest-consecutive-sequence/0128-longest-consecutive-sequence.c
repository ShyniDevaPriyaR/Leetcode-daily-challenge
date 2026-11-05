int compare(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    return (x>y) - (x<y);
}

int longestConsecutive(int* nums, int numsSize) {
    if(numsSize == 0)
    {
        return 0;
    }
    //  for (int i = 0; i < numsSize; i++)
    // {
    //     for (int j = 0; j < numsSize - i - 1; j++)
    //     {
    //         if (nums[j] > nums[j + 1])
    //         {
    //             long long temp = nums[j];
    //             nums[j] = nums[j + 1];
    //             nums[j + 1] = temp;
    //         }
    //     }
    // }
     
     qsort(nums, numsSize, sizeof(int), compare);

    // Step 2: Find the longest consecutive sequence
    long long count = 1;
    long long maxCount = 1;
   

    for (int i = 1; i < numsSize; i++)
    {
        if (nums[i] == nums[i - 1])
        {
            continue;
        }
        else if ((long long)nums[i] == (long long)nums[i - 1] + 1)
        {
            count++;
        }
        else
        {
            count = 1;
        }

        if (count > maxCount)
        {
            maxCount = count;
        }
    }

    return maxCount;
    
}