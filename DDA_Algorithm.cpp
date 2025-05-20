#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;
float x = -0.5, y = -0.5, x_end = 0.5, y_end = 0.5;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    glPointSize(2.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    float dx = x_end - x;
    float dy = y_end - y;
    int steps;
    if (fabs(dx) > fabs(dy))
    {
        steps = (int)(fabs(dx) * 1000);
    }
    else {
        steps = (int)(fabs(dx) * 1000);
    }
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(x, y);
        x += x_inc;
        y += y_inc;
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(540, 480);
    glutCreateWindow("DDA");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}