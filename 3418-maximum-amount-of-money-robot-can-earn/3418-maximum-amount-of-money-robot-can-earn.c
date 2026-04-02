#include <stdlib.h>
#include <limits.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int maximumAmount(int** coins, int coinsSize, int* coinsColSize) {
    
     int m = coinsSize;          
    int n = coinsColSize[0];

    // dp[i][j][k]
    int*** dp = (int***)malloc(m * sizeof(int**));
    for(int i = 0; i < m; i++) {
        dp[i] = (int**)malloc(n * sizeof(int*));
        for(int j = 0; j < n; j++) {
            dp[i][j] = (int*)malloc(3 * sizeof(int));
            for(int k = 0; k < 3; k++) {
                dp[i][j][k] = INT_MIN;
            }
        }
    }

    // Start cell (0,0)
    for(int k = 0; k < 3; k++) {
        if(coins[0][0] >= 0) {
            dp[0][0][k] = coins[0][0];
        } else {
            // either take loss OR neutralize
            if(k > 0)
                dp[0][0][k] = 0; // neutralized
            else
                dp[0][0][k] = coins[0][0];
        }
    }

    // Fill DP
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {

            if(i == 0 && j == 0) continue;

            for(int k = 0; k < 3; k++) {

                int best = INT_MIN;

                // from top
                if(i > 0 && dp[i-1][j][k] != INT_MIN) {
                    best = MAX(best, dp[i-1][j][k] + coins[i][j]);
                }

                // from left
                if(j > 0 && dp[i][j-1][k] != INT_MIN) {
                    best = MAX(best, dp[i][j-1][k] + coins[i][j]);
                }

                dp[i][j][k] = best;

                // try neutralizing if negative
                if(coins[i][j] < 0 && k > 0) {

                    int bestNeutral = INT_MIN;

                    if(i > 0 && dp[i-1][j][k-1] != INT_MIN) {
                        bestNeutral = MAX(bestNeutral, dp[i-1][j][k-1]);
                    }

                    if(j > 0 && dp[i][j-1][k-1] != INT_MIN) {
                        bestNeutral = MAX(bestNeutral, dp[i][j-1][k-1]);
                    }

                    dp[i][j][k] = MAX(dp[i][j][k], bestNeutral);
                }
            }
        }
    }

    // answer = max of all k at destination
    int ans = INT_MIN;
    for(int k = 0; k < 3; k++) {
        ans = MAX(ans, dp[m-1][n-1][k]);
    }

    // free memory
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

    return ans;
}