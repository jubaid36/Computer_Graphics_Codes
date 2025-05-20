#include <GL/glut.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(23.0);
    glBegin(GL_POINTS);

    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glEnd();

    glPointSize(3.0);
    glBegin(GL_POINTS);
    for (float x = -1.0; x <= 1.0; x += 0.001)
    {
        glColor3f(1.0, 0.0, 1.0);
        glVertex2f(x, 0.0);
    }
    for (float y = -1.0; y <= 1.0; y += 0.001)
    {
        glVertex2f(0.0, y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(840, 840);
    glutCreateWindow("Draw Points");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}