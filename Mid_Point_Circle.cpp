#include <GL/glut.h>

int xc = 0, yc = 0, r = 100;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCircle(int xc, int yc, int x, int y) {
    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);
    drawPixel(xc + y, yc + x);
    drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x);
    drawPixel(xc - y, yc - x);
}

void midPointCircle() {
    int x = 0;
    int y = r;
    int p = 1 - r;

    while (x <= y) {
        drawCircle(xc, yc, x, y);
        x++;
        if (p < 0) {
            p = p + 2 * x + 1;
        }
        else {
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    midPointCircle();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(3);
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
