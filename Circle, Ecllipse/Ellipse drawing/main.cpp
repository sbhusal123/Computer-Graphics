#include<stdio.h>
#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
class Elipse
{
    int xc, yc,a,b; ///user supplied data.
    int x,y; /// plotting points.
    float p1,p2; ///two decision parameters.

    void display(int color) ///symmetric plotting.
    {
        setcolor(color);
        putpixel(xc+x,yc+y,color);
        putpixel(xc-x,yc+y,color);
        putpixel(xc+x,yc-y,color);
        putpixel(xc-x,yc-y,color);
    }

    void drawRegion1()
    {
        x=0;
        y=b;
        p1=(b*b)-(a*a*b)+((a*a)/4.0);
        while((2.0*b*b*x)<=(2.0*a*y*a))
        {
            x++;
            if(p1<=0)
                p1=p1+(2.0*b*b*x)+(b*b);
            else
            {
                y--;
                p1=p1+(2.0*b*b*x)+(b*b)-(2.0*a*a*y);
            }
            display(GREEN);
        }
    }

    void drawRegion2()
    {
        x=a;
        y=0.0;
        p2=((b*b)/4.0)+(a*b*b)+(a*a);
        while((2.0*b*b*x)>(2.0*a*a*y))
        {
            y++;
            if(p2>0)
                p2=p2+(a*a)-(2.0*a*a*y);
            else
            {
                x--;
                p2=p2+(2.0*b*b*x)+(a*a)-(2.0*a*a*y);
            }
            display(RED);
        }
    }

    void drawEllipse()
    {
        drawRegion1();
        drawRegion2();
    }
public:
    Elipse(int xc, int yc,int a,int b)
    {
        this-> xc = xc;
        this-> yc = yc;
        this-> a = a;
        this-> b = b;
        drawEllipse();
    }
};

int main(){
    int gd = DETECT, gm = DETECT;
    initgraph(&gd,&gm, "");
    Elipse el(200,200,100,100);
    getch();
    closegraph();
}
