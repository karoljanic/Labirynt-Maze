#ifndef LABIRYNT_H
#define LABIRYNT_H

#include "Punkt.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <windows.h>

using namespace std;

class Labirynt
{
    public:                 /// incjalizowanie i ustawianie parametrow powinno odbywac sie w podanej kolejnosci:
        Labirynt(int, int);
        wczytaj_z_pliku(string);
        wygeneruj();
        ustaw_losowe_pozycje();
        ustaw_pozycje(int, int, int, int);
        wyszukaj_najktrotsza_droge();
        wyswietl();
        zapisz(string);
        virtual ~Labirynt();

    private:
        HANDLE hOut;
        int n;  /// liczba wierszy: najlepiej aby byla to liczba nieparzysta i wieksza od 10
        int m;  /// liczba kolumn: najlepiej aby byla to liczba nieparzysta i wieksza od 10
        int **labirynt; /// tablica dynamiczna n x m reprezentujaca labirynt
        int start_x, start_y, koniec_x, koniec_y;
        Punkt START = Punkt(0,0);
        Punkt KONIEC = Punkt(0,0);
        int d_max=0;
        bool pom_x, pom_y;
        void odwiedz(int, int);
};

#endif // LABIRYNT_H
