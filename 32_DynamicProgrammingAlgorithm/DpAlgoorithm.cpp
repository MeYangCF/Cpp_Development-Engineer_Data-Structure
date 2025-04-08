/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-03-22 ����1:14
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
    // 509.쳲�������
    int fib(int n) {
        if(n <= 1) {
            return n;
        }
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i <= n; i++){
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

public:
    // 70.��¥��
    int climbStairs(int n) {
        if(n <= 2) {
            return n;
        }
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

public:
    // 746.ʹ����С������¥��
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size() + 1);
        dp[0] = 0;
        dp[1] = 0;
        for(int i = 2; i <= cost.size(); i++){
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
        }
        return dp[cost.size()];
    }

public:
    // 62.��ͬ·��
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector(n, 0));
        for(int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for(int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

public:
    // 63.��ͬ·�� II
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector(n, 0));
        for(int i = 0; i < m && obstacleGrid[i][0] != 1; i++) {
            dp[i][0] = 1;
        }
        for(int j = 0; j < n && obstacleGrid[0][j] != 1; j++) {
            dp[0][j] = 1;
        }
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                if(obstacleGrid[i][j] == 1) {
                    continue;
                }
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

public:
    // 343.�������
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n ; i++) {
            for (int j = 1; j <= i / 2; j++) {
                dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
            }
        }
        return dp[n];
    }

public:
    // 96.��ͬ�Ķ���������
    int numTrees(int n) {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }

public:
    // 416.�ָ�Ⱥ��Ӽ�
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
    // 1049.���һ��ʯͷ������II
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
    // 494.Ŀ���
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

public:
    // 474.һ����
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int> (n + 1, 0)); // Ĭ�ϳ�ʼ��0
        for (string str : strs) { // ������Ʒ
            int oneNum = 0, zeroNum = 0;
            for (char c : str) {
                if (c == '0') zeroNum++;
                else oneNum++;
            }
            for (int i = m; i >= zeroNum; i--) { // �������������ҴӺ���ǰ������
                for (int j = n; j >= oneNum; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
                }
            }
        }
        return dp[m][n];
    }

public:
    // 518.��Ǯ�һ�II
    int change(int amount, vector<int>& coins) {
        int bagSize = amount;
        vector<vector<uint64_t>> dp(coins.size(), vector<uint64_t>(bagSize + 1, 0));
        for (int j = 0; j <= bagSize; j++) {
            if (j % coins[0] == 0) {
                dp[0][j] = 1;
            }
        }
        for (int i = 0; i < coins.size(); i++) {
            dp[i][0] = 1;
        }
        for (int i = 1; i < coins.size(); i++) {
            for (int j = 0; j <= bagSize; j++) {
                if (coins[i] > j) {
                    dp[i][j] = dp[i - 1][j];
                }
                else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]];
                }
            }
        }
        return dp[coins.size() - 1][bagSize];
    }

public:
    // 377.����ܺ͢�
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 0; i <= target; i++) { // ��������
            for (int j = 0; j < nums.size(); j++) { // ������Ʒ
                if (i - nums[j] >= 0 && dp[i] < INT_MAX - dp[i - nums[j]]) {
                    dp[i] += dp[i - nums[j]];
                }
            }
        }
        return dp[target];
    }
};