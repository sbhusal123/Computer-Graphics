#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
/*
every logic of method is commented on the class method.
basic colors
1 -> blue
2 -> green
3 -> teal
4 -> red
5 -> pink like
6 -> yellow
7 -> white
9 -> light blue
*/
using namespace std;

class BasicObjects
{
public:
    /// circle, lines, rectangles
    void drawLine(int x1, int y1, int x2, int y2)
    {
        setcolor(2); /// set color for lines.
        line(x1,y1,x2,y2); ///draw lines.
    }

    void drawRectangle(int leftUpwardX, int leftUpwardY, int righDownwardX, int rightDownwardY)
    {
        rectangle(leftUpwardX,leftUpwardY,righDownwardX,rightDownwardY);
        /// for rectangle we take two points i.e left upward point and right downward point
    }

    void drawCircle(int x, int y, int radius)
    {
        circle(x,y,radius);
    }
};

class basicDrawing : public BasicObjects ///inheriting the basic Objects
{
public:
    void fillColorInsideObject(int fillColor, int surfaceColor)
    {
        ///this can be easily understood by recalling how the color is filled in the Microsoft Paint.
        setcolor(surfaceColor);
        setfillstyle(SOLID_FILL,fillColor); /// solid fill -> filling style , fillColor-> color to be filled in region.
        drawRectangle(0,50,80,80);
        floodfill(55,70,surfaceColor); /// fill fillColor until meets the surface color.

        /// example on choosing color for drawing
        setcolor(fillColor); /// set color for drawing fillColor.
        drawRectangle(0,100,80,200);

        setcolor(surfaceColor); /// this is surface color.
        drawRectangle(200,100,300,400);
    }

    void makeMovementAnimation()
    {
        int i;
        for(i = 50; i <= 200; i += 10)
        {
            delay(100); /// delay the movement.
            setcolor(2);
            drawCircle(i,50,20); ///circle center(x,y) and radius
        }
    }

    void makeMovementByClearingPreviousPathOfObject(int fillColor, int surfaceColor)
    {
        /// simply this section is for circle only.
        /// for this section we must have concept of the flood filling on the object.
        /// refer the logic of the fillColorInsideObject method.
        /// this is simple animation but we'll be later working with more complex.

        int i = 0; /// this is used to increase the x co-ordinate of the object.
        int backgroundColor = 5; ///here background color is set to pink/5.

        floodfill(300,500,backgroundColor); ///fill the background color.
        for (i = 10; i<= 600; i+=20)
        {

            /// this is for clearing.
            /*
            * while clearing we go to the previous co-ordinate of the object and draw it using the background color.
            */
            setcolor(backgroundColor);
            setfillstyle(SOLID_FILL,backgroundColor); /// solid fill -> filling style , fillColor-> color to be filled in region.
            drawCircle(i,10,10); /// i = i+20; as 20 is the diameter of the circle.
            floodfill(i-20,10,backgroundColor); /// actually i-20 refers to the previous x co-ordinate.

            /// this is for drawing
            setcolor(surfaceColor);
            setfillstyle(SOLID_FILL,fillColor); /// solid fill -> filling style , fillColor-> color to be filled in region.
            drawCircle(i,10,10);
            floodfill(i,10,surfaceColor);

            delay(150); /// this is to delay the frame loading.
        }

    }
};

class AdvanceAnimation
{
public:
    void circleInStLine()
    {
        /// this is the simulation of the circle moving the st-line.
        int X = 100;
        int y = 400;
        for (X = 100; X<=400; X+=15)  ///here the X axis is increased by 30;
        {

            setcolor(1); ///set color 1 for drawing.
            setfillstyle(SOLID_FILL,2); /// fill color 2 inside the region.
            circle(X,y,10); ///radius is 20, draw circle.
            floodfill(X,y,1); /// fill color until meets the region with color 1.

            y = y-15; /// y axis is decreased by 30;
            delay(100);
            /// yo can do clearing of pr30evious path by yourself using concept of flood fill.
        }
    }


    void circleInSinusodalPath(){
     /// concept of frequency and amplitude.
     /// we have basically to plot angle in x and amplitude in y;
    int angle; /// this variable holds the angle.
    int amplitude = 50; /// this variable hold the amplitude of sine wave.

    /// some constants
    float time = 300; /// time T of the wave.
    float pie = 3.14; /// constant pie.
    float frequency = 1/time; /// frequency = 1/ Time, simple.

    /// to understand this change the value of time, amplitude and try to simulate that.
    float conversion = 2*pie*frequency; /// this is the important term.

    /// yet another interesting is 2*pie*time.


    double x, y; /// this is for the storing the center co-ordinate of circle.

    for (angle = 20; angle <= 500; angle+=15){
        /// here angle is maintained to decrease the region of interface between two circle. angle += 15.
        x = angle;
        y = 200 + amplitude * sin(conversion*angle);
        /// 10 is added to display the circle in the center. nothing special about that.
        circle(x,y,10);
        delay(100);
    }

    }
};

int main()
{
/// here test the every object every method.
    int gd = DETECT, gm = DETECT; /// initialize the graphics driver and graphics mode.
    initgraph(&gd,&gm,""); /// initialize the graphics screen.
    cleardevice(); /// used to clear the screen.

    /// basicDrawing drawing; /// instance of the class/ object.
    ///drawing.fillColorInsideObject(1,2); /// two parameters are well described by the parameter name in method of class.
    ///drawing.makeMovementAnimation(); /// make the movement animation
    /// drawing.makeMovementByClearingPreviousPathOfObject(1,2);

    AdvanceAnimation anim;
    anim.circleInSinusodalPath();

    getch();
}
