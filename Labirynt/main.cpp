#include <iostream>
#include "Labirynt.h"

using namespace std;

int main()
{
/// znalezienie drogi miedzy losowo wybranymi pozycjami z wczytanego pliku-przykladu(labirynt.txt)
/*
    Labirynt lab = Labirynt(40,30);
    lab.wczytaj_z_pliku("labirynt.txt");
    lab.ustaw_losowe_pozycje();
    lab.wyszukaj_najktrotsza_droge();
    lab.wyswietl();
*/

/// znalezienie drogi pomiedzy podanymi pozycjami z wczytanego pliku-przykladu(labirynt.txt) bez bledow zwiazanych z pozycja
/*
    Labirynt lab = Labirynt(40,30);
    lab.wczytaj_z_pliku("labirynt.txt");
    lab.ustaw_pozycje(2,7,25,24);
    lab.wyszukaj_najktrotsza_droge();
    lab.wyswietl();

*/
/// znalezenie drogi pomiedzy podanymi pozycjami z wczytanego pliku-przykladu(labirynt.txt) z bledem: start = koniec
/*
    Labirynt lab = Labirynt(40,30);
    lab.wczytaj_z_pliku("labirynt.txt");
    lab.ustaw_pozycje(21,37,21,37);
    lab.wyszukaj_najktrotsza_droge();
    lab.wyswietl();
*/

/// znalezenie drogi pomiedzy podanymi pozycjami z wczytanego pliku-przykladu(labirynt.txt) z bledem: start lub stop znajduja sie na scianie
/*
    Labirynt lab = Labirynt(40,30);
    lab.wczytaj_z_pliku("labirynt.txt");
    lab.ustaw_pozycje(21,19,19,17);
    lab.wyszukaj_najktrotsza_droge();
    lab.wyswietl();
*/

/// znalezenie drogi pomiedzy podanymi pozycjami z wczytanego pliku-przykladu(labirynt.txt) z bledem: start lub stop znajduja sie poza labiryntem
/*
    Labirynt lab = Labirynt(40,30);
    lab.wczytaj_z_pliku("labirynt.txt");
    lab.ustaw_pozycje(7,45,30,24);
    lab.wyszukaj_najktrotsza_droge();
    lab.wyswietl();
*/

/// znalezenie drogi pomiedzy podanymi pozycjami z wczytanego pliku-przykladu(labirynt.txt) z bledem: podanie ujemnych wspolrzednych
/*
    Labirynt lab = Labirynt(40,30);
    lab.wczytaj_z_pliku("labirynt.txt");
    lab.ustaw_pozycje(7,-25,30,24);
    lab.wyszukaj_najktrotsza_droge();
    lab.wyswietl();
*/

/// tworzenie labiryntu, znalezienie najkrotszej drogi pomiedzy wylosowanymi polami startu i konca, zapis do pliku

    Labirynt labirynt = Labirynt(10,10);
    labirynt.wygeneruj();
    labirynt.ustaw_losowe_pozycje();
    //labirynt.ustaw_pozycje(1,1,37,197);
    labirynt.wyszukaj_najktrotsza_droge();
    labirynt.wyswietl();
    //labirynt.zapisz("fajny_labirynt.txt");



    return 0;
}
