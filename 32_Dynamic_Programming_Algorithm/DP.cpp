/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-02-17 上午9:13
@description:
*/


# include <iostream>
# include <algorithm>
#include <string>
using namespace std;

//1.硬币选择问题
/*
const int n = 100;
int dp[n + 1] = {0};
int cnt = 0;

//递归解决问题
int func1(int n) {
  if (dp[n] > 0) {
    cnt++;
    return dp[n];
  }
  if (n == 1 || n == 3 || n == 5) {
    dp[n] = 1;
    return 1;
  }
  else if (n == 2 || n == 4) {
    dp[n] = 2;
    return 2;
  }
  else {
    int n1 = func1(n - 1) + 1;
    int n2 = func1(n - 3) + 1;
    int n3 = func1(n - 5) + 1;
    dp[n] = std::min({ n1, n2, n3});
    return dp[n];
  }
}

int main() {
  // int num = func1(n);
  // cout << "num:" << num << endl;
  // cout << "cnt:" << cnt << endl;

  //非递归解决问题
  int v[] = {1, 3, 5};
  int length = sizeof(v) / sizeof(v[0]);
  int c = 18;
  int *dp = new int[c + 1]();
  for (int i = 1; i <= c; ++i) {
    dp[i] = i;
    for (int j = 0; j < length; ++j) {
      if (i >= v[j] && (1 + dp[i - v[j]]) < dp[i]) {
        dp[i] = 1 + dp[i - v[j]];
      }
    }
  }
  cout << dp[c] << endl;
  delete[] dp;

  return 0;
}
*/

//2.斐波那契数列

/*
//递归解决问题
int fabnacci(int n, int dp[]) {
  if (dp[n] > 0) {
    return dp[n];
  }
  if (n == 1 || n == 2) {
    dp[n] = 1;
    return 1;
  }
  else {
    dp[n] = fabnacci(n -1, dp) + fabnacci(n - 2, dp);
    return dp[n];
  }
}

int main() {
  // int n = 10;
  // int *dp = new int[n + 1]();
  // int val = fabnacci(n, dp);
  // cout << val << endl;
  // delete [] dp;

  //非递归解决问题
  const int n = 10;
  int dp[n + 1] = {0};
  dp[1] = dp[2] = 1;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 2] + dp[i - 1];
  }
  cout << dp[n] << endl;
  return 0;
}
*/

// 3.最大子段和问题
/*
int main() {
  int ar[] = {-2, 11, -4, 13, -5, -2};
  const int n = sizeof(ar) / sizeof(ar[0]);
  int dp[n] = {0};
  dp[0] = ar[0] < 0 ? 0 : ar[0];
  int maxval = dp[0];

  for (int i = 1; i < n; ++i) {
    dp[i] = ar[i] + dp[i - 1];
    if (dp[i] < 0) {
      dp[i] = 0;
    }

    if (dp[i] > maxval) {
      maxval = dp[i];
    }
  }

  cout << maxval << endl;
  return 0;
}
*/

//4.最长非降子序列LIS问题
/*
int main() {
  int ar[] = {5, 3, 4, 1, 8, 6, 7, 10};
  const int n = sizeof(ar) / sizeof(ar[0]);
  int dp[] = {0};
  int maxval = 0;

  for (int i = 0; i < n; ++i) {
    dp[i] = 1;
    for (int j = 0; j < i; ++j) {
      if (ar[j] <= ar[i] && 1 + dp[j] > dp[i]) {
        dp[i] = 1 + dp[j];
      }
    }

    if (dp[i] > maxval) {
      maxval = dp[i];
    }
  }

  cout << maxval << endl;
  return 0;
}
*/

//5.最长公共子序列问题LCS

static int cnt = 0;
string str1 = "helloworld";
string str2 = "hlweord";
int **dp = nullptr;
int **path = nullptr;

//递归实现
int LCS01(string X, int n, string Y, int m) {
  if (n < 0 || m < 0) {
    return 0;
  }

  if (dp[n][m] >= 0) {
    return dp[n][m];
  }

  cnt++;

  if (X[n] == Y[m]) {
    dp[n][m] = LCS01(X, n - 1, Y, m - 1) + 1;
    path[n][m] = 1;
    return dp[n][m];
  }
  else {
    int len1 = LCS01(X, n, Y, m - 1);
    int len2 = LCS01(X, n - 1, Y, m);
    if (len1 >= len2) {
      dp[n][m] = len1;
      path[n][m] = 2;
    }
    else {
      dp[n][m] = len2;
      path[n][m] = 3;
    }
    return dp[n][m];
  }
}

//非递归实现
int LCS(string X, int i, string Y, int j) {
  for (int n = 1; n <= i+1; ++n) {
    for (int m = 1; m <= j+1; ++m) {
      if (X[n-1] == Y[m-1]) {
        dp[n][m] = 1 + dp[n - 1][m - 1];  // n==0 m ==0
        path[n][m] = 1;
      }
      else {
        int len1 = dp[n-1][m]; // 上面来
        int len2 = dp[n][m-1]; // 左边来
        if (len1 >= len2) {
          dp[n][m] = len1;
          path[n][m] = 3;
        }
        else {
          dp[n][m] = len2;
          path[n][m] = 2;
        }
      }
    }
  }
  return dp[i+1][j+1];
}

void backStrace(string str1, int n, int m) {
  if (n <= 0 || m <= 0) {
    return;
  }

  if (path[n][m] == 1) {  // 对应位置的元素是相等的
    backStrace(str1, n - 1, m - 1); // 向对角线递归
    cout << str1[n-1];
  }
  else {
    if (path[n][m] == 2) {
      backStrace(str1, n, m - 1);  // 向左递归
    }
    else {  // path[n][m] = 3
      backStrace(str1, n - 1, m); // 向上递归
    }
  }
}

int main() {
  int n = str1.size();
  int m = str2.size();
  dp = new int*[n+1];
  for (int i = 0; i < n+1; ++i) {
    dp[i] = new int[m+1];
    for (int j = 0; j < m+1; ++j) {
      dp[i][j] = 0;
    }
  }
  path = new int*[n+1];
  for (int i = 0; i < n+1; ++i) {
    path[i] = new int[m+1]();
  }

  int size = LCS(str1, n-1, str2, m-1);
  cout << "LCS length:" << size << endl;
  cout << "cnt:" << cnt << endl;

  backStrace(str1, n, m);
  return 0;
}
