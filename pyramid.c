#include <stdio.h>

int main(void)
{
  int type;
  int level;
  int exit;

  while (1)
  {
    printf("Input Type (0 or 1): \n");
    scanf("%d", &type);
    printf("Input Level : \n");
    scanf("%d", &level);

    if (type == 0)
    {
      for (int i = 0; i < level; i++)
      {
        for (int j = 0; j < (level - i); j++)
        {
          printf(" ");
        }
        for (int j = 0; j < (i * 2) + 1; j++)
        {
          printf("*");
        }
        printf("\n");
      }
    }
    else
    {
      for (int i = 1; i <= level; i++)
      {
        for (int j = 1; j <= (level - i); j++)
        {
          printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
          printf("* ");
        }
        printf("\n");
      }
    }

    printf("EXIT? (1 is exit) : \n");
    scanf("%d", &exit);

    if (exit)
    {
      break;
    }
  }

  return 0;
}