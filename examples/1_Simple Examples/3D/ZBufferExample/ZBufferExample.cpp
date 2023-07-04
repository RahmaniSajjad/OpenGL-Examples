#include <GL/glut.h>
#include<cmath>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int N = 360;
    float Delta = 2 * 3.1415926 / N;
    float r = 0.7;

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(cos(270 * Delta) * r + 0.5, sin(270 * Delta) * r + 0.5);
    glVertex2f(cos(270 * Delta) * r + 0.7, sin(270 * Delta) * r + 0.7);
    glVertex2f(0.7, -0.25);
    glVertex2f(0.5, -0.45);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1.5 * cos(180 * Delta) * r + 0.5, sin(180 * Delta) * r + 0.5);
    glVertex2f(1.5 * cos(180 * Delta) * r + 0.7, sin(180 * Delta) * r + 0.7);
    glVertex2f(-0.35, -0.25);
    glVertex2f(-0.55, -0.45);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    //glLineWidth(10);
    glBegin(GL_LINE_STRIP);
    for (int i = 180; i <= 270; i++) {
        float angle = i * Delta;
        glVertex2f(1.5 * cos(angle) * r + 0.5, sin(angle) * r + 0.5);
        glVertex2f(1.5 * cos(angle) * r + 0.7, sin(angle) * r + 0.7);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("example z buffer");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
