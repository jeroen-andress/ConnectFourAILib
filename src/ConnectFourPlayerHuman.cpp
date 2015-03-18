#include "ConnectFourPlayerInterface.h"
#include "ConnectFourPlayboard.h"

#include "ConnectFourPlayerHuman.h"
#include "ConnectFourPlayerInterface.h"

#include <iostream>
#include <limits>

using namespace std;

ConnectFourPlayerHuman::ConnectFourPlayerHuman(ConnectFourPlayboard &Playboard, ConnectFourPlayboard::Player Player): ConnectFourPlayerInterface(Playboard, Player)
{
}

int ConnectFourPlayerHuman::MakeMove()
{
    int col = -1;

    while(! (col >= 0 && col < _Playboard.GetColumns() && _Playboard.IsInsertAble(col) && !cin.fail()))
    {
        cout << "Player ";
        cout << (_Player == ConnectFourPlayboard::WHITE ? "White: " : "Red: ");
        cout << "col ( 0 - " << _Playboard.GetColumns() - 1 << " ) ? ";
        cin >> col;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }

    if (col >= 0 && col < _Playboard.GetColumns())
    {
        _Playboard.Move(col, _Player);
    }

    return col;
}
