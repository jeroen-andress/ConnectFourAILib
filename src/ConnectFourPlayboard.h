#ifndef CONNECTFOURPLAYBOARD_H
#define CONNECTFOURPLAYBOARD_H

#include <string>

class ConnectFourPlayboard
{
public:
    enum Player {NONE = 0, RED = 1, WHITE = 2};

    ConnectFourPlayboard(const ConnectFourPlayboard&);
    ConnectFourPlayboard();

    bool Move(const int Column, const Player Type);
    bool MoveWhite(const int Column);
    bool MoveRed(const int Column);

    Player GetField(const int Row, const int Col) const;

    int GetColumns() const;
    int GetRows() const;

    Player GetWinner() const;

    bool IsInsertAble(const int Column) const;
    bool IsFull() const;

    std::string ToString() const;

private:
    static const int _Cols = 7;
    static const int _Rows = 6;

    Player _Playboard[_Rows][_Cols];

    void SetField(const int Row, const int Col, Player Type);
    bool HasHorizontalDiagonale(const int Row, const int Col) const;
    bool HasVerticalDiagonal(const int Row, const int Col) const;
    bool HasRightDiagonal(const int Row, const int Col) const;
    bool HasLeftDiagonal(const int Row, const int Col) const;
};

#endif
