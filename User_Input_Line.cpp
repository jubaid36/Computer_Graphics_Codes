/*
 * এই প্রোগ্রামটি OpenGL ব্যবহার করে একটি বর্গাকার আকৃতির (square) মূল চিত্র এবং
 * তার ৪৫ ডিগ্রি কোণে ঘোরানো রূপ স্ক্রিনে প্রদর্শন করে।
 *
 * ১. মূল আকৃতি (নীল রঙে) একটি বর্গ যা চারটি কোণের (ax,ay), (bx,by), (cx,cy), (dx,dy) দ্বারা সংজ্ঞায়িত।
 *
 * ২. rotate() ফাংশন:
 *    - এটি একটি পয়েন্টকে নির্দিষ্ট কেন্দ্র (centerX, centerY) এর চারপাশে নির্দিষ্ট কোণে (angle) ঘোরায়।
 *    - কোণকে ডিগ্রি থেকে রেডিয়ানে রূপান্তর করা হয়।
 *    - ট্রান্সলেশন ও রোটেশন ম্যাথমেটিক্স ব্যবহার করে পয়েন্ট ঘোরানো হয়।
 *
 * ৩. drawShape() ফাংশন:
 *    - চারটি বিন্দুর মধ্যকার রেখা (lines) আঁকে যা বর্গাকার আকৃতি তৈরি করে।
 *
 * ৪. display() ফাংশন:
 *    - ব্যাকগ্রাউন্ড পরিষ্কার করে,
 *    - নীল রঙে মূল আকৃতি আঁকে,
 *    - ওরেঞ্জ রঙে রোটেটেড আকৃতি আঁকে (৪৫ ডিগ্রি ঘোরানো),
 *    - এবং শেষেই রেন্ডারিং সম্পন্ন করে।
 *
 * ৫. init() ফাংশন:
 *    - ব্যাকগ্রাউন্ড কালার সেট করে (কালো),
 *    - ২D অরথোগ্রাফিক ভিউ সিস্টেম কনফিগার করে (-১ থেকে ১ পর্যন্ত এক্স ও ওয়াই)।
 *
 * ৬. main() ফাংশন:
 *    - GLUT ইনিশিয়ালাইজ করে,
 *    - উইন্ডো তৈরি করে এবং সেটআপ করে,
 *    - display() ফাংশনকে রেন্ডার কলব্যাক হিসেবে রেজিস্টার করে,
 *    - এবং মেইন লুপ চালু করে।
 *
 * সারমর্ম: এই প্রোগ্রামটি ২D-তে একটি বর্গাকার আকৃতিকে একটি নির্দিষ্ট কেন্দ্রের চারপাশে ঘোরানোর
 * প্রক্রিয়া প্রদর্শন করে এবং একই সঙ্গে মূল আকৃতিও দেখায়।
 */


 #include <GL/glut.h>
#include <cmath>  // গণিতের জন্য, বিশেষ করে sin, cos, এবং M_PI এর জন্য

// মূল চতুর্ভুজের চারটি কোণার কোঅর্ডিনেট (x,y)
float ax = -0.3, ay = -0.3;
float bx = 0.3, by = -0.3;
float cx = 0.3, cy = 0.3;
float dx = -0.3, dy = 0.3;

// রোটেশন এর জন্য এঙ্গেল (ডিগ্রি তে)
float angle = 45.0;

// রোটেশন এর কেন্দ্র (এখানে অরিজিন)
float centerX = 0.0, centerY = 0.0;

// ফাংশন: লাইন দিয়ে চার পাশ ড্র করবে (shape)
void drawShape(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_LINES);
    
    // চার কোণাকে লাইনের মাধ্যমে সংযুক্ত করা হচ্ছে
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glVertex2f(x2, y2);
    glVertex2f(x3, y3);

    glVertex2f(x3, y3);
    glVertex2f(x4, y4);

    glVertex2f(x4, y4);
    glVertex2f(x1, y1);

    glEnd();
}

// ফাংশন: পয়েন্টকে নির্দিষ্ট এঙ্গেল দিয়ে ঘোরানো (Rotation)
void rotate(float& x, float& y, float angle, float centerX, float centerY) {
    float radian = angle * (M_PI / 180.0);  // ডিগ্রি থেকে রেডিয়ান এ রূপান্তর
    float cosA = cos(radian);  // কসাইন
    float sinA = sin(radian);  // সাইন

    // পয়েন্টকে অরিজিন এর কাছে নিয়ে আসা (translate)
    float tempX = x - centerX;
    float tempY = y - centerY;

    // রোটেশন ম্যাট্রিক্স প্রয়োগ
    x = cosA * tempX - sinA * tempY + centerX;
    y = sinA * tempX + cosA * tempY + centerY;
}

// ডিসপ্লে ফাংশন - এখানে দুইটি shape ড্র করা হবে: মূল এবং রোটেটেড
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // পর্দা পরিষ্কার

    // মূল চতুর্ভুজ (নীল রঙে)
    glColor3f(0.0, 0.0, 1.0);
    drawShape(ax, ay, bx, by, cx, cy, dx, dy);

    // রোটেটেড চতুর্ভুজ (কমলা রঙে)
    glColor3f(1.0, 0.5, 0.0);
    // প্রতিটি কোণাকে রোটেট করা হচ্ছে নতুন ভেরিয়েবলে
    float ax_rot = ax, ay_rot = ay;
    rotate(ax_rot, ay_rot, angle, centerX, centerY);

    float bx_rot = bx, by_rot = by;
    rotate(bx_rot, by_rot, angle, centerX, centerY);

    float cx_rot = cx, cy_rot = cy;
    rotate(cx_rot, cy_rot, angle, centerX, centerY);

    float dx_rot = dx, dy_rot = dy;
    rotate(dx_rot, dy_rot, angle, centerX, centerY);

    drawShape(ax_rot, ay_rot, bx_rot, by_rot, cx_rot, cy_rot, dx_rot, dy_rot);

    glFlush();  // রেন্ডার শেষ
}

// ইনিশিয়ালাইজেশন ফাংশন
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // ব্যাকগ্রাউন্ড কালো
    glMatrixMode(GL_PROJECTION);       // প্রজেকশন ম্যাট্রিক্স নির্বাচন
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // ২D ভিউপোর্ট সেট
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotation Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
