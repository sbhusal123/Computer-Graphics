/*
God is who made the class. Who made the basics of nature i.e Class and we are just the object
of it's manipulation. We are the object but what rules us is the same class.
*/
#include<math.h>
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
    int radius = 10;

    void createBall()
    {
        /// this method is used to create a ball of certain color and at certain position on screen.
        setcolor(RED); ///red is the drawing color for the circle/object.
        setfillstyle(1,color); ///we fill the color of int type color inside object.
        circle(posX,posY,radius); ///plot the circle at position (x,y) with radius of 10.
        floodfill(posX,posY,RED); ///spread the color until meets the region with red.
    }

    int toAscii(char inp)
    {
        return int(inp);
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

    void clearPreviousPosition(int clearX, int clearY)
    {
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

    void moveDown()
    {
        posY = posY + 1;
        clearPreviousPosition(posX,posY-1);
        updateGraphics();
    }

    void moveLeft()
    {
        /// Concept is to first clear the screen and plot the next position.
        posX = posX - 1; /// decrease the position of x by 1.
        clearPreviousPosition(posX+1,posY);  ///used to clear the previous position of the ball.
        /// parameters are the previous X and Y co-ordinates of the ball.
        updateGraphics(); /// then the next position of the ball is plotted by this function.
    }

    void moveRight()
    {
        posX = posX + 1;
        clearPreviousPosition(posX-1,posY);
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

    bool checkCollision(ball b1) ///here the ball1 is another ball. Check implementation in main.
    {
        ///if balls are in the way to collide then the distance between
        /// center is equal or lesser to the sum of radius.

        float distanceBetweenCenters;
        distanceBetweenCenters = sqrt(pow((posX - b1.posX),2) + pow((posY-b1.posY),2));
        if(distanceBetweenCenters <= radius+radius+1)
        {
            /// distance between centers of circle = Sum of radius of the circles.
            /*
            though the distance between the center of the circle are the sum of radius
            but to maintain the shape of the ball in original form. We need to add 1.
            */
            return true; ///if collides then return true.
        }
        else
        {
            return false;
        }
    }


    char preventCollision(char keyPressed)
    {
        /// actual concept is to automatically press the counter key so to prevent collision.

        /***
        Key Pressed     counterKey
         w                  s
         s                  w
         a                  d
         d                  a
        */

        int diffAscii; /// used to store the difference of the ASCII. Further....

        char counterKeyToPreventCollision; /// which is the counter key to be pressed??????
        cout<<"You can't collide with the object"<<endl;

        if(keyPressed == 'w' || keyPressed == 's')
        {
            diffAscii = toAscii(keyPressed) - toAscii('w'); /// is key pressed = w.
            counterKeyToPreventCollision = diffAscii == 0 ? 's' : 'w'; ///simple conditional statement to check
        }
        else if(keyPressed == 'a' || keyPressed == 'd')
        {
            diffAscii = toAscii(keyPressed) - toAscii('a');
            counterKeyToPreventCollision = diffAscii == 0 ? 'd' : 'a';
        }
        return counterKeyToPreventCollision;
    }

    void movementController(char movementFlag, ball b)
    {
        /* this is actually the movement controller.
         * run the program to understand this.
         */
        if(movementFlag == 'w')
        {
            /* no matter which ball is it we decide to move ball upward when pressed w/t.
            * ball selection is done in the main method.
            * So no need to declare which ball needs to be moved.
            */
            moveUp();
        }
        else if(movementFlag == 'a')
        {
            moveLeft();
        }
        else if(movementFlag == 's')
        {
            moveDown();
        }
        else if(movementFlag == 'd')
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
    cout<<"--------------GREEN Ball------------"<<endl;
    cout<<" Upward -> t"<<endl;
    cout<<" Downward -> g"<<endl;
    cout<<" Left -> f"<<endl;
    cout<<" Right -> h"<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<" Press q to quit the game"<<endl;
    cout<<"-------------------------------------"<<endl<<endl;

    char counterCollisionKey;

    ball gre(10,10,GREEN);
    ball red(100,100,RED);


    input = _getch(); ///take the input in the window other than plotting window.
    while(input != 'q') /// loop/allow user to enter the key until q key is pressed.
    {
        if(!gre.checkCollision(red))
        {
            /** don't allow user to press key if collision
            takes place because the counter key is found and simulated automatically.
            */
            input = _getch();
        }
        if( input == 'w' || input == 's' || input == 'a' || input == 'd')
        {
            if(!gre.checkCollision(red))  ///if collision does not takes place. Normal execution.
            {
                gre.movementController(input,gre);
            }
            else /// if collision takes place.
            {
                counterCollisionKey = gre.preventCollision(input);
                /// to prevent the collision find suitable counter key.

                gre.movementController(counterCollisionKey,gre);
                /// now simulate the key in graphics.
            }
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
