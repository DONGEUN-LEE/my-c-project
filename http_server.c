#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

int server_sock;
int client_sock;
struct sockaddr_in addr;
struct sockaddr_in client;
#define PORT_NUM 7777

/* reads from keypress, doesn't echo */
int getch(void)
{
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

// IP 주소 얻기
int getAddrHost(void)
{
  int i;
  struct hostent *lpHost;    //  호스트 정보를 저장하는 구조체
  struct in_addr inaddr;     // IP 주소를 저장하는 구조체
  char szBuf[256], szIP[16]; // 호스트 이름/IP 주소를 저장하는 배열

  // 로컬 머신의 호스트 이름을 얻는다
  gethostname(szBuf, (int)sizeof(szBuf));

  // 호스트 정보 얻기
  lpHost = gethostbyname(szBuf);
  // IP 주소 얻기
  for (i = 0; lpHost->h_addr_list[i]; i++)
  {
    memcpy(&inaddr, lpHost->h_addr_list[i], 4);
  }
  strcpy(szIP, inet_ntoa(inaddr));
  printf("build server: http://%s:%d\n", szIP, PORT_NUM);

  return 0;
}

int main(void)
{
  int len;
  int n;
  int sockaddr_in_size = sizeof(struct sockaddr_in);
  int recv_len = 0;
  unsigned char buf[1024];
  unsigned char path[1024];
  unsigned char html[1024];

  //IP 어드레스 표시
  if (getAddrHost() != 0)
  {
    printf("get IP address failed");
    getch();
    return -1;
  }

  // 소켓 만들기
  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock == -1)
  {
    printf("socket : %s\n", "socket error!");
    getch();
    return -1;
  }

  // 소켓 설정
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT_NUM);
  addr.sin_addr.s_addr = INADDR_ANY;

  // 소켓 바인드
  if (bind(server_sock, (struct sockaddr *)&addr, sizeof(addr)) != 0)
  {
    printf("bind : %s\n", "socket bind error!");
    getch();
    return -1;
  }

  // TCP 클라이언트로부터의 접속 요구를 기다리면서 대기한다
  if (listen(server_sock, 5) != 0)
  {
    printf("listen : %s\n", "socket listen error!");
    getch();
    return -1;
  }

  // 서버 시작
  while (1)
  {

    len = sizeof(client);
    client_sock = accept(server_sock, (struct sockaddr *)&client, &len);
    if (client_sock == -1)
    {
      printf("accept : %s\n", "socket accept error!");
      break;
    }

    // 버퍼 초기화
    memset(path, 0, 1024);
    memset(html, 0, 1024);

    // 접속
    recv_len = recvfrom(client_sock, buf, 1024, 0, (struct sockaddr *)&client, &sockaddr_in_size);
    buf[recv_len - 1] = 0;
    if (buf[0] == '\0')
      strcpy(buf, "");

    // 통신 표시
    printf("%s \n", buf);

    // method
    for (int i = 0; i < strlen(buf); i++)
    {
      printf("%d\n", i);
      if (buf[i] == 'G' && buf[i + 1] == 'E' && buf[i + 2] == 'T' && buf[i + 3] == ' ')
      {
        for (int j = 0; buf[i + 4 + j] != ' '; j++)
        {
          path[j] = buf[i + 4 + j];
        }
        break;
      }
      else if (buf[i] == 'P' && buf[i + 1] == 'O' && buf[i + 2] == 'S' && buf[i + 3] == 'T' && buf[i + 4] == ' ')
      {
        for (int j = 0; buf[i + 4 + j] != ' '; j++)
        {
          path[j] = buf[i + 4 + j];
        }
        break;
      }
    }
    printf("request: %s \n", path);

    // HTTP
    unsigned char *header =
        "HTTP/1.0 200 OK\n"
        "Content-type: text/html\n"
        "\n";

    send(client_sock, header, strlen(header), 0);

    // 라우팅
    if (strcmp(path, "/page1") == 0)
    {
      strcpy(html,
             "<!DOCTYPE html>\n"
             "<html lang = \"ja\">\n"
             "<head>\n"
             "<meta charset = \"utf-8\">\n"
             "</head>\n"
             "<body>\n"
             "<h1>Page1</h1>\n"
             "<a href=\"/page2\">->page2</a>\n"
             "</body>"
             "</html>");
    }
    else if (strcmp(path, "/page2") == 0)
    {
      strcpy(html,
             "<!DOCTYPE html>\n"
             "<html lang = \"ja\">\n"
             "<head>\n"
             "<meta charset = \"utf-8\">\n"
             "</head>\n"
             "<body>\n"
             "<h1>Page2</h1>\n"
             "<a href=\"/page1\">->page1</a>\n"
             "</body>"
             "</html>");
    }
    else
    {
      strcpy(html,
             "<!DOCTYPE html>\n"
             "<html lang = \"ja\">\n"
             "<head>\n"
             "<meta charset = \"utf-8\">\n"
             "</head>\n"
             "<body>\n"
             "<h1>404- Not Found</h1>\n"
             "</body>"
             "</html>");
    }

    // 응답（HTML을 보낸다）
    if (send(client_sock, html, strlen(html), 0) < 1)
    {
      printf("send : %s\n", "socket send error!");
      break;
    }

    // 소켓 닫기
    close(client_sock);
  }

  // socket 종료 처리
  close(server_sock);
  return 0;
}