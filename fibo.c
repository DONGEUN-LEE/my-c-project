#include <stdio.h>
#include <string.h>
#include <time.h>

#define DP_SIZE 50

int dp[DP_SIZE];

int fibo(int n)
{
  if (n == 0)
    return 0;

  if (n == 1)
    return 1;

  return fibo(n - 1) + fibo(n - 2);
}

int fibo_dp(int n)
{
  if (n == 0)
    return 0;

  if (n == 1)
    return 1;

  if (dp[n] != -1)
    return dp[n];

  return dp[n] = (fibo_dp(n - 1) + fibo_dp(n - 2));
}

int main(void)
{
  clock_t start, finish;

  start = clock();

  printf("Result : %d\n", fibo(45));

  finish = clock();

  printf("Elipsed Time => %f sec.\n", (double)(finish - start) / CLOCKS_PER_SEC);

  start = clock();

  memset(dp, -1, sizeof(dp));
  printf("Result : %d\n", fibo_dp(45));

  finish = clock();

  printf("Elipsed Time => %f sec.\n", (double)(finish - start) / CLOCKS_PER_SEC);

  return 0;
}