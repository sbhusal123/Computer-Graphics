#include <iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
int roundOff(float x){
    return (x+0.5);
}

void plot(float x0,float y0,float x1,float y1){

    int k = 0;
    int gd = DETECT, gm = DETECT;
    float dx,dy,step,x,y,Xinc,Yinc;
    initgraph(&gd,&gm,"");
    dx = x1-x0;
    dy = y1-y0;
    if(abs(dx) > abs(dy)){
        step = dx;
    }else{
        step = dy;
    }
    Xinc = dx/step;
    Yinc = dy/step;
    x = x0;
    y = y0;
    cout<<"Output estimation"<<endl;
    cout<<"________________________"<<endl;
    cout<<"k \t"<<"x \t"<<"y"<<endl;
    cout<<"________________________"<<endl;
    do{
     cout<<k<<"\t"<<roundOff(x)<<"\t"<<roundOff(y)<<endl;
     k = k + 1;
     x = x + Xinc;
     y = y + Yinc;
     putpixel(roundOff(x),roundOff(y),3);
    }while(k<=abs(step));
    cout<<"________________________"<<endl;
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
