#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1024

int num[6] = {0, 0, 0, 0, 0, 0};

int checkNumber(int rnum);

int main(void)
{
  srand(time(NULL));
  FILE *file = fopen("lotto.txt", "wb");
  if (file == NULL)
  {
    printf("File Open Failed!\n");
    return 1;
  }

  fputs("Lotto Numbers : ", file);
  int idx = 0;
  int rnum;
  while (1)
  {
    rnum = rand() % 45 + 1;
    if (checkNumber(rnum))
    {
      if (idx == 6)
      {
        break;
      }
      num[idx] = rnum;
      idx++;
    }
  }

  for (int i = 0; i < 6; i++)
  {
    fprintf(file, "%d ", num[i]);
  }

  fputs("\nBonus Number : ", file);
  fprintf(file, "%d\n", rnum);

  fclose(file);

  return 0;
}

int checkNumber(int rnum)
{
  for (int i = 0; i < 6; i++)
  {
    if (num[i] == rnum)
    {
      return 0;
    }
  }
  return 1;
}