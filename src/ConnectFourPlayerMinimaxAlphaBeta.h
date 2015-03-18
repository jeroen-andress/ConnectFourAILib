#ifndef CONNECTFOURPLAYERMINIMAXALPHABETA_H
#define CONNECTFOURPLAYERMINIMAXALPHABETA_H

#include "ConnectFourPlayerMinimax.h"
#include "ConnectFourPlayerInterface.h"
#include "ConnectFourPlayboard.h"

class ConnectFourPlayerMinimaxAlphaBeta: public ConnectFourPlayerMinimax
{
protected:
    int Minimax(ConnectFourPlayboard, const int Depth, int Alpha, int Beta);
    int Minimax(ConnectFourPlayboard, const int Depth = 0);

public:
    ConnectFourPlayerMinimaxAlphaBeta(ConnectFourPlayboard &, ConnectFourPlayboard::Player, const int Depth);
};

#endif
