#include <windows.h>
#include <GL/glut.h>

float xmin = -100, ymin = -100, xmax = 100, ymax = 100;

float x1_inside = -50, y1_inside = -50, x2_inside = 50, y2_inside = 50;
float x1_outside = -250, y1_outside = -250, x2_outside = -200, y2_outside = -200;
float x1_partial = -200, y1_partial = -200, x2_partial = 50, y2_partial = 50;

float cx1, cy1, cx2, cy2;

int computeCode(float x, float y) {
    int code = 0;
    if (x < xmin) code |= 1;
    if (x > xmax) code |= 2;
    if (y < ymin) code |= 4;
    if (y > ymax) code |= 8;
    return code;
}

bool cohenSutherlandClip(float x1, float y1, float x2, float y2, float& cx1, float& cy1, float& cx2, float& cy2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 | code2) == 0) {
            accept = true;
            cx1 = x1; cy1 = y1;
            cx2 = x2; cy2 = y2;
            break;
        }
        else if (code1 & code2) {
            break;
        }
        else {
            int codeOut = code1 ? code1 : code2;
            float x, y;

            if (codeOut & 8) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & 4) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & 2) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (codeOut & 1) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        cx1 = x1;
        cy1 = y1;
        cx2 = x2;
        cy2 = y2;
    }

    return accept;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    glLineWidth(2);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x1_inside, y1_inside);
    glVertex2f(x2_inside, y2_inside);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(x1_outside, y1_outside);
    glVertex2f(x2_outside, y2_outside);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x1_partial, y1_partial);
    glVertex2f(x2_partial, y2_partial);
    glEnd();

    if (cohenSutherlandClip(x1_partial, y1_partial, x2_partial, y2_partial, cx1, cy1, cx2, cy2)) {
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(cx1, cy1);
        glVertex2f(cx2, cy2);
        glEnd();
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Clipping - 3 Cases");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}