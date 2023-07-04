#include <GL/glut.h>
#include <cmath>

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

// Function to draw the shape
void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    int N = 360;
    float Dtheta = 2 * 3.1415926 / N;
    float angle = 0.0;
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 1, 0);
    for (int i = 0; i <= N; i++) {
        float angle = i * Dtheta;
        float r = cos(2 * angle);

        glVertex2f(r * cos(angle), r * sin(angle));
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Example");
    init();
    glutDisplayFunc(draw);

    glutMainLoop();
    return 0;
}
