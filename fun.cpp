#include <iostream>
#include <stdio.h>
#include "extras.h"
#include <vector>
#include <string>
#include <algorithm>
#include <graphics.h>
#include <climits>
#include <fstream>
#include <stdlib.h>

using namespace std;

int fullArea(vector<Rect> rs);

void printVector(vector<Rect> vv)
{
    for (size_t i = 0; i < vv.size(); i++)
    {
        cout << vv[i].print() << " ";
    }
    cout << "\n";
}

bool compareArea(Rect r1, Rect r2)
{
    return (r1.w * r1.h > r2.w * r2.h);
}

vector<Rect> load(char *name)
{
    //  FUNCION ENCARGADA DE CARGAR LOS DATOS DESDE EL INPUT
    FILE *fp;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    fscanf(fp, "%d", &N);
    fscanf(fp, "%d", &W);
    int id, w, h;
    vector<Rect> all;
    all.reserve(N);
    for (int i = 0; i < N; i++)
    {
        fscanf(fp, "%d %d %d", &id, &w, &h);
        if (w > h)
        {
            all.push_back(Rect(id, w, h));
        }
        else
        {
            all.push_back(Rect(id, h, w));
            all.back().change = true;
        }
    }
    sort(all.begin(), all.end(), compareArea);
    area = fullArea(all);
    fclose(fp);
    return all;
}

Point::Point(int xx, int yy)
{
    x = xx;
    y = yy;
}

Point::Point() {}

void Solution::add(Rect r)
{
    all.push_back(r);
}

void Solution::pop()
{
    all.pop_back();
}

pair<bool, int> Solution::checkPoint(Point p1)
{
    //ESTA FUNCION SE ENCARGA DE CHECKEAR SI UN PUNTO ESTA DISPONIBLE DENTRO DE LA GRILLA DE SOLUCION
    pair<bool, int> info;
    for (Rect rr : all)
    {
        // cout << rr.print();
        if (rr.left.x <= p1.x && p1.x < rr.right.x && rr.left.y <= p1.y && p1.y < rr.right.y)
        {
            info.first = false;
            info.second = rr.right.x;
            return info;
        }
    }
    info.first = true;
    info.second = -1;
    return info;
}

pair<bool, int> Solution::check(Rect r1)
{
    //ESTA FUNCION SE ENCARGA DE CHECKEAR LA POSICION Y ROTACION
    // DE UN RECTANGULO ESTA DISPONIBLE DENTRO DE LA GRILLA DE SOLUCION
    pair<bool, int> p1(true, -1);
    int c = 0;
    for (Rect rr : all)
    {
        if (max({r1.left.x - rr.right.x,
                 rr.left.x - r1.right.x,
                 r1.left.y - rr.right.y,
                 rr.left.y - r1.right.y}) < 0)
        {
            p1.first = false;
            p1.second = c;
            return p1;
        }
        c += 1;
    }
    if (r1.right.x > W)
    {
        p1.first = false;
        p1.second = -2;
        return p1;
    }
    return p1;
}

// TODO DRAWER ESTA DESHABILITADO, PERO SE UTILIZA PARA TENER UNA INSTANCIA GRAFICA SOBRE EL PROBLEMA,
// NORMALMANTE NO SE PUEDE ACTIVAR YA QUE REQUIERE UNA LIBRERIA DEPRECADA

Drawer::Drawer(){};
void Drawer::init(vector<Rect> rects)
{
    int sum = 0;
    for (Rect r : rects)
    {
        sum += max({r.w, r.h});
    }
    cout << best << "\n";
    scale = ((float)(400) / (float)best);
    cout << scale << "\n";
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    // settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
};

void Drawer::draw(Solution sol)
{
    cleardevice();
    setcolor(15);
    int c = 0;
    char number[10];
    for (Rect rr : sol.all)
    {
        // sprintf(number, "%d", c);
        rectangle(4 * rr.left.x * scale, rr.left.y * scale,
                  4 * rr.right.x * scale, rr.right.y * scale);
        outtextxy(4 * scale * (rr.left.x + rr.right.x) / 2,
                  scale * (rr.left.y + rr.right.y) / 2,
                  number);
        // outtextxy(20, 20 + 20, "Program to print different fonts in C graphics");
        c += 1;
    }
    setcolor(4);
    if (best != INT_MAX)
    {
        line(0, best * scale, 800, best * scale);
    }
}

bool comp(Rect r1, Rect r2)
{
    return (r1.right.y < r2.right.y);
}

int Solution::getMax()
{
    int currentMax = -1;
    for (Rect r : all)
    {
        if (r.right.y > currentMax)
        {
            currentMax = r.right.y;
        }
    }
    return currentMax;
}

void Drawer::drawLine(int height)
{
    setcolor(4);
    line(0, height, 800, height);
}

int Solution::getBest()
{
    int c = 0;
    for (Rect r : all)
    {
        if (r.right.y == best)
        {
            return c;
        }
        c += 1;
    }
    return c;
}

bool compareID(Rect i1, Rect i2) 
{ 
    return (i1.id < i2.id); 
} 

void Solution::storeSolution()
{
    vector<Rect> vect2;
    Point temp;
    for (Rect e : all)
    {
        if (e.change){
            vect2.push_back(Rect(e.id, e.h, e.w));
        } else {
            vect2.push_back(Rect(e.id, e.w, e.h));
        }
        
        vect2.back().left = Point(e.left.x, e.left.y);
        vect2.back().right = Point(e.right.x, e.right.y);
        vect2.back().rot = e.rot;
    }
    sort(vect2.begin(), vect2.end(), compareID); 


    FILE *fp = fopen(fileName, "a");
    fprintf(fp, "==================\n");
    fprintf(fp, "%d\n", best);
    fprintf(fp, "%d %.2f%% %lu\n", W * best, 100 * (float)((W * best) - area) / (W * best), iter);
    for (Rect e : all)
    {
        fprintf(fp, "%d %d %d\n", e.left.x, e.left.y, e.rot);
    }

    fclose(fp);
}

int fullArea(vector<Rect> rs)
{
    int sum = 0;
    for (Rect e : rs)
    {
        sum += e.w * e.h;
    }
    return sum;
}