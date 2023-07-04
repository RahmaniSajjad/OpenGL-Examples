#include <GL/glut.h>

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
}

// Function to handle rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glLoadIdentity(); // Reset transformations

    // Draw a cube
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, 0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.2, -0.2);
    glEnd();

    glPopMatrix();

    // Draw a sphere
    glPushMatrix();
    glutSolidSphere(0.2, 100, 10);
    glPopMatrix();

    // Draw a triangle
    glPushMatrix();
    glTranslatef(-0.5, -0.5, 0.0);

    glBegin(GL_POLYGON);
    glVertex2f(-0.2, -0.2);
    glVertex2f(0.0, 0.4);
    glVertex2f(0.2, -0.2);
    glEnd();

    glPopMatrix();

    glFlush();
    glutSwapBuffers(); // Swap the front and back buffers to display the rendered image
}

// Function to calculate and update data
void calculateData(int id) {
    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
    glutTimerFunc(50, calculateData, 0); // Set a timer to call calculateData function after 50 milliseconds
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set the display mode
    glutInitWindowSize(500, 500); // Set the initial window size
    glutInitWindowPosition(500, 100); // Set the initial window position
    glutCreateWindow("Name"); // Create a window with the specified title
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    init(); // Initialize OpenGL settings
    glutDisplayFunc(display); // Register the display function
    calculateData(0); // Start the data calculation process
    glutMainLoop(); // Enter the event processing loop
    return 0;
}
