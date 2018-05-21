#!/usr/bin/env python

from ConnectFourAI import ConnectFourPlayboard
from ConnectFourAI import ConnectFourPlayerMinimaxAlphaBeta
import sys, time, os

def main():
  Playboard = ConnectFourPlayboard()
  AIPlayer = ConnectFourPlayerMinimaxAlphaBeta(Playboard, ConnectFourPlayboard.RED, 8)
  
  while Playboard.GetWinner() == ConnectFourPlayboard.NONE and not Playboard.IsFull():
  
    if Playboard.GetWinner() == ConnectFourPlayboard.NONE:
      print(Playboard.ToString())
      print("Chooice a column between 0 and %d:" % Playboard.GetColumns())
      Column = int(sys.stdin.readline())
      Playboard.MoveWhite(Column)
  
    t0 = time.time()
    AIMove = AIPlayer.MakeMove()
    t1 = time.time()
  
    print('AI choose column %d in %.2fs:' % (AIMove, (t1-t0)))
  
  print(Playboard.ToString())
  
  if Playboard.GetWinner() == ConnectFourPlayboard.RED:
    print("And the winner is Red")
  elif Playboard.GetWinner() == ConnectFourPlayboard.WHITE:
    print("And the winner is White")
  else:
    print("Drawn")

if __name__ == "__main__":
  main();
