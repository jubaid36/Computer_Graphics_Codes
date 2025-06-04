/*
 * এই প্রোগ্রামটি OpenGL ব্যবহার করে একটি ত্রিভুজকে দুই ভাবে স্কেল (বড় বা ছোট) করে দেখায়।
 *
 * - drawTriangle() ফাংশন তিনটি বিন্দু দিয়ে একটি ত্রিভুজ আঁকে।
 * - display() ফাংশনে প্রথমে নীল রঙে মূল ত্রিভুজের কোঅর্ডিনেটগুলোকে বড় স্কেলে (scaleX=1.5, scaleY=1.5) আকার পরিবর্তন করে আঁকা হয়।
 * - এরপর কমলা রঙে একই ত্রিভুজকে ছোট স্কেলে (scaleX2=0.5, scaleY2=0.5) স্কেল করে আঁকা হয়।
 * - ফলে, স্ক্রিনে দুটি ত্রিভুজ দেখা যাবে — একটি বড় এবং অন্যটি ছোট, তবে উভয়ই একই আকারের ত্রিভুজের স্কেল করা রূপ।
 * - init() ফাংশনে ব্যাকগ্রাউন্ড সাদা করে এবং 2D ভিউপোর্ট সেট করা হয়েছে (-1 থেকে 1 কোঅর্ডিনেটস)।
 *
 * এই প্রোগ্রামটি স্কেলিং কনসেপ্ট এবং 2D গ্রাফিক্সে এর প্রয়োগ দেখায়।
 */


 #include <GL/glut.h>

// ত্রিভুজের তিনটি বিন্দু (vertex) এর x, y কোঅর্ডিনেট
float ax = -0.3, ay = -0.3;
float bx = 0.0, by = 0.3;
float cx = 0.3, cy = -0.3;

// প্রথম ত্রিভুজের স্কেল (বড় করা) এর জন্য scale factor
float scaleX = 1.5;
float scaleY = 1.5;

// দ্বিতীয় ত্রিভুজের স্কেল (ছোট করা) এর জন্য scale factor
float scaleX2 = 0.5;
float scaleY2 = 0.5;

// ত্রিভুজ আঁকার ফাংশন, যেখানে তিনটি বিন্দু পয়েন্ট দেয়া হয়
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_POLYGON);       // বহুভুজ শুরু (ত্রিভুজের জন্য)
    glVertex2f(x1, y1);        // প্রথম বিন্দু
    glVertex2f(x2, y2);        // দ্বিতীয় বিন্দু
    glVertex2f(x3, y3);        // তৃতীয় বিন্দু
    glEnd();                   // বহুভুজ শেষ
}

// ডিসপ্লে ফাংশন — যা স্ক্রীনে ড্র হয়
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // স্ক্রীন ক্লিয়ার

    // নীল রঙে বড় করা ত্রিভুজ আঁকো
    glColor3f(0.0, 0.0, 1.0);
    drawTriangle(
        ax * scaleX, ay * scaleY,  // প্রথম বিন্দু স্কেল প্রয়োগ
        bx * scaleX, by * scaleY,  // দ্বিতীয় বিন্দু স্কেল প্রয়োগ
        cx * scaleX, cy * scaleY   // তৃতীয় বিন্দু স্কেল প্রয়োগ
    );

    // কমলা রঙে ছোট করা ত্রিভুজ আঁকো
    glColor3f(1.0, 0.5, 0.0);
    drawTriangle(
        ax * scaleX2, ay * scaleY2,
        bx * scaleX2, by * scaleY2,
        cx * scaleX2, cy * scaleY2
    );

    glFlush();  // সব ড্রিং সম্পন্ন করে স্ক্রীনে দেখাও
}

// OpenGL সেটআপ ফাংশন
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // ব্যাকগ্রাউন্ড সাদা
    glMatrixMode(GL_PROJECTION);        // প্রজেকশন ম্যাট্রিক্স মোড সক্রিয়
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // 2D ভিউপোর্ট নির্ধারণ
}

// মেইন ফাংশন — প্রোগ্রামের শুরু
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // GLUT শুরু
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // সিঙ্গেল বাফার ও RGB কালার মোড
    glutInitWindowSize(800, 600);               // উইন্ডোর সাইজ
    glutInitWindowPosition(100, 100);           // উইন্ডোর স্ক্রীনে অবস্থান
    glutCreateWindow("Triangle Scaling");       // উইন্ডোর টাইটেল
    init();                                     // ওপেনজিএল ইনিশিয়ালাইজ
    glutDisplayFunc(display);                    // ডিসপ্লে কলব্যাক ফাংশন সেট করা
    glutMainLoop();                             // ইভেন্ট লুপ শুরু
    return 0;
}
