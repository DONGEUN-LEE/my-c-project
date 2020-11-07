#include <stdio.h>

int main(void)
{
  int i = 0x00000001;
  if (((char *)&i))
    printf("Big Endian\n");
  else
    printf("Little Endian\n");

  return 0;
}