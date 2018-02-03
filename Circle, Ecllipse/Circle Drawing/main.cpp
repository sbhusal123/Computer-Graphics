#include<iostream>
#include<graphics.h>
using namespace std;
class Circle
{
    int xc,yc,r,p,x,y;
    /**
    p -> decision parameter.
    x,y -> plot point.
    */

    void initializeData()
    {
        p = 1-r;
        x = 0;
        y = r;
    }

    void drawCircle(int color)
    {
        for(x = 0; x <= y; x++){
            if(p<0)
            {
                y = y;
                p = p + 2*x + 1;
            }
            else
            {
                y = y - 1;
                p = p + 2*(x+1) - 2*y;
            }
            ///symmetric plotting on all quadrants.
            putpixel(xc+x,yc+y,1);
            putpixel(xc+x,yc-y,1);
            putpixel(xc-x,yc+y,1);
            putpixel(xc-x,yc-y,1);
            putpixel(yc-y,xc+x,1);
            putpixel(yc+y,xc-x,1);
            putpixel(yc-y,xc-x,1);
            putpixel(yc+y,xc+x,1);
            delay(10);
        }
    }

public:
    Circle(int xc, int yc, int r)
    {
        this-> xc = xc;
        this-> yc = yc;
        this-> r = r;
        initializeData();
        drawCircle(RED);
    }
};
int main()
{
    int gd = DETECT, gm = DETECT;
    initgraph(&gd,&gm,"");
    int xc,yc,r;
    cout<<"Enter the center for the circle(x,y)"<<endl;
    cin>>xc>>yc;
    cout<<"Enter the radius of the circle"<<endl;
    cin>>r;
    Circle c1(xc,yc,r);
    getch();
    closegraph();
}
