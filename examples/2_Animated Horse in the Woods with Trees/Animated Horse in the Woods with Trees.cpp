#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using  namespace std;

//variable declarations
int horseStatus = 0;

float horseX = 0;
float horseY = 0;

//text variables
int i, s, m, y; //i is loop variable, s is spacing, m is index var for msg[], y axis value
string ins[2] = { "B: START HORSE","E: STOP HORSE" };
string t; //temp string

//function declarations
void instructions();
void draw_background();
void draw_tree(int, int);
void draw_horse();

//keyboard entries
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'B':		//horse start
        case 'b':
            horseStatus = 1;
            break;
        case 'E':		//horse stop
        case 'e':
            horseStatus = 0;
            break;
        default:
            break;
    }
}

//displays instructions on screen
void instructions()
{
    m = 0;
    y = 700;
    s = 15;
    while (m < 2)
    {
        t = ins[m];
        for (i = 0; i < t.length(); i++)
        {
            glColor3f(0, 0, 0);
            glRasterPos2i((i * s) + 20, y);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, t.at(i));
        }
        m++;
        y = y - 20;
    }
}

void draw_background()
{
    glBegin(GL_POLYGON);		//rectangular background lower
    glColor3f(0.2, 0.4, 0.1);
    glVertex2i(0, 0);
    glVertex2i(1200, 0);
    glVertex2i(1200, 220);
    glVertex2i(0, 220);
    glEnd();

    glBegin(GL_POLYGON);		//rectangular background upper
    glColor3f(0.2, 0.6, 0.2);
    glVertex2i(0, 220);
    glVertex2i(1200, 220);
    glVertex2i(1200, 750);
    glVertex2i(0, 750);
    glEnd();
}

void draw_tree(int x, int y)
{
    glBegin(GL_POLYGON);		//rectangular trunk
    glColor3f(0.3, 0.2, 0.1);
    glVertex2i(0 + x, 0 + y);
    glVertex2i(0 + x, 120 + y);
    glVertex2i(20 + x, 120 + y);
    glVertex2i(20 + x, 0 + y);
    glEnd();

    glBegin(GL_POLYGON);		//triangle lower
    glColor3f(0.1, 0.2, 0.1);
    glVertex2i(x - 60, 120 + y);
    glVertex2i(x + 80, 120 + y);
    glVertex2i(x + 10, 230 + y);
    glEnd();

    glBegin(GL_POLYGON);		//triangle middle
    glColor3f(0.1, 0.2, 0.1);
    glVertex2i(x - 40, 190 + y);
    glVertex2i(x + 60, 190 + y);
    glVertex2i(x + 10, 300 + y);
    glEnd();

    glBegin(GL_POLYGON);		//triangle upper
    glColor3f(0.1, 0.2, 0.1);
    glVertex2i(x - 20, 260 + y);
    glVertex2i(x + 40, 260 + y);
    glVertex2i(x + 10, 360 + y);
    glEnd();
}

void draw_horse()
{
    int x = 400; //vary x to position the horse in diff. locations along the horizontal axis

    //front leg
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(100 + x, 200);
    glVertex2i(110 + x, 200);
    glVertex2i(110 + x, 250);
    glVertex2i(100 + x, 250);
    glEnd();

    //back leg
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(190 + x, 200);
    glVertex2i(180 + x, 200);
    glVertex2i(180 + x, 250);
    glVertex2i(190 + x, 250);
    glEnd();

    //body
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.3, 0.1);
    glVertex2i(100 + x, 250);
    glVertex2i(190 + x, 250);
    glVertex2i(190 + x, 300);
    glVertex2i(100 + x, 300);
    glEnd();

    //neck and face
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.3, 0.1);
    glVertex2i(120 + x, 300);
    glVertex2i(90 + x, 390);
    glVertex2i(60 + x, 330);
    glVertex2i(60 + x, 350);
    glVertex2i(80 + x, 350);
    glVertex2i(100 + x, 300);
    glEnd();

    //mane
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(150 + x, 300);
    glVertex2i(90 + x, 390);
    glVertex2i(120 + x, 300);
    glVertex2i(150 + x, 300);
    glEnd();

    //muscle
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2i(70 + x, 325);
    glVertex2i(70 + x, 351);
    glVertex2i(72 + x, 352);
    glVertex2i(72 + x, 324);
    glEnd();

    //tail
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(190 + x, 300);
    glVertex2i(190 + x, 300);
    glVertex2i(200 + x, 220);
    glVertex2i(210 + x, 300);
    glEnd();

    //eye
    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2i(85 + x, 360);
    glEnd();

}

//movement of horse along x axis in negative direction
void horse()
{
    if (horseStatus == 1)
    {
        horseX -= .3; //speed
    }
    if (horseX < -600) //if posn exceeds then reposn
    {
        horseX = +600;
    }

    glPushMatrix();
    glTranslatef(horseX, horseY, 0); //translation
    draw_horse();					//horse is redrawn
    glPopMatrix();
}
//
//
//
//
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1200.0, 0.0, 750.0);
}

void myDisplay(void)
{
    draw_background();
    instructions();
    //trees behind horse
    draw_tree(700, 220);
    draw_tree(900, 300);
    draw_tree(1100, 260);
    horse();
    //trees infornt of horse
    draw_tree(200, 0);
    draw_tree(500, 0);
    glFlush();
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1150, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Horse in the Woods");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(myDisplay);
    init();
    glutMainLoop();

    return 0;
}