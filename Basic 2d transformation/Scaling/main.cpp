#include<graphics.h>
class scalLine{
    int x1,y1,x2,y2;

    void drawLine(int color){
        setcolor(color);
        line(x1,y1,x2,y2);
    }

public:
    scalLine(int x1, int y1, int x2, int y2){
        this-> x1 = x1;
        this-> y1 = y1;
        this-> x2 = x2;
        this-> y2 = y2;
        drawLine(RED);
    }

    void scallingLine(int sX, int sY){
        x1 = x1*sX;
        y1 = y1*sY;
        x2 = x2*sX;
        y2 = y2*sY;
        drawLine(WHITE);
    }

};
int main(){
    int gd = DETECT, gm = DETECT;
    initgraph(&gd,&gm,"");
    scalLine l1(100,100,300,200);
    l1.scallingLine(2,2);
    getch();
}
