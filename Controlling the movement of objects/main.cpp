/*
God is who made the class. Who made the basics of nature i.e Class and we are just the object
of it's manipulation. We are the object but what rules us is the same class.
*/
#include<iostream>
#include<conio.h>
#include<graphics.h>
using namespace std;
class ball
{
protected:
    int posX; ///used to hold x-co-ordinate for next plot
    int posY;  ///used to hold y-co-ordinate for next plot
    int color; /// used to hold the color of the ball.

    void createBall()
    {
        /// this method is used to create a ball of certain color and at certain position on screen.

        setcolor(RED); ///red is the drawing color for the circle/object.
        setfillstyle(1,color); ///we fill the color of int type color inside object.
        circle(posX,posY,10); ///plot the circle at position (x,y) with radius of 10.
        floodfill(posX,posY,RED); ///spread the color until meets the region with red.
    }


    void updateGraphics()
    {
        /* used to update the graphics. It only plots the next position of the ball.
        * It doesn't clears the previous position of the ball.
        */

        setcolor(RED);
        setfillstyle(1,color);
        circle(posX,posY,10);
        floodfill(posX,posY,RED);
    }

    void moveLeft()
    {
        /// Concept is to first clear the screen and plot the next position.
        posX = posX - 1; /// decrease the position of x by 1.
        clearPreviousPosition(posX+1,posY);  ///used to clear the previous position of the ball.
        /// parameters are the previous X and Y co-ordinates of the ball.
        updateGraphics(); /// then the next position of the ball is plotted by this function.
    }

    void clearPreviousPosition(int clearX, int clearY){
        /* this takes the previous position of the ball and draw using background color.
        * this concept is described in the other code also.
        */
        setcolor(BLACK);
        setfillstyle(1,BLACK);
        circle(clearX,clearY,10);
        floodfill(clearX,clearY,BLACK);
    }


    void moveUp()
    {
        posY = posY - 1;
        clearPreviousPosition(posX,posY+1);
        updateGraphics();
    }

    void moveRight()
    {
        posX = posX + 1;
        clearPreviousPosition(posX-1,posY);
        updateGraphics();
    }

    void moveDown()
    {
        posY = posY + 1;
        clearPreviousPosition(posX,posY-1);
        updateGraphics();
    }

public:
    ball(int posX, int posY, int color)
    {
        this-> posX = posX;
        this-> posY = posY;
        this-> color = color;
        createBall();
        /* when the object is created then the ball is created with the color by
         calling the member function createBall() in the constructor.
         Done during the creation of object.
         */
    }

    void movementController(char movementFlag)
    {
        /* this is actually the movement controller.
         * run the program to understand this.
         */
        if(movementFlag == 'w' || movementFlag == 't' )
        {
            /* no matter which ball is it we decide to move ball upward when pressed w/t.
            * ball selection is done in the main method.
            * So no need to declare which ball needs to be moved.
            */
            moveUp();
        }
        else if(movementFlag == 'a' || movementFlag == 'f')
        {
            moveLeft();
        }
        else if(movementFlag == 's' || movementFlag == 'g')
        {
            moveDown();
        }
        else if(movementFlag == 'd' || movementFlag == 'h')
        {
            moveRight();
        }
    }

};
int main()
{
    int gd= DETECT, gm = DETECT; ///graphics mode and graphics driver;
    initgraph(&gd,&gm,""); /// "" denotes the default path of the driver.

    char input = 'o';

    /// Displaying information about movement control.
    cout<<"Movement Controller Buttons: Input here"<<endl<<endl;
    cout<<"--------------Red Ball---------------"<<endl;
    cout<<" Upward -> w"<<endl;
    cout<<" Downward -> s"<<endl;
    cout<<" Left -> a"<<endl;
    cout<<" Right -> d"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;
    cout<<"--------------GREEN Ball------------"<<endl;
    cout<<" Upward -> t"<<endl;
    cout<<" Downward -> g"<<endl;
    cout<<" Left -> f"<<endl;
    cout<<" Right -> h"<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<" Press q to quit the game"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;


    ball gre(10,10,GREEN);
    ball red(10,50,RED);


    input = _getch(); ///take the input in the window other than plotting window.
    while(input != 'q') /// loop/allow user to enter the key until q key is pressed.
    {
        input = _getch();
        if(input == 'w' || input == 's' || input == 'a' || input == 'd')
        {
            /* if the keys are associated with red ball.
            * pass the parameter to the method movementController which is inside the same object.
            * don't confuse between class and the object.
            * Each object has it's own unique memory address in runTime.
            * So it executes the function for the particular object only.
            */
            red.movementController(input);
            cout<<"Red ball movement"<<endl;
        }
        else if(input == 't' || input == 'g' || input == 'f' || input == 'h')
        {
            gre.movementController(input);
            cout<<"Green ball movement"<<endl;
        }
        else if(input == 'q')
        {
            break;
        }
        else
        {
            cout<<endl<<"____________________________________________"<<endl;
            cout<<"Wrong input. Please press the right key."<<endl;
            cout<<"____________________________________________"<<endl;
        }
    }
}
