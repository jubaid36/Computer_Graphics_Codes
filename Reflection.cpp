/*
 * এই প্রোগ্রামটি OpenGL ব্যবহার করে একটি ত্রিভুজ আঁকে এবং তার পর একই ত্রিভুজটিকে X-axis এর ওপর প্রতিফলন (reflection) দেখায়।
 * 
 * - drawTriangle() ফাংশন তিনটি কোঅর্ডিনেট নিয়ে একটি ত্রিভুজ আঁকে।
 * - display() ফাংশনে প্রথমে নীল রঙে মূল ত্রিভুজ (ax, ay), (bx, by), (cx, cy) আঁকা হয়।
 * - তারপর একই ত্রিভুজকে X-axis এর ওপর প্রতিফলিত করে কমলা রঙে (ax, -ay), (bx, -by), (cx, -cy) আঁকা হয়।
 * - init() ফাংশনে স্ক্রিনের ব্যাকগ্রাউন্ড সাদা করা হয় এবং 2D কর্ডিনেট সিস্টেম সেট করা হয়।
 * 
 * ফলে, স্ক্রিনে দুটি ত্রিভুজ দেখা যাবে — একটির নিচে আরেকটি তার উপর X-axis এর প্রতিফলন।
 */
#include <GL/glut.h>  // OpenGL Utility Toolkit লাইব্রেরি

// তিনটি বিন্দুর (vertex) কোঅর্ডিনেট, যা মূল ত্রিভুজের জন্য ব্যবহৃত হবে
float ax = -0.3, ay = -0.3;  // প্রথম বিন্দু
float bx = 0.0, by = 0.3;    // দ্বিতীয় বিন্দু
float cx = 0.3, cy = -0.3;   // তৃতীয় বিন্দু

// একটি ত্রিভুজ আঁকার জন্য ফাংশন
// x1,y1; x2,y2; x3,y3 হচ্ছে ত্রিভুজের তিনটি কোঅর্ডিনেট
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_POLYGON);   // বহুভুজ ড্র শুরু
    glVertex2f(x1, y1);    // প্রথম বিন্দু সেট করো
    glVertex2f(x2, y2);    // দ্বিতীয় বিন্দু সেট করো
    glVertex2f(x3, y3);    // তৃতীয় বিন্দু সেট করো
    glEnd();               // বহুভুজ ড্র শেষ
}

// ডিসপ্লে ফাংশন যা OpenGL এর সাথে কল হবে যখন স্ক্রীনে ড্র করতে হবে
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // স্ক্রীন ক্লিয়ার করো (ব্যাকগ্রাউন্ড রঙ অনুযায়ী)

    // প্রথম ত্রিভুজের জন্য রঙ নীল সেট করা (RGB: 0, 0, 1)
    glColor3f(0.0, 0.0, 1.0);
    // মূল ত্রিভুজ ড্র করো
    drawTriangle(ax, ay, bx, by, cx, cy);

    // দ্বিতীয় ত্রিভুজের জন্য রঙ কমলা সেট করা (RGB: 1, 0.5, 0)
    glColor3f(1.0, 0.5, 0.0);
    // x-axis এর উপর রিফ্লেকশন: y মানের সাইন পাল্টিয়ে ত্রিভুজ ড্র করো
    drawTriangle(ax, -ay, bx, -by, cx, -cy);

    glFlush();  // ড্রয়িং শেষ করে স্ক্রীনে দেখাও
}

// OpenGL এর প্রাথমিক সেটআপ ফাংশন
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // ব্যাকগ্রাউন্ড কালার সাদা (RGBA)
    glMatrixMode(GL_PROJECTION);        // প্রজেকশন ম্যাট্রিক্স মোড সক্রিয় করো
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // 2D ভিউপোর্ট সেট করো -1 থেকে +1 পর্যন্ত
}

// মেইন ফাংশন যেখানে প্রোগ্রামের এন্ট্রি পয়েন্ট
int main(int argc, char** argv) {
    glutInit(&argc, argv);                         // GLUT ইনিশিয়ালাইজ করো
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // সিঙ্গেল বাফার ও RGB মোড সেট করো
    glutInitWindowSize(800, 600);                  // উইন্ডোর সাইজ ৮০০x৬০০ পিক্সেল
    glutInitWindowPosition(100, 100);              // উইন্ডোর স্ক্রীনে অবস্থান নির্ধারণ
    glutCreateWindow("Triangle Reflection Over X-axis");  // উইন্ডোর শিরোনাম
    init();                                        // OpenGL সেটআপ কল করো
    glutDisplayFunc(display);                       // ডিসপ্লে ফাংশন রেজিস্টার করো
    glutMainLoop();                                // মেইন লুপ চালু করো, ইভেন্ট হ্যান্ডলিং শুরু
    return 0;
}
