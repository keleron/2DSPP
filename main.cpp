#include <iostream>
#include "extras.h"
#include <vector>
#include <climits>
#include <unistd.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;
int back(int level, pair<int, int> freeSpot);
void printSet(set<int> my_set);
int findMax(set<int> my_set);
int N, W, best, where, area, low;
string name;
bool super = true;
vector<Rect> all;
Solution ss;
unsigned int usecs = 10000;
char fileName[100];

int main(int argc, char *argv[])
{
    printf("\nINIT INSTANCE %s\n", argv[1]);
    all = load(argv[1]);
    best = INT_MAX;
    sprintf(fileName, "%s.log", argv[1]);


    FILE *fp = fopen(fileName, "w");
    fprintf(fp, "%d %d\n", N, W);
    fclose(fp);

    low = ceil((float)area / (float)W);
    pair<int, int> cords(0, 0);
    back(0, cords);
    printf("FINISH\n");
    usleep(usecs * 10);
    return 0;
}

int back(int level, pair<int, int> freeSpot)
{
    set<int> seto;
    if (level == N)
    {
        int height = ss.getMax();
        if (height < best)
        {
            best = height;
            where = ss.getBest();

            printf("\tNEW BEST: %d\n", best);
            ss.storeSolution();
            if (best == low)
                return -1;
            return where;
        }
        return (level - 1);
    }

    pair<int, int> cords;
    bool once = true;
    Rect r = all[level];
    int i = freeSpot.first, j = freeSpot.second;

    int xlim = W - 1;

    pair<bool, int> info;
    while (j < best)
    {
        while (i < xlim)
        {
            info = ss.checkPoint(Point(i, j));
            if (info.first == false)
            {

                i = info.second;
                continue;
            }
            else
            {
                if (once)
                {

                    cords.first = i;
                    cords.second = j;
                    once = false;
                }

                r.set(i, j);
                if (r.left.y + min(r.w, r.h) >= best)
                {
                    if (!seto.empty())
                    {

                        return findMax(seto);
                    }
                    return (level - 1);
                }
                for (size_t i = 0; i < 2; i++)
                {
                    if (r.right.y >= best)
                    {

                        continue;
                    }
                    pair<bool, int> info2 = ss.check(r);
                    if (info2.first)
                    {

                        ss.add(r);
                        where = back(level + 1, cords);

                        if (where != level)
                        {
                            ss.pop();
                            return where;
                        }

                        ss.pop();
                    }
                    else if (info2.second != -2)
                    {

                        seto.insert(info2.second);
                    }
                    r.rotate();
                }
            }
            i += 1;
        }

        i = 0;
        j += 1;
    }
    if (!seto.empty())
    {

        return findMax(seto);
    }
    return (level - 1);
}

int findMax(set<int> my_set)
{

    int max_element;
    if (!my_set.empty())
    {
        max_element = *(my_set.rbegin());
    }
    else
    {
        max_element = -1;
    }

    return max_element;
}

void printSet(set<int> my_set)
{

    cout << "Set: ";
    for (auto i : my_set)
        cout << i << " ";

    cout << '\n';
}