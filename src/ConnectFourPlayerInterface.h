#ifndef CONNECTFOURPLAYERINTERFACE_H
#define CONNECTFOURPLAYERINTERFACE_H

#include "ConnectFourPlayboard.h"

class ConnectFourPlayerInterface
{
protected:
    ConnectFourPlayboard &_Playboard;
    ConnectFourPlayboard::Player _Player;

public:
    ConnectFourPlayerInterface(ConnectFourPlayboard &Playboard, ConnectFourPlayboard::Player Player);
    ConnectFourPlayboard::Player GetPlayer() const;

    virtual int MakeMove() = 0;
    virtual ~ConnectFourPlayerInterface();
};

#endif
