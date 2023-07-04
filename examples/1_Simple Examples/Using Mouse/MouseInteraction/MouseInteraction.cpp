#include <GL/glut.h>
#include <cstdio>

static float r = 1.0, g = 0.0, b = 0.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex3f(20.0, 20.0, 0.0);
    glVertex3f(80.0, 20.0, 0.0);
    glVertex3f(80.0, 80.0, 0.0);
    glVertex3f(20.0, 80.0, 0.0);
    glEnd();

    glFlush();
}

void mouseControl(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                r = 0.0;
                g = 1.0;
                b = 0.0;
            } else if (state == GLUT_UP) {
                r = 1.0;
                g = 0.0;
                b = 0.0;
            }
            break;
        default:
            break;
    }
    printf("x = %d | y = %d\n", x, y);
    glutPostRedisplay();  // Notify GLUT that the window needs to be redrawn
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("mouse using");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseControl);
    glutMainLoop();
    return 0;
}
