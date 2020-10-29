#include "Labirynt.h"
#include "Punkt.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <windows.h>

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

Labirynt::Labirynt(int liczba_wierszy, int liczba_kolumn){  /// inicjalizacja labiryntu o rozmiarach n x m

    hOut = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );

    n = liczba_wierszy;
    m = liczba_kolumn;
    labirynt = new int*[n];
    for(int i = 0; i<n; i++){
        labirynt[i] = new int[m];
    }
}


Labirynt::wczytaj_z_pliku(string sciezka){   /// wczytuje labirynt zapisany w pliku do ktorego podajemy sciezke
                                             /// zalozenie, ze labirynt posiada przynajmniej jedna sciane na brzegu
    fstream plik_labirynt;
    plik_labirynt.open(sciezka, ios::in);

    string s;
    for(int i = 0; i<n; i++){
        getline(plik_labirynt,s);
        for(int j = 0; j<m; j++){
            if(s.at(j) == '*'){
                labirynt[i][j] = -11;
            }else
                labirynt[i][j] = -1;
        }
    }

    plik_labirynt.close();
}


Labirynt::wygeneruj(){      /// generuje labirynt, ktory ma sens i nie ma niedostepnych pol, najelepszy efekt dla nieparzystych wymiarow

    if(n < 10 || m < 10){
        cout << "Aby wygenerowac labirynt wymiary labiryntu musza byc niemniejsze niz 10!";
        exit(0);
    }
    cout << "Trwa generowanie labiryntu... Czekaj!" << endl;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            labirynt[i][j] = -11;
        }
    }
    if(n%2 == 0){
        n--;
        pom_x = true;
    }
    else
        pom_x = false;
    if(m%2 == 0){
        m--;
        pom_y = true;
    }
    else
        pom_y = false;
    srand (time(NULL));
    int x1 = rand()%n;
    int y1 = rand()%m;
    if(x1%2 == 0)
        x1 = (x1+1)%n;
    if(y1%2 == 0)
        y1 = (y1+1)%m;

    odwiedz(x1, y1);

    if(pom_x){
        n++;
    }
    if(pom_y){
        m++;
    }

    for(int i = 0; i<n; i++){
        labirynt[i][0] = -11;
        labirynt[i][m-1] = -11;
    }
    for(int i = 0; i<m; i++){
        labirynt[0][i] = -11;
        labirynt[n-1][i] = -11;
    }
}

void Labirynt::odwiedz(int x, int y){

    labirynt[x][y] = -1;
    int kierunki[4];
    kierunki[0] = NORTH;
    kierunki[1] = EAST;
    kierunki[2] = SOUTH;
    kierunki[3] = WEST;

    for (int i=0; i<4; ++i){     /// losowanie kolejnosci przechodzenia kierunkow

        int r = rand() & 3;
        int temp = kierunki[r];
        kierunki[r] = kierunki[i];
        kierunki[i] = temp;
    }

    for(int i = 0; i<4; i++){   /// przechodzenie kierunkow

        int kierunek_x = 0, kierunek_y = 0;
        switch (kierunki[i]){
            case NORTH: kierunek_y = -1; break;
            case SOUTH: kierunek_y = 1; break;
            case EAST: kierunek_x = 1; break;
            case WEST: kierunek_x = -1; break;
        }
        int x2 = x + (kierunek_x<<1);
        int y2 = y + (kierunek_y<<1);

        if(x2 > 0 && y2 > 0 && x2 < n && y2 < m){
            if(labirynt[x2][y2] == -11){
                labirynt[x2-kierunek_x][y2-kierunek_y] = -1;
                odwiedz(x2, y2);
            }
        }
    }
}


Labirynt::ustaw_pozycje(int start_x, int start_y, int koniec_x, int koniec_y){      /// ustawia pozycje startowa i koncowa dla labiryntu
                                                                                    /// sprawdzana jest poprawnosc podanych danych
    if(start_x < 0 || start_y < 0 || koniec_x < 0 || koniec_y < 0){
        cout << "Wspolrzedne nie moga byc ujemne ;)" << endl;
        exit(0);
    }
    if(start_x >= n || koniec_x >= n || start_y >= m || koniec_y >= m){
        cout << "Wspolrzedne poza tablica!" << endl;
        exit(0);
    }
    if(labirynt[start_x][start_y] == -11)
    {
        cout << "Nieprawidlowa wspolrzedna punktu startowego!" << endl;
        exit(0);
    }
    if(labirynt[koniec_x][koniec_y] == -11){
        cout << "Nieprawidlowa wspolrzedna punktu koncowego!" << endl;
        exit(0);
    }
    if(start_x == koniec_x && start_y == koniec_y){
        cout << "Blad. Wspolrzedne punktow sie pokrywaja!" << endl;
        exit(0);
    }

    START.x = start_x;
    START.y = start_y;
    KONIEC.x = koniec_x;
    KONIEC.y  = koniec_y;
    labirynt[START.x][START.y] = 0;
    labirynt[KONIEC.x][KONIEC.y] = -5;
}


Labirynt::ustaw_losowe_pozycje(){       /// ustawia losowe pozycje startowa i koncowa
                                        /// sprawdzana jest poprawnosc wylosowanych pozycji
    cout << "Trwa losowanie pozycji poczatkowej i koncowej... Czekaj!" << endl;
    srand (time(NULL));
    start_x = rand()%m;
    start_y = rand()%n;
    koniec_x = rand()%m;
    koniec_y = rand()%n;
    while(labirynt[start_y][start_x] == -11 || labirynt[koniec_y][koniec_x] == -11 || start_x == koniec_x || start_y == koniec_y){
        srand (time(NULL));
        start_x = rand()%m;
        start_y = rand()%n;
        koniec_x = rand()%m;
        koniec_y = rand()%n;
    }

    START.x = start_x;
    START.y = start_y;
    KONIEC.x = koniec_x;
    KONIEC.y  = koniec_y;
    labirynt[START.y][START.x] = 0;
    labirynt[KONIEC.y][KONIEC.x] = -5;
}

Labirynt::wyszukaj_najktrotsza_droge(){

    vector <Punkt> kolejka;
    kolejka.push_back(START);
    labirynt[START.y][START.x] = 0;
    Punkt obecny_punkt = Punkt(0,0);
    Punkt pomocniczy_punkt = Punkt(0,0);
    Punkt koncowy_punkt = Punkt(0,0);

    while(kolejka.size()>0){
        obecny_punkt = kolejka.at(0);
        kolejka.erase(kolejka.begin());

        if(labirynt[obecny_punkt.y+1][obecny_punkt.x] == -5){
            cout << "ZNALAZLEM!!!" << endl;
            koncowy_punkt.x = obecny_punkt.x;
            koncowy_punkt.y = obecny_punkt.y+1;
            d_max = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            break;
        }else if(labirynt[obecny_punkt.y+1][obecny_punkt.x] == -1){
            labirynt[obecny_punkt.y+1][obecny_punkt.x] = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            pomocniczy_punkt.x = obecny_punkt.x;
            pomocniczy_punkt.y = obecny_punkt.y+1;
            kolejka.push_back(pomocniczy_punkt);
        }

        if(labirynt[obecny_punkt.y-1][obecny_punkt.x] == -5){
            cout << "ZNALAZLEM!!!" << endl;
            koncowy_punkt.x = obecny_punkt.x;
            koncowy_punkt.y = obecny_punkt.y-1;
            d_max = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            break;
        }else if(labirynt[obecny_punkt.y-1][obecny_punkt.x] == -1){
            labirynt[obecny_punkt.y-1][obecny_punkt.x] = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            pomocniczy_punkt.x = obecny_punkt.x;
            pomocniczy_punkt.y = obecny_punkt.y-1;
            kolejka.push_back(pomocniczy_punkt);

        }if(labirynt[obecny_punkt.y][obecny_punkt.x+1] == -5){
            cout << "ZNALAZLEM!!!" << endl;
            koncowy_punkt.x = obecny_punkt.x+1;
            koncowy_punkt.y = obecny_punkt.y;
            d_max = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            break;
        }else if(labirynt[obecny_punkt.y][obecny_punkt.x+1] == -1){
            labirynt[obecny_punkt.y][obecny_punkt.x+1] = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            pomocniczy_punkt.x = obecny_punkt.x+1;
            pomocniczy_punkt.y = obecny_punkt.y;
            kolejka.push_back(pomocniczy_punkt);
        }

        if(labirynt[obecny_punkt.y][obecny_punkt.x-1] == -5){
            cout << "ZNALAZLEM!!!" << endl;
            koncowy_punkt.x = obecny_punkt.x-1;
            koncowy_punkt.y = obecny_punkt.y;
            d_max = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            break;
        }else if(labirynt[obecny_punkt.y][obecny_punkt.x-1] == -1){
            labirynt[obecny_punkt.y][obecny_punkt.x-1] = labirynt[obecny_punkt.y][obecny_punkt.x]+1;
            pomocniczy_punkt.x = obecny_punkt.x-1;
            pomocniczy_punkt.y = obecny_punkt.y;
            kolejka.push_back(pomocniczy_punkt);
        }
    }

    int d = d_max;
    while(d>1){
        d--;
        if(labirynt[koncowy_punkt.y+1][koncowy_punkt.x] == d){
            labirynt[koncowy_punkt.y+1][koncowy_punkt.x] = -10;
            koncowy_punkt.y += 1;
        }else if(labirynt[koncowy_punkt.y-1][koncowy_punkt.x] == d){
            labirynt[koncowy_punkt.y-1][koncowy_punkt.x] = -10;
            koncowy_punkt.y -= 1;
        }else if(labirynt[koncowy_punkt.y][koncowy_punkt.x+1] == d){
            labirynt[koncowy_punkt.y][koncowy_punkt.x+1] = -10;
            koncowy_punkt.x += 1;
        }else if(labirynt[koncowy_punkt.y][koncowy_punkt.x-1] == d){
            labirynt[koncowy_punkt.y][koncowy_punkt.x-1] = -10;
            koncowy_punkt.x -= 1;
        }
    }
}


Labirynt::wyswietl(){

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(labirynt[i][j] == -11){
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN);
                cout << (char)219;
            }else if(labirynt[i][j] == 0){
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                SetConsoleTextAttribute( hOut, BACKGROUND_RED);
                cout << "S";
            }else if(labirynt[i][j] == -5){
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                SetConsoleTextAttribute( hOut, BACKGROUND_RED);
                cout << "M";
            }else if(labirynt[i][j] == -10){
                SetConsoleTextAttribute( hOut, BACKGROUND_BLUE);
                cout << " ";
            }else{
                SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
                cout << " ";
            }
        }
        cout << endl;
    }

    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    cout << "Dlugosc drogi: " << d_max << endl;     /// ilosc ruchow ktore nalezy zrobic aby dostac sie ze startu do konca
}


Labirynt::zapisz(string nazwa){        /// zapisuje labirynt do pliku txt o podanej nazwie(tylko sciany)

    fstream wynik;
    wynik.open(nazwa, ios::out);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(labirynt[i][j] == -11)
                wynik << "*";
            else
                wynik << " ";
        }
        wynik << endl;
    }
    wynik.close();
}

Labirynt::~Labirynt(){

    for(int i = 0; i<n; i++)
        delete [] labirynt[i];
    delete [] labirynt;
}
