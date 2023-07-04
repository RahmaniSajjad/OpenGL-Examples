#include <cmath>
#include <GL/glut.h>
#include "windows.h"
#include "iostream"

struct GeImageData {
    int width;
    int height;
    unsigned *bits;

    GeImageData(int w = 0, int h = 0, unsigned *p = 0) : width(w), height(h), bits(p) {}
};

// texture and glu data
GLUquadricObj *g_sphere = NULL;
GeImageData g_imgData;
GLuint g_img = 0;
GLfloat g_angle_x = 27.0f;
GLfloat g__inc = 0.0f;
char g_filename[128] = R"(G:\C++\opengl\map.rgb)";


GLdouble eqn1[4] = {0.0, 0.0, 1.0, 0.0};
GLfloat g_inc = 0.0f;

float x_light = 3.0;
float he = 4.7, het = 1;
static float ang = 0;
static int isAnimate = 0;
bool m = true;
static int spin = 0;
static long font = (long) GLUT_BITMAP_HELVETICA_18;

// change speed of walking
static int speed = 10;
static int MAX_SPEED = 50;
static int MIN_SPEED = 2;
// -----------------------

// -----------------------
static bool isPaused = true;
static bool isFullScreen = false;
// -----------------------

const int COLOR_COUNT = 11;

const float BODY_COLOR[][3] = {
        {0.0784, 0.7647, 0.5568},
        {0.8313, 0.9098, 0.9019},
        {0.4784, 0.8117, 0.5254},
        {1.0000, 1.0000, 1.0000},
        {0.0000, 0.4549, 0.4549},
        {0.9215, 0.6745, 0.3294},
        {0.9607, 0.8235, 0.7098},
        {0.0784, 0.2000, 0.2705},
        {0.9568, 0.7490, 0.7490},
        {0.6039, 0.5254, 0.6431},
        {0.8980, 0.7960, 0.6235}
};
int BODY_COLOR_index = 0;

const float HEAD_COLOR[][3] = {
        {0.8980, 0.7960, 0.6235},
        {0.0784, 0.7647, 0.5568},
        {0.5000, 0.5000, 0.5000},
        {0.0000, 0.4549, 0.4549},
        {0.9215, 0.6745, 0.3294},
        {0.9607, 0.8235, 0.7098},
        {0.0784, 0.2000, 0.2705},
        {0.8313, 0.9098, 0.9019},
        {0.4784, 0.8117, 0.5254},
        {0.9568, 0.7490, 0.7490},
        {0.6039, 0.5254, 0.6431}
};
int HEAD_COLOR_index = 0;

const float ARM_COLOR[][3] = {
        {0.9215, 0.6745, 0.3294},
        {0.5000, 0.5000, 0.5000},
        {0.0000, 0.4549, 0.4549},
        {0.9607, 0.8235, 0.7098},
        {0.0784, 0.2000, 0.2705},
        {0.8313, 0.9098, 0.9019},
        {0.4784, 0.8117, 0.5254},
        {0.9568, 0.7490, 0.7490},
        {0.0784, 0.7647, 0.5568},
        {0.6039, 0.5254, 0.6431},
        {0.8980, 0.7960, 0.6235}
};
int ARM_COLOR_index = 0;

const float LEG_COLOR[][3] = {
        {0.0000, 0.4549, 0.4549},
        {0.9607, 0.8235, 0.7098},
        {0.5000, 0.5000, 0.5000},
        {0.9215, 0.6745, 0.3294},
        {0.0784, 0.2000, 0.2705},
        {0.8313, 0.9098, 0.9019},
        {0.4784, 0.8117, 0.5254},
        {0.9568, 0.7490, 0.7490},
        {0.0784, 0.7647, 0.5568},
        {0.6039, 0.5254, 0.6431},
        {0.8980, 0.7960, 0.6235}
};
int LEG_COLOR_index = 0;

const float LINE_COLOR[][3] = {
        {0.0784, 0.2000, 0.2705},
        {0.0000, 0.4549, 0.4549},
        {0.8000, 0.8000, 0.8000},
        {0.9215, 0.6745, 0.3294},
        {0.9607, 0.8235, 0.7098},
        {0.8313, 0.9098, 0.9019},
        {0.4784, 0.8117, 0.5254},
        {0.9568, 0.7490, 0.7490},
        {0.0784, 0.7647, 0.5568},
        {0.6039, 0.5254, 0.6431},
        {0.8980, 0.7960, 0.6235}
};
int LINE_COLOR_index = 0;
// -----------------------

// -----------------------
#define GLOBAL_SIZE 0.5
#define LEG_XSCALE 2.0
#define LEG_YSCALE 0.5
#define LEG_ZSCALE 0.5
#define BODY_XSCALE 0.5
#define BODY_YSCALE LEG_XSCALE * 1.05
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
const static double PI = acos(-1.0);
const static int lineNUM = 2000;
const static double lineGap = GROUND_LENGTH_SCALE / lineNUM;

static int leftHigherLegAngle = -60, rightHigherLegAngle = -120;
static int leftLowerLegAngle = 0, rightLowerLegAngle = 0;
static int leftHigherARMAngle = -120, rightHigherARMAngle = -60;
static int leftLowerARMAngle = -60, rightLowerARMAngle = 0;
static int leftFootAngle = 0, rightFootAngle = 0;

static GLfloat centerX = 0.0, centerY = 0.0, centerZ = 0.0;
static GLint vangle = 90;

bool dir1 = false;
static const double legLength = 2 * GLOBAL_SIZE * LEG_XSCALE + GLOBAL_SIZE * FOOT_YSCALE;

GLUquadricObj *quadratic;

// -----------------------
void bwtorgba(unsigned char *b, unsigned char *l, int n) {
    while (n--) {
        l[0] = *b;
        l[1] = *b;
        l[2] = *b;
        l[3] = 0xff;
        l += 4;
        b++;
    }
}

void rgbtorgba(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *l, int n) {
    while (n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = 0xff;
        l += 4;
        r++;
        g++;
        b++;
    }
}

void rgbatorgba(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a, unsigned char *l, int n) {
    while (n--) {
        l[0] = r[0];
        l[1] = g[0];
        l[2] = b[0];
        l[3] = a[0];
        l += 4;
        r++;
        g++;
        b++;
        a++;
    }
}

typedef struct _ImageRec {
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short xsize, ysize, zsize;
    unsigned int min, max;
    unsigned int wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB;
    unsigned long rleEnd;
    unsigned int *rowStart;
    int *rowSize;
} ImageRec;

static void ConvertShort(unsigned short *array, unsigned int length) {
    unsigned short b1, b2;
    unsigned char *ptr;

    ptr = (unsigned char *) array;
    while (length--) {
        b1 = *ptr++;
        b2 = *ptr++;
        *array++ = (b1 << 8) | (b2);
    }
}

static void ConvertUint(unsigned *array, unsigned int length) {
    unsigned int b1, b2, b3, b4;
    unsigned char *ptr;

    ptr = (unsigned char *) array;
    while (length--) {
        b1 = *ptr++;
        b2 = *ptr++;
        b3 = *ptr++;
        b4 = *ptr++;
        *array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
    }
}

static ImageRec *ImageOpen(const char *fileName) {
    union {
        int testWord;
        char testByte[4];
    } endianTest;
    ImageRec *image;
    int swapFlag;
    int x;

    endianTest.testWord = 1;
    if (endianTest.testByte[0] == 1) {
        swapFlag = 1;
    } else {
        swapFlag = 0;
    }

    image = (ImageRec *) malloc(sizeof(ImageRec));
    if (image == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    if ((image->file = fopen(fileName, "rb")) == NULL) {
        perror(fileName);
        //exit(1);
        return NULL;
    }

    fread(image, 1, 12, image->file);

    if (swapFlag) {
        ConvertShort(&image->imagic, 6);
    }

    image->tmp = (unsigned char *) malloc(image->xsize * 256);
    image->tmpR = (unsigned char *) malloc(image->xsize * 256);
    image->tmpG = (unsigned char *) malloc(image->xsize * 256);
    image->tmpB = (unsigned char *) malloc(image->xsize * 256);
    if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
        image->tmpB == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    if ((image->type & 0xFF00) == 0x0100) {
        x = image->ysize * image->zsize * (int) sizeof(unsigned);
        image->rowStart = (unsigned *) malloc(x);
        image->rowSize = (int *) malloc(x);
        if (image->rowStart == NULL || image->rowSize == NULL) {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        image->rleEnd = 512 + (2 * x);
        fseek(image->file, 512, SEEK_SET);
        fread(image->rowStart, 1, x, image->file);
        fread(image->rowSize, 1, x, image->file);
        if (swapFlag) {
            ConvertUint(image->rowStart, x / (int) sizeof(unsigned));
            ConvertUint((unsigned *) image->rowSize, x / (int) sizeof(int));
        }
    }
    return image;
}

static void ImageClose(ImageRec *image) {
    fclose(image->file);
    free(image->tmp);
    free(image->tmpR);
    free(image->tmpG);
    free(image->tmpB);
    free(image);
}

static void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z) {
    unsigned char *iPtr, *oPtr, pixel;
    int count;

    if ((image->type & 0xFF00) == 0x0100) {
        fseek(image->file, (long) image->rowStart[y + z * image->ysize],
              SEEK_SET);
        fread(image->tmp, 1, (unsigned int) image->rowSize[y + z * image->ysize],
              image->file);

        iPtr = image->tmp;
        oPtr = buf;
        for (;;) {
            pixel = *iPtr++;
            count = (int) (pixel & 0x7F);
            if (!count) {
                return;
            }
            if (pixel & 0x80) {
                while (count--) {
                    *oPtr++ = *iPtr++;
                }
            } else {
                pixel = *iPtr++;
                while (count--) {
                    *oPtr++ = pixel;
                }
            }
        }
    } else {
        fseek(image->file,
              512 + (y * image->xsize) + (z * image->xsize * image->ysize),
              SEEK_SET);
        fread(buf, 1, image->xsize, image->file);
    }
}

unsigned *ge_read_rgb(const char *name, int *width, int *height, int *components) {
    unsigned *base, *lptr;
    unsigned char *rbuf, *gbuf, *bbuf, *abuf;
    ImageRec *image;
    int y;

    image = ImageOpen(name);

    if (!image)
        return NULL;
    (*width) = image->xsize;
    (*height) = image->ysize;
    (*components) = image->zsize;
    base = (unsigned *) malloc(image->xsize * image->ysize * sizeof(unsigned));
    rbuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    gbuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    bbuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    abuf = (unsigned char *) malloc(image->xsize * sizeof(unsigned char));
    if (!base || !rbuf || !gbuf || !bbuf)
        return NULL;
    lptr = base;
    for (y = 0; y < image->ysize; y++) {
        if (image->zsize >= 4) {
            ImageGetRow(image, rbuf, y, 0);
            ImageGetRow(image, gbuf, y, 1);
            ImageGetRow(image, bbuf, y, 2);
            ImageGetRow(image, abuf, y, 3);
            rgbatorgba(rbuf, gbuf, bbuf, abuf,
                       (unsigned char *) lptr, image->xsize);
            lptr += image->xsize;
        } else if (image->zsize == 3) {
            ImageGetRow(image, rbuf, y, 0);
            ImageGetRow(image, gbuf, y, 1);
            ImageGetRow(image, bbuf, y, 2);
            rgbtorgba(rbuf, gbuf, bbuf, (unsigned char *) lptr, image->xsize);
            lptr += image->xsize;
        } else {
            ImageGetRow(image, rbuf, y, 0);
            bwtorgba(rbuf, (unsigned char *) lptr, image->xsize);
            lptr += image->xsize;
        }
    }
    ImageClose(image);
    free(rbuf);
    free(gbuf);
    free(bbuf);
    free(abuf);

    return (unsigned *) base;
}

bool ge_read_image(const char *filename, GeImageData *pImgData) {
    int c;
    if (!filename || !pImgData)
        return false;

    // zero out the memory
    memset(pImgData, 0, sizeof(GeImageData));

    pImgData->bits = ge_read_rgb(filename, &pImgData->width,
                                 &pImgData->height, &c);

    return (pImgData->bits != 0);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);

    // set the front faces of polygons
    glFrontFace(GL_CCW);
    // set fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // material have diffuse and ambient lighting
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // enable color
    glEnable(GL_COLOR_MATERIAL);

    // initialize our sphere
    g_sphere = gluNewQuadric();
    gluQuadricNormals(g_sphere, (GLenum) GLU_SMOOTH);
    gluQuadricTexture(g_sphere, GL_TRUE);

    // set texture state
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // read the texture
    if (!ge_read_image(g_filename, &g_imgData)) {
        printf("couldn't open file '%s'...\n", g_filename);
        printf("usage: globe <filename>.rgb\n");
        exit(1);
    }

    // generate OpenGL texture
    glGenTextures(1, &g_img);
    glBindTexture(GL_TEXTURE_2D, g_img);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            g_imgData.width,
            g_imgData.height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            g_imgData.bits
    );
}

void writeBitmapString(void *font, char *string) {
    char *c;
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void light() {
    GLfloat position[] = {x_light, 4, 0, 1.0};

    glPointSize(20.0);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3fv(position);
    glEnd();

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    if (!spin)
        glDisable(GL_LIGHTING);
    else
        glEnable(GL_LIGHTING);
}

void mirror() {
    glVertex3f(5, 3, 0);
    glVertex3f(-5, 3, 0);
    glVertex3f(-5, -1, 0);
    glVertex3f(5, -1, 0);
}

void draw_leaf() {
    int N = 360;
    float Dtheta = 2 * 3.1415926 / N;
    float angle = 0.0;
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(0, 1, 0);
    for (int i = -90; i <= 90; i++) {
        float angle = i * Dtheta;
        glVertex3f(cos(angle) / 3, angle / 3 + 2, -49);
        glVertex3f(-cos(angle) / 3, angle / 3 + 2, -49);
    }
    for (int i = -90; i <= 90; i++) {
        float angle = i * Dtheta;
        glVertex3f(cos(angle) / 20, angle / 3 + 2, -49);
    }

    for (int i = -200; i <= -170; i++) {
        float angle = i * Dtheta;
        glVertex3f((cos(angle)) + 0.98, (angle / 3) + 2.46, -49);
    }
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    angle = 60 * Dtheta;
    glVertex3f(cos(angle) / 3, angle / 3 + 2, -49);
    angle = 35 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = 60 * Dtheta;
    glVertex3f(-cos(angle) / 3, angle / 3 + 2, -49);
    angle = 35 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = 35 * Dtheta;
    glVertex3f(cos(angle) / 3, angle / 3 + 2, -49);
    angle = 0 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = 35 * Dtheta;
    glVertex3f(-cos(angle) / 3, angle / 3 + 2, -49);
    angle = 0 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = 5 * Dtheta;
    glVertex3f(cos(angle) / 3, angle / 3 + 2, -49);
    angle = -35 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = 5 * Dtheta;
    glVertex3f(-cos(angle) / 3, angle / 3 + 2, -49);
    angle = -35 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = -35 * Dtheta;
    glVertex3f(cos(angle) / 3, angle / 3 + 2, -49);
    angle = -70 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    angle = -35 * Dtheta;
    glVertex3f(-cos(angle) / 3, angle / 3 + 2, -49);
    angle = -70 * Dtheta;
    glVertex3f(cos(angle) / 25, angle / 3 + 2, -49);
    glEnd();
}

void home() {
    glBegin(GL_QUADS);  // کف
    float a = 0.5, b = 0.5, c = 0.5, e = 1, f = 1, g = 1;
    for (float z = -80.0; z <= -55.0; z += 5.0) {
        for (float i = -10.0; i <= 6.0; i += 4.0) {
            glColor3f(a, b, c);
            glVertex3f(i, 0.01f, z);
            glVertex3f(i, 0.01f, z + 5);
            glVertex3f(i + 2, 0.01f, z + 5);
            glVertex3f(i + 2, 0.01f, z);
            glColor3f(e, f, g);
            glVertex3f(i + 2, 0.01f, z);
            glVertex3f(i + 2, 0.01f, z + 5);
            glVertex3f(i + 4, 0.01f, z + 5);
            glVertex3f(i + 4, 0.01f, z);
        }
        float temp = 0;
        temp = a;
        a = e;
        e = temp;
        temp = 0;
        temp = b;
        b = f;
        f = temp;
        temp = 0;
        temp = c;
        c = g;
        g = temp;
        temp = 0;
    }
    glEnd();

    glBegin(GL_POLYGON);  // سقف
    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(-10.0f, 10.0f, -80.0f);
    glVertex3f(-10.0f, 10.0f, -50.0f);
    glVertex3f(10.0f, 10.0f, -50.0f);
    glVertex3f(10.0f, 10.0f, -80.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex3f(-10.0f, 0.01f, -80.0f);
    glVertex3f(-10.0f, 10.0f, -80.0f);
    glVertex3f(10.0f, 10.0f, -80.0f);
    glVertex3f(10.0f, 0.01f, -80.0f);
    glVertex3f(-11.0f, 0.01f, -81.0f);
    glVertex3f(-11.0f, 10.0f, -81.0f);
    glVertex3f(11.0f, 10.0f, -81.0f);
    glVertex3f(11.0f, 0.01f, -81.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex3f(-10.0f, 0.01f, -80.0f);
    glVertex3f(-10.0f, 10.0f, -80.0f);
    glVertex3f(-10.0f, 10.0f, -50.0f);
    glVertex3f(-10.0f, 0.01f, -50.0f);
    glVertex3f(-11.0f, 0.01f, -81.0f);
    glVertex3f(-11.0f, 10.0f, -81.0f);
    glVertex3f(-11.0f, 10.0f, -49.0f);
    glVertex3f(-11.0f, 0.01f, -49.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 1, 1);
    glVertex3f(10.0f, 0.01f, -80.0f);
    glVertex3f(10.0f, 10.0f, -80.0f);
    glVertex3f(10.0f, 10.0f, -50.0f);
    glVertex3f(10.0f, 0.01f, -50.0f);
    glVertex3f(11.0f, 0.01f, -81.0f);
    glVertex3f(11.0f, 10.0f, -81.0f);
    glVertex3f(11.0f, 10.0f, -49.0f);
    glVertex3f(11.0f, 0.01f, -49.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2, 0.0, 0);
    glVertex3f(10.0f, 0.01f, -50.0f);
    glVertex3f(10.0f, 10.0f, -50.0f);
    glVertex3f(2.5f, 10.0f, -50.0f);
    glVertex3f(2.5f, 0.01f, -50.0f);
    glVertex3f(11.0f, 0.01f, -49.0f);
    glVertex3f(11.0f, 10.0f, -49.0f);
    glVertex3f(2.5f, 10.0f, -49.0f);
    glVertex3f(2.5f, 0.01f, -49.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.01f, -50.0f);
    glVertex3f(-10.0f, 10.0f, -50.0f);
    glVertex3f(-2.5f, 10.0f, -50.0f);
    glVertex3f(-2.5f, 0.01f, -50.0f);
    glVertex3f(-11.0f, 0.01f, -49.0f);
    glVertex3f(-11.0f, 10.0f, -49.0f);
    glVertex3f(-2.5f, 10.0f, -49.0f);
    glVertex3f(-2.5f, 0.01f, -49.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-2.5f, 10.0f, -50.0f);
    glVertex3f(2.5f, 10.0f, -50.0f);
    glVertex3f(2.5f, 6.0f, -50.0f);
    glVertex3f(-2.5f, 6.0f, -50.0f);
    glVertex3f(-2.5f, 10.0f, -49.0f);
    glVertex3f(2.5f, 10.0f, -49.0f);
    glVertex3f(2.5f, 6.0f, -49.0f);
    glVertex3f(-2.5f, 6.0f, -49.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-2.5f, 0.01f, -50.0f);
    glVertex3f(-2.5f, 0.01, -49.0f);
    glVertex3f(-2.5f, 6.0f, -49.0f);
    glVertex3f(-2.5f, 6.0f, -50.0f);
    glVertex3f(2.5f, 0.01f, -50.0f);
    glVertex3f(2.5f, 0.01, -49.0f);
    glVertex3f(2.5f, 6.0f, -49.0f);
    glVertex3f(2.5f, 6.0f, -50.0f);
    glVertex3f(-2.5f, 6.0f, -50.0f);
    glVertex3f(-2.5f, 6.0f, -49.0f);
    glVertex3f(2.5f, 6.0f, -49.0f);
    glVertex3f(2.5f, 6.0f, -50.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex3f(-11.0f, 10.0f, -81.0f);
    glVertex3f(-11.0f, 10.0f, -49.0f);
    glVertex3f(0.0f, 15.0f, -49.0f);
    glVertex3f(0.0f, 15.0f, -81.0f);
    glVertex3f(11.0f, 10.0f, -81.0f);
    glVertex3f(11.0f, 10.0f, -49.0f);
    glVertex3f(0.0f, 15.0f, -49.0f);
    glVertex3f(0.0f, 15.0f, -81.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(11.0f, 10.0f, -81.0f);
    glVertex3f(0.0f, 15.0f, -81.0f);
    glVertex3f(-11.0f, 10.0f, -81.0f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-11.0f, 10.0f, -49.0f);
    glVertex3f(0.0f, 15.0f, -49.0f);
    glVertex3f(11.0f, 10.0f, -49.0f);
    glEnd();
}

void radio() {
    glPushMatrix();
    glTranslatef(-5, 4, -74);
    glColor3f(0, 0, 0);
    glutSolidCube(1.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, 4, -74);
    glutSolidCube(1.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-5, he, -74);
    glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(-5.1, 4.0, -73.30);
    glRotatef(ang, 0, 0, 1);
    glutWireCone(0.3, 0.0, 20, 10);
    glRotatef(-ang, 0, 0, 1);
    glTranslatef(+0.8, 0, 0);
    glRotatef(ang, 0, 0, 1);
    glutWireCone(0.3, 0.0, 20, 10);
    glPopMatrix();
}

void door() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.4, 0);
    glVertex3f(-2.5f, 0.01f, -49.75f);
    glVertex3f(-2.5f, 7.0f, -49.75f);
    glVertex3f(2.5f, 7.0f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.75f);
    glVertex3f(-2.5f, 0.01f, -49.25f);
    glVertex3f(-2.5f, 7.0f, -49.25f);
    glVertex3f(2.5f, 7.0f, -49.25f);
    glVertex3f(2.5f, 0.01f, -49.25f);
    glVertex3f(-2.5f, 0.01f, -49.25f);
    glVertex3f(-2.5f, 0.01f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.25f);
    glVertex3f(-2.5f, 0.01f, -49.25f);
    glVertex3f(-2.5f, 6.0f, -49.25f);
    glVertex3f(-2.5f, 6.0f, -49.75f);
    glVertex3f(-2.5f, 0.01f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.25f);
    glVertex3f(2.5f, 6.0f, -49.25f);
    glVertex3f(2.5f, 6.0f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.75f);
    glVertex3f(-2.5f, 6.0f, -49.25f);
    glVertex3f(-2.5f, 6.0f, -49.75f);
    glVertex3f(2.5f, 6.0f, -49.75f);
    glVertex3f(2.5f, 6.0f, -49.25f);
    glEnd();

    glPushMatrix();
    glTranslatef(-2, 3, -49);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -4.7, 0);
    glScalef(4, 4, 1.0);
    draw_leaf();
    glPopMatrix();
}

void opendoor() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.4, 0);
    glVertex3f(2.5f, 0.01f, -49.75f);
    glVertex3f(2.5f, 6.0f, -49.75f);
    glVertex3f(2.5f, 6.0f, -44.75f);
    glVertex3f(2.5f, 0.01f, -44.75f);
    glVertex3f(2.2f, 0.01f, -49.75f);
    glVertex3f(2.2f, 6.0f, -49.75f);
    glVertex3f(2.2f, 6.0f, -44.75f);
    glVertex3f(2.2f, 0.01f, -44.75f);
    glVertex3f(2.2f, 0.01f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.75f);
    glVertex3f(2.5f, 0.01f, -44.75f);
    glVertex3f(2.2f, 0.01f, -44.75f);
    glVertex3f(2.2f, 6.0f, -49.75f);
    glVertex3f(2.5f, 6.0f, -49.75f);
    glVertex3f(2.5f, 6.0f, -44.75f);
    glVertex3f(2.2f, 6.0f, -44.75f);
    glVertex3f(2.2f, 0.01f, -49.75f);
    glVertex3f(2.5f, 0.01f, -49.75f);
    glVertex3f(2.5f, 6.0f, -49.75f);
    glVertex3f(2.2f, 6.0f, -49.75f);
    glVertex3f(2.2f, 0.01f, -44.75f);
    glVertex3f(2.5f, 0.01f, -44.75f);
    glVertex3f(2.5f, 6.0f, -44.75f);
    glVertex3f(2.2f, 6.0f, -44.75f);
    glEnd();

    glPushMatrix();
    glTranslatef(2.5, 3, -45);
    glColor3f(0, 0, 0);
    glutSolidSphere(0.2, 20, 20);
    glPopMatrix();
}

void desk() {
    glBegin(GL_QUADS);
    glColor3f(0.7, 0.3, 0.0);
    for (float i = 3.5; i >= 3.2; i -= 0.001) {
        glVertex3f(-9, i, -75);
        glVertex3f(-9, i, -70);
        glVertex3f(-3, i, -70);
        glVertex3f(-3, i, -75);
    }
    glColor3f(0.5, 0.2, 0.1);
    glVertex3f(-7.5, 0.01, -75);
    glVertex3f(-4.5, 0.01, -75);
    glVertex3f(-4.5, 3.2, -75);
    glVertex3f(-7.5, 3.2, -75);
    glVertex3f(-7.5, 0.01, -70);
    glVertex3f(-4.5, 0.01, -70);
    glVertex3f(-4.5, 3.2, -70);
    glVertex3f(-7.5, 3.2, -70);
    glVertex3f(-7.5, 0.01, -75);
    glVertex3f(-7.5, 3.2, -75);
    glVertex3f(-7.5, 3.2, -70);
    glVertex3f(-7.5, 0.01, -70);
    glVertex3f(-4.5, 0.01, -75);
    glVertex3f(-4.5, 3.2, -75);
    glVertex3f(-4.5, 3.2, -70);
    glVertex3f(-4.5, 0.01, -70);
    glEnd();

    glPushMatrix();
    glTranslatef(-7, 3.9, -71);
    glColor3f(0.2, 0.1, 0);
    glutSolidTeapot(0.6);
    glPopMatrix();

    radio();
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

void render(float tx, float ty, float tz) {
    glTranslatef(-tx, -ty, -tz); // ***********

    glPushMatrix();
    glTranslatef(0, -2, 0);
    light();
    home();
    desk();
    if (m)
        door();
    else {
        opendoor();
    }
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.0);
    glRasterPos3f(12, 11, -50);
    writeBitmapString((void *) font, "Sajjad Rahmani");

    glColor3f(0.0, 0.0, 1.0);
    glRasterPos3f(12, 9, -50);
    writeBitmapString((void *) font, "----------------");

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(12, 7, -50);
    writeBitmapString((void *) font, "Press O to open/close the door");

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(12, 4, -50);
    writeBitmapString((void *) font, "Press L to off/on the light");

    glColor3f(1, 1, 1);
    glRasterPos3f(12, 1, -50);
    writeBitmapString((void *) font, "Press R to off/on the radio");

    int N = 360;
    float Dtheta = 2 * 3.1415926 / N;
    float angle = 0.0;
    glBegin(GL_LINE_LOOP);  // flower
    glColor3f(0, 0, 0);
    for (int i = 0; i <= N; i++) {
        float angle = i * Dtheta;
        float r = cos(2 * angle);
        glVertex3f(r * cos(angle), r * sin(angle) + 10, -48);
    }
    glEnd();

    glColor3f(LINE_COLOR[LINE_COLOR_index][0], LINE_COLOR[LINE_COLOR_index][1], LINE_COLOR[LINE_COLOR_index][2]);
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
    glColor3f(LEG_COLOR[LEG_COLOR_index][0], LEG_COLOR[LEG_COLOR_index][1], LEG_COLOR[LEG_COLOR_index][2]);
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
    glColor3f(BODY_COLOR[BODY_COLOR_index][0], BODY_COLOR[BODY_COLOR_index][1], BODY_COLOR[BODY_COLOR_index][2]);
    glPushMatrix();
    glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE / 2, 0.0);
    glScalef(BODY_XSCALE, BODY_YSCALE, BODY_ZSCALE);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();
    glColor3f(LEG_COLOR[LEG_COLOR_index][0], LEG_COLOR[LEG_COLOR_index][1], LEG_COLOR[LEG_COLOR_index][2]);
    glPushMatrix();
    glTranslatef(0, -GLOBAL_SIZE * BODY_YSCALE / 2 + 0.4, 0.0);
    glScalef(BODY_XSCALE - 0.1, 0.5, 0.5);
    glutSolidCube(GLOBAL_SIZE);
    glPopMatrix();

    // Head
    glColor3f(HEAD_COLOR[HEAD_COLOR_index][0], HEAD_COLOR[HEAD_COLOR_index][1], HEAD_COLOR[HEAD_COLOR_index][2]);
    glPushMatrix();
    glTranslatef(0, GLOBAL_SIZE * BODY_YSCALE + HEAD_RADIUS, 0.0);
    glutSolidSphere(HEAD_RADIUS, 10, 8);
    glPopMatrix();

    // Left Arm
    glColor3f(ARM_COLOR[ARM_COLOR_index][0], ARM_COLOR[ARM_COLOR_index][1], ARM_COLOR[ARM_COLOR_index][2]);
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


    // Sphere
    static GLfloat x = 0.0f;
    if (g_img) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, g_img);
    }
    // save the current matrix
    glPushMatrix();
    // rotate the view point
    glRotatef(g_angle_x, 1.0f, 0.0f, 0.0f);
    // translate ***
    glTranslatef(5, -33.5, -66);
    g_angle_x += g__inc;
    // rotate the planet
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(x, 0.0f, 0.0f, 1.0f);
    x += .4f;
    // draw the sphere
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(g_sphere, 1.28f, 24, 24);
    glPopMatrix();
    if (g_img)
        glDisable(GL_TEXTURE_2D);
}

void display() {
    GLfloat angle = 0.0;
    GLint buffers = GL_NONE;

    // get the current color buffer being drawn to
    glGetIntegerv(GL_DRAW_BUFFER, &buffers);

    glPushMatrix();
    // rotate the viewpoint
    glRotatef(angle += g_inc, 0.0f, 1.0f, 0.0f);
    // translate ***
    float tx = 0, ty = 0, tz = -79.9;
    glTranslatef(tx, ty, tz);

    // set the clear value
    glClearStencil(0x0);
    // clear the stencil buffer
    glClear(GL_STENCIL_BUFFER_BIT);
    // always pass the stencil test
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    // set the operation to modify the stencil buffer
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    // disable drawing to the color buffer
    glDrawBuffer(GL_NONE);
    // enable stencil
    glEnable(GL_STENCIL_TEST);

    // draw the stencil mask
    glBegin(GL_QUADS);
    mirror();
    glEnd();

    // reenable drawing to color buffer
    glDrawBuffer((GLenum) buffers);
    // make stencil buffer read only
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);


    // clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the mirror image
    glPushMatrix();
    // invert image about xy plane
    glScalef(1.0f, 1.0f, -1.0f);

    // invert the clipping plane based on the view point
    if (cos(angle * M_PI / 180.0) < 0.0)
        eqn1[2] = -1.0;
    else
        eqn1[2] = 1.0;

    // clip one side of the plane
    glClipPlane(GL_CLIP_PLANE0, eqn1);
    glEnable(GL_CLIP_PLANE0);

    // draw only where the stencil buffer == 1
    glStencilFunc(GL_EQUAL, 0x1, 0x1);
    // draw the object
    render(tx, ty, tz);

    // turn off clipping plane
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();

    // disable the stencil buffer
    glDisable(GL_STENCIL_TEST);
    // disable drawing to the color buffer
    glDrawBuffer(GL_NONE);

    // draw the mirror pane into depth buffer -
    // to prevent object behind mirror from being render
    glBegin(GL_QUADS);
    mirror();
    glEnd();

    // enable drawing to the color buffer
    glDrawBuffer((GLenum) buffers);

    // draw the normal image, without stencil test
    glPushMatrix();
    render(tx, ty, tz);
    glPopMatrix();

    // draw the outline of the mirror
    glColor3f(0.4f, 0.4f, 1.0f);
    glBegin(GL_LINE_LOOP);
    mirror();
    glEnd();

    // mirror shine
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_LIGHTING);

    glColor4f(1.0f, 1.0f, 1.0f, .2f);
    glTranslatef(0.0f, 0.0f, 0.001f * eqn1[2]);
    glBegin(GL_QUADS);
    mirror();
    glEnd();

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

static double lookatx = 3.5, lookatz = 3.5, lookaty = 0;
static int scrw, scrh;

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

void calculateData(int id) {
    if (!isPaused) {
        centerY = legLength * sin(-leftHigherLegAngle / 180.0 * PI) - legLength;
        double mvx = cos(vangle / 180.0 * PI) * 0.04;
        double mvz = sin(vangle / 180.0 * PI) * 0.04;

        if (!dir1) {
            leftHigherLegAngle--;
            rightHigherLegAngle++;
            if (leftHigherLegAngle >= -85) {
                leftLowerLegAngle += 3;
                leftFootAngle = 0;
            } else if (leftHigherLegAngle < -95)
                leftLowerLegAngle -= 3;

            if (leftHigherLegAngle == -120) {
                dir1 = true;
            }

            rightFootAngle = -rightHigherLegAngle - 90;

            leftHigherARMAngle++;
            leftLowerARMAngle++;
            rightHigherARMAngle--;
            rightLowerARMAngle--;
        } else {
            leftHigherLegAngle++;
            rightHigherLegAngle--;
            if (rightHigherLegAngle >= -85) {
                rightLowerLegAngle += 3;
                rightFootAngle = 0;
            } else if (rightHigherLegAngle < -95) rightLowerLegAngle -= 3;

            if (leftHigherLegAngle == -60) dir1 = false;

            leftFootAngle = -leftHigherLegAngle - 90;

            leftHigherARMAngle--;
            leftLowerARMAngle--;
            rightHigherARMAngle++;
            rightLowerARMAngle++;
        }

        centerX -= mvx;
        lookatx -= mvx;
        centerZ += mvz;
        lookatz += mvz;

        if ((int) centerZ == -48 and -12 < (int) centerX and (int) centerX < 12)
            if (!(!m and -3.5 < (float) centerX and (float) centerX < 3.5))
                vangle = (vangle + 180) % 360;

        if ((int) centerX == -9 and -80 < (int) centerZ and (int) centerZ < -49)
            vangle = (vangle + 180) % 360;

        if ((int) centerX == 9 and -80 < (int) centerZ and (int) centerZ < -49)
            vangle = (vangle + 180) % 360;

        if ((int) centerZ == -80 and -12 < (int) centerX and (int) centerX < 12)
            vangle = (vangle + 180) % 360;

        glLoadIdentity();
        gluLookAt(lookatx, lookaty, lookatz, centerX, 0, centerZ, 0.0, 1.0, 0.0);

        glutPostRedisplay();
    }

    // for radio
    if (isAnimate) {
        ang += 5;
        glutPostRedisplay();
    }

    glutTimerFunc(speed, calculateData, 0);
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

        case '2':  // speed++
            if (speed < MAX_SPEED)
                speed++;
            break;
        case '8':  // speed--
            if (speed > MIN_SPEED)
                speed--;
            break;

        case 27:    //"ESC" to exit the program
            exit(0);
        case 32:    //"space" to pause
            isPaused = !isPaused;
            break;
        case 13:    //"enter" to full screen
            if (isFullScreen)
                glutReshapeWindow(500, 500);
            else
                glutFullScreen();

            isFullScreen = !isFullScreen;
            break;

        case 'Q':
            HEAD_COLOR_index = (HEAD_COLOR_index + 1) % COLOR_COUNT;
            break;
        case 'W':
            BODY_COLOR_index = (BODY_COLOR_index + 1) % COLOR_COUNT;
            break;
        case 'E':
            ARM_COLOR_index = (ARM_COLOR_index + 1) % COLOR_COUNT;
            break;
        case 'R':
            LEG_COLOR_index = (LEG_COLOR_index + 1) % COLOR_COUNT;
            break;
        case 'T':
            LINE_COLOR_index = (LINE_COLOR_index + 1) % COLOR_COUNT;
            break;
        case 'Y':
            LINE_COLOR_index = LEG_COLOR_index = ARM_COLOR_index = BODY_COLOR_index = HEAD_COLOR_index = 0;
            break;

        case 'o':  // open|close door
            m = 1 - m;
            break;

        case 'r':  // turn on|off radio
            if (isAnimate)
                isAnimate = 0;
            else {
                isAnimate = 1;
                calculateData(1);
            }
            if (het) {
                he -= 0.1;
                het = 0;
            } else {
                he += 0.1;
                het = 1;
            }
            break;

        case 'l':  // turn on|off light
            if (spin)
                spin = 0;
            else
                spin = 1;
            break;
        case ']':  // x_light++
            x_light++;
            break;
        case '[':  // x_light--
            x_light--;
            break;

        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
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
