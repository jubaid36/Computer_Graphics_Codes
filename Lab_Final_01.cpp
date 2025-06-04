#include<GL/glut.h>
#include<cmath>
void DDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
}
void rotatePoint(float x, float y, float originX, float originY, float angle, float& xr, float& yr)
{
    float rad = angle * M_PI / 180.0f;
    xr = originX + (x - originX) * cos(rad) - (y - originY) * sin(rad);
    yr = originY + (x - originX) * sin(rad) + (y - originY) * cos(rad);
}
void shearPoint(float x, float y, float originX, float originY, float shx, float shy, float& xs, float& ys)
{
    // Translate to origin
    float xt = x - originX;
    float yt = y - originY;

    // Shearing
    xs = xt + shx * yt;
    ys = yt + shy * xt;

    // Translate back
    xs += originX;
    ys += originY;
}
void reflectPoint(float x, float y, float originX, float originY, bool reflectX, bool reflectY, float& xr, float& yr)
{
    // Translate point to origin
    float xt = x - originX;
    float yt = y - originY;

    // Reflection
    if (reflectX)
        yt = -yt;
    if (reflectY)
        xt = -xt;

    // Translate back
    xr = xt + originX;
    yr = yt + originY;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    DDA(100, 100, 100, 250);
    DDA(100, 250, 180, 250);
    DDA(100, 175, 150, 175);

    float dx = 120;
    float dy = 50;
    glColor3f(1.0, 1.0, 0.0);
    DDA(100 + dx, 100 + dy, 100 + dx, 250 + dy);
    DDA(100 + dx, 250 + dy, 180 + dx, 250 + dy);
    DDA(100 + dx, 175 + dy, 150 + dx, 175 + dy);

    float Sx = 1.5;
    float Sy = 1.5;

    float originX = 100;
    float originY = 100;

    glColor3f(0.0, 1.0, 1.0);
    DDA(originX + (275 - originX) * Sx, originY + (275 - originY) * Sy, originX + (275 - originX) * Sx, originY + (350 - originY) * Sy);
    DDA(originX + (275 - originX) * Sx, originY + (350 - originY) * Sy, originX + (330 - originX) * Sx, originY + (350 - originY) * Sy);
    DDA(originX + (275 - originX) * Sx, originY + (325 - originY) * Sy, originX + (330 - originX) * Sx, originY + (325 - originY) * Sy);

    float angle = 45; // degree
    glColor3f(1.0, 0.0, 1.0);

    // Rotate all 3 lines points
    float x1r, y1r, x2r, y2r;

    // Line 1: (100,100) to (100,250)
    rotatePoint(100, 100, originX, originY, angle, x1r, y1r);
    rotatePoint(100, 250, originX, originY, angle, x2r, y2r);
    DDA(x1r, y1r, x2r, y2r);

    // Line 2: (100,250) to (180,250)
    rotatePoint(100, 250, originX, originY, angle, x1r, y1r);
    rotatePoint(180, 250, originX, originY, angle, x2r, y2r);
    DDA(x1r, y1r, x2r, y2r);

    // Line 3: (100,175) to (150,175)
    rotatePoint(100, 175, originX, originY, angle, x1r, y1r);
    rotatePoint(150, 175, originX, originY, angle, x2r, y2r);
    DDA(x1r, y1r, x2r, y2r);

    // Shearing (green)
    float shx = 0.5;  // shear factor along x
    float shy = 0.0;  // shear factor along y
    glColor3f(0.0, 1.0, 0.0);

    float xs1, ys1, xs2, ys2;

    // Line 1: (100,100) to (100,250)
    shearPoint(100, 100, originX, originY, shx, shy, xs1, ys1);
    shearPoint(100, 250, originX, originY, shx, shy, xs2, ys2);
    DDA(xs1, ys1, xs2, ys2);

    // Line 2: (100,250) to (180,250)
    shearPoint(100, 250, originX, originY, shx, shy, xs1, ys1);
    shearPoint(180, 250, originX, originY, shx, shy, xs2, ys2);
    DDA(xs1, ys1, xs2, ys2);

    // Line 3: (100,175) to (150,175)
    shearPoint(100, 175, originX, originY, shx, shy, xs1, ys1);
    shearPoint(150, 175, originX, originY, shx, shy, xs2, ys2);
    DDA(xs1, ys1, xs2, ys2);

    // Reflection (red)
    glColor3f(1.0, 0.0, 0.0);
    float xr1, yr1, xr2, yr2;

    // Reflection about X-axis (reflectY = false, reflectX = true)
    // অর্থাৎ y কে -y করা হবে originY এর respect-এ

    reflectPoint(100, 100, originX, originY, true, false, xr1, yr1);
    reflectPoint(100, 250, originX, originY, true, false, xr2, yr2);
    DDA(xr1, yr1, xr2, yr2);

    reflectPoint(100, 250, originX, originY, true, false, xr1, yr1);
    reflectPoint(180, 250, originX, originY, true, false, xr2, yr2);
    DDA(xr1, yr1, xr2, yr2);

    reflectPoint(100, 175, originX, originY, true, false, xr1, yr1);
    reflectPoint(150, 175, originX, originY, true, false, xr2, yr2);
    DDA(xr1, yr1, xr2, yr2);

    glFlush();
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("DDA");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}