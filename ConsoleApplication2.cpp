#include <iostream>
#include <windows.h>
#include <stdlib.h>
using namespace std;
int genislik = 15;
int yukseklik = 10;
int sayac = 0;
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
class Ekran {
public:
    Ekran(int x, int y)
    {
        ShowConsoleCursor(false);
        screenx = x;
        screeny = y;
        for (int i = 0; i < screeny; i++)
        {
            for (int j = 0; j < screenx; j++)
            {
                if (j == 0) {
                    screen[j][i] = 'I';
                }
                else if (i == 0 || i == screeny - 1) {
                    screen[j][i] = '-';
                }
                else {
                    screen[j][i] = ' ';
                }

            }
            cout << endl;
        }
    }
    void addChar(int x, int y, char c) {
        if (x != 0 && x != screenx - 1 && y != 0 && y != screeny - 1) {
            screen[x][y] = c;
        }
    }
    void moveChar(int x, int y, char c, int r, int l) {
        if (x != 0 && x != screenx - 1 && y != 0 && y != screeny - 1 && x + r != 0 && x + r != screenx - 1 && y + l != 0 && y + l != screeny - 1) {
            screen[x][y] = ' ';
            screen[x + r][y + l] = c;
        }
    }
    void drawScreen() {
        system("cls");
        for (int i = 0; i < screeny; i++) {
            for (int j = 0; j < screenx; j++) {
                cout << screen[j][i] << " ";
            }
            cout << endl;
        }
        cout << "SCORE : " << sayac << endl;
    }
private:
    char screen[100][100];
    int screenx;
    int screeny;
};
Ekran ekran(genislik, yukseklik);
class Top {
public:
    int posx;
    int posy;
    char a;
    int height;
    int yatay;
    int dusey;
    Top(int x, int y, char c, int h)
    {
        posx = x;
        posy = y;
        a = c;
        height = h;
        yatay = 1;
        dusey = 1;
    }
};
class Raket{
public:
    int posx;
    int posy;
    char a;
    int height;
    int dusey;
    Raket(int x, int y, char c, int h)
    {
        posx = x;
        posy = y;
        a = c;
        height = h;
        dusey = 1;
    }
};
Top top(1, 1, 'O', 1);
Raket raket(genislik - 2, 5, '|', 3);
class Moves{
public:
    void move(int mod)
    {
        if (mod == 0)
        {
            ekran.moveChar(top.posx, top.posy, top.a, top.yatay, top.dusey);
            top.posx = top.posx + top.yatay;
            top.posy = top.posy + top.dusey;
            if (top.posx == 1) {
                top.yatay = top.yatay * -1;
            }
            if ((top.posy == 1 && top.dusey == -1) || (top.posy == yukseklik - 2 && top.dusey == 1)) {
                top.dusey = top.dusey * -1;
            }
        }
        else
        {
            if (GetAsyncKeyState(VK_UP) && (raket.posy - 2) != 0)
            {
                for (int i = -1; i <= raket.height - 2; i++)
                {
                    ekran.moveChar(raket.posx, raket.posy + i, raket.a, 0, (raket.dusey * -1));
                }
                raket.posy--;
            }
            else if (GetAsyncKeyState(VK_DOWN) && (raket.posy + 2) != yukseklik - 1)
            {
                for (int i = 1; i >= -raket.height + 2; i--)
                {
                    ekran.moveChar(raket.posx, raket.posy + i, raket.a, 0, raket.dusey);
                }
                raket.posy++;
            }
            if (top.posx == raket.posx - 1 && ((top.posy <= (raket.posy + ((raket.height - 1) / 2))) && (top.posy >= (raket.posy - ((raket.height - 1) / 2)))))
            {
                top.yatay = top.yatay * -1;
                sayac++;
            }
            else if (top.posx == raket.posx)
            {
                cout << "GAME OVER\n";
                system("pause");
                top.posx = 1;
                top.posy = 1;
                top.yatay = 1;
                top.dusey = 1;
                sayac = 0;
            }
        }
    }
};
int main()
{
    Moves hareketler;
    ekran.addChar(1, 1, 'P');
    while (true) {
        hareketler.move(0);
        hareketler.move(1);
        ekran.drawScreen();
        Sleep(20);
    }
    system("pause");
    return 0;
}