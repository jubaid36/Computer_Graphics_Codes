#include <GL/glut.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (float x = -1.0; x <= 1.0; x += 0.001)
    {
        glVertex2f(x, 0.0);
    }
    for (float y = -1.0; y <= 1.0; y += 0.001)
    {
        glVertex2f(0.0, y);
    }
    glEnd();
    glBegin(GL_POINTS);
    for (float x = 0.0; x <= 1.0; x += 0.001)
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x, 0.5);
    }
    for (float x = 0.0; x <= 1.0; x += 0.001)
    {
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(x, 0.3);
    }
    for (float x = 0.0; x <= 1.0; x += 0.001)
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(x, 0.7);
    }
    for (float y = 0.0; y <= 1.0; y += 0.001)
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.5, -y);
    }
    for (float y = 0.0; y <= 1.0; y += 0.001)
    {
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.3, -y);
    }
    for (float y = 0.0; y <= 1.0; y += 0.001)
    {
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(-0.7, -y);
    }
    glEnd();
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(480, 440);
    glutCreateWindow("3Lines");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}