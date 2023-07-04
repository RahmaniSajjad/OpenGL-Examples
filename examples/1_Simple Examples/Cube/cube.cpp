#include <GL/glut.h>

GLfloat sign = 1;

GLfloat translate_x = 0;
GLfloat translate_y = 0;
GLfloat translate_z = 0;

GLfloat rotate_x = 50;
GLfloat rotate_y = 50;
GLfloat rotate_z = 0;

GLfloat scale_x = 1;
GLfloat scale_y = 1;
GLfloat scale_z = 1;

// Function to handle rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  // Reset transformations

    // Translate
    glTranslatef(translate_x, 0.0, 0.0);
    glTranslatef(0.0, translate_y, 0.0);
    glTranslatef(0.0, 0.0, translate_z);

    // Rotate
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    // Scale
    glScaled(scale_x, 1.0, 1.0);
    glScaled(1.0, scale_y, 1.0);
    glScaled(1.0, 1.0, scale_z);

    // Creating Cube
    // FRONT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.5, 0.5, -0.5);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-0.5, 0.5, -0.5);

    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // BACK
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 1.0);

    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);

    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);

    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

// Function to calculate and update data
void calculateData(int id) {
    // Translate
    // if (translate_x > 1 or translate_x < -1)
    //     sign *= -1;
    // translate_x += sign * 0.1f;

    // Rotate
    rotate_x += 5;
    rotate_y += 5;
    rotate_z += 5;

    // Scale
    // if (scale_x > 1 or scale_x < -1)
    //     sign *= -1;
    // scale_x += sign * 0.03f;

    glutPostRedisplay();
    glutTimerFunc(50, calculateData, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("Cube");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    calculateData(0);
    glutMainLoop();
    return 0;
}
