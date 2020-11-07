#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  //rand 초기화
  //하지 않을 경우 rand함수의 값이 매번 똑같다.
  srand(time(NULL));
  int num = rand() % 100 + 1;
  int input;

  while (1)
  {
    printf("Input Number (1 ~ 100): \n");
    scanf("%d", &input);
    if (input > 0 && input <= 100)
    {
      if (input < num)
      {
        printf("Up\n");
        continue;
      }
      else if (input > num)
      {
        printf("Down\n");
        continue;
      }
      else
      {
        printf("Correct!\n");
        break;
      }
    }
    else
    {
      printf("Wrong Number!\n");
    }
  }

  return 0;
}