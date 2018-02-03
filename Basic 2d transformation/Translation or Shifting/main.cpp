#include<iostream>
#include<graphics.h>
using namespace std;
class lineTranslation
{

    int x1,y1,x2,y2;

    void drawLine(int color)
    {
        setcolor(color);
        line(x1,y1,x2,y2);
    }
public:

    lineTranslation(int x1,int y1, int x2, int y2)
    {
        this-> x1= x1;
        this-> y1 = y1;
        this-> x2 = x2;
        this-> y2 = y2;
        drawLine(RED);
    }

    void translateLine(int tX, int tY)
    {
        x1 = x1+tX;
        y1 = y1+tY;
        x2 = x2+tX;
        y2 = y2+tY;
        drawLine(WHITE);
    }
};

int main()
{
    int gd = DETECT, gm = DETECT;
    initgraph(&gd,&gm,"");
    lineTranslation line1(200,100,300,400);
    line1.translateLine(20,30);
    getch();
}
