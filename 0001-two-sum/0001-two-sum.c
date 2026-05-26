/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>

#define SIZE 20011

typedef struct{
    int key;
    int value;
    int used;
} Hash;

int hashFunc(int key){
    return ((key % SIZE) + SIZE) % SIZE;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    Hash table[SIZE] = {0};

    for(int i=0;i<numsSize;i++){

        int needed = target - nums[i];
        int index = hashFunc(needed);

        // Search
        while(table[index].used){

            if(table[index].key == needed){

                int *result = malloc(2*sizeof(int));

                result[0] = table[index].value;
                result[1] = i;

                *returnSize = 2;

                return result;
            }

            index = (index+1)%SIZE;
        }

        // Insert current number
        index = hashFunc(nums[i]);

        while(table[index].used)
            index = (index+1)%SIZE;

        table[index].key = nums[i];
        table[index].value = i;
        table[index].used = 1;
    }

    *returnSize = 0;
    return NULL;
}