#include <cstdio>
#include <GL/glut.h>

static int n = 0;
static long font = (long) GLUT_BITMAP_TIMES_ROMAN_24;

void writeBitmapString(void *font, char *string) {
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void floatToString(char *destStr, int p, float v) {
    sprintf(destStr, "%f", v);
}

void drawWorldAxes() {
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-300.0, 0.0);
    glVertex2f(300.0, 0.0);
    glVertex2f(0.0, -300.0);
    glVertex2f(0.0, 300.0);
    glEnd();
}

void writeFixedMessages() {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(190.0, 90.0, 0.0);
    writeBitmapString((void *) font, "draw ");

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(190.0, 110.0, 0.0);
    writeBitmapString((void *) font, "translate");
    glRasterPos3f(190, 130.0, 0.0);
    writeBitmapString((void *) font, "rotate");

    glRasterPos3f(190, 150.0, 0.0);
    writeBitmapString((void *) font, "scale");
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    writeFixedMessages();
    drawWorldAxes();

    glLoadIdentity();
    switch (n) {
        case 4:  // scale
            glColor3f(0.0, 0.0, 1.0);
            glPushMatrix();
            glLoadIdentity();
            glRasterPos3f(190.0, 150.0, 0.0);
            writeBitmapString((void *) font, "scale!");
            glPopMatrix();
            glLoadIdentity();
            glScalef(-0.5, 1.0, 1.0);
            glRecti(50, 100, 150, 150);
        case 3:  // rotate
            glColor3f(0.0, 1.0, 0.0);
            glPushMatrix();
            glLoadIdentity();
            glRasterPos3f(190.0, 130.0, 0.0);
            writeBitmapString((void *) font, "rotate!");
            glPopMatrix();
            glLoadIdentity();
            glRotatef(90, 0.0, 0.0, 1.0);
            glRecti(50, 100, 150, 150);
        case 2:  // translate
            glColor3f(1.0, 0.0, 0.0);
            glPushMatrix();
            glLoadIdentity();
            glRasterPos3f(190.0, 110.0, 0.0);
            writeBitmapString((void *) font, "translate!");
            glPopMatrix();
            glLoadIdentity();
            glTranslatef(-200.0, -50.0, 0.0);
            glRecti(50, 100, 150, 150);
        case 1:  // draw
            glColor3f(1.0, 0.0, 1.0);
            glLoadIdentity();
            glRasterPos3f(190.0, 90.0, 0.0);
            writeBitmapString((void *) font, "draw! ");
            glLoadIdentity();
            glRecti(50, 100, 150, 150);
        case 0:  // empty
            glFlush();
        default:
            break;
    }
}


void init() {
    glClearColor(0.7, 0.7, 0.7, 1.0);
}


void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300.0, 300.0, -300.0, 300.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void key2(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        n = n < 4 ? n + 1 : 0;
    }
    if (key == GLUT_KEY_DOWN) {
        n = n > 0 ? n - 1 : 4;
    }

    glutPostRedisplay();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("relativePlacement");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(key2);
    init();
    glutMainLoop();
    return 0;
}
