#include "ConnectFourPlayboard.h"
#include "ConnectFourPlayerInterface.h"


ConnectFourPlayerInterface::ConnectFourPlayerInterface(ConnectFourPlayboard &Playboard, ConnectFourPlayboard::Player Player) : _Playboard(Playboard), _Player(Player)
{
}

ConnectFourPlayboard::Player ConnectFourPlayerInterface::GetPlayer() const
{
    return _Player;
}

ConnectFourPlayerInterface::~ConnectFourPlayerInterface()
{
}

