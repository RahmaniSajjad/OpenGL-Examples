#include<GL/glut.h>
#include "iostream"

float i = 7.0;

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.7, 0.6);  // رنگ مدنظر
    glRectf(-7.0, -7.0, i, 7.0);  // مختصات مستطیل
    glColor3f(1.0, 1.0, 1.0);
    glRectf(-4.0, -4.0, 4.0, 4.0);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(4.0, 4.0);
    glVertex2f(-7.0, 7.0);
    glVertex2f(-4.0, 4.0);
    glVertex2f(-7.0, -7.0);
    glEnd();
    glFlush();

}

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);  // مختصات مستطیل صفحه نمایش

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void calculateData(int id) {
    std::cout << "+";
    i += 0.01;
    display();

    glutTimerFunc(100, calculateData, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("example1");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    calculateData(0);
    glutMainLoop();
    return 0;
}