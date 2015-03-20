#ifndef CONNECTFOURPLAYERMINIMAX_H
#define CONNECTFOURPLAYERMINIMAX_H

#include "ConnectFourPlayboard.h"
#include "ConnectFourPlayerInterface.h"

class ConnectFourPlayerMinimax: public ConnectFourPlayerInterface
{
#ifdef USEMULTITHREADING
friend void *MiniMaxThread(void *);
#endif

protected:
    int _Depth;

    static const int _WeightOwnField = 10;
    static const int _WeightEmptyField = 1;

    virtual int Minimax(ConnectFourPlayboard Playboard, const int Depth = 0);

    int CalcHeuristic(const ConnectFourPlayboard &Playboard);
    int CalcHeuristicForField(const ConnectFourPlayboard &Playboard, const int Row, const int Col); /* not used */

    int CountHorizontalDiagonale(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const;
    int CountVerticalDiagonal(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const;
    int CountLeftDiagonal(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const;
    int CountRightDiagonal(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const;

public:
    ConnectFourPlayerMinimax(ConnectFourPlayboard &Playboard, ConnectFourPlayboard::Player, const int Depth);
    int MakeMove();
};

#endif

