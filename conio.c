#include "conio.h"
#include <unistd.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void initTermios(int echo)
{
    tcgetattr(0, &oldterm);
    newterm = oldterm;
    newterm.c_lflag &= ~ICANON;
    newterm.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &newterm);
}
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &oldterm);
}

int getch_(int echo)
{
    int ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

void cagxy(unsigned int x, unsigned int y)
{
    printf("%s\x1b[%d;%df", CLEAR, y, x);
}

void clrscr(void)
{
    printf("%s%s",CLEAR, SET11);
}

int getch(void)
{
    return getch_(0);
}

int getche(void)
{
    return getch_(1);
}

void gotox(unsigned int x)
{
    printf("\x1b[%dG", x);
}

void gotoxy(unsigned int x, unsigned int y)
{
    printf("\x1b[%d;%df", y, x);
}

void nocursor(void)
{
    printf("\x1b[?25l");
}

void normvideo(void)
{
    printf("\x1b[0m");
}

void showcursor(void)
{
    printf("\x1b[?25h");
}

void textcolor(int newcolor)
{
  //https://en.wikipedia.org/wiki/ANSI_escape_code

  const char * s = "\x1b[30m";

  switch (newcolor)
  {
  case BLACK:
    s = "\x1b[30m";
    break;

  case BLUE:
    s = "\x1b[34m";
    break;

  case GREEN:
    s = "\x1b[32m";
    break;

  case CYAN:
    s = "\x1b[36m";
    break;

  case RED:
    s = "\x1b[31m";
    break;

  case MAGENTA:
    s = "\x1b[35m";
    break;

  case BROWN:
    s = "\x1b[33m";
    break;

  case LIGHTGRAY:
    s = "\x1b[37m";
    break;

  case DARKGRAY:
    s = "\x1b[90m";
    break;

  case LIGHTBLUE:
    s = "\x1b[94m";
    break;

  case LIGHTGREEN:
    s = "\x1b[92m";;
    break;

  case LIGHTCYAN:
    s = "\x1b[96m";
    break;

  case LIGHTRED:
    s = "\x1b[91m";
    break;

  case LIGHTMAGENTA:
    s = "\x1b[95m";
    break;

  case YELLOW:
    s = "\x1b[93m";
    break;

  case WHITE:
    s = "\x1b[97m";
    break;

  case BLINK:
    s = "\x1b[30m";
    break;
  };

  printf("%s", s);
}

void textbackground(int newcolor)
{
  //https://en.wikipedia.org/wiki/ANSI_escape_code

  const char * s = "\x1b[40m";

  switch (newcolor)
  {
  case BLACK:
    s = "\x1b[40m";
    break;

  case BLUE:
    s = "\x1b[44m";
    break;

  case GREEN:
    s = "\x1b[42m";
    break;

  case CYAN:
    s = "\x1b[46m";
    break;

  case RED:
    s = "\x1b[41m";
    break;

  case MAGENTA:
    s = "\x1b[45m";
    break;

  case BROWN:
    s = "\x1b[43m";
    break;

  case LIGHTGRAY:
    s = "\x1b[47m";
    break;

  case DARKGRAY:
    s = "\x1b[100m";
    break;

  case LIGHTBLUE:
    s = "\x1b[104m";
    break;

  case LIGHTGREEN:
    s = "\x1b[102m";;
    break;

  case LIGHTCYAN:
    s = "\x1b[106m";
    break;

  case LIGHTRED:
    s = "\x1b[101m";
    break;

  case LIGHTMAGENTA:
    s = "\x1b[105m";
    break;

  case YELLOW:
    s = "\x1b[103m";
    break;

  case WHITE:
    s = "\x1b[107m";
    break;

  case BLINK:
    s = "\x1b[40m";
    break;
  };

  printf("%s", s);
}

void delline(void)
{
    printf("%s%s", ERASE_LINE, CURSOR_UP);
}

void clreol(void)
{
    printf("%s",CLEAR);
}
int putch(const char c)
{
    printf("%c",c);
    return (int)c;
}

int cputs(const char*str)
{
    printf(str);
    return 0;
}


int wherexy(int *x, int *y)
{
    printf("\033[6n");
    if(getch() != '\x1B') return 0;
    if(getch() != '\x5B') return 0;
    int in;
    int ly = 0;
    while((in = getch()) != ';')
        ly = ly * 10 + in - '0';
    int lx = 0;
    while((in = getch()) != 'R')
        lx = lx * 10 + in - '0';
    *x = lx;
    *y = ly;
}
int wherex(void)
{
    int x=0,y=0;
    wherexy(&x, &y);
    return x;
}

int wherey(void)
{
    int x=0,y=0;
    wherexy(&x, &y);
    return y;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif
