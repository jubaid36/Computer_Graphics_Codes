/*
============================================================================
    Note: এই প্রোগ্রামটি OpenGL ব্যবহার করে Bresenham's Line Drawing 
    Algorithm বাস্তবায়ন করে। এটি দুটি নির্দিষ্ট পয়েন্ট (x, y) এবং 
    (x_end, y_end) এর মধ্যে একটি সরল রেখা (line) আঁকে।

    Bresenham's Algorithm একটি efficient এবং accurate লাইন আঁকার 
    অ্যালগরিদম যা শুধুমাত্র পূর্ণসংখ্যা ব্যবহার করে এবং ফ্লোটিং পয়েন্ট
    ক্যালকুলেশন ছাড়াই লাইন ড্র করতে পারে।

    এই প্রোগ্রামটি OpenGL এর glBegin(GL_POINTS) এবং glVertex2i()
    ফাংশন ব্যবহার করে প্রতিটি পিক্সেল পয়েন্ট আলাদাভাবে স্ক্রিনে আঁকে।

    কোডটি Windows এবং GLUT (OpenGL Utility Toolkit) লাইব্রেরি ব্যবহার করে 
    একটি উইন্ডো তৈরি করে যেখানে ঐ রেখাটি প্রদর্শিত হয়।
============================================================================
*/

#include <windows.h>        // Windows OS এর জন্য প্রয়োজনীয় হেডার ফাইল
#include <GL/glut.h>        // OpenGL Utility Toolkit এর হেডার ফাইল, যা window তৈরি ও rendering সহজ করে

// লাইন আঁকার জন্য শুরু এবং শেষ পয়েন্টের কো-অর্ডিনেট
int x = 100, y = 200, x_end = 300, y_end = 400;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);           // আগের সব কিছু মুছে ফেলে নতুনভাবে আঁকার জন্য স্ক্রিন পরিষ্কার করে
    glMatrixMode(GL_PROJECTION);           // Projection ম্যাট্রিক্স নির্বাচন করা হয়
    glLoadIdentity();                      // ম্যাট্রিক্স রিসেট করে
    gluOrtho2D(0, 640, 0, 480);            // 2D অরথোগ্রাফিক ভিউ সেট করে (0,0) থেকে (640,480) পর্যন্ত

    glPointSize(3);                        // পয়েন্টের সাইজ ৩ পিক্সেল সেট করা হয়
    glBegin(GL_POINTS);                   // এখন পয়েন্ট আঁকা শুরু হবে

    // Bresenham's Line Algorithm এর জন্য প্রয়োজনীয় ভ্যারিয়েবল তৈরি
    int dx = abs(x_end - x);              // X দূরত্বের মান (positive নেওয়া হয়)
    int dy = abs(y_end - y);              // Y দূরত্বের মান (positive নেওয়া হয়)
    int sx = (x_end > x) ? 1 : -1;        // X-দিক কোন দিকে যাবে তা নির্ধারণ (positive না negative)
    int sy = (y_end > y) ? 1 : -1;        // Y-দিক কোন দিকে যাবে তা নির্ধারণ
    int curr_x = x, curr_y = y;           // বর্তমান পয়েন্টের অবস্থান
    int p = 2 * dy - dx;                  // প্রাথমিক decision parameter

    // যদি লাইনটি X-অ্যাক্সিসে বেশি বিস্তৃত হয় (gentle slope)
    if (dx > dy) {
        for (int i = 0; i <= dx; i++) {   // X অনুযায়ী loop চলবে
            glVertex2i(curr_x, curr_y);   // পিক্সেল আঁকা হবে (x, y)
            curr_x += sx;                 // X-এ এক ধাপ এগোবে
            if (p >= 0) {                 // যদি decision parameter ধনাত্মক হয়
                curr_y += sy;            // Y-ও এক ধাপ এগোবে
                p -= 2 * dx;             // p আপডেট হবে
            }
            p += 2 * dy;                  // p সবসময় আপডেট হবে
        }
    }
    // যদি লাইনটি Y-অ্যাক্সিসে বেশি বিস্তৃত হয় (steep slope)
    else {
        p = 2 * dx - dy;                  // নতুনভাবে p হিসেব করা হয়
        for (int i = 0; i <= dy; i++) {   // Y অনুযায়ী loop চলবে
            glVertex2i(curr_x, curr_y);   // পিক্সেল আঁকা হবে
            curr_y += sy;                 // Y-এ এক ধাপ এগোবে
            if (p >= 0) {                 // যদি p ধনাত্মক হয়
                curr_x += sx;            // X-ও এক ধাপ এগোবে
                p -= 2 * dy;             // p আপডেট হবে
            }
            p += 2 * dx;                  // p সবসময় আপডেট হবে
        }
    }

    glEnd();              // পয়েন্ট আঁকা শেষ
    glFlush();            // সব আঁকা শেষ হলে স্ক্রিনে দেখানো হয়
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);                             // GLUT initialize করে
    glutInitWindowSize(640, 480);                      // উইন্ডোর সাইজ নির্ধারণ করে (width, height)
    glutInitWindowPosition(10, 10);                    // স্ক্রিনে উইন্ডোর পজিশন নির্ধারণ
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); // display mode: RGB color, single buffer, depth enabled
    glutCreateWindow("Bresenham's Line Drawing Algorithm");    // একটি উইন্ডো তৈরি হয় এই টাইটেল দিয়ে

    glutDisplayFunc(display);                         // display ফাংশনটি কল করা হবে যখন রেন্ডার করতে হবে
    glutMainLoop();                                   // main loop চালানো হয়, যাতে উইন্ডো চালু থাকে

    return 0;                                         // প্রোগ্রাম শেষ
}
