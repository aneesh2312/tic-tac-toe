
//
//  Tic-Tac-Toe Game - You can't beat it!
//
//  Created by Aneesh D H  on 13/02/17.
//
//

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
int win(int board[3][3], int player)
{
    int flag = 0, flag2;
    for (int i = 0; i < 3; i++)
    {
        flag2 = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != player)
            {
                flag2++;
                break;
            }
        }
        if (!flag2)
            flag++;
    }

    for (int i = 0; i < 3; i++)
    {
        flag2 = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[j][i] != player)
            {
                flag2++;
                break;
            }
        }
        if (!flag2)
            flag++;
    }

    flag2 = 0;

    for (int i = 0; i < 3; i++)
    {
        if (board[i][i] != player)
        {
            flag2++;
            break;
        }
    }

    if (!flag2)
        flag++;

    flag2 = 0;

    for (int i = 0; i < 3; i++)
    {
        if (board[i][2-i] != player)
        {
            flag2++;
            break;
        }
    }

    if (!flag2)
        flag++;

    return (flag > 0);    
}
int game_over(int board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                return 0;
        }
    }
    return 1;
}
void display(int board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                cout<<"- ";
            else if (board[i][j] == 1)
                cout<<"O ";
            else
                cout<<"X ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
int make_move(int board[3][3], int x, int y, int player)
{
    if (x > 2 or y > 2)
        return 0;
    if (board[x][y] != 0)
        return 0;
    board[x][y] = player;
    return 1;
}
void copy(int b[3][3], int a[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            a[i][j] = b[i][j];
}

int minimise_ply(int a);
int maximise_ply(int b[3][3], int a);

void g_bfs(int board[3][3], int player)
{
    int x0 = -1, y0 = -1, maxim = -1000000, board1[3][3];
    copy(board, board1);
    maximise_ply(board1, 1);
    copy(board1, board);    
}
int main()
{
    int board[3][3], x1, y1, player;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            board[i][j] = 0;
    }
    cout<<"Who goes first? You or the computer?\n1. Me\n2. Computer\n";
    cin>>player;
    if (player == 1)
        player = 2;
    else
        player = 1;
    if (player == 2)
        display(board);
    cout<<"You play by entering the x and y co-ordinates of the cell you wish to cross out. The top-left is (1,1) and the bottom right is (3,3)\n";
    while (!win(board, 1) and !win(board, 2) and !game_over(board))
    {
        if (player == 1)
        {
            g_bfs(board, 1);
            display(board);
            player = 2;
        }
        else
        {
            cout<<"Enter x and y: ";
            cin>>x1>>y1;
            x1--; y1--;
            make_move(board, x1, y1, 2);
            display(board);
            player = 1;
        }
    }
    if ((win(board, 1) and player == 1) or (win(board, 2) and player == 2))
    {
        cout<<"Computer wins!\n";
    }
    else if (win(board, 1) or win(board, 2))
    {
        cout<<"Well played! You win!\n";
    }
    else
        cout<<"It's a draw. I hate draws. -_-\n";
}
int minimise_ply(int board[3][3])
{
    if (win(board, 1))
        return 1000000;
    if (win(board, 2))
        return -1000000;
    if (game_over(board))
        return 0;
    int x0, y0, temp[3][3], minim = 10000000;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                copy(board, temp);
                temp[i][j] = 2;
                int res = maximise_ply(temp, 0);
                if (res < minim)
                {
                    x0 = i;
                    y0 = j;
                    minim = res;
                }
            }
        }
    }
    return minim;
}
int maximise_ply(int board[3][3], int mode)
{
    if (win(board, 1))
        return 1000000;
    if (win(board, 2))
        return -1000000;
    if (game_over(board))
        return 0;
    int x0, y0, temp[3][3], maxim = -10000000;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                copy(board, temp);
                temp[i][j] = 1;
                int res = minimise_ply(temp);
                if (res > maxim)
                {
                    x0 = i;
                    y0 = j;
                    maxim = res;
                }
            }
        }
    }
    if (mode == 1)
        board[x0][y0] = 1;
    return maxim;
}
