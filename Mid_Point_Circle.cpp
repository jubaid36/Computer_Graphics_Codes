/*
 * এই প্রোগ্রামটি OpenGL ব্যবহার করে Midpoint Circle Drawing Algorithm এর মাধ্যমে একটি বৃত্ত আঁকে।
 * - drawPixel() ফাংশন একটি পয়েন্ট (পিক্সেল) স্ক্রিনে আঁকে।
 * - drawCircle() ফাংশন বৃত্তের ৮টি symmetry পয়েন্ট একই সময়ে আঁকতে ব্যবহৃত হয়।
 * - midPointCircle() ফাংশনটি Midpoint Circle Algorithm অনুযায়ী বৃত্তের পয়েন্ট নির্ণয় করে এবং drawCircle() কল করে।
 * - display() ফাংশনটি OpenGL এর ডিসপ্লে কলব্যাকে midPointCircle() চালায়।
 * - init() ফাংশনে উইন্ডোর ব্যাকগ্রাউন্ড সাদা করা, পয়েন্টের কালার কালো করা এবং 2D coordinate system সেট করা হয়।
 * 
 * ফলস্বরূপ, একটি কেন্দ্রে (0,0) এবং ব্যাসার্ধ 100 পিক্সেলের বৃত্ত স্ক্রিনে দেখা যাবে।
 */
#include <GL/glut.h>  // OpenGL Utility Toolkit লাইব্রেরি

// কেন্দ্র (xc, yc) এবং বৃত্তের ব্যাসার্ধ r নির্ধারণ
int xc = 0, yc = 0, r = 100;

// একটি পয়েন্ট (pixel) স্ক্রীনে ড্র করার জন্য ফাংশন
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);      // পয়েন্ট ড্র করতে শুরু
    glVertex2i(x, y);        // (x, y) অবস্থানে পয়েন্ট বসানো
    glEnd();                 // পয়েন্ট ড্র শেষ
}

// বৃত্তের প্রতিটি অক্ট্যান্টে সিমেট্রিক পয়েন্টগুলো ড্র করার জন্য ফাংশন
void drawCircle(int xc, int yc, int x, int y) {
    drawPixel(xc + x, yc + y);  // প্রথম অক্ট্যান্ট
    drawPixel(xc - x, yc + y);  // দ্বিতীয় অক্ট্যান্ট
    drawPixel(xc + x, yc - y);  // তৃতীয় অক্ট্যান্ট
    drawPixel(xc - x, yc - y);  // চতুর্থ অক্ট্যান্ট
    drawPixel(xc + y, yc + x);  // পঞ্চম অক্ট্যান্ট
    drawPixel(xc - y, yc + x);  // ষষ্ঠ অক্ট্যান্ট
    drawPixel(xc + y, yc - x);  // সপ্তম অক্ট্যান্ট
    drawPixel(xc - y, yc - x);  // অষ্টম অক্ট্যান্ট
}

// Midpoint Circle Drawing Algorithm এর মূল ফাংশন
void midPointCircle() {
    int x = 0;
    int y = r;          // শুরুতে y=radius
    int p = 1 - r;      // Decision parameter, শুরু মান

    // x যতক্ষণ y এর ছোট বা সমান ততক্ষণ লুপ চালাও
    while (x <= y) {
        drawCircle(xc, yc, x, y);  // প্রতিটি পয়েন্টে বৃত্তের 8 অংশে পয়েন্ট বসাও
        x++;                      // x বাড়াও এক ধাপ

        // Decision parameter অনুযায়ী y এর মান ঠিক করা
        if (p < 0) {
            p = p + 2 * x + 1;    // যদি পজিটিভ হয় তাহলে y অপরিবর্তিত
        }
        else {
            y--;                  // y কমাও এক ধাপ
            p = p + 2 * x - 2 * y + 1;  // Decision parameter আপডেট করো
        }
    }
}

// ডিসপ্লে ফাংশন যা OpenGL এর সাথে কল হবে
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // স্ক্রীন ক্লিয়ার করো
    midPointCircle();             // বৃত্ত আঁকো
    glFlush();                   // ড্রয়িং সম্পন্ন করে স্ক্রীনে দেখাও
}

// OpenGL এর প্রাথমিক সেটআপ ফাংশন
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // ব্যাকগ্রাউন্ড কালার সাদা (RGBA)
    glColor3f(0.0, 0.0, 0.0);          // পয়েন্টের কালার কালো (RGB)
    glPointSize(3);                    // পয়েন্ট সাইজ নির্ধারণ (3 পিক্সেল)
    gluOrtho2D(-500, 500, -500, 500);  // 2D অরথোগ্রাফিক প্রজেকশন সেট করা
}

// মেইন ফাংশন যেখানে প্রোগ্রামের এন্ট্রি পয়েন্ট
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // GLUT ইনিশিয়ালাইজ করো
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // সিঙ্গেল বাফার ও RGB মোড সেট
    glutInitWindowSize(800, 800);               // উইন্ডোর সাইজ ৮০০x৮০০ পিক্সেল
    glutInitWindowPosition(100, 100);           // উইন্ডো স্ক্রীনের অবস্থান
    glutCreateWindow("Midpoint Circle Drawing Algorithm"); // উইন্ডোর শিরোনাম
    init();                                    // OpenGL সেটআপ কল
    glutDisplayFunc(display);                   // ডিসপ্লে ফাংশন রেজিস্টার
    glutMainLoop();                             // মেইন লুপ চালু, ইভেন্ট হ্যান্ডেলিং
}
