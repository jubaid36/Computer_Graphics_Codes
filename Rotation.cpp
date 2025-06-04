/*
 * এই প্রোগ্রামটি OpenGL ব্যবহার করে একটি ত্রিভুজ আঁকে এবং সেটিকে নির্দিষ্ট কোণে (45 ডিগ্রী) ঘুরিয়ে দেখায়।
 * 
 * - drawTriangle() ফাংশন তিনটি পয়েন্ট ব্যবহার করে একটি ত্রিভুজ আঁকে।
 * - display() ফাংশনে প্রথমে নীল রঙে মূল ত্রিভুজটি (ax, ay), (bx, by), (cx, cy) আঁকা হয়।
 * - এরপর কমলা রঙে সেই একই ত্রিভুজটি 45 ডিগ্রী কোণে রেডিয়ানে রূপান্তর করে ঘুরিয়ে আঁকা হয়, যার জন্য রোটেশন ম্যাট্রিক্সের সূত্র ব্যবহার করা হয়েছে:
 *     x' = x*cosθ - y*sinθ
 *     y' = x*sinθ + y*cosθ
 * - init() ফাংশনে স্ক্রিনের ব্যাকগ্রাউন্ড সাদা করে এবং 2D কোঅর্ডিনেট সিস্টেম (-1.0 থেকে 1.0) সেট করা হয়।
 * 
 * ফলাফলস্বরূপ, স্ক্রিনে দুটি ত্রিভুজ দেখা যাবে: একটির মূল অবস্থান এবং আরেকটি তার 45 ডিগ্রী কোণে ঘুরানো রূপ।
 */

 #include <GL/glut.h>
#include <cmath>      // গণনার জন্য প্রয়োজন (sin, cos)
using namespace std;

// মূল ত্রিভুজের তিনটি বিন্দু (vertex) এর কোঅর্ডিনেট
float ax = -0.3, ay = -0.3;
float bx = 0.0, by = 0.4;
float cx = 0.3, cy = -0.3;

// ঘূর্ণনের কোণ (degree তে)
float angle = 45.0;
// রেডিয়ানে কোণ রূপান্তর (OpenGL trigonometrical ফাংশন রেডিয়ান ইনপুট নেয়)
float rad = angle * 3.1416 / 180.0;

// একটি ত্রিভুজ আঁকার ফাংশন
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_POLYGON);        // বহুভুজ শুরু (ত্রিভুজের জন্য)
    glVertex2f(x1, y1);         // প্রথম বিন্দু
    glVertex2f(x2, y2);         // দ্বিতীয় বিন্দু
    glVertex2f(x3, y3);         // তৃতীয় বিন্দু
    glEnd();                    // বহুভুজ শেষ
}

// ডিসপ্লে ফাংশন, যা স্ক্রীনে ড্র করার জন্য কল হয়
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // স্ক্রীন ক্লিয়ার

    // মূল ত্রিভুজ নীল রঙে আঁকো
    glColor3f(0.0, 0.0, 1.0);
    drawTriangle(ax, ay, bx, by, cx, cy);

    // রোটেট করা ত্রিভুজ কমলা রঙে আঁকো
    glColor3f(1.0, 0.5, 0.0);
    drawTriangle(
        // X' = X*cosθ - Y*sinθ
        ax * cos(rad) - ay * sin(rad), 
        // Y' = X*sinθ + Y*cosθ
        ax * sin(rad) + ay * cos(rad),

        bx * cos(rad) - by * sin(rad), 
        bx * sin(rad) + by * cos(rad),

        cx * cos(rad) - cy * sin(rad), 
        cx * sin(rad) + cy * cos(rad)
    );

    glFlush();   // ড্র শেষ করে স্ক্রীনে দেখাও
}

// OpenGL সেটআপ
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // ব্যাকগ্রাউন্ড সাদা
    glMatrixMode(GL_PROJECTION);        // প্রজেকশন ম্যাট্রিক্স সক্রিয়
    glLoadIdentity();                   // প্রজেকশন ম্যাট্রিক্স রিসেট
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // 2D ভিউপোর্ট নির্ধারণ (-1 থেকে +1)
}

// মেইন ফাংশন, প্রোগ্রামের এন্ট্রি পয়েন্ট
int main(int argc, char** argv) {
    glutInit(&argc, argv);                           // GLUT ইনিশিয়ালাইজ
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // সিঙ্গেল বাফার ও RGB মোড
    glutInitWindowSize(800, 600);                    // উইন্ডোর সাইজ নির্ধারণ
    glutInitWindowPosition(150, 100);                // উইন্ডোর অবস্থান
    glutCreateWindow("Rotated Triangle Visualization");  // উইন্ডোর শিরোনাম
    init();                                          // ওপেনজিএল সেটআপ
    glutDisplayFunc(display);                         // ডিসপ্লে ফাংশন রেজিস্টার
    glutMainLoop();                                  // ইভেন্ট লুপ শুরু
    return 0;
}
