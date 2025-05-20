#include <windows.h>
#include <GL/glut.h>

int x = 100, y = 200, x_end = 300, y_end = 400;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);

    glPointSize(3);
    glBegin(GL_POINTS);

    int dx = abs(x_end - x);
    int dy = abs(y_end - y);
    int sx = (x_end > x) ? 1 : -1;
    int sy = (y_end > y) ? 1 : -1;
    int curr_x = x, curr_y = y;
    int p = 2 * dy - dx;

    if (dx > dy) {
        for (int i = 0; i <= dx; i++) {
            glVertex2i(curr_x, curr_y);
            curr_x += sx;
            if (p >= 0) {
                curr_y += sy;
                p -= 2 * dx;
            }
            p += 2 * dy;
        }
    }
    else {
        p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            glVertex2i(curr_x, curr_y);
            curr_y += sy;
            if (p >= 0) {
                curr_x += sx;
                p -= 2 * dy;
            }
            p += 2 * dx;
        }
    }

    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
