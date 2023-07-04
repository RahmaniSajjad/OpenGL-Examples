#include "cstdio"
#include <cmath>
#include <GL/glut.h>

// -----------------------
static int leftHigherLegAngle = -90, rightHigherLegAngle = -90;
static int leftLowerLegAngle = 0, rightLowerLegAngle = 0;
static int leftHigherARMAngle = -90, rightHigherARMAngle = -90;
static int leftLowerARMAngle = 0, rightLowerARMAngle = 0;
static int leftFootAngle = 0, rightFootAngle = 0;

static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
static GLint vangle = 90;

static double lookatx = 3.5, lookatz = 3.5, lookaty = 0;
static int scrw, scrh;
// -----------------------

// -----------------------
#define GLOBAL_SIZE 0.5
#define LEG_XSCALE 2.0
#define LEG_YSCALE 0.5
#define LEG_ZSCALE 0.5
#define BODY_XSCALE 0.5
#define BODY_YSCALE (LEG_XSCALE * 1.05)
#define BODY_ZSCALE 1.45
#define HEAD_RADIUS GLOBAL_SIZE * BODY_XSCALE
#define ARM_XSCALE 1.5
#define ARM_YSCALE (LEG_YSCALE - 0.15)
#define ARM_ZSCALE (LEG_ZSCALE - 0.15)
#define FOOT_XSCALE 1.0
#define FOOT_YSCALE 0.15
#define FOOT_ZSCALE LEG_ZSCALE
#define GROUND_LENGTH_SCALE 7500
// -----------------------

// -----------------------
const static double PI = M_PI;
const static int lineNUM = 2000;
const static double lineGap = GROUND_LENGTH_SCALE / lineNUM;


GLUquadricObj *quadratic;
// -----------------------

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);
}


void drawSolidCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int part = 200;
    GLfloat TWOPI = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= part; ++i) {
        glVertex2f(x + radius * cos(i * TWOPI / part), y + radius * sin(i * TWOPI / part));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0784, 0.2000, 0.2705);
    for (int i = 0; i < lineNUM; ++i) {

        glBegin(GL_LINES);
        glVertex3f(-GROUND_LENGTH_SCALE / 2 + lineGap * i, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE,
                   GROUND_LENGTH_SCALE / 2);
        glVertex3f(-GROUND_LENGTH_SCALE / 2 + lineGap * i, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE,
                   -GROUND_LENGTH_SCALE / 2);
        glEnd();

        glBegin(GL_LINES);
        glVertex3f(-GROUND_LENGTH_SCALE / 2, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE,
                   -GROUND_LENGTH_SCALE / 2 + lineGap * i);
        glVertex3f(GROUND_LENGTH_SCALE / 2, -GLOBAL_SIZE * LEG_XSCALE * 2 - GLOBAL_SIZE * FOOT_YSCALE,
                   -GROUND_LENGTH_SCALE / 2 + lineGap * i);
        glEnd();
    }

    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(vangle, 0.0, 1.0, 0.0);

    // Left LegAngle
    glColor3f(0.0000, 0.4549, 0.4549);
    glPushMatrix();
    glRotatef((GLfloat) leftHigherLegAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, GLOBAL_SIZE * LEG_ZSCALE);
    glPushMatrix();
    glScalef(LEG_XSCALE, LEG_YSCALE, LEG_ZSCALE);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);

    // (Joint of Left LegAngle)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE / 2);
    gluCylinder(quadratic, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_ZSCALE, 32,
                32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, GLOBAL_SIZE * LEG_ZSCALE / 2);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
    glPopMatrix();
    glRotatef((GLfloat) leftLowerLegAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
    glPushMatrix();
    glScalef(LEG_XSCALE, LEG_YSCALE - 0.05, LEG_ZSCALE - 0.05);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();

    // Left Foot
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glTranslatef(-GLOBAL_SIZE * FOOT_XSCALE / 2 + GLOBAL_SIZE * LEG_YSCALE / 2, 0.0, 0.0);
    glRotatef((GLfloat) leftFootAngle, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(FOOT_XSCALE, FOOT_YSCALE, FOOT_ZSCALE - 0.05);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glPopMatrix();

    // Right LegAngle
    glPushMatrix();
    glRotatef((GLfloat) rightHigherLegAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, -GLOBAL_SIZE * LEG_ZSCALE);
    glPushMatrix();
    glScalef(LEG_XSCALE, LEG_YSCALE, LEG_ZSCALE);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);

    // (Joint of Right LegAngle)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE / 2);
    gluCylinder(quadratic, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_YSCALE / 2, GLOBAL_SIZE * LEG_ZSCALE, 32,
                32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, GLOBAL_SIZE * LEG_ZSCALE / 2);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * LEG_ZSCALE);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * LEG_YSCALE / 2);
    glPopMatrix();
    glRotatef((GLfloat) rightLowerLegAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
    glPushMatrix();
    glScalef(LEG_XSCALE, LEG_YSCALE - 0.05, LEG_ZSCALE - 0.05);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();

    // Right Foot
    glTranslatef(GLOBAL_SIZE * LEG_XSCALE / 2, 0.0, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glTranslatef(-GLOBAL_SIZE * FOOT_XSCALE / 2 + GLOBAL_SIZE * LEG_YSCALE / 2, 0.0, 0.0);
    glRotatef((GLfloat) rightFootAngle, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(FOOT_XSCALE, FOOT_YSCALE, FOOT_ZSCALE - 0.05);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glPopMatrix();

    // Body
    glColor3f(0.0784, 0.7647, 0.5568);
    glPushMatrix();
    glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE / 2, 0.0);
    glScalef(BODY_XSCALE, BODY_YSCALE, BODY_ZSCALE);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glColor3f(0.0000, 0.4549, 0.4549);
    glPushMatrix();
    glTranslatef(0, -GLOBAL_SIZE * BODY_YSCALE / 2 + 0.4, 0.0);
    glScalef(BODY_XSCALE - 0.1, 0.5, 0.5);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();

    // Head
    glColor3f(0.8980, 0.7960, 0.6235);
    glPushMatrix();
    glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE + HEAD_RADIUS, 0.0);
    glutSolidSphere(HEAD_RADIUS, 10, 8);
    glPopMatrix();

    // Left Arm
    glColor3f(0.9215, 0.6745, 0.3294);
    glPushMatrix();
    glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE, 0.0);
    glRotatef((GLfloat) leftHigherARMAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * ARM_XSCALE / 2 + 0.03, 0.0, GLOBAL_SIZE * (BODY_ZSCALE + ARM_ZSCALE) / 2);

    // (Higher Joint of Left Arm)
    glPushMatrix();
    glTranslatef(-0.35, 0.0, -GLOBAL_SIZE * ARM_ZSCALE / 2);
    gluCylinder(quadratic, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_ZSCALE, 32,
                32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.35, 0.0, GLOBAL_SIZE * ARM_ZSCALE / 2);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * ARM_ZSCALE);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glPopMatrix();
    glPushMatrix();
    glScalef(ARM_XSCALE, ARM_YSCALE, ARM_ZSCALE);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glTranslatef(GLOBAL_SIZE * ARM_XSCALE / 2, 0.0, 0.0);

    // (Medium Joint of Left Arm)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * ARM_ZSCALE / 2);
    gluCylinder(quadratic, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_ZSCALE, 32,
                32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, GLOBAL_SIZE * ARM_ZSCALE / 2);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * ARM_ZSCALE);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glPopMatrix();
    glRotatef((GLfloat) leftLowerARMAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * ARM_XSCALE / 2, 0.0, 0.0);
    glPushMatrix();
    glScalef(ARM_XSCALE, ARM_YSCALE - 0.02, ARM_ZSCALE - 0.02);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE, 0.0);
    glRotatef((GLfloat) rightHigherARMAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * ARM_XSCALE / 2 + 0.03, 0.0, -GLOBAL_SIZE * (BODY_ZSCALE + ARM_ZSCALE) / 2);

    // (Higher Joint of Right Arm)
    glPushMatrix();
    glTranslatef(-0.35, 0.0, -GLOBAL_SIZE * ARM_ZSCALE / 2);
    gluCylinder(quadratic, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_ZSCALE, 32,
                32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.35, 0.0, GLOBAL_SIZE * ARM_ZSCALE / 2);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * ARM_ZSCALE);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glPopMatrix();
    glPushMatrix();
    glScalef(ARM_XSCALE, ARM_YSCALE, ARM_ZSCALE);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glTranslatef(GLOBAL_SIZE * ARM_XSCALE / 2, 0.0, 0.0);

    // (Medium Joint of Right Arm)
    glPushMatrix();
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * ARM_ZSCALE / 2);
    gluCylinder(quadratic, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_YSCALE / 2, GLOBAL_SIZE * ARM_ZSCALE, 32,
                32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, GLOBAL_SIZE * ARM_ZSCALE / 2);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glTranslatef(0.0, 0.0, -GLOBAL_SIZE * ARM_ZSCALE);
    drawSolidCircle(0.0, 0.0, GLOBAL_SIZE * ARM_YSCALE / 2);
    glPopMatrix();

    glRotatef((GLfloat) rightLowerARMAngle, 0.0, 0.0, 1.0);
    glTranslatef(GLOBAL_SIZE * ARM_XSCALE / 2, 0.0, 0.0);
    glPushMatrix();
    glScalef(ARM_XSCALE, ARM_YSCALE - 0.02, ARM_ZSCALE - 0.02);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    scrw = w;
    scrh = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
}

void passiveMotionFunc(int x, int y) {
    lookatx = -5.0 + (double) x / scrw * 10.0;
    lookatz = sqrt(25 - lookatx * lookatx) + centerZ;
    lookatx += centerX;
    double tmpy = -5.0 + (double) y / scrh * 10.0;
    if (tmpy >= -GLOBAL_SIZE * LEG_XSCALE * 2)
        lookaty = tmpy;

    glLoadIdentity();
    gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    //printf("%d", key);
    switch (key) {
        case '4':    //counter-clockwise rotating
            vangle = (vangle + 1) % 360;
            break;
        case '6':    //clockwise rotating
            vangle = (vangle - 1) % 360;
            break;

        case 's':    // 180 rotation
            vangle = (vangle + 180) % 360;
            break;
        case 'a':    // 90 rotation
            vangle = (vangle + 90) % 360;
            break;
        case 'd':    // -90 rotation
            vangle = (vangle + 270) % 360;
            break;

        default:
            break;
    }
}

void calculateData(int id) {

    // Change body coordinates
    leftHigherARMAngle -= 0;
    rightHigherARMAngle += 0;

    leftLowerARMAngle -= 0;
    rightLowerARMAngle += 0;

    leftHigherLegAngle += 0;
    rightHigherLegAngle += 0;

    leftLowerLegAngle += 0;
    rightLowerLegAngle += 0;

    leftFootAngle += 0;
    rightFootAngle += 0;

    centerX += 0;
    centerY += 0;
    centerZ += 0;

    vangle += 0;

    // Change camera coordinates
    lookatx += 0;
    lookaty += 0;
    lookatz += 0;

    glLoadIdentity();
    gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);

    glutPostRedisplay();
    glutTimerFunc(60, calculateData, 0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("Sajjad Rahmani Project");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passiveMotionFunc);
    calculateData(0);
    glutMainLoop();
    return 0;
}
