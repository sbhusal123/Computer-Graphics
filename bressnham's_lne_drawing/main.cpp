#include<graphics.h>
#include<iostream>
using namespace std;
void plot(int x0,int y0,int x1,int y1)
{
    int gd = DETECT, gm = DETECT; //graphics mode and driver;
    initgraph(&gd,&gm,"");
    int dx, dy, p, x=x0, y=y0;
    dx = x1-x0;
    dy = y1-y0;

    p = 2*dy-dx;
     cout<<"_____________________________"<<endl;
    cout<<"k \t"<<"p \t"<<"x \t"<<"y \t"<<endl;
    cout<<"_____________________________"<<endl;
    for(int k = 0;k<=dx;k++){
         cout<<k<<" \t"<<p<<" \t"<<x<<" \t"<<y<<endl;
        if(p<0)
        {
            x = x+1;
            y = y;
            p = p+2*dy;
        }
        else
        {
            x = x+1;
            y = y+1;
            p = p+2*dy-2*dx;
        }
        putpixel(x,y,3);
    }
    cout<<"_____________________________"<<endl;
    getch();
}
int main()
{
    int x0,y0,x1,y1;
    cout<<"Enter first point"<<endl;
    cin>>x0>>y0;
    cout<<"Enter second point"<<endl;
    cin>>x1>>y1;
    plot(x0,y0,x1,y1);
}
