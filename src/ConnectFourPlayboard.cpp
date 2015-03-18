#include <string>
#include <sstream>

#include "ConnectFourPlayboard.h"

using namespace std;

ConnectFourPlayboard::ConnectFourPlayboard()
{
    for (int row = 0; row < GetRows(); row++)
    {
        for (int col = 0; col < GetColumns(); col++)
        {
            SetField(row, col, NONE);
        }
    }
}

bool ConnectFourPlayboard::MoveWhite(const int Column)
{
    return Move(Column, WHITE);
}

bool ConnectFourPlayboard::MoveRed(const int Column)
{
    return Move(Column, RED);
}

bool ConnectFourPlayboard::Move(const int Column, const Player Type)
{
    for(int row = GetRows() - 1; row >= 0 ; row--)
    {
        if (_Playboard[row][Column] == NONE)
        {
            SetField(row, Column, Type);
            return true;
        }
    }

    // Spalte ist voll
    return false;    
}

ConnectFourPlayboard::Player ConnectFourPlayboard::GetField(const int Row, const int Col) const
{
    return _Playboard[Row][Col];
}

int ConnectFourPlayboard::GetColumns() const
{
    return _Cols;
}

int ConnectFourPlayboard::GetRows() const
{
    return _Rows;
}

void ConnectFourPlayboard::SetField(const int Row, const int Col, Player Type)
{
    _Playboard[Row][Col] = Type;
}

ConnectFourPlayboard::Player ConnectFourPlayboard::GetWinner() const
{
    for(int row = 0; row < GetRows(); row++)
    {
        for(int col = 0; col < GetColumns(); col++)
        {
            if (_Playboard[row][col] != NONE)
            {
                if (HasHorizontalDiagonale(row, col) || HasVerticalDiagonal(row, col) || HasLeftDiagonal(row, col) || HasRightDiagonal(row, col))
                {
                    return _Playboard[row][col];
                }
            }
        }
    }

    return NONE;
}

bool ConnectFourPlayboard::HasLeftDiagonal(const int Row, const int Col) const
{
    const Player Start = _Playboard[Row][Col];
    int i, j;
    
    if ((Row + 3) < GetRows() && (Col - 3) >= 0)
    {
        for (i = Row, j = Col; j >= (Col - 3); i++, j--)
        {
            if (_Playboard[i][j] != Start)
            {
                return false;
            }
        }
      
    }
    else
    {
        return false;
    }
  
    return true;
}

bool ConnectFourPlayboard::HasRightDiagonal(const int Row, const int Col) const
{
    const Player Start = _Playboard[Row][Col];
    int i, j;

    if ((Row + 3) < GetRows() && (Col + 3) < GetColumns())
    {
        for (i = Row, j = Col; i < (Row + 4); i++, j++)
        {
            if (_Playboard[i][j] != Start)
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool ConnectFourPlayboard::HasHorizontalDiagonale(const int Row, const int Col) const
{
    const Player Start = _Playboard[Row][Col];

    if ((Col + 3) < GetColumns())
    {
        for (int i = Col; i < (Col + 4); i++)
        {
            if (_Playboard[Row][i] != Start)
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool ConnectFourPlayboard::HasVerticalDiagonal(const int Row, const int Col) const
{
    const Player Start = _Playboard[Row][Col];

    /* Die 4 Felder auf der vertikalen druchsuchen */
    if ((Row + 3) < GetRows())
    {
        for (int i = Row; i < (Row + 4); i++)
        {
            if (_Playboard[i][Col] != Start)
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool ConnectFourPlayboard::IsFull() const
{
    for(int col = 0; col < GetColumns(); col++)
    {
        if (IsInsertAble(col))
        {
            return false;
        }
    }

    return true;
}

bool ConnectFourPlayboard::IsInsertAble(const int Column) const
{
    return _Playboard[0][Column] == NONE;
}

string ConnectFourPlayboard::ToString() const
{
    ostringstream os;

    os << "  ";

    for (int i = 0; i < GetColumns(); i++)
    {
        os << " " << i  << " ";
    }

    os << endl;

    for (int row = 0; row < GetRows(); row++)
    {
        os << row << " ";

        for (int col = 0; col < GetColumns(); col++)
        {
            if (_Playboard[row][col] == NONE)
            {
                os << " - ";
            }
            else if (_Playboard[row][col] == RED)
            {
                os << " R ";
            }
            else
            {
                os << " W ";
            }
        }

        os << endl;
    }

    return os.str();
}
