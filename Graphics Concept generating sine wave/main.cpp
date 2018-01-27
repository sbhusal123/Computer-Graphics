#include<iostream>
#include<graphics.h>
#include<math.h>
#include<conio.h>
using namespace std;

class Animation
{
    int background;
public:
    Animation()
    {
        background = BLUE;
        setBackground();
    }

    void setBackground()
    {
        setcolor(2);
        setfillstyle(1,background);
        rectangle(0,0,getmaxx(),getmaxy());
        floodfill(10,10,2);
    }

    void drawCircle(int x, int y, int r)
    {
        circle(x,y,r);
    }

    void moveCircleInSinePath(int f, int a, char clearFlag)
    {
        int angle;
        int frequency = f;
        int amplitude = a;

        int angleIncreament = 10; /// what is the value by which angle needs to be increased.

        double x,y; /// this holds the center of the circle for the next plot.
        double xClear, yClear; /// this holds the center of the previous circle which needs to be cleared.


        int beginX = 100; /// this is the X point from where circle plotting starts.
        int beginY = 200; /// similarly this is the Y point from where circle plotting starts.

        float conversion = (2*3.14)/frequency;
        for(angle = 0; angle <=500; angle+=angleIncreament)
        {
            /// calculation of the next co-ordinate to plot the circle.
            x = beginX+angle;
            y = beginY+amplitude*sin(conversion*angle);

            /// calculation of the previous co-ordinate to clear the previous circle.
            xClear = beginX + (angle-angleIncreament);
            yClear = beginY + amplitude*sin(conversion*(angle-angleIncreament));

            if(clearFlag == 'y'){
            /// this is for clearing the previous path executes only if the user wants to clear the previous path.
            setcolor(background);
            setfillstyle(1,background);
            drawCircle(xClear,yClear,10);
            floodfill(xClear,yClear,background);
            }


            /// for filling green color on the region.
            setcolor(YELLOW);
            setfillstyle(8,GREEN); /// check the effect of value 8 by changing.
            drawCircle(x,y,10);
            floodfill(x,y,YELLOW);
            delay(100);
        }
    }
};

int main()
{

    int gd = DETECT, gm = DETECT;
    initgraph(&gd, &gm, "");
    char flag;

    int frequency;
    int amplitude;

    cout<<"Enter the frequency:"<<endl;
    cin>>frequency;

    cout<<"Enter the amplitude:"<<endl;
    cin>>amplitude;

    /// best fit for frequency is 200 and amplitude is 100 for checking.

    /// this is to validate the input for y/n.
    do{
    cout<<"Do you want previous path to be cleared?(y/n)"<<endl;
    cin>>flag;
    if(flag != 'y' && flag != 'n'){
        cout<<"___________________________________"<<endl;
        cout<<endl<<"Please enter valid input (y/n)"<<endl;
        cout<<"___________________________________"<<endl;
    }
    } while(flag!= 'y' && flag != 'n');

    Animation anim; ///parameter is background color.
    anim.moveCircleInSinePath(frequency,amplitude,flag);
    getch();
}
