#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

extern int N, W, best, where, area;
extern string name;
extern char fileName[100];
extern long unsigned int iter;

class Point
{
public:
    int x, y;
    Point(int xx, int yy);
    Point();
};

class Rect
{
private:
    /* data */
public:
    int w, h,id;
    bool rot = false;
    Point left, right;
    Rect(int idd, int ww, int hh);
    string print();
    void rotate();
    void set(int x, int y);
};

class Solution
{
public:
    vector<Rect> all;
    void add(Rect r);
    void pop();
    pair<bool, int> checkPoint(Point p1);
    pair<bool, int> check(Rect r1);
    int  getMax();
    int  getBest();
    void storeSolution();
};

vector<Rect> load(char* name);
void printVector(vector<Rect> vv);

class Drawer {
    float scale;
    public:
        Drawer();
        void init(vector<Rect> rects);
        void draw(Solution sol);
        void drawLine(int height);
};


