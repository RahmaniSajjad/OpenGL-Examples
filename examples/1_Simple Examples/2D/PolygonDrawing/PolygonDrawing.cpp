#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846

void init() {
    glClearColor(1.0, 0.0, 0.0, 0.0);  // Set clear color to red
}

int numVertex = 10;  // Number of vertices in the polygon
float x = 0.0, y = 0.0;  // Center coordinates of the polygon
float r = 1.0;  // Radius of the polygon
float t;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the buffer

    glBegin(GL_LINE_LOOP);  // Start drawing a line loop

    for (int i = 0; i < numVertex; i++) {
        glVertex2f(x + r * cos(t), y + r * sin(t));  // Calculate vertex position and add to the loop
        t += 2 * PI / numVertex;  // Increment angle for each vertex
    }

    glEnd();  // End drawing the line loop

    glFlush();  // Flush the buffer to display the polygon
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Polygon");
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
