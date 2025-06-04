/*
 * এই প্রোগ্রামটি OpenGL এবং GLUT ব্যবহার করে দুটি ত্রিভুজ স্ক্রিনে ড্র করে,
 * যেখানে দ্বিতীয় ত্রিভুজটি প্রথম ত্রিভুজ থেকে নির্দিষ্ট দূরত্বে (translation) সরানো হয়েছে।
 *
 * ১. drawTriangle ফাংশন:
 *    - তিনটি বিন্দু (x, y) নিয়ে একটি ত্রিভুজ আকারে পলিগন ড্র করে।
 *
 * ২. display ফাংশন:
 *    - প্রথমে স্ক্রিন পরিষ্কার করে (সাদা ব্যাকগ্রাউন্ড)।
 *    - নীল রঙে (0.0, 0.0, 1.0) প্রথম ত্রিভুজ ড্র করা হয়, যার কোঅর্ডিনেটস হলো (ax, ay), (bx, by), (cx, cy)।
 *    - তারপর কমলা রঙে (1.0, 0.5, 0.0) দ্বিতীয় ত্রিভুজ ড্র করা হয়, যেটি প্রথম ত্রিভুজ থেকে (dx, dy) দ্বারা সরানো হয়েছে।
 *
 * ৩. init ফাংশন:
 *    - ব্যাকগ্রাউন্ড রঙ সাদা সেট করে।
 *    - ২D অর্থোগ্রাফিক ভিউপোর্ট -1 থেকে 1 পর্যন্ত এক্স ও ওয়াই এরিয়া সেট করা হয়।
 *
 * ৪. main ফাংশন:
 *    - উইন্ডোর আকার এবং অবস্থান সেট করে।
 *    - "Translated Triangle Visualization" নামের উইন্ডো তৈরি করে।
 *    - প্রদর্শনের জন্য display ফাংশন রেজিস্টার করে।
 *    - GLUT এর মেইন লুপ শুরু করে যা উইন্ডো ও রেন্ডারিং নিয়ন্ত্রণ করে।
 *
 * মূলত, এই প্রোগ্রামটি ত্রিভুজের স্থানান্তর (translation) কনসেপ্ট বুঝানোর জন্য একটি সহজ OpenGL উদাহরণ।
 */


 #include <GL/glut.h>  // OpenGL Utility Toolkit লাইব্রেরি

// ত্রিভুজের তিনটি বিন্দুর কোঅর্ডিনেট
float ax = -0.3, ay = -0.3;
float bx = 0.0, by = 0.4;
float cx = 0.3, cy = -0.3;

// ট্রান্সলেশন বা সরানোর জন্য x ও y এর মান
float dx = 0.4;
float dy = 0.4;

// ত্রিভুজ ড্র করার ফাংশন - ৩টি পয়েন্ট নেয়
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_POLYGON);       // পলিগন শুরু
    glVertex2f(x1, y1);        // প্রথম বিন্দু
    glVertex2f(x2, y2);        // দ্বিতীয় বিন্দু
    glVertex2f(x3, y3);        // তৃতীয় বিন্দু
    glEnd();                   // পলিগন শেষ
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // পর্দা পরিষ্কার করা

    // প্রথম ত্রিভুজের রঙ সেট (নীল)
    glColor3f(0.0, 0.0, 1.0);
    // মূল ত্রিভুজ ড্র করা
    drawTriangle(ax, ay, bx, by, cx, cy);

    // দ্বিতীয় ত্রিভুজের রঙ সেট (কমলা)
    glColor3f(1.0, 0.5, 0.0);
    // প্রথম ত্রিভুজের প্রত্যেক বিন্দু dx ও dy যোগ করে সরানো হয়েছে
    drawTriangle(ax + dx, ay + dy, bx + dx, by + dy, cx + dx, cy + dy);

    glFlush();  // OpenGL কমান্ড রেন্ডার করা
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // পর্দার ব্যাকগ্রাউন্ড রঙ সাদা
    glMatrixMode(GL_PROJECTION);        // প্রজেকশন ম্যাট্রিক্স সেট
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // 2D অরথোগ্রাফিক ভিউপোর্ট সেট করা (-1 থেকে 1)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                // GLUT ইনিশিয়ালাইজ
    glutInitWindowSize(800, 600);         // উইন্ডোর সাইজ
    glutInitWindowPosition(150, 100);     // উইন্ডোর পজিশন
    glutCreateWindow("Translated Triangle Visualization");  // উইন্ডো তৈরি ও শিরোনাম
    init();                              // ইনিশিয়ালাইজ ফাংশন কল
    glutDisplayFunc(display);            // ডিসপ্লে ফাংশন সেট
    glutMainLoop();                      // মেইন লুপ শুরু

    return 0;
}
