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

//MUCHAS CONSTANTES QUE SE UTILIZARAN A LO LARGO DE TODO EL DOCUMENTO
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
long unsigned int iter;

int main(int argc, char *argv[])
{
    //LECTURA DEL INPUT
    printf("\nINIT INSTANCE %s\n", argv[1]);
    all = load(argv[1]);
    best = INT_MAX;
    sprintf(fileName, "%s.log", argv[1]);
    FILE *fp = fopen(fileName, "w");
    fprintf(fp, "%d %d\n", N, W);
    fclose(fp);
    //END LECTURA
    low = ceil((float)area / (float)W);
    pair<int, int> cords(0, 0);
    back(0, cords);
    printf("FINISH\n");
    usleep(usecs * 10);
    return 0;
}

int back(int level, pair<int, int> freeSpot)
{
    //CADA VEZ QUE SE ENTRA ACA ES DEBIDO A QUE LA INSTANCIACION ANTERIOR FUE UN EXITO
    iter++;
    set<int> seto;
    if (level == N)
    {
        //EN CASO DE QUE LA SOLUCION ES MEJOR SE REEMPLAZA Y SE ESCRIBE LA SOLUCION EN EL OUT.PUT
        int height = ss.getMax();
        if (height < best)
        {
            //NUEVO MEJOR SOLUCION
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

    //COMIENZO DE LA BUSQUEDA POR UN ESPACIO DISPONIBLE
    pair<int, int> cords;
    bool once = true;
    Rect r = all[level];
    int i = freeSpot.first, j = freeSpot.second;

    int xlim = W - 1;

    pair<bool, int> info;

    //ESTOS DOS WHILE SE ENCARGAN DE BUSCAR PUNTO POR PUNTO UN LUGAR DISPONIBLE
    while (j < best)
    {
        while (i < xlim)
        {
            //UNICAMENTE CHECKEA SI EL PUNTO ESTA DISPONIBLE, NO SI EL RECTANGULO ENCAJA
            info = ss.checkPoint(Point(i, j));
            if (info.first == false)
            {
                //SI NO ESTA DISPONIBLE HACE UN SALTO INTELIGENTE BASANDOSE EN LA DIMENSION DEL
                //RECTANGULO CON EL QUE SE COLISIONO
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
                //YA QUE ESTA DISPONIBLE SE SETEA EL RECTANGULO EN LA POSICION I,J
                r.set(i, j);
                if (r.left.y + min(r.w, r.h) >= best)
                {
                    if (!seto.empty())
                    {

                        return findMax(seto);
                    }
                    return (level - 1);
                }

                //Y SE PRUEBA CON AMBAS ROTACIONES
                for (size_t i = 0; i < 2; i++)
                {
                    if (r.right.y >= best)
                    {

                        continue;
                    }
                    pair<bool, int> info2 = ss.check(r);
                    if (info2.first)
                    {
                        //SI LA ROTACION ENCAJA EL RECTANGULO SE AGREGA Y PASA AL SIGUIENTE ELEMENTO

                        ss.add(r);
                        where = back(level + 1, cords);

                        if (where != level)
                        {
                            //WHERE REPRESENTA EL SALTO INTELIGENTE, POR LO TANTO HAY VECES QUE SALTARA
                            //MUCHO MAS QUE UN NIVEL HACIA ARRIBA
                            ss.pop();
                            return where;
                        }

                        ss.pop();
                    }
                    else if (info2.second != -2)
                    {
                        //SI NO LOGRA ENCARGAR SE INSERTARA EL CONFLICTO MAS PREMATURAMENTE INSTANCIADO
                        //EN UN CONJUNTO DEL NODO PADRE
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
        //CUANDO HAY UNA FALLA TOTAL, SE ELIGE EL MAYOR DE DEL CONJUNTO Y SE BUSCA SALTAR HACIA ESE NIVEL
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