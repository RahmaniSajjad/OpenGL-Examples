#include <GL/glut.h>
#include <vector>

static int width, height;

class point {
public:
    point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void drawPoint() {
        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex3f(x, y, 0.0);
        glEnd();
    }

private :
    int x, y;
};

std::vector<point> points;
std::vector<point>::iterator pointit;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    pointit = points.begin();
    while (pointit != points.end()) {
        pointit->drawPoint();
        pointit++;
    }

    glFlush();
}

void mouseControl(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        points.push_back(point(x, height - y));

    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && !points.empty())
        points.pop_back();

    glutPostRedisplay();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, w, -1.0, 1.0);
    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutCreateWindow("paint");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouseControl);
    glutMainLoop();
    return 0;
}
