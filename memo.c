#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int main(void)
{
  char line[MAX];

  FILE *file = fopen("memo.txt", "a+b");
  if (file == NULL)
  {
    printf("File Open Failed!\n");
    return 1;
  }

  while (fgets(line, MAX, file) != NULL)
  {
    printf("%s", line);
  }

  while (1)
  {
    scanf("%[^\n]", line);
    getchar(); //\n을 없애 버린다.
    if (strcmp(line, "exit") == 0 || strcmp(line, "EXIT") == 0)
    {
      break;
    }
    fprintf(file, "%s\n", line);
  }

  fclose(file);

  return 0;
}