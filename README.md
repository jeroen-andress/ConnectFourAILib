# ConnectFourAILib

## Build
Check to build Demo/demo.sh to build a python lib

## Python3
To build a shared lib compatible with python3, the following makefile can be used: 

```make
PYTHON_CONFIG=python3.6-config
CFLAGS=`$(PYTHON_CONFIG) --includes` `$(PYTHON_CONFIG) --cflags` -fPIC
LDFLAGS=-shared `$(PYTHON_CONFIG) --ldflags` -lstdc++
CC=g++
OBJ=ConnectFourPlayboard.o ConnectFourPlayerHuman.o ConnectFourPlayerInterface.o ConnectFourPlayerMinimaxAlphaBeta.o ConnectFourPlayerMinimax.o ConnectFourAI_wrap.o
SWIG=swig3.0
TARGET=_ConnectFourAI.so
%.o: %.cpp
        $(CC) $(CFLAGS) -c $<

ConnectFourAI: ConnectFourAI_wrap.cpp $(OBJ)
        $(CC) -o $(TARGET) $(OBJ) $(LDFLAGS)

ConnectFourAI_wrap.cpp:
        $(SWIG) -o $@ -c++ -python ConnectFourAI.i

clean:
        rm -f $(OBJ) ConnectFourAI_wrap.cpp ConnectFourAI.so ConnectFourAI.py*
```
