#include "tetris.h"

HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE ); //kolory

void Tetris::losuj()
{
    ksztalt();
    Reset_FIGURY();
}
void Tetris::Reset_FIGURY() //resetuje figure spadajaca
{
    Field[0][Y/2] = FIGURA.klocek[0];
    Field[0][Y/2+1] = FIGURA.klocek[1];
    Field[0][Y/2+2] = FIGURA.klocek[2];
    Field[1][Y/2] = FIGURA.klocek[3];
    Field[1][Y/2+1] = FIGURA.klocek[4];
    Field[1][Y/2+2] = FIGURA.klocek[5];
    Field[2][Y/2] = FIGURA.klocek[6];
    Field[2][Y/2+1] = FIGURA.klocek[7];
    Field[2][Y/2+2] = FIGURA.klocek[8];
    klocekxy[0].y = Y/2;
    klocekxy[0].x = 0;
    klocekxy[1].y = Y/2 + 1;
    klocekxy[1].x = 0;
    klocekxy[2].y = Y/2 + 2;
    klocekxy[2].x = 0;
    klocekxy[3].y = Y/2;
    klocekxy[3].x = 1;
    klocekxy[4].y = Y/2 + 1;
    klocekxy[4].x = 1;
    klocekxy[5].y = Y/2 + 2;
    klocekxy[5].x = 1;
    klocekxy[6].y = Y/2 + 0;
    klocekxy[6].x = 2;
    klocekxy[7].y = Y/2 + 1;
    klocekxy[7].x = 2;
    klocekxy[8].y = Y/2 + 2;
    klocekxy[8].x = 2;
}

void Tetris::show()
{
    system("cls");
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY ); //zoltu
    cout <<"Punkty: "<<Punkty<<endl;
    string ramka(Y+2, 176);
    SetConsoleTextAttribute( hOut, BACKGROUND_RED ); // czerwone tlo
    cout<<ramka<<endl;
    for (int i = 3; i<X;i++)
    {
        SetConsoleTextAttribute( hOut, BACKGROUND_RED ); // czerwone tlo
        cout <<(char) 176 ;
            for (int j = 0; j<Y;j++)
            {
                for (int k = 0; k<9;k++)
                    if ( FIGURA.klocek[k] == POLE && klocekxy[k].x==i && klocekxy[k].y == j)
                    Field[i][j] = SPADA;
                    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
                    //seledynowy napis
                cout << (char) Field[i][j];
            }
        SetConsoleTextAttribute( hOut, BACKGROUND_RED ); // czerwone tlo
        cout << (char) 176 <<"\n";
    }
    SetConsoleTextAttribute( hOut, BACKGROUND_RED ); //czerwone tlo
    cout<<ramka<<endl;
    upadl();
    usuwa_pozostalosci_klockow();
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    // przywraca czarne tlo i szary napis
}

void Tetris::usuwa_pozostalosci_klockow()
{
    for (int i = 0; i<X;i++)
        for (int j = 0; j<Y;j++)
            if (Field[i][j] == SPADA)
                Field[i][j] = EMPTY;
}

void Tetris::Reset()
{
    for (int i = 0; i<X;i++)
        for (int j = 0; j<Y;j++)
            Field[i][j] = EMPTY;
}

void Tetris::down() // przesuwa klocek o jeden w dol
{
    for (int i = 0; i<9;i++)
        ++klocekxy[i].x;    //zmienia wspolrzedna x - przesuwa klocek o jeden w dol
}

void Tetris::left()
{
    for (int j = 0; j <9; j++)
        if ((Field[klocekxy[j].x][klocekxy[j].y-1] == LEZY && FIGURA.klocek[j] == POLE )||
                (klocekxy[j].y-1 == -1 && FIGURA.klocek[j] == POLE ))
            return;
        for (int i = 0; i<9;i++)
            --klocekxy[i].y;    //zmienia wspolrzedna y - przesuwa klocek o jeden w lewo
}

void Tetris::right()
{
    for (int j = 0; j <9; j++)
        if ((Field[klocekxy[j].x][klocekxy[j].y+1] == LEZY && FIGURA.klocek[j] == POLE) ||
                (klocekxy[j].y-1 == Y-2 && FIGURA.klocek[j] == POLE ))
            return;
    for (int i = 0; i<9;i++)
        ++klocekxy[i].y;    //zmienia wspolrzedna y - przesuwa klocek o jeden w prawo
}

 void Tetris::obrot()
 {
     if (klocekxy[4].y == Y-1 || klocekxy[4].y == 0
         || Field[klocekxy[4].x][klocekxy[4].y+1] == LEZY || Field[klocekxy[4].x][klocekxy[4].y-1] == LEZY)
        // zabezpieczenie przed obroceniem klocka poza plansze i na inny klocek
        return;

    SPADAJACY TEMP;
    TEMP = FIGURA;
    FIGURA.klocek[0] = TEMP.klocek[6];
    FIGURA.klocek[1] = TEMP.klocek[3];
    FIGURA.klocek[2] = TEMP.klocek[0];
    FIGURA.klocek[3] = TEMP.klocek[7];

    FIGURA.klocek[5] = TEMP.klocek[1];
    FIGURA.klocek[6] = TEMP.klocek[8];
    FIGURA.klocek[7] = TEMP.klocek[5];
    FIGURA.klocek[8] = TEMP.klocek[2];
 }

void Tetris::ruch()
{
    if (kbhit())
    {
        while (kbhit())
		{
        switch(getch())
        {
        case 'A':
        case 'a':
            left();
            break;
        case 'D':
        case 'd':
            right();
            break;
        case 'S':
        case 's':
            down();
            break;
        case 'w':
        case 'W':
            obrot();
            break;
        case 'P':
        case 'p':
            system("cls");
            SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );//zloty
            cout << "\n\n\t\t\t\tPauza!\n\t\tAby kontynuowac wcisnij dowolny klawisz!";
            getch();
            break;
        }
        show();
        Sleep(50);
        }
    }
    down();
    usun();
}

void Tetris::upadl()
{
    for (int i = 0; i<9;i++)
        if ( (klocekxy[i].x == X-1 && FIGURA.klocek[i] == POLE)
                    || (Field[klocekxy[i].x+1][klocekxy[i].y] == LEZY && FIGURA.klocek[i] == POLE ) ){
                for (int i=0;i<9;i++){
                        if ( Field[klocekxy[i].x][klocekxy[i].y] == SPADA)
                    Field[klocekxy[i].x][klocekxy[i].y] = LEZY;
                }
        set_points(25);
        losuj();
        }
}

void Tetris::usun() // usuwa pelna linie
{
    int licz;
    for (int i = 0; i<X; i++)
    {
        licz = 0;
        for (int j = 0; j<Y; j++){
            if ( Field[i][j] == LEZY)
                ++licz;
            if (licz == Y){
                for (int k = 0;k<Y;k++){
                    Field[i][k] = EMPTY;//usuwa pelna linie
                }
                for (int l = i; l>0;l--){// to ma przesuwac "wiszace" klocki w dol
                    for (int m = 0; m<Y; m++)
                    {
                        if (Field[l][m] == LEZY){
                            Field[l][m] = EMPTY;
                            Field[l+1][m] = LEZY;
                        }
                    }
                }
                set_points(100);
            }
        }
    }
}

bool Tetris::sprawdz()
{
    for (int i = 0; i<Y; i++){
        if (Field[3][i] == LEZY)
            return false;
    }
    return true;
}

void Tetris::ksztalt()// nadaje ksztalt klockowi
{
    time_t t;
    srand((unsigned) time(&t));

    /* tablica klocka
    0 1 2
    3 4 5
    6 7 8
     */

    switch( rand() % 9 + 1 )
    {
    case 1:
        /*   wzor klocka
        1 000
        2 111
        3 111
        */
        for (int i=3;i<9;i++)
            FIGURA.klocek[i] = POLE;

            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = EMPTY;
            FIGURA.klocek[2] = EMPTY;
            break;
    case 2:
        /*
        1 010
        2 010
        3 010
        */
            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = POLE;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = EMPTY;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = EMPTY;
            FIGURA.klocek[6] = EMPTY;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = EMPTY;
            break;
    case 3:
        /*
        1 1 0 0
        2 1 0 0
        3 1 1 0
        */
            FIGURA.klocek[0] = POLE;
            FIGURA.klocek[1] = EMPTY;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = POLE;
            FIGURA.klocek[4] = EMPTY;
            FIGURA.klocek[5] = EMPTY;
            FIGURA.klocek[6] = POLE;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = EMPTY;
            break;
    case 4:
        /*
        1 0 0 0
        2 1 1 0
        3 0 1 1
        */
            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = EMPTY;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = POLE;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = EMPTY;
            FIGURA.klocek[6] = EMPTY;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = POLE;
            break;
    case 5:
        /*
        1 0 0 0
        2 0 1 1
        3 1 1 0
        */
            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = EMPTY;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = EMPTY;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = POLE;
            FIGURA.klocek[6] = POLE;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = EMPTY;
            break;
    case 6:
        /*
        1 0 0 0
        2 0 1 0
        3 1 1 1
        */
            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = EMPTY;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = EMPTY;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = EMPTY;
            FIGURA.klocek[6] = POLE;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = POLE;
            break;
    case 7:
        /*
        1 1 1 1
        2 1 1 1
        3 1 1 1
        */
            FIGURA.klocek[0] = POLE;
            FIGURA.klocek[1] = POLE;
            FIGURA.klocek[2] = POLE;
            FIGURA.klocek[3] = POLE;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = POLE;
            FIGURA.klocek[6] = POLE;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = POLE;
            break;
    case 8:
        /*
        1 0 1 0
        2 0 1 0
        3 1 1 0
        */
            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = POLE;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = EMPTY;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = EMPTY;
            FIGURA.klocek[6] = POLE;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = EMPTY;
            break;
    case 9:
        /*
        1 1 1 1
        2 1 0 1
        3 1 1 1
        */
            FIGURA.klocek[0] = POLE;
            FIGURA.klocek[1] = POLE;
            FIGURA.klocek[2] = POLE;
            FIGURA.klocek[3] = POLE;
            FIGURA.klocek[4] = EMPTY;
            FIGURA.klocek[5] = POLE;
            FIGURA.klocek[6] = POLE;
            FIGURA.klocek[7] = POLE;
            FIGURA.klocek[8] = POLE;
            break;
    default:
        /*
        1 0 0 0
        2 0 1 0
        3 0 0 0
        */
            FIGURA.klocek[0] = EMPTY;
            FIGURA.klocek[1] = EMPTY;
            FIGURA.klocek[2] = EMPTY;
            FIGURA.klocek[3] = EMPTY;
            FIGURA.klocek[4] = POLE;
            FIGURA.klocek[5] = EMPTY;
            FIGURA.klocek[6] = EMPTY;
            FIGURA.klocek[7] = EMPTY;
            FIGURA.klocek[8] = EMPTY;
            break;
    }
}
