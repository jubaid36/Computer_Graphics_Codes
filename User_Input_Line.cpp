#include <GL/glut.h>
#include <cmath>

// Original shape coordinates (a square for simplicity)
float ax = -0.3, ay = -0.3;
float bx = 0.3, by = -0.3;
float cx = 0.3, cy = 0.3;
float dx = -0.3, dy = 0.3;

// Rotation parameters
float angle = 45.0;  // Rotation angle in degrees
float centerX = 0.0, centerY = 0.0;  // Rotation center (origin)

// Function to draw a shape using GL_LINES
void drawShape(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glVertex2f(x2, y2);
    glVertex2f(x3, y3);

    glVertex2f(x3, y3);
    glVertex2f(x4, y4);

    glVertex2f(x4, y4);
    glVertex2f(x1, y1);
    glEnd();
}

// Function for Rotation
void rotate(float& x, float& y, float angle, float centerX, float centerY) {
    float radian = angle * (M_PI / 180.0);  // Convert angle to radians
    float cosA = cos(radian);
    float sinA = sin(radian);

    // Translate point back to origin, rotate, and then translate back
    float tempX = x - centerX;
    float tempY = y - centerY;

    x = cosA * tempX - sinA * tempY + centerX;
    y = sinA * tempX + cosA * tempY + centerY;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Original Shape (Blue)
    glColor3f(0.0, 0.0, 1.0);
    drawShape(ax, ay, bx, by, cx, cy, dx, dy);

    // Rotated Shape (Orange)
    glColor3f(1.0, 0.5, 0.0);
    float ax_rot = ax, ay_rot = ay;
    rotate(ax_rot, ay_rot, angle, centerX, centerY);
    float bx_rot = bx, by_rot = by;
    rotate(bx_rot, by_rot, angle, centerX, centerY);
    float cx_rot = cx, cy_rot = cy;
    rotate(cx_rot, cy_rot, angle, centerX, centerY);
    float dx_rot = dx, dy_rot = dy;
    rotate(dx_rot, dy_rot, angle, centerX, centerY);
    drawShape(ax_rot, ay_rot, bx_rot, by_rot, cx_rot, cy_rot, dx_rot, dy_rot);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set 2D coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotation Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
