#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  srand(time(NULL));
  int input;
  int sugar = rand() % 4;

  int currentShowCnt = 0;
  int prevShowCnt = 0;

  for (int i = 0; i < 3; i++)
  {
    int bowl[4] = {0, 0, 0, 0};

    do
    {
      currentShowCnt = rand() % 2 + 2;
    } while (currentShowCnt == prevShowCnt);

    int isInclude = 0;
    printf(" > %d times : ", i + 1);

    for (int j = 0; j < currentShowCnt; j++)
    {
      int randBowl = rand() % 4;

      if (bowl[randBowl] == 0)
      {
        bowl[randBowl] = 1;
        if (randBowl == sugar)
        {
          isInclude = 1;
        }
      }
      else
      {
        j--;
      }
    }

    for (int k = 0; k < 4; k++)
    {
      if (bowl[k] == 1)
      {
        printf("%d ", k + 1);
      }
    }

    printf("\n");

    if (isInclude)
    {
      printf("Taest is Good!\n");
    }
    else
    {
      printf("Taest is Bad!\n");
    }

    printf("Do you continue press any key!\n");
    getchar();

    prevShowCnt = currentShowCnt;
  }

  printf("What's number of sugar? ");
  scanf("%d", &input);

  if (input == sugar + 1)
  {
    printf("Correct!\n");
  }
  else
  {
    printf("Wrong!\n");
  }

  return 0;
}