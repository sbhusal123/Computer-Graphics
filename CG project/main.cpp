#include<iostream>
#include<conio.h>
#include<fstream> /// for sprintf
#include<graphics.h>
#include<thread>
using namespace std;
int background = BLUE;
class gameObjects
{
protected:
    void drawLine(int x0,int y0,int x1,int y1, int color)
    {
        /// DDA line drawing algorithm.
        int k = 0;
        float dx,dy,step,x,y,Xinc,Yinc;
        dx = x1-x0;
        dy = y1-y0;
        if(abs(dx) > abs(dy))
        {
            step = dx;
        }
        else
        {
            step = dy;
        }
        Xinc = dx/step;
        Yinc = dy/step;
        x = x0;
        y = y0;
        do
        {
            k = k + 1;
            x = x + Xinc;
            y = y + Yinc;
            putpixel(x,y,color);
        }
        while(k<=abs(step));
    }

    void drawRect(int x0,int y0, int x1, int y1,int color)
    {
        ///two horizontal lines
        drawLine(x0,y0,x1,y0,color); ///upper
        drawLine(x0,y1,x1,y1,color); ///lower
        ///sides
        drawLine(x0,y0,x0,y1,color); ///left
        drawLine(x1,y0,x1,y1,color); ///right
    }

    void drawCircle(int xc, int yc, int r,int color)
    {
        int p,x,y;

        p = 1-r;
        x = 0;
        y = r;

        for(x = 0; x <= y; x++)
        {
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
            putpixel(xc+x, yc+y, color);
            putpixel(xc-x, yc+y, color);
            putpixel(xc+x, yc-y, color);
            putpixel(xc-x, yc-y, color);
            putpixel(xc+y, yc+x, color);
            putpixel(xc-y, yc+x, color);
            putpixel(xc+y, yc-x, color);
            putpixel(xc-y, yc-x, color);
            /// symmetricity refrence at https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
        }
    }
};

class  game:protected gameObjects
{
    char scrdisp[10];
    thread* t1;
    ///-------------------- Variables-------------------///
    char keyPressed = NULL;
    /// structure for holding player information.
    struct player
    {
        int x, y0, y1,color,score;
    };
    player player1, player2;
    /// for ball
    int ballX, ballY,ballColor,ballBorderColor;

    bool ballAtLeft, ballAtRight;

    bool ballAtTop, ballAtBottom;

    ///--------------------------------------------------///
    void initializeData()
    {
        ballX = 41;
        ballY = 130;

        player1.color = LIGHTCYAN;
        player1.x = 30;
        player1.y0 = 100;
        player1.y1 = 200;


        player2.color = LIGHTMAGENTA;
        player2.x = 600;
        player2.y0 = 100;
        player2.y1 = 200;

        ///  Basic setUp For Game and Game Screen
        ballBorderColor = RED;
        ballColor  = GREEN;
    }

    void displayScoreBoard()
    {

        /// whole score board border.
        drawRect(20,10,620,50,RED);

        /// left score board
        drawRect(21,11,321,49,CYAN);
        setfillstyle(SOLID_FILL,CYAN);
        floodfill(30,40,CYAN);
        setbkcolor(CYAN);
        setcolor(LIGHTGREEN);
        sprintf(scrdisp,"Score:%d",player1.score);
        outtextxy(35,20,scrdisp);

        ///right score board.
        drawRect(323,11,619,49,LIGHTMAGENTA);
        setfillstyle(SOLID_FILL,LIGHTMAGENTA);
        floodfill(330,40,LIGHTMAGENTA);
        setbkcolor(LIGHTMAGENTA);
        setcolor(LIGHTGREEN);
        sprintf(scrdisp,"Score:%d",player2.score);
        outtextxy(350,20,scrdisp);
    }

    void ballPosition()
    {
        setfillstyle(SOLID_FILL,ballColor);
        drawCircle(ballX,ballY,10,ballBorderColor); ///ball for game
        floodfill(ballX,ballY,ballBorderColor);
    }

    void playerBatPosition()
    {
        drawLine(player1.x,player1.y0,player1.x,player1.y1,player1.color);
        drawLine(player2.x,player2.y0,player2.x,player2.y1,player2.color);
    }


    void setBackground()
    {
        setfillstyle(SOLID_FILL,background);
        drawRect(0,0,getmaxx(),getmaxy(),RED);
        floodfill(getmaxx()/2,getmaxy()/2,RED);

        drawRect(20,60,620,470,WHITE); ///white line.
    }

    void updateScreenActivity()
    {
        playerBatPosition();
    }


    void startPlaying()
    {
        do
        {
            keyPressed = _getch();
            if(keyPressed == 'w')
            {
                if(player1.y0 > 60)
                {
                    drawLine(player1.x,player1.y0,player1.x,player1.y1,background);
                    player1.y0-=5;
                    player1.y1-=5;
                }
            }
            else if(keyPressed == 's')
            {
                if(player1.y1 < 470)
                {
                    drawLine(player1.x,player1.y0,player1.x,player1.y1,background);
                    player1.y0+=5;
                    player1.y1+=5;
                }
            }

            if(keyPressed == 't')
            {
                if(player2.y0 > 60)
                {
                    drawLine(player2.x,player2.y0,player2.x,player2.y1,background);
                    player2.y0-=5;
                    player2.y1-=5;
                }
            }
            else if(keyPressed == 'g')
            {
                if(player2.y1 < 470)
                {
                    drawLine(player2.x,player2.y0,player2.x,player2.y1,background);
                    player2.y0+=5;
                    player2.y1+=5;
                }
            }
            updateScreenActivity();
        }
        while(keyPressed != 'q');
    }


    ///-------------------Threading call --------------///


    void clearPreviousPositionOfBall()
    {
        setfillstyle(SOLID_FILL,background);
        drawCircle(ballX,ballY,10,background); ///ball for game
        floodfill(ballX,ballY,background);
    }


    void makeScoreIncreamentAndDisplay()
    {
        if(ballX == 41)
        {
            if( ballY >= player1.y0 && ballY <= player1.y1 )
            {
                player1.score++;
                sprintf(scrdisp,"Score:%d",player1.score);
                setbkcolor(CYAN);
                outtextxy(35,20,scrdisp);
                /***
                Uncomment this to understand.
                cout<<"Player 1 good"<<endl;
                getch();
                */
            }
            else
            {

                ///cout<<"Player 1 bad"<<endl; uncomment
            }
        }

        if(ballX == 589)
        {
            if( ballY >= player2.y0 && ballY <= player2.y1 )
            {
                player2.score++;
                sprintf(scrdisp,"Score:%d",player2.score);
                setbkcolor(LIGHTMAGENTA);
                outtextxy(350,20,scrdisp);
                /***
                uncomment
                cout<<"Player 2 good"<<endl;
                getch();
                */
            }
            else
            {
                ///cout<<"Player 2 bad"<<endl; uncomment

            }
        }

    }

    void checkBallPosition()  ///checks whether the ball is at left or right.
    {
        if(ballX==41)
        {
            ballAtRight = false;
            ballAtLeft = true;
        }
        else if(ballX == 589)
        {
            ballAtLeft = false;
            ballAtRight = true;
        }

        if(ballY == 71)
        {
            ballAtBottom = false;
            ballAtTop = true;
        }
        else if(ballY == 609 || ballY   == 130)
        {
            ballAtTop = false;
            ballAtBottom = true;
        }
    }

    void makeMovementPrediction()
    {
        if(ballAtLeft)
        {
            ballX+=1;
        }
        else if(ballAtRight)
        {
            ballX-=1;
        }

        if(ballAtTop)
        {
            ballY += 1;
        }
        else if(ballAtBottom)
        {
            ballY -=1;
        }
    }

    void startBallMovement()
    {
        while(true)
        {
            clearPreviousPositionOfBall(); ///clearing the previous position of ball.
            checkBallPosition(); /// check where the ball is.
            makeMovementPrediction(); /// based on user's strategy make movement prediction.
            ballPosition(); ///used to update the position of ball.
            makeScoreIncreamentAndDisplay(); ///upgrade the score of the player.
            delay(2); /// used to delay the frame update.
        }
    }
    ///-----------------------------------------------///


public:
    game()
    {
        cleardevice();
        initializeData();
        setBackground();
        displayScoreBoard();
        playerBatPosition();
        ballPosition();

        /// starting the thread which maintains the ball movements.
        t1 = new thread([this]() ///similar to the lambda expression in JAVA.
        {
            startBallMovement();
        });

        /** reference at
        https://stackoverflow.com/questions/48878005/creating-a-thread-inside-the-class-in-c/48878172#48878172
        */

        /// actual simulation starts from here. Game play.
        startPlaying();
    }

    ~game()
    {
        if(t1 != nullptr)
        {
            t1 -> join(); ///wait till the main thread stops.
            delete t1;
        }
    }
};
class Screen: protected gameObjects
{
    game* start;

    /// initializing the class variable without initializing the object.
    /// reference at https://stackoverflow.com/questions/800368/declaring-an-object-before-initializing-it-in-c.
private:
    void displayScreenMessage()
    {
        setbkcolor(BLUE); ///background color for text.
        setcolor(YELLOW);
        outtextxy(185,50,"WELCOME TO PONG GAME !!");
        setcolor(RED);
        outtextxy(150,70," DEVELOPED IN COLLABORATION WITH: ");
        setcolor(GREEN);
        outtextxy(200,90," DIPESH LAMICHANE ");
        outtextxy(205,110," KHAGENDRA SAUD ");
        outtextxy(200,130," PADAM SHARMA AND ");
        outtextxy(210,150," SURYA BHUSAL ");
    }

    void loadingAnimation()
    {
        char loadingText[10]; ///display text by the side of loading.
        setcolor(YELLOW);
        drawRect(199,399,401,421,YELLOW);
        int i = 0;
        for(i = 0; i<=200; i++)
        {
            setcolor(GREEN);
            setfillstyle(SOLID_FILL,GREEN);
            drawRect(200,400,200+i,420,GREEN);
            floodfill(200+i/2,410,GREEN);
            /// for displaying the percentage of load by the side.
            sprintf(loadingText,"%d'%'",i/2);
            outtextxy(405,402,loadingText);
            delay(10);
        }
        setcolor(RED);
        outtextxy(120,425,"Please press any key to continue or c to see control keys.");
    }

    void displayControllScreen()
    {
        cleardevice();
        setBackground();
        setbkcolor(BLUE);
        setcolor(GREEN);
        outtextxy(250,20," CONTROLL KEYS  ");

        setcolor(BLACK);
        outtextxy(100,100,"LEFT -- PLAYER");
        setcolor(3);
        outtextxy(100,150,"A -> Upward");
        outtextxy(100,200,"D -> Downward");

        drawLine(270,70,270,300,RED);

        setcolor(YELLOW);
        outtextxy(350,100,"RIGHT -- PLAYER");
        setcolor(6);
        outtextxy(350,150,"T -> UPWARD");
        outtextxy(350,200,"G -> DOWNWARD");

        setcolor(RED);
        outtextxy(100,450,"Please press any key to continue game else q to close.");

        if(_getch()=='q')
        {
            exit(0);
        }
        else
        {
            start = new game(); /// assigning the new object to the class variable type.
        }
    }

    void setBackground()
    {
        setfillstyle(SOLID_FILL,background);
        drawRect(0,0,getmaxx(),getmaxy(),RED);
        floodfill(getmaxx()/2,getmaxy()/2,RED);
    }
public:
    Screen()
    {
        setBackground();
        displayScreenMessage();
        loadingAnimation();
    }

    void screenSwitchingController(char inp)
    {
        if(inp =='c')
        {
            displayControllScreen();
        }
        else
        {
            // game starts from here.
            start = new game(); /// assigning the new object to the class variable type.
        }
    }
};
int main()
{
    char input;
    int gd = DETECT,gm = DETECT;
    initgraph(&gd,&gm,"");
    Screen sc;
    input = _getch();
    sc.screenSwitchingController(input);
    getch();
}
