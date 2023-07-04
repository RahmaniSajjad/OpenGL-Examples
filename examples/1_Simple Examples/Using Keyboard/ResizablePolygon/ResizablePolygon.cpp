#include <GL/glut.h>
#include <cmath>

int n = 10;  // Initial number of sides
float x = 0.0, y = 0.0;
float r = 1.0;
float t;

void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++) {
        glVertex2f(x + r * cos(t), y + r * sin(t));
        t += 2 * 3.14 / n;
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            n++;  // Increase the number of sides
            break;
        case GLUT_KEY_DOWN:
            if (n > 0)
                n--;  // Decrease the number of sides if greater than zero
            break;
        default:
            break;
    }

    glutPostRedisplay();  // Notify GLUT that the window needs to be redrawn
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("keyboard using");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
