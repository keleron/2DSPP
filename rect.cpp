#include <iostream>
#include <stdio.h>
#include "extras.h"
#include <vector>
#include <string>

Rect::Rect(int idd, int ww, int hh)
{   
    id = idd;
    w = ww;
    h = hh;
}

void Rect::rotate(){
    if (rot == false){
        right.x = left.x + h;
        right.y = left.y + w;
    } else {
        right.x = left.x + w;
        right.y = left.y + h;
    }
    rot = !rot;
    return;
}

string Rect::print()
{
    return "(" + to_string(w) + "," + to_string(h) + ")";
}

void Rect::set(int x, int y){
    left.x = x;
    left.y = y;
    right.x = x+w;
    right.y = y+h;
}