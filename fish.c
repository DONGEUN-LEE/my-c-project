#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int level;
int arrayFish[6];

void initData();
void printFishes();
void decreseWater(long prevElapsedTime);
int checkFishAlive();

int main(void)
{
  srand(time(NULL));
  long startTime = 0;
  long totalElapsedTime = 0;
  long prevElapsedTime = 0;

  int num;

  initData();

  startTime = clock();

  while (1)
  {
    printFishes();
    printf("what's number of fish? ");
    scanf("%d", &num);

    if (num < 1 || num > 6)
    {
      printf("Wrong Number!\n");
      continue;
    }

    totalElapsedTime = (clock() - startTime) / 1000;
    printf("Total Elapsed Time : %ld sec.\n", totalElapsedTime);

    prevElapsedTime = totalElapsedTime - prevElapsedTime;
    printf("Prev Elapsed Time : %ld sec.\n", prevElapsedTime);

    decreseWater(prevElapsedTime);

    if (arrayFish[num - 1] <= 0)
    {
      printf("%d Fish is dead!\n", num);
    }
    else if (arrayFish[num - 1] + 1 < 100)
    {
      printf("%d Fishbowl increse water!\n", num);
      arrayFish[num - 1] += 1;
    }

    if (totalElapsedTime / 20 > level - 1)
    {
      level++;
      printf("Level Up!\n%d => %d\n", level - 1, level);

      if (level >= 5)
      {
        printf("You Win!\n");
        exit(0);
      }
    }

    if (checkFishAlive() == 0)
    {
      printf("You Lose!\n");
      exit(0);
    }
    prevElapsedTime = totalElapsedTime;
  }

  return 0;
}

void initData()
{
  level = 1;
  for (int i = 0; i < 6; i++)
  {
    arrayFish[i] = 100;
  }
}

void printFishes()
{
  for (int i = 0; i < 6; i++)
  {
    printf("%d: %d\n", i + 1, arrayFish[i]);
  }
  printf("\n");
}

void decreseWater(long prevElapsedTime)
{
  for (int i = 0; i < 6; i++)
  {
    arrayFish[i] -= (level * 3 * (int)prevElapsedTime);
    if (arrayFish[i] < 0)
    {
      arrayFish[i] = 0;
    }
  }
}

int checkFishAlive()
{
  for (int i = 0; i < 6; i++)
  {
    if (arrayFish[i] > 0)
    {
      return 1;
    }
  }
  return 0;
}