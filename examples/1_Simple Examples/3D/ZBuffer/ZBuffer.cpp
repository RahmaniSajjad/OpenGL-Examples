#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265
#define N 40.0

// Function to draw a circle at given (x, y, z) position with radius R
void drawCircle(float x, float y, float z, float R) {
    glBegin(GL_TRIANGLE_FAN);
    float t;
    int i;
    glVertex3f(x, y, z);  // Center of the circle
    for (i = 0; i <= N; ++i) {
        t = 2 * PI * i / N;
        glVertex3f(x + cos(t) * R, y + sin(t) * R, z);  // Points on the circle perimeter
    }
    glEnd();
}

// Display function
void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);  // Enable depth testing to handle overlapping circles

    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    drawCircle(50.0, 50.0, 0.0, 30.0);

    glColor3f(0.0, 1.0, 0.0);  // Set color to green
    drawCircle(50.0, 50.0, 0.2, 20.0);

    glColor3f(0.0, 0.0, 1.0);  // Set color to blue
    drawCircle(50.0, 50.0, 0.4, 10.0);

    glColor3f(1.0, 0.0, 1.0);  // Set color to magenta
    drawCircle(50.0, 50.0, 0.6, 5.0);

    glDisable(GL_DEPTH_TEST);  // Disable depth testing after rendering circles
    glFlush();  // Flush the buffer
}

// Resize function to handle window resizing
void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);  // Set the orthographic view

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set clear color to black
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("z buffer");
    glutDisplayFunc(Display);
    glutReshapeFunc(resize);
    init();
    glutMainLoop();
    return 0;
}
