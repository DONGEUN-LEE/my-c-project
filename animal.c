#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
  int x;
  int y;
  int num;
  char *name;
  char color[12];
  char flag;
} Pos;

Pos map[4][5];
char *names[10];

void setSleep(int sec);
void initMap();
void initNames();
void shuffle();
Pos *getEmptyPosition();
int convertPosX(int pos);
int convertPosY(int pos);
void printAnimal();
void printMap();
int checkWin();

int main(void)
{
  system("clear");
  srand(time(NULL));
  int fail = 0;
  int x, y;

  initMap();
  initNames();

  shuffle();

  printAnimal();

  setSleep(5);
  system("clear");

  int input = 0;
  Pos *prev = NULL;

  while (1)
  {
    printMap();
    printf("\ninput number (EXIT: -1) => ");
    scanf("%d", &input);

    if (input == -1)
    {
      break;
    }

    if (input < 0 || input > 20)
    {
      printf("Wrong Number!\n");
      getchar();
    }
    else
    {
      x = convertPosX(input - 1);
      y = convertPosY(input - 1);
      if (map[x][y].flag == 1)
      {
        printf("Wrong Number!\n");
        getchar();
      }
      else
      {
        map[x][y].flag = 1;
        if (prev == NULL)
        {
          prev = &map[x][y];
        }
        else
        {
          if (strcmp(prev->name, map[x][y].name) != 0)
          {
            system("clear");
            printMap();
            setSleep(1);
            prev->flag = 0;
            map[x][y].flag = 0;
            fail++;
          }
          else
          {
            if (checkWin())
            {
              break;
            }
          }
          prev = NULL;
        }
      }
    }

    system("clear");
  }

  system("clear");
  printf("Total Fail Count => %d\n", fail);
  if (checkWin())
  {
    printf("You Win!\n");
  }
  else
  {
    printf("You Lose!\n");
  }

  return 0;
}

void setSleep(int sec)
{
  clock_t start = clock();

  while (1)
  {
    if ((clock() - start) / CLOCKS_PER_SEC >= sec)
    {
      break;
    }
  }
}

void initMap()
{
  int cnt = 1;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      Pos pos = {i, j, cnt, "", 0};
      map[i][j] = pos;
      cnt++;
    }
  }
}

void initNames()
{
  names[0] = "mouse";
  names[1] = "cow";
  names[2] = "tiger";
  names[3] = "rabbit";
  names[4] = "dragon";
  names[5] = "snake";
  names[6] = "horse";
  names[7] = "sheep";
  names[8] = "monkey";
  names[9] = "chiken";
}

void shuffle()
{
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      Pos *pos = getEmptyPosition();
      map[pos->x][pos->y].name = names[i];
      sprintf(map[pos->x][pos->y].color, "\033[0;%d0;%d%dm", i % 2 + 3, 4 - i % 2, i % 5 + 1);
    }
  }
}

Pos *getEmptyPosition()
{
  while (1)
  {
    int randPos = rand() % 20;
    int x = convertPosX(randPos);
    int y = convertPosY(randPos);

    if (strcmp(map[x][y].name, "") == 0)
    {
      return &map[x][y];
    }
  }
  return NULL;
}

int convertPosX(int pos)
{
  return pos / 5;
}

int convertPosY(int pos)
{
  return pos % 5;
}

void printAnimal()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      printf("%s", map[i][j].color);
      printf("%7s", map[i][j].name);
      printf("\033[0;0m");
    }
    printf("\n");
  }
  printf("\n");
}

void printMap()
{
  int seq;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (map[i][j].flag == 0)
      {
        printf("%7d", map[i][j].num);
      }
      else
      {
        printf("%s", map[i][j].color);
        printf("%7s", map[i][j].name);
        printf("\033[0;0m");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int checkWin()
{
  int seq;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (map[i][j].flag == 0)
      {
        return 0;
      }
    }
  }
  return 1;
}