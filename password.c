#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mul(int a, int b)
{
  return a * b;
}

int getRandomNumber(int level)
{
  return rand() % (level * 7) + 1;
}

void showQuestion(int level, int num1, int num2)
{
  printf("\n\n\n######## password %d times ########\n", level);
  printf("\n\t%d * %d ? \n\n", num1, num2);
  printf("##################################\n");
  printf("\nInput Password (EXIT : -1) >> ");
}

int main(void)
{
  srand(time(NULL));
  int cnt = 0;
  int num1, num2;
  int input;
  for (int i = 1; i <= 5; i++)
  {
    num1 = getRandomNumber(i);
    num2 = getRandomNumber(i);

    showQuestion(i, num1, num2);

    scanf("%d", &input);

    if (input == -1)
    {
      break;
    }
    else if (input == num1 * num2)
    {
      printf("Success!\n");
      cnt++;
      continue;
    }
    else
    {
      printf("Fail!\n");
      break;
    }
  }

  if (cnt == 5)
  {
    printf("\nYou Win!\n");
  }
  else
  {
    printf("\nYou Lose!\n");
  }
}