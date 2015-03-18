%module ConnectFourAI 
%include "std_string.i"

%{
#include "ConnectFourPlayboard.h"
#include "ConnectFourPlayerInterface.h"
#include "ConnectFourPlayerMinimax.h"
#include "ConnectFourPlayerMinimaxAlphaBeta.h"
%}

%include "ConnectFourPlayboard.h"
%include "ConnectFourPlayerInterface.h"
%include "ConnectFourPlayerMinimax.h"
%include "ConnectFourPlayerMinimaxAlphaBeta.h"
