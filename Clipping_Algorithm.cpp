/*
==================================================================================
    Note: এই প্রোগ্রামটি OpenGL ব্যবহার করে Cohen-Sutherland Line Clipping Algorithm
    বাস্তবায়ন করেছে। এটি একটি ক্লিপিং উইন্ডোর (xmin, ymin) থেকে (xmax, ymax) পর্যন্ত
    সীমানার ভিতরে এবং বাইরে থাকা লাইনগুলোকে শনাক্ত করে এবং ক্লিপ করে।

    প্রোগ্রামটিতে তিনটি ভিন্ন ধরনের লাইন ড্র করা হয়:
    1) সম্পূর্ণ ক্লিপিং উইন্ডোর ভিতরে থাকা লাইন (লাল রঙে)
    2) সম্পূর্ণ ক্লিপিং উইন্ডোর বাইরে থাকা লাইন (নীল রঙে)
    3) ক্লিপিং উইন্ডোর বাইরে থাকা এবং আংশিক ভিতরে থাকা লাইন (সবুজ রঙে)

    তারপর ক্লিপিং অ্যালগরিদম ব্যবহার করে আংশিক ভিতরে থাকা লাইনের
    ক্লিপ হওয়া অংশ (অর্থাৎ উইন্ডোর ভিতরে থাকা অংশ) হলুদ রঙে দেখানো হয়।

    ক্লিপিং এর জন্য কোডটি নিচের ধাপগুলো অনুসরণ করে:
    - computeCode() ফাংশন লাইনটির প্রতিটি পয়েন্টের অবস্থান নির্ধারণ করে (উইন্ডোর কোন সাইডে)
    - cohenSutherlandClip() ফাংশন লাইনটির শুরু ও শেষ পয়েন্টের কোড দেখে
      লাইনটি পুরোপুরি গ্রহণযোগ্য, পুরোপুরি প্রত্যাখ্যাত, অথবা আংশিক ক্লিপিংয়ের মধ্য থেকে সিদ্ধান্ত নেয়।
    - যদি লাইন আংশিক ক্লিপ হয়, তাহলে এর প্রান্তগুলো নতুন করে নির্ধারণ করে উইন্ডোর ভিতর আনা হয়।

    OpenGL এর মাধ্যমে ক্লিপিং উইন্ডো এবং লাইনগুলো যথাক্রমে সাদা, লাল, নীল, সবুজ এবং হলুদ রঙে
    প্রদর্শিত হয়, যা কোডের লজিক বুঝতে সহায়তা করে।

    Important OpenGL calls:
    - gluOrtho2D(-300, 300, -300, 300): 2D ভিউ সেট করে ক্লিপিং উইন্ডোর চারপাশে বড় জায়গা দেয়।
    - glBegin(GL_LINE_LOOP) এবং glVertex2f(): ক্লিপিং উইন্ডোর বর্ডার ড্র করে।
    - glBegin(GL_LINES): বিভিন্ন লাইনগুলো ড্র করে।

==================================================================================
*/

#include <windows.h>
#include <GL/glut.h>

// Window-এর ভিতরে clipping region define করা হচ্ছে (xmin,ymin) থেকে (xmax,ymax)
float xmin = -100, ymin = -100, xmax = 100, ymax = 100;

// তিনটি লাইন ডিফাইন করা হচ্ছে - 
// ১. সম্পূর্ণভাবে clipping box এর ভিতরে
float x1_inside = -50, y1_inside = -50, x2_inside = 50, y2_inside = 50;
// ২. সম্পূর্ণভাবে clipping box এর বাইরে
float x1_outside = -250, y1_outside = -250, x2_outside = -200, y2_outside = -200;
// ৩. আংশিক clipping box এর ভিতরে এবং আংশিক বাইরে
float x1_partial = -200, y1_partial = -200, x2_partial = 50, y2_partial = 50;

// clipping এর পর new line segment এর কোঅর্ডিনেট গুলো রাখার জন্য global variables
float cx1, cy1, cx2, cy2;

// কোড নির্ণয় করার ফাংশন: 
// point (x,y) clipping box এর কোন দিকে/বাইরে আছে তা bitmask হিসেবে রিটার্ন করে
// ১ -> left, ২ -> right, ৪ -> bottom, ৮ -> top
int computeCode(float x, float y) {
    int code = 0;
    if (x < xmin) code |= 1;    // left
    if (x > xmax) code |= 2;    // right
    if (y < ymin) code |= 4;    // bottom
    if (y > ymax) code |= 8;    // top
    return code;
}

// Cohen-Sutherland clipping algorithm
// ইনপুট: লাইনের দুটি পয়েন্ট (x1,y1) এবং (x2,y2)
// আউটপুট: clipping করা লাইন এর নতুন পয়েন্ট (cx1, cy1), (cx2, cy2)
// রিটার্ন: true হলে লাইন clipping box এর ভিতরে বা আংশিক ভিতরে আছে, false হলে পুরোপুরি বাইরে
bool cohenSutherlandClip(float x1, float y1, float x2, float y2, float& cx1, float& cy1, float& cx2, float& cy2) {
    int code1 = computeCode(x1, y1);  // প্রথম পয়েন্টের কোড
    int code2 = computeCode(x2, y2);  // দ্বিতীয় পয়েন্টের কোড
    bool accept = false;

    while (true) {
        if ((code1 | code2) == 0) {
            // দুই পয়েন্টই clipping box এর ভিতরে - সম্পূর্ণ লাইন গ্রহণযোগ্য
            accept = true;
            cx1 = x1; cy1 = y1;
            cx2 = x2; cy2 = y2;
            break;
        }
        else if (code1 & code2) {
            // দুই পয়েন্টের একই বাইরের region আছে -> লাইন সম্পূর্ণ clipping box এর বাইরে
            break;
        }
        else {
            // লাইন partially clipping box এর বাইরে -> clipping করতে হবে
            int codeOut = code1 ? code1 : code2; // বাইরের পয়েন্ট নির্বাচন

            float x, y;

            // clipping box এর কোন সীমানায় লাইন কাটতে হবে সেটি নির্ণয়
            if (codeOut & 8) {          // উপরের সীমানা
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & 4) {     // নিচের সীমানা
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & 2) {     // ডান সীমানা
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (codeOut & 1) {     // বাম সীমানা
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // বাইরের পয়েন্ট এর স্থান পরিবর্তন clipping point এ করা হচ্ছে
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

    // clipping সফল হলে নতুন পয়েন্ট রিটার্ন করা হচ্ছে
    if (accept) {
        cx1 = x1;
        cy1 = y1;
        cx2 = x2;
        cy2 = y2;
    }

    return accept;
}

// OpenGL display ফাংশন: সবকিছু রেন্ডার করার জন্য
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Clipping box (white রঙে) আঁকা
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmin, ymax);
    glVertex2f(xmax, ymax);
    glVertex2f(xmax, ymin);
    glEnd();

    glLineWidth(2);

    // সম্পূর্ণ clipping box এর ভিতরে থাকা লাইন (লাল)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x1_inside, y1_inside);
    glVertex2f(x2_inside, y2_inside);
    glEnd();

    // সম্পূর্ণ clipping box এর বাইরে থাকা লাইন (নীল)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(x1_outside, y1_outside);
    glVertex2f(x2_outside, y2_outside);
    glEnd();

    // আংশিক clipping box এর ভিতরে ও বাইরে থাকা লাইন (সবুজ)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x1_partial, y1_partial);
    glVertex2f(x2_partial, y2_partial);
    glEnd();

    // আংশিক লাইনের clipping করে yellow রঙে clipping করা অংশ দেখানো
    if (cohenSutherlandClip(x1_partial, y1_partial, x2_partial, y2_partial, cx1, cy1, cx2, cy2)) {
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2f(cx1, cy1);
        glVertex2f(cx2, cy2);
        glEnd();
    }

    glFlush();
}

// OpenGL সেটআপ ফাংশন: ব্যাকগ্রাউন্ড কালার, projection সেট করা হচ্ছে
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);       // কালো ব্যাকগ্রাউন্ড
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -300, 300);       // 2D orthographic projection সেট করা
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // single buffer ও RGB মোড
    glutInitWindowSize(700, 700);                  // উইন্ডোর সাইজ
    glutInitWindowPosition(100, 100);              // উইন্ডোর পজিশন
    glutCreateWindow("Cohen-Sutherland Clipping - 3 Cases"); // উইন্ডোর টাইটেল
    init();
    glutDisplayFunc(display);                      // display callback সেট
    glutMainLoop();                                // main loop শুরু
    return 0;
}
