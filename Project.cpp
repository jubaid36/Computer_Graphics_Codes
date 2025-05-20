#include <GL/glut.h>
#include <cmath>

// Window size
int winWidth = 800, winHeight = 600;

// Clipping window bounds
float xmin = -200, xmax = 200, ymin = -150, ymax = 150;

// For rotating fan
float fanAngle = 0.0;

// For moving car
float carX = -400;

// For line clipping
float xd1 = -250, yd1 = -100, xd2 = 300, yd2 = 200;
float xdd1 = xd1, ydd1 = yd1, xdd2 = xd2, ydd2 = yd2;
bool lineClipped = false;

// --- Cohen-Sutherland Helper Functions ---
int computeCode(float x, float y) {
    int code = 0;
    if (y > ymax) code |= 8;
    if (y < ymin) code |= 4;
    if (x > xmax) code |= 2;
    if (x < xmin) code |= 1;
    return code;
}

void cohenSutherland(float x1, float y1, float x2, float y2) {
    int c1 = computeCode(x1, y1);
    int c2 = computeCode(x2, y2);
    bool done = false, draw = false;

    while (!done) {
        if ((c1 | c2) == 0) {
            draw = true;
            done = true;
        }
        else if ((c1 & c2) != 0) {
            done = true;
        }
        else {
            float x, y;
            int out = c1 ? c1 : c2;
            float m = (x2 - x1) != 0 ? (y2 - y1) / (x2 - x1) : 1e9;

            if (out & 8) { y = ymax; x = x1 + (1.0 / m) * (ymax - y1); }
            else if (out & 4) { y = ymin; x = x1 + (1.0 / m) * (ymin - y1); }
            else if (out & 2) { x = xmax; y = y1 + m * (xmax - x1); }
            else { x = xmin; y = y1 + m * (xmin - x1); }

            if (out == c1) { x1 = x; y1 = y; c1 = computeCode(x1, y1); }
            else { x2 = x; y2 = y; c2 = computeCode(x2, y2); }
        }
    }

    if (draw) {
        xdd1 = x1;
        ydd1 = y1;
        xdd2 = x2;
        ydd2 = y2;
        lineClipped = true;
    }
    else {
        lineClipped = false;
    }

    glutPostRedisplay();
}

// --- Drawing Functions ---
void drawClippingWindow() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();
}

void drawFan() {
    glPushMatrix();
    glTranslatef(-250, 200, 0);
    glRotatef(fanAngle, 0, 0, 1);
    glColor3f(0.2, 0.7, 1);
    for (int i = 0; i < 4; i++) {
        glRotatef(90, 0, 0, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(0, 0);
        glVertex2f(20, 80);
        glVertex2f(-20, 80);
        glEnd();
    }
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    glTranslatef(carX, -200, 0);
    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_POLYGON); // Body
    glVertex2f(-30, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 20);
    glVertex2f(-30, 20);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON); // Wheels
    glVertex2f(-20, -5); glVertex2f(-10, -5); glVertex2f(-10, 5); glVertex2f(-20, 5);
    glVertex2f(10, -5); glVertex2f(20, -5); glVertex2f(20, 5); glVertex2f(10, 5);
    glEnd();
    glPopMatrix();
}

void drawLine() {
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(xd1, yd1);
    glVertex2f(xd2, yd2);
    glEnd();

    if (lineClipped) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(xdd1, ydd1);
        glVertex2f(xdd2, ydd2);
        glEnd();
    }
}

// --- Display ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawClippingWindow();
    drawFan();
    drawCar();
    drawLine();
    glFlush();
}

// --- Animation Timer ---
void timer(int) {
    fanAngle += 5;
    if (fanAngle >= 360) fanAngle = 0;

    carX += 2;
    if (carX > 400) carX = -400;

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

// --- Keyboard ---
void keyboard(unsigned char key, int x, int y) {
    if (key == 'c') {
        cohenSutherland(xd1, yd1, xd2, yd2);
    }
}

// --- Init ---
void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-400, 400, -300, 300);
}

// --- Main ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(winWidth, winHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Fan + Car + Clipping Animation");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
