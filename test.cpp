#include<conio.h>
#include<graphics.h>
void main()
{
  clrscr();
  int gdriver=DETECT,gmode;
  initgraph(&gdriver,&gmode,"C:\TC\BGI");
  circle(20,15,30);
  getch();
  closegraph();
}
