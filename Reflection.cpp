#include <GL/glut.h>

float ax = -0.3, ay = -0.3;
float bx = 0.0, by = 0.3;
float cx = 0.3, cy = -0.3;

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 1.0);
    drawTriangle(ax, ay, bx, by, cx, cy);

    glColor3f(1.0, 0.5, 0.0);
    drawTriangle(ax, -ay, bx, -by, cx, -cy);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Triangle Reflection Over X-axis");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
