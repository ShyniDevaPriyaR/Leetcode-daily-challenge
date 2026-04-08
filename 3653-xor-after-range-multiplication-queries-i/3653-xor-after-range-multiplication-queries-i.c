int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    
    int MOD = 1000000007;

    // Process each query
    for(int i = 0; i < queriesSize; i++) {
        
        int l = queries[i][0];
        int r = queries[i][1];
        int k = queries[i][2];
        int v = queries[i][3];

        int idx = l;

        // Apply updates
        while(idx <= r) {
            long long temp = nums[idx];
            temp = (temp * v) % MOD;
            nums[idx] = (int)temp;

            idx += k;
        }
    }

    // Compute XOR
    int result = 0;
    for(int i = 0; i < numsSize; i++) {
        result ^= nums[i];
    }

    return result;
}