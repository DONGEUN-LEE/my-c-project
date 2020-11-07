#include <stdio.h>

int main(void)
{
  char name[256];
  int age;
  float weight;
  char history[1024];
  printf("Name : \n");
  // 1. scanf => scanf_s
  // scanf(format_str, buffer_address) 대신 scanf_s(format_str, buffer_address, buffer_size)를 사용하여
  // buffer overflow 에러를 방지 할 수 있지만 scanf_s는 Windows에만 정의되어 있으므로 gcc에서는 scanf 사용
  //
  // 2. %s => %[^\n]
  // %s대신 %[close str regex]를 사용하여 종료 문자열을 지정할 수 있다. ex) %[1] 1이 나오면 입력 종료
  // space를 입력 받아야 한다면 [^\n] (\n을 제외한 모든 문자 입력 받음)을
  // 사용하여 입력 받기 가능
  scanf("%[^\n]", name);
  printf("Age : \n");
  scanf("%d", &age);
  printf("Weight : \n");
  scanf("%f", &weight);
  getchar();
  printf("History : \n");
  scanf("%[^\n]", history);

  printf("\n\n-- Resume --\n");
  printf("Name : %s\n", name);
  printf("Age : %d\n", age);
  // .1은 소수점 첫 번째 자리 까지만 표시 하겠다는 의미
  printf("Weight : %.1f\n", weight);
  printf("History : %s\n", history);
  return 0;
}