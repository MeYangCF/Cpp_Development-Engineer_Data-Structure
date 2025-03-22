/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-22 ÏÂÎç1:14
@description:
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 == 1) {
            return false;
        }
        int target = sum / 2;
        vector<vector<int>> dp(nums.size(), vector<int>(10001, 0));
        for (int j = nums[0]; j <= target; j++) {
            dp[0][j] = nums[0];
        }
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= target; j++) {
                if (j < nums[i]) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - nums[i]] + nums[i]);
                }
            }
        }
        if (dp[nums.size() - 1][target] == target) {
            return true;
        }
        return false;
    }

public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        vector<int> dp(1501, 0);
        for (int i = 0; i < stones.size(); i++) {
            for (int j = target; j >= stones[i]; j--) {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - dp[target] - dp[target];
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > sum) {
            return 0;
        }
        if ((target + sum) % 2 == 1) {
            return 0;
        }
        int bigSize = (target + sum) / 2;
        vector<vector<int>> dp(nums.size(), vector<int>(bigSize + 1, 0));
        if (nums[0] <= bigSize) {
            dp[0][nums[0]] = 1;
        }
        dp[0][0] = 1;
        int numZero = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                numZero++;
            }
            dp[i][0] = (int)pow(2.0, numZero);
        }
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j <= bigSize; j++) {
                if (nums[i] > j) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];
                }
            }
        }
        return dp[nums.size() - 1][bigSize];
    }
};