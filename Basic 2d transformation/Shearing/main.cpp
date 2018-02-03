#include<iostream>
#include<graphics.h>
using namespace std;
class rectangleShearing{
    int x1,y1,x2,y2,x3,y3,x4,y4;
    int length,width;

    void plotRectangle(int color){
        setcolor(color);
        ///along x
        line(x1,y1,x2,y2);
        line(x3,y3,x4,y4);
        ///along y
        line(x1,y1,x3,y3);
        line(x2,y2,x4,y4);
    }

public:
    rectangleShearing(int x1,int y1,int x4,int y4){

         /// diagonal points as input;
        this -> x1 = x1;
        this -> y1 = y1;
        this -> x4 = x4;
        this -> y4 = y4;

        /// length and width of rectangle.
        length = x4-x1;
        width  = y4-y1;

        /// other 2 points calculation.
        x3 = x1;
        y3 = y4;
        x2 = x4;
        y2 = y1;

        plotRectangle(RED);
    }


    void shearTowardsX(int shX){
        x1 = x1 + shX*y1;
        y1 = y1;

        x2 = x2 + shX*y2;
        y2 = y2;
        plotRectangle(WHITE);
    }

     void shearTowardsY(int shY){
       y2 = y2+shY*x2;
       x2 = x2;

       y4 = y2+shY*x4;
       x4 = x4;

        plotRectangle(WHITE);

    }

};
int main(){
    int gd= DETECT, gm = DETECT;
    initgraph(&gd,&gm,"");
    rectangleShearing rect1(20,20,50,50);
    rectangleShearing rect2(60,60,80,80);
    rect1.shearTowardsX(2);
    rect2.shearTowardsY(2);
    getch();
}
