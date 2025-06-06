/*
==================================================================================
    Note: এই প্রোগ্রামটি OpenGL ব্যবহার করে DDA (Digital Differential Analyzer) 
    অ্যালগরিদমের মাধ্যমে 2D লাইনের ড্রয়িং করে।

    কাজের ধাপ:
    - x, y থেকে শুরু করে x_end, y_end পর্যন্ত একটি সরলরেখা ড্র করা হয়।
    - DDA অ্যালগরিদমে মূলত স্টেপ নির্ধারণ করা হয়, যা নির্ভর করে
      x এবং y এর ডেল্টার (dx, dy) উপর।
    - স্টেপের সংখ্যার ভিত্তিতে x এবং y এর ইনক্রিমেন্ট (x_inc, y_inc) হিসাব করা হয়,
      যা প্রতিটি পিক্সেল বা পয়েন্টের অবস্থান নির্ধারণ করে।
    - লুপ চালিয়ে ধাপে ধাপে পয়েন্টগুলো প্লট করা হয়, ফলে একটি লাইন তৈরি হয়।

    OpenGL এ করা কাজ:
    - দুটি অক্ষ (X ও Y) সাদা লাইনে ড্র করা হয়েছে যাতে গ্রাফিক্স বোঝা সহজ হয়।
    - DDA অ্যালগরিদমের মাধ্যমে পয়েন্টগুলো ম্যাজেন্টা (গোলাপী) রঙে ড্র করা হয়েছে।
    - glPointSize(2.0) দিয়ে পয়েন্টগুলো একটু বড় করা হয়েছে যাতে স্পষ্ট দেখা যায়।

    গুরুত্বপূর্ণ:
    - fabs(dx) ও fabs(dy) ব্যবহার করে ইনক্রিমেন্ট এবং স্টেপের সংখ্যা ঠিক করা হয়।
    - এই কোডে একটি ভুল আছে: dy এর তুলনায় dx বারবার স্টেপ হিসেবে নেওয়া হয়েছে,
      এটিকে dy এর সঙ্গে তুলনা করা উচিত ছিল।

    প্রোগ্রামটি একটি উইন্ডো খুলবে এবং ওই উইন্ডোর মধ্যে লাইনের ড্রিং দেখাবে।

==================================================================================
*/

#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// লাইন এর শুরু এবং শেষ পয়েন্টের কোঅর্ডিনেট (x,y) ও (x_end,y_end)
float x = -0.5, y = -0.5, x_end = 0.5, y_end = 0.5;

void display()
{
    // স্ক্রীন ক্লিয়ার করা (কালার বাফার ফ্লাশ)
    glClear(GL_COLOR_BUFFER_BIT);

    // x ও y অক্ষ অঙ্কন - একটি সাদা রঙের ক্রস (axes)
    glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 1.0); // রং: সাদা
    glVertex2f(-1.0, 0.0);    // x অক্ষ শুরু (বাম)
    glVertex2f(1.0, 0.0);     // x অক্ষ শেষ (ডান)
    glVertex2f(0.0, -1.0);    // y অক্ষ শুরু (নীচে)
    glVertex2f(0.0, 1.0);     // y অক্ষ শেষ (উপরে)
    glEnd();

    // পয়েন্টের সাইজ সেট করা (প্রতি পয়েন্টের পিক্সেল সাইজ)
    glPointSize(2.0);

    // লাইন ড্র করবো যেটা DDA অ্যালগোরিদম ব্যবহার করে করা হবে
    glColor3f(1.0, 0.0, 1.0); // রং: ম্যাজেন্টা (গাঢ় গোলাপী)
    glBegin(GL_POINTS);

    // লাইন এর x ও y এর ডেল্টা (পরিবর্তন) হিসাব
    float dx = x_end - x;
    float dy = y_end - y;

    // কোন পরিবর্তন বেশি তার উপর নির্ভর করে স্টেপ নির্ধারণ করা হবে
    int steps;
    if (fabs(dx) > fabs(dy))
    {
        // x এর পরিবর্তন বেশি হলে x এর মান অনুযায়ী ধাপের সংখ্যা
        steps = (int)(fabs(dx) * 1000);
    }
    else {
        // y এর পরিবর্তন বেশি হলে y এর মান অনুযায়ী ধাপের সংখ্যা
        // লক্ষ্য করো, এখানে ভুল আছে, এটা y এর পরিবর্তন হওয়া উচিত কিন্তু dx আবার আছে
        // তাই এটা ঠিক করা দরকার: steps = (int)(fabs(dy) * 1000);
        steps = (int)(fabs(dy) * 1000); // এখানে dy হওয়া উচিত ছিল
    }

    // প্রতি ধাপে x ও y কতটুকু বাড়বে তা নির্ধারণ
    float x_inc = dx / steps;
    float y_inc = dy / steps;

    // DDA অ্যালগোরিদম অনুযায়ী পয়েন্ট গুলো প্লট করা
    for (int i = 0; i <= steps; i++)
    {
        glVertex2f(x, y); // বর্তমান পয়েন্টের অবস্থান এ পয়েন্ট আঁকো
        x += x_inc;       // x এর মান আপডেট করো পরবর্তী পয়েন্টের জন্য
        y += y_inc;       // y এর মান আপডেট করো পরবর্তী পয়েন্টের জন্য
    }
    glEnd();

    // OpenGL এর বাফার ফ্লাশ করো যাতে আঁকা দৃশ্যমান হয়
    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv); // GLUT লাইব্রেরি ইনিশিয়ালাইজ করা
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // সিঙ্গল বাফার মোড ও RGB কালার মোড সেট
    glutInitWindowSize(540, 480); // উইন্ডোর সাইজ সেট
    glutCreateWindow("DDA"); // উইন্ডোর টাইটেল
    glutDisplayFunc(display); // ড্র ফাংশন সেট করা যা রেন্ডারিং করবে
    glutMainLoop(); // মেইন লুপ চালু যা উইন্ডো দেখাবে ও ইভেন্ট হ্যান্ডেল করবে
    return 0;
}
