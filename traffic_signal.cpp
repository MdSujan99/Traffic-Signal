#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
//declarations
float zb_h= 200;
float zb_w= 40;
void myInit();
void myDraw();
void myReshape(int, int);
void drawSquare(float, float, float, float, float, float);
void drawSquare(float, float, float, float, float, float);
void drawRect(float, float, float, float, float, float, float);
void drawZebraCrossing(int, float, float);
void drawCar(float, float, float, float, float, float, float);

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(1920,1080);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Traffic Signal");

    glutDisplayFunc(myDraw);
    glutReshapeFunc(myReshape);
    myInit();

	glutMainLoop();

	return 0;
}

void myInit()
{
    glClearColor(.4,.4,.4,1);
}


void myDraw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

//draw

    //road
    drawRect(-360,-540,700,1080,0,0,0);

    //zebra crossing
    drawZebraCrossing(5,-330,-100);
    //drawRect(-310,-100,zb_w,zb_h,1,1,1);
    //drawRect(-280,-100,zb_w,zb_h,1,1,1);

    //car
    drawCar(-160,-500,200,100,1,1,0);
    //signal post
    drawRect(390,0,30,370,1,0,1);
    glBegin(GL_TRIANGLES);
        glVertex2f(380,0);
        glVertex2f(405,50);
        glVertex2f(430,0);
    glEnd();
    //signals box
    drawRect(160,280,185,65,1,0,1);
    drawSquare(345,290,50,1,0,1);

    //signals red,green,yellow
    //red
    drawSquare(165,285,55,1,0,0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
        glVertex2f(165,285);
        glVertex2f(165,340);
        glVertex2f(220,340);
        glVertex2f(220,285);
    glEnd();
    //green
    drawSquare(225,285,55,0,1,0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
        glVertex2f(225,285);
        glVertex2f(225,340);
        glVertex2f(280,340);
        glVertex2f(280,285);
    glEnd();
    //yellow
    drawSquare(285,285,55,1,1,0);
    glBegin(GL_LINE_LOOP);
    glColor3f(0,0,0);
        glVertex2f(285,285);
        glVertex2f(285,340);
        glVertex2f(340,340);
        glVertex2f(340,285);
    glEnd();

    //guide line
    glBegin(GL_LINES);
    glColor3f(0,1,0);
        glVertex2f(0,-540);
        glVertex2f(0,540);
        glVertex2f(-960,0);
        glVertex2f(960,0);
    glEnd();

    glFlush();
}

void myReshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-960,960,-540,540);
    glMatrixMode(GL_MODELVIEW);
}

void drawSquare(float x, float y, float length, float r, float g, float b)
{


    glBegin(GL_POLYGON);
        glColor3f(r,g,b);
        glVertex2f(x,y);
        glVertex2f(x,y+length);
        glVertex2f(x+length,y+length);
        glVertex2f(x+length,y);
    glEnd();
}


void drawRect(float x, float y, float length, float breadth, float r, float g, float b)
{
    //drawRect(-480, 480, 1080, 0,0,0 );
    glBegin(GL_POLYGON);
        glColor3f(r,g,b);
        glVertex2f(x,y);
        glVertex2f(x,y+breadth);
        glVertex2f(x+length,y+breadth);
        glVertex2f(x+length,y);
    glEnd();
}

void drawCar(float x, float y, float l, float b, float R, float G, float B)
{
    glBegin(GL_POLYGON);
        glColor3f(R,G,B);
        glVertex2f(x-20,y);//1
        glVertex2f(x,y+20);//2
        glVertex2f(x,y+l-20);//3
        glVertex2f(x-20,y+l);//4
        glVertex2f(x-b+20,y+l);//5
        glVertex2f(x-b,y+l-20);//6
        glVertex2f(x-b,y+20);//7
        glVertex2f(x-b+20,y);//8
    glEnd();
}

void drawZebraCrossing(int strips, float x, float y)//-310
 {
    int i=1;
    while(i<=strips)
    {
        drawRect(x,y,zb_w,zb_h,1,1,1);
        x = x + (3.85*zb_w);
        i++;
    }

}
//comment
/*



for( i = 1; i <= strips; i++ )
     {
         drawRect(x+(i*10), y, zb_w, zb_h, 1,1,1);
     }
*/


























