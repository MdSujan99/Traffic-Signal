#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
//declarations
float car_x = -160;
float car_y = -540;
float car_h = 200;
float car_w = 100;
int car_state = 0;//1->keep moving;-1->slow down;0->stop;
float zb_h= 200;
float zb_w= 40;
void myInit();
void timer(int);
void myDraw();
void keyboard(unsigned char c, int x, int y);
void myReshape(int w, int h) ;
void drawSquare(float x, float y, float s, float R, float G, float B);
void drawRect(float x, float y, float l, float b, float R, float G, float B);
void drawZebraCrossing(int n, float x, float y);
void drawCar(float x, float y, float R, float G, float B);
void drawSignalPost(float x, float y, float b, float h, float R, float G, float B);
void addText(char str[],float x, float y, float R, float G, float B);

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(1920,1080);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Traffic Signal");

    glutDisplayFunc(myDraw);
    glutReshapeFunc(myReshape);
    glutTimerFunc(1000,timer,0);
    myInit();

	glutMainLoop();

	return 0;
}
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
    float speed = 15;
    switch(car_state)
    {
        //green
        case 1  :   break;

        //yellow
        case -1 :   speed -= 12;
                    break;
        //red
        case 0  :   speed = 0;
                    break;
    }

    if(car_y <= 540)
        car_y += speed;
    else
        car_y = -540;
}

void myInit()
{
    glClearColor(.4,.4,.4,1);
}


void myDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //road
    drawRect(-360,-540,700,1080,0,0,0);

    //zebra crossing
    drawZebraCrossing(5,-330,-100);

    drawCar(car_x,car_y,1,1,0);

    drawSignalPost(400,0,30,370,.15,.15,.15);

    addText("Hello:-",350,-100,1,1,1);
    addText("Name : Md Sujan",350,-200,1,1,0);
    addText("Controls:-",350,-400,1,1,1);
    addText("R:(RED)/Stop",350,-430,1,1,1);
    addText("Y:(YELLOW)/Slow Down",350,-460,1,1,1);
    addText("G:(GREEN)/Keep Going",350,-490,1,1,1);
    /*
    glBegin(GL_LINES);
        glColor3f(0,1,0);
            glVertex2f(0,-540);
            glVertex2f(0,540);
            glVertex2f(-960,0);
            glVertex2f(960,0);
    glEnd();
    */

    glutSwapBuffers();
    glutKeyboardFunc(keyboard);

}

void keyboard(unsigned char key, int x, int y)
{
    if(key == 27)
        exit(0);
    if(key == 'r')
        car_state = 0;
    if(key == 'y')
        car_state = -1;
    if(key == 'g')
        car_state = 1;

}

void myReshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960,960,-540,540);
    glMatrixMode(GL_MODELVIEW);
}

void drawSquare(float x, float y, float length, float R, float G, float B)
{


    glBegin(GL_POLYGON);
        glColor3f(R,G,B);
        glVertex2f(x,y);
        glVertex2f(x,y+length);
        glVertex2f(x+length,y+length);
        glVertex2f(x+length,y);
    glEnd();
}


void drawRect(float x, float y, float length, float breadth, float R, float G, float B)
{
    //drawRect(-480, 480, 1080, 0,0,0 );
    glBegin(GL_POLYGON);
        glColor3f(R,G,B);
        glVertex2f(x,y);
        glVertex2f(x,y+breadth);
        glVertex2f(x+length,y+breadth);
        glVertex2f(x+length,y);
    glEnd();
}

void drawCar(float x, float y, float R, float G, float B)
{
    float l = car_h;
    float b = car_w;
    glBegin(GL_POLYGON);
        glColor3f(R,G,B);
        glVertex2f(x-20,y);//1
        glVertex2f(x,y+20);//2
        glVertex2f(x,y+l-10);//3
        glVertex2f(x-20,y+l);//4
        glVertex2f(x-b+20,y+l);//5
        glVertex2f(x-b,y+l-10);//6
        glVertex2f(x-b,y+20);//7
        glVertex2f(x-b+20,y);//8
    glEnd();
}
void drawZebraCrossing(int strips, float x, float y)
{
    int i=1;
    while(i<=strips)
    {
        drawRect(x,y,zb_w,zb_h,1,1,1);
        x = x + (3.85*zb_w);
        i++;
    }

}
void addText(char str[], float x, float y, float R, float G, float B)
{
    int i;
    for(i=0;i<strlen(str);i++)
    {
        glColor3f(R,G,B);
        glRasterPos2d(x,y);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        glRasterPos2d(x+20,y);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
        x += 20;
    }
}
void drawSignalPost(float x, float y, float b, float h, float R, float G, float B)
{
    //top
    glBegin(GL_POLYGON);
    glColor3f(R,G,B);
        glVertex2f(x,h);
        glVertex2f(x-15,h+30);
        glVertex2f(x+b+15,h+30);
        glVertex2f(x+b,h);
    glEnd();
    //post
    drawRect(x,y,b,h,R,G,B);
    //base
    glBegin(GL_TRIANGLES);
    glColor3f(R,G,B);
        glVertex2f(x-15,y);
        glVertex2f(x+b+15,y);
        glVertex2f(x+(b/2),y+30);
    glEnd();
    //signal box
    drawRect(x-20,y+(h/2)-5,b+40,h/2+5,.3,.3,.3);
    if(car_state == 1){
        //red
        drawSquare(x-15,y+(h/2)+2*b+60,b+30,.3,0,0);
        //green active
        drawSquare(x-15,y+(h/2),b+30,0,1,0);
        //yellow
        drawSquare(x-15,y+(h/2)+b+30,b+30,.4,.2,0);
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x-15,y+(h/2));
            glVertex2f(x-15,y+(h/2)+b+30);
            glVertex2f(x-15+60,y+(h/2)+b+30);
            glVertex2f(x-15+60,y+(h/2));
        glEnd();

    }
    else if(car_state == 0){
        //red active
        drawSquare(x-15,y+(h/2)+2*b+60,b+30,1,0,0.1);
        //green
        drawSquare(x-15,y+(h/2),b+30,0,.4,0);
        //yellow
        drawSquare(x-15,y+(h/2)+b+30,b+30,.4,.2,0);
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x-15,y+(h/2)+2*b+60);
            glVertex2f(x-15,y+(h/2)+2*b+60+60);
            glVertex2f(x-15+60,y+(h/2)+2*b+60+60);
            glVertex2f(x-15+60,y+(h/2)+2*b+60);
        glEnd();
    }
    else{
        //red
        drawSquare(x-15,y+(h/2)+2*b+60,b+30,.3,0,0);
        //green
        drawSquare(x-15,y+(h/2),b+30,0,.4,0);
        //yellow active
        drawSquare(x-15,y+(h/2)+b+30,b+30,1,.9,0);
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(x-15,y+(h/2)+b+30);
            glVertex2f(x-15,y+(h/2)+b+30+60);
            glVertex2f(x-15+60,y+(h/2)+b+30+60);
            glVertex2f(x-15+60,y+(h/2)+b+30);
        glEnd();
    }
}


























