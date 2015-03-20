#include "ConnectFourPlayerMinimax.h"
#include "ConnectFourPlayerInterface.h"
#include "ConnectFourPlayboard.h"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#ifdef USEMULTITHREADING
#include <pthread.h>
#endif

using namespace std;

#ifdef USEMULTITHREADING
struct MiniMaxThreadHelper
{
    ConnectFourPlayerMinimax *Instance;
    ConnectFourPlayboard Playboard;
    int Column;
};

void *MiniMaxThread(void *Argument)
{
    MiniMaxThreadHelper *Helper = (MiniMaxThreadHelper *)Argument;
    Helper->Playboard.Move(Helper->Column, Helper->Instance->_Player);

    int *Result = new int;
    *Result = Helper->Instance->Minimax(Helper->Playboard, 1);

#ifdef DEBUG
    cout << Helper->Column << ": Result=" << *Result << endl;
#endif

    return Result;
}
#endif

ConnectFourPlayerMinimax::ConnectFourPlayerMinimax(ConnectFourPlayboard &Playboard, ConnectFourPlayboard::Player Player, const int Depth): ConnectFourPlayerInterface(Playboard, Player), _Depth(Depth)
{
}

int ConnectFourPlayerMinimax::MakeMove()
{
#ifdef USEMULTITHREADING
    vector<pthread_t> Threads;
    Threads.reserve(_Playboard.GetColumns());

    vector<MiniMaxThreadHelper> Helper(_Playboard.GetColumns());

    for (int i = 0; i < _Playboard.GetColumns(); i++)
    {
         if (_Playboard.IsInsertAble(i))
         {
             Helper[i].Instance = this;
             Helper[i].Playboard = _Playboard;
             Helper[i].Column = i;
    
             pthread_t Thread;
             if (pthread_create(&Thread, NULL, MiniMaxThread, &Helper[i]) != 0)
             {
                  return -1;
             }
    
             Threads.push_back(Thread);
         }
    }

    int MaxValue = numeric_limits<int>::min(), MaxPos = -1;
    for (vector<pthread_t>::iterator i = Threads.begin(); i != Threads.end(); i++)
    {
         void *ResultValue;
         pthread_join(*i, &ResultValue);

         int Result = *((int *)ResultValue);
         delete (int*)ResultValue;

         if (Result > MaxValue)
         {
              MaxValue = Result;
              MaxPos = distance(Threads.begin(), i);
         }
    }

    _Playboard.Move(MaxPos, _Player);
    return MaxPos;
#else
    vector<int> Val(_Playboard.GetColumns());

    for (int i = 0; i < _Playboard.GetColumns(); i++)
    {
        ConnectFourPlayboard t = _Playboard;

        if (t.IsInsertAble(i))
        {
            t.Move(i, _Player);
            Val[i] = Minimax(t, 1);
        }
        else
        {
            Val[i] = numeric_limits< int >::min();
        }
    }

    const int MaxPos = distance(Val.begin(), max_element(Val.begin(), Val.end()));
    
#ifdef DEBUG
    cout << "depth=" << 0 << ", max=" << Val[MaxPos] << endl;
#endif

    _Playboard.Move(MaxPos, _Player);
    return MaxPos;
#endif
}

int ConnectFourPlayerMinimax::Minimax(ConnectFourPlayboard Playboard, const int Depth)
{
    vector<int> Val(Playboard.GetColumns());
    int i;
    ConnectFourPlayboard t_Playboard;


    ConnectFourPlayboard::Player Winner = Playboard.GetWinner();

    if (Winner != ConnectFourPlayboard::NONE)
    {
        if (_Player == Winner) // Ich habe gewonnen
        {
            return numeric_limits< int >::max() / Depth;
        }
        else
        {
            return numeric_limits< int >::min() / Depth;
        }
    }

    if (Playboard.IsFull())
    {
        return 0;
    }

#ifdef DEBUG
        cout << "minimax: depth=" << Depth << endl;
        cout << Playboard.ToString() << endl;
#endif

    if (Depth < _Depth)
    {
        for (i = 0; i < Val.size(); i++)
        {
            if (Playboard.IsInsertAble(i))
            {
                t_Playboard = Playboard;

                if (Depth % 2 == 0) /* ist grade, also die eigende farbe benutzen */
                {
                    t_Playboard.Move(i, _Player);
                }
                else /* möglicher zug des gegners */
                {
                    t_Playboard.Move(i, _Player == ConnectFourPlayboard::WHITE ? ConnectFourPlayboard::RED : ConnectFourPlayboard::WHITE);
                }

                Val[i] = Minimax(t_Playboard, Depth + 1);
            }
            else
            {
                Val[i] = CalcHeuristic(Playboard);
            }
        }

        if (Depth % 2 == 0) /* max */
        {
#ifdef DEBUG
            cout << "depth=" << Depth << ", max= " << *max_element(Val.begin(), Val.end()) << endl;
#endif

            return *max_element(Val.begin(), Val.end());
        }
        else /* min */
        {
#ifdef DEBUG
            cout << "depth=" << Depth << ", min= " << *min_element(Val.begin(), Val.end()) << endl;
#endif

            return *min_element(Val.begin(), Val.end());;
        }
    }
    else
    {
        int h = CalcHeuristic(Playboard);

#ifdef DEBUG
        cout << "Rekustionsende: h=" << h << endl;
#endif

        return h;
    }
}

int ConnectFourPlayerMinimax::CalcHeuristic(const ConnectFourPlayboard &Playboard)
{
    ConnectFourPlayboard::Player Winner = Playboard.GetWinner();

    int HeuristicSelf = 0, HeuristicAntis = 0;

    if (Winner == ConnectFourPlayboard::NONE)
    {
        for(int row = Playboard.GetRows()- 1; row >= 0 ; row--)
        {
            for(int col = 0; col < Playboard.GetColumns(); col++)
            {       
                if (Playboard.GetField(row, col) != ConnectFourPlayboard::NONE)
                {
                    if (Playboard.GetField(row, col) == _Player)
                    {
                        HeuristicSelf += CountHorizontalDiagonale(Playboard, row, col);
                        HeuristicSelf += CountVerticalDiagonal(Playboard, row, col);
                        HeuristicSelf += CountLeftDiagonal(Playboard, row, col);
                        HeuristicSelf += CountRightDiagonal(Playboard, row, col);
                    }
                    else
                    {
                        HeuristicAntis += CountHorizontalDiagonale(Playboard, row, col);
                        HeuristicAntis += CountVerticalDiagonal(Playboard, row, col);
                        HeuristicAntis += CountLeftDiagonal(Playboard, row, col);
                        HeuristicAntis += CountRightDiagonal(Playboard, row, col);
                    }
                }
            }
        }

        return (HeuristicSelf - HeuristicAntis);
    }
    else
    {
        /* Der gegner hat gewonnen */
        return Winner != _Player ? numeric_limits< int >::min() : numeric_limits< int >::max();
    }
}


int ConnectFourPlayerMinimax::CountLeftDiagonal(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const
{
    ConnectFourPlayboard::Player Start = Playboard.GetField(Row, Col);
    int i, j;
    int Res = 0;

    if ((Row - 3) >= 0 && (Col - 3) >= 0)
    {
        for (i = Row - 1, j = Col - 1; i >= (Row - 3) && j >= (Col - 3); i--, j--)
        {
            if (Playboard.GetField(i, j) == Start)
            {
                Res += _WeightOwnField;
            }
            else if (Playboard.GetField(i, j) == ConnectFourPlayboard::NONE)
            {
                Res += _WeightEmptyField;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    return Res;
}

int ConnectFourPlayerMinimax::CountRightDiagonal(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const
{
    ConnectFourPlayboard::Player Start = Playboard.GetField(Row, Col);
    int i, j;
    int Res = 0;

    if ((Row - 3) >= 0 && (Col + 3) < Playboard.GetColumns())
    {
        for (i = Row - 1, j = Col + 1; i >= (Row - 3) && j <= (Col + 3) ; i--, j++)
        {
            if (Playboard.GetField(i, j) == Start)
            {
                Res += _WeightOwnField;
            }
            else if (Playboard.GetField(i, j) == ConnectFourPlayboard::NONE)
            {
                Res += _WeightEmptyField;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    return Res;
}

int ConnectFourPlayerMinimax::CountHorizontalDiagonale(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const
{
    ConnectFourPlayboard::Player Start = Playboard.GetField(Row, Col);
    int Res = 0;
      
    if ((Col + 3) < Playboard.GetColumns())
    {
        for (int i = Col + 1; i < (Col + 4); i++)
        {
            if (Playboard.GetField(Row, i) == Start)
            {
                Res += _WeightOwnField ;
            }
            else if (Playboard.GetField(Row, i) == ConnectFourPlayboard::NONE)
            {
                Res += _WeightEmptyField;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    return Res;
}

int ConnectFourPlayerMinimax::CountVerticalDiagonal(const ConnectFourPlayboard &Playboard, const int Row, const int Col) const
{
    ConnectFourPlayboard::Player Start = Playboard.GetField(Row, Col);
    int Res = 0;

    if ((Row - 3) >= 0)
    {
        for (int i = Row - 1; i > (Row - 4); i--)
        {
            //cout << "(" << i << "," << Col << ")" << endl;

            if (Playboard.GetField(i, Col) == Start)
            {
                Res += _WeightOwnField;
            }
            else if (Playboard.GetField(i, Col) == ConnectFourPlayboard::NONE)
            {
                Res += _WeightEmptyField;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }

    return Res;
}


int ConnectFourPlayerMinimax::CalcHeuristicForField(const ConnectFourPlayboard &Playboard, const int Row, const int Col)
{
    int Res = 0;

    if ((Col + 1) < Playboard.GetColumns())
    {
        if (Playboard.GetField(Row, Col) == Playboard.GetField(Row, Col + 1))
        {
            Res++;
        }
    }

    if ((Col + 1) < Playboard.GetColumns() && (Row + 1) < Playboard.GetRows())
    {
        if (Playboard.GetField(Row, Col) == Playboard.GetField(Row + 1, Col + 1))
        {
            Res++;
        }
    }

    if ((Row + 1) < Playboard.GetRows())
    {
        if (Playboard.GetField(Row, Col) == Playboard.GetField(Row + 1, Col))
        {
            Res++;
        }
    }

    if ((Row + 1) < Playboard.GetRows() && (Col - 1) >= 0)
    {
        if (Playboard.GetField(Row, Col) == Playboard.GetField(Row + 1, Col - 1))
        {
            Res++;
        }
    }

    return Res;
}
