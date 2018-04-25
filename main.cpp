#include <iostream>
#include "adhi_ganteng.h"
#include <windows.h>
#include <stdlib.h>

using namespace std;

struct Position
{
    int x;
    int y;
};

const int m_row = 27;
const int m_col = 27;
const char border = '0';
const char dead = '*';
const char alive = 'X';
char board[m_row][m_col];
int alive_neighbor = 0;
int alive_count_0 = 0;
int alive_count_1 = 0;
Position basic[3];

void Define(char board[m_row][m_col]);
void Print();
void Check_State(char board[m_row][m_col]);

int main()
{
    Define(board);
    Sleep(2000);
    ClearScreen();
    while (true)
    {
        Check_State(board);
        Sleep(2000);
        ClearScreen();
    }
    return 0;
}

void Define(char board[m_row][m_col])
{
    int n;

    cout << "how many living cell you wanna have?" << endl;
    cin >> n;

    for (int k = 0; k < n; k++)
    {
        basic[k].x = 1 + rand() % 26;
        basic[k].y = 1 + rand() % 26;
    }

    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            board[i][j] = dead;
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < m_row; i++)
        {
            for (int j = 0; j < m_col; j++)
            {
                if (i == basic[k].x && j == basic[k].y)
                {
                    board[i][j] = alive;
                }
            }
        }
    }

    Print();
}

void Print()
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void Check_State(char board[m_row][m_col])
{
    for (int i = 0; i < m_row; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            if (board[i][j] == alive)
            {
                alive_count_0++;
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        if (!(k == 0 && l == 0))
                        {
                            if (board[i + k][j + l] == alive)
                            {
                                alive_neighbor++;
                            }
                        }
                    }
                }

                if (alive_neighbor == 2 || alive_neighbor == 3)
                {
                    board[i][j] = alive;
                }
                else
                {
                    board[i][j] = dead;
                }
            }

            if(board[i][j] == dead)
            {
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        if (!(k == 0 && l == 0))
                        {
                            if (board[i + k][j + l] == alive)
                            {
                                alive_neighbor++;
                            }
                        }
                    }
                }

                if (alive_neighbor == 3)
                {
                    board[i][j] = alive;
                }

                else
                {
                    board[i][j] = dead;
                }

            }
            alive_neighbor = 0;
        }
    }
    Print();

    if(alive_count_0 - alive_count_1 == 0)
    {
        cout << "EQUILIBRIUM ACHIEVED!" << endl;
        exit(0);
    }

    alive_count_1 = alive_count_0;
}

