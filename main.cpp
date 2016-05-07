#include "tetris.h"

void Welcome();
void Menu();
void PLAY();

int main()
{
    Welcome();
    Menu();
    return 0;
}

void Welcome()
{
    HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE ); //kolory
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );//zloty
    cout << "\n\n\t\t\t=== TETRIS 2014! ===\n\n\n\t\t\t\t\tBy Bartek";
    Sleep(1500);
    system("cls");
}
 void PLAY()
 {
    Tetris gra;
    while (gra.sprawdz())
    {
        gra.show();
        Sleep(200);
        gra.ruch();
    }
 }
 void Menu()
 {
     HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE ); //kolory
     SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );//zloty
     cout <<"[1] - Graj\n[2] - sterowanie\n[0] - Wyjscie\nWybierz: ";
     int wybor;
     while (!(cin >> wybor))
     {
         cin.clear();
         while (cin.get() != '\n')
            continue;
         cout <<"Nie ma takiej opcji!\nWybierz ponownie: ";
     }
     switch(wybor)
     {
     case 1:
        PLAY();
        Menu();
        break;
     case 2:
         system("cls");
         cout << "Sterowanie:\nA - przesun w lewo\nD - przesun w prawo"
                "\nS - przesun w dol\nW - obrot\nP - pauza";
         cin.get();
         cin.get();
         system("cls");
         Menu();
         break;
     case 0:
        cout <<"\nZagraj jeszcze kiedys! :D";
        Sleep(2000);
        system("exit");
        break;
     default:
        Menu();
        break;
     }
 }
