#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<math.h>
/// here the line is rotated to certain point.
/// to do so we rotate the point x2,y2 about x1,y1.
using namespace std;
class lineObj
{

    int x1,y1,x2,y2;

    int trX, trY; ///these are the point translated.

    void drawLine()
    {
        setcolor(RED);
        line(x1,y1,x2,y2);
    }

    void translate(int aboutX, int aboutY, bool drawFlag)
    {
        trX = x2+aboutX;
        trY = y2+aboutY;
        if(drawFlag)
        {
            /// this is used to draw the final result.
            /// if the flag is true then the final result is drawn on screen.
            setcolor(WHITE);
            line(x1,y1,trX,trY);
            x2 = trX;
            y2 = trY;
        }
    }

    void rotationAboutOrigin(double angle)
    {
        angle = (3.14*angle)/180; /// conversion to degree from radian.
        x2 = trX*cos(angle)-trY*sin(angle);
        y2 = trX *sin(angle)+trY*cos(angle);
    }


public:
    lineObj(int x1, int y1, int x2, int y2)
    {
        this -> x1= x1;
        this -> x2= x2;
        this -> y1= y1;
        this -> y2= y2;
        drawLine();
    }


    void rotateLine(double angle)
    {
        int aboutX, aboutY;
        translate(-x1,-y1,false);
        /// the use of boolean expression is described in the method.
        rotationAboutOrigin(angle);
        translate(x1,y1,true);
    }



};

int main()
{
    int gd = DETECT, gm = DETECT, rotationAngle;
    initgraph(&gd, &gm, "");

    lineObj line1(400,300,500,300),line2(200,200,250,200);


    line2.rotateLine(90);
    line2.rotateLine(90); /// as a whole line 2is rotated by 180 deg.

    cout<<"Enter the angle by which you want to rotate"<<endl;
    cin>>rotationAngle;
    line1.rotateLine(rotationAngle);
    /// here total rotated about 180.
    getch();
}
