#include "ConnectFourPlayboard.h"
#include "ConnectFourPlayerInterface.h"
#include "ConnectFourPlayerMinimax.h"
#include "ConnectFourPlayerMinimaxAlphaBeta.h"

#include <limits>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

using namespace std;

ConnectFourPlayerMinimaxAlphaBeta::ConnectFourPlayerMinimaxAlphaBeta(ConnectFourPlayboard &Playboard, ConnectFourPlayboard::Player Player, const int Depth) : ConnectFourPlayerMinimax(Playboard, Player, Depth)
{
}

int ConnectFourPlayerMinimaxAlphaBeta::Minimax(ConnectFourPlayboard Playboard, const int Depth)
{
    return Minimax(Playboard, Depth, numeric_limits<int>::min(), numeric_limits<int>::max());
}

int ConnectFourPlayerMinimaxAlphaBeta::Minimax(ConnectFourPlayboard Playboard, const int Depth, int Alpha, int Beta)
{
    int Score;

    if (Playboard.GetWinner() != ConnectFourPlayboard::NONE)
    {
        if (Playboard.GetWinner() == _Player)
        {
            return numeric_limits<int>::max() / Depth;
        }
        else
        {
            return numeric_limits<int>::min() / Depth;
        }
    }

    if (Playboard.IsFull())
    {
        return 0;
    }

    if (Depth < _Depth)
    {
        vector<int> Follower(Playboard.GetColumns());

        for (int i = 0; i < Follower.size(); i++)
        {
            Follower[i] = i;
        }   

        /* Zufällig einen Zug auswählen */
        random_shuffle(Follower.begin(), Follower.end());

        for(int i = 0; i < Playboard.GetColumns(); i++)
        {
            ConnectFourPlayboard Playboard_t = Playboard;

            if (Playboard_t.IsInsertAble(Follower[i]))
            {
                if (Depth % 2 == 0) /* selber */
                {
                    Playboard_t.Move(Follower[i], _Player);
                }
                else /* gegner */
                {
                    Playboard_t.Move(Follower[i], _Player == ConnectFourPlayboard::WHITE ? ConnectFourPlayboard::RED : ConnectFourPlayboard::WHITE);
                }

                Score = Minimax(Playboard_t, Depth + 1, Alpha, Beta);

                if (Depth % 2 == 0) /* max */
                {
                    if (Score > Alpha)
                    {
                        Alpha = Score;
                    }

                    if (Alpha >= Beta)
                    {
                        return Alpha;
                    }
                }
                else /* min */
                {
                    if (Score < Beta)
                    {
                        Beta = Score;
                    }

                    if (Alpha >= Beta)
                    {
                        return Beta;
                    }
                }
            }
        }

        if (Depth % 2 == 0) /* max */
        {
            return Alpha;
        }
        else
        {
            return Beta;
        }
    }
    else
    {
        return ConnectFourPlayerMinimax::CalcHeuristic(Playboard);
    }
}

