#ifndef CONNECTFOURPLAYERHUMAN_H
#define CONNECTFOURPLAYERHUMAN_H

#include "ConnectFourPlayboard.h"
#include "ConnectFourPlayerInterface.h"

class ConnectFourPlayerHuman: public ConnectFourPlayerInterface
{
public:
    ConnectFourPlayerHuman(ConnectFourPlayboard &, ConnectFourPlayboard::Player);
    int MakeMove();
};

#endif
