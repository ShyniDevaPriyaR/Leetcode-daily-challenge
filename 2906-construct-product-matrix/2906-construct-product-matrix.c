#include <stdlib.h>

#define MOD 12345
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int m = gridColSize[0];
    int total = n * m;

    // Step 1: Flatten the matrix
    long long *arr = (long long*)malloc(sizeof(long long) * total);
    int k = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            arr[k++] = grid[i][j] % MOD;
        }
    }

    // Step 2: Prefix product
    long long *prefix = (long long*)malloc(sizeof(long long) * total);
    prefix[0] = 1;
    for(int i = 1; i < total; i++) {
        prefix[i] = (prefix[i-1] * arr[i-1]) % MOD;
    }

    // Step 3: Suffix product
    long long *suffix = (long long*)malloc(sizeof(long long) * total);
    suffix[total-1] = 1;
    for(int i = total-2; i >= 0; i--) {
        suffix[i] = (suffix[i+1] * arr[i+1]) % MOD;
    }

    // Step 4: Build result matrix
    int** result = (int**)malloc(sizeof(int*) * n);
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);

    k = 0;
    for(int i = 0; i < n; i++) {
        result[i] = (int*)malloc(sizeof(int) * m);
        (*returnColumnSizes)[i] = m;

        for(int j = 0; j < m; j++) {
            long long val = (prefix[k] * suffix[k]) % MOD;
            result[i][j] = (int)val;
            k++;
        }
    }

    *returnSize = n;

    // Free temp arrays
    free(arr);
    free(prefix);
    free(suffix);

    return result;
    
}