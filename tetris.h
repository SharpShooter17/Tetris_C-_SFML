#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point{ int x, y;};

class Tetris
{
private:
    static const int X = 20; //wymiary planszy
    static const int Y = 21;
    enum STAN {EMPTY = ' ', SPADA = 219, LEZY = 177, POLE = 1};
    // pole odnoi sie do struktury spadajacego klocka
    STAN Field[X][Y]; //plansza

    struct SPADAJACY{ STAN klocek[9]; };
    Point klocekxy[9]; // wspolrzedne pojedynczego elementu klocka
    SPADAJACY FIGURA;
    // spadajace klocki!
    void down(); //posuwa klocek w dol
    void left(); //w lewo
    void right(); // w prawo
    void obrot(); // wykonuje obrot klocka
    void losuj(); //gdy klocek spadnie losuje nowy wraz z ksztaltem
    void ksztalt(); // nowy ksztalt klocka
    void upadl(); //sprawdza czy upadl klocek jesli tak to losuje nowy!
    void Reset_FIGURY(); // gdy figura upadnie jest ona resetowana i ustawiana na gorze
    void usun(); //usuwa plna linie
    void usuwa_pozostalosci_klockow();
    void Reset();// resetuje cala plansze
    unsigned Punkty;
    inline void set_points(unsigned x) { Punkty += x; }
public:
    Tetris() { Reset(); losuj();  set_points(0);} //konstruktor
    void show();//pokazuje plansze
    void ruch();//mowi samo za siebie
    bool sprawdz();// czy gra trwa?
};

#endif // TETRIS_H_INCLUDED
